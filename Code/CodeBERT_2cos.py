import os
import pandas as pd
import numpy as np
import pickle
import json
import gc
import time
from scipy.spatial import distance
from transformers import AutoTokenizer, AutoModel
import torch

# 配置路径
WORKING_DIR = r".\CodeBERT"
DATASET_PATH = os.path.join(WORKING_DIR, 'dataset', 'small.jsonl')

def load_model():
    """加载模型和分词器"""
    print("Loading tokenizer and model...")
    
    # 加载分词器
    tokenizer = AutoTokenizer.from_pretrained("microsoft/codebert-base")
    
    # 加载预训练模型
    model = AutoModel.from_pretrained("microsoft/codebert-base")
    
    # 加载训练好的权重
    model_path = os.path.join(WORKING_DIR, 'code', 'saved_models', 'checkpoint-best-acc', 'model.bin')
    if os.path.exists(model_path):
        model.load_state_dict(torch.load(model_path), strict=False)
        print("Loaded trained model weights")
    else:
        raise FileNotFoundError(f"Model weights not found at {model_path}")
    
    return tokenizer, model

def test_model(tokenizer, model):
    """测试模型"""
    print("Testing model...")
    
    nl_tokens = tokenizer.tokenize("return maximum value")
    code_tokens = tokenizer.tokenize("def max(a,b): if a>b: return a else return b")
    
    tokens = [tokenizer.cls_token] + nl_tokens + [tokenizer.sep_token] + code_tokens + [tokenizer.eos_token]
    tokens_ids = tokenizer.convert_tokens_to_ids(tokens)
    context_embeddings = model(torch.tensor(tokens_ids)[None,:])[0]
    
    print(f"Context embeddings shape: {context_embeddings.shape}")
    return context_embeddings

def create_embeddings(tokenizer, model, df):
    """创建嵌入向量"""
    print("Creating embeddings...")
    
    vectors_table_padded = []
    vectors_calculation_passes = []
    row_counter = 0
    completed_passes = 0  # 如果需要从中断处继续，可以设置这个值
    
    # 创建保存嵌入向量块的目录
    embed_chunks_dir = os.path.join(WORKING_DIR, 'dataset', 'embed_chunks')
    os.makedirs(embed_chunks_dir, exist_ok=True)
    
    def create_padded_vector(x):
        nonlocal vectors_table_padded, vectors_calculation_passes, row_counter
        
        row_counter += 1
        
        # 如果从中断处继续，跳过已处理的行
        if (completed_passes > 0) and (row_counter <= (completed_passes * 1000)):
            if (row_counter > 0) and (row_counter % 1000 == 0):
                vectors_calculation_passes.append(time.time())
                print(f"\nSkipped pass: {len(vectors_calculation_passes)}")
                print(f"Processed {row_counter} entries.\n")
            return
        
        # 清理代码文本
        x = x.replace('\n', ' ').replace('"', ' ')
        
        # 分词
        tokens = [tokenizer.cls_token] + tokenizer.tokenize(x, truncation=True, max_length=510) + [tokenizer.sep_token]
        
        try:
            # 生成嵌入向量
            context_embeddings = model(torch.tensor(tokenizer.convert_tokens_to_ids(tokens))[None,:])[0]
        except Exception as e:
            print(f"\nError processing text: {str(e)}\n")
            return
        
        # 创建填充向量
        c = list(context_embeddings[-1,::].size())
        target = torch.zeros(512, 768)
        source = context_embeddings[-1,::]
        target[:c[0]] = source
        vectors_table_padded.append(np.hstack(target.detach().numpy()))
        
        print('.', end='', flush=True)
        
        # 每1000行保存一次
        if (len(vectors_table_padded) > 0) and (len(vectors_table_padded) % 1000 == 0):
            vectors_calculation_passes.append(time.time())
            
            # 保存块文件
            chunk_file = os.path.join(embed_chunks_dir, f'outputCodeEmbeddingCodeBERT_{len(vectors_calculation_passes)}.pkl')
            with open(chunk_file, 'wb') as handle:
                pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
            
            # 追加到总文件
            all_file = os.path.join(WORKING_DIR, 'dataset', 'outputCodeEmbeddingCodeBERT_all.pkl')
            with open(all_file, 'ab+') as handle:
                pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
            
            # 重置数组以节省内存
            vectors_table_padded = []
            
            print(f"\nFinished pass: {len(vectors_calculation_passes)}")
            print(f"Processed {len(vectors_calculation_passes) * 1000} entries.\n")
    
    # 应用到所有函数
    df['func'].apply(create_padded_vector)
    
    # 处理剩余的向量
    if len(vectors_table_padded) > 0:
        vectors_calculation_passes.append(time.time())
        
        chunk_file = os.path.join(embed_chunks_dir, f'outputCodeEmbeddingCodeBERT_{len(vectors_calculation_passes)}.pkl')
        with open(chunk_file, 'wb') as handle:
            pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
        
        all_file = os.path.join(WORKING_DIR, 'dataset', 'outputCodeEmbeddingCodeBERT_all.pkl')
        with open(all_file, 'ab+') as handle:
            pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
        
        print(f"\nFinished pass: {len(vectors_calculation_passes)}")
        print(f"Processed {(len(vectors_calculation_passes) - 1) * 1000 + len(vectors_table_padded)} entries.\n")
        
        vectors_table_padded = []
    
    print(f"Finished processing in {len(vectors_calculation_passes)} passes")
    return len(vectors_calculation_passes)

def combine_embeddings(num_passes):
    """合并嵌入向量块"""
    print("Combining embedding chunks...")
    
    vectors_table_padded = []
    embed_chunks_dir = os.path.join(WORKING_DIR, 'dataset', 'embed_chunks')
    
    # 加载所有块
    for i in range(num_passes):
        chunk_file = os.path.join(embed_chunks_dir, f'outputCodeEmbeddingCodeBERT_{i + 1}.pkl')
        with open(chunk_file, 'rb') as handle:
            vectors_table_padded.extend(pickle.load(handle))
        print(f"Loaded chunk {i + 1}/{num_passes}")
    
    print(f"Total embeddings: {len(vectors_table_padded)}")
    print(f"Embedding dimension: {len(vectors_table_padded[0])}")
    
    # 转换为numpy数组
    vectors_table_padded = np.asarray(vectors_table_padded)
    
    # 保存完整的嵌入文件
    embedding_file = os.path.join(WORKING_DIR, 'dataset', 'outputCodeEmbeddingCodeBERT_all.pkl')
    with open(embedding_file, 'wb') as handle:
        pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
    
    # 保存为numpy格式
    embedding_np_file = os.path.join(WORKING_DIR, 'dataset', 'embedding_all_np.pkl')
    with open(embedding_np_file, 'wb') as handle:
        pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
    
    # 保存为npy格式
    embedding_npy_file = os.path.join(WORKING_DIR, 'dataset', 'embedding_all_np_direct.npy')
    with open(embedding_npy_file, 'wb') as handle:
        np.save(handle, vectors_table_padded)
    
    print("Saved all embedding files")
    return vectors_table_padded

def calculate_similarity_chunks(vectors_table_padded):
    """分块计算相似度矩阵"""
    print("Calculating similarity matrix in chunks...")
    
    table_length = len(vectors_table_padded)
    similarity_array = np.zeros((table_length, table_length))
    
    # 计算总批次数
    total_batches = (table_length + 999) // 1000  # 向上取整
    
    all_start_time = time.time()
    
    for i in range(1, total_batches + 1):
        row_start_time = time.time()
        start_index_i = (i - 1) * 1000
        end_index_i = min(i * 1000, table_length)
        
        # 加载第i个块
        chunk_file = os.path.join(WORKING_DIR, 'dataset', 'embed_chunks', f'outputCodeEmbeddingCodeBERT_{i}.pkl')
        with open(chunk_file, 'rb') as handle:
            chunk_i = pickle.load(handle)
        
        for j in range(i, total_batches + 1):
            start_index_j = (j - 1) * 1000
            end_index_j = min(j * 1000, table_length)
            
            # 加载第j个块
            chunk_file = os.path.join(WORKING_DIR, 'dataset', 'embed_chunks', f'outputCodeEmbeddingCodeBERT_{j}.pkl')
            with open(chunk_file, 'rb') as handle:
                chunk_j = pickle.load(handle)
            
            # 计算相似度
            similarity = 1 - distance.cdist(chunk_i, chunk_j, metric='cosine')
            
            # 更新相似度矩阵
            similarity_array[start_index_i:end_index_i, start_index_j:end_index_j] = similarity
            if i != j:  # 避免对角线重复
                similarity_array[start_index_j:end_index_j, start_index_i:end_index_i] = similarity.T
            
            print(f"Processed: ({start_index_i}-{end_index_i}, {start_index_j}-{end_index_j})")
            
            # 保存中间结果
            similarity_file = os.path.join(WORKING_DIR, 'dataset', 'similarity_all.npy')
            with open(similarity_file, 'wb') as handle:
                np.save(handle, similarity_array)
        
        print(f"Finished batch {i}/{total_batches}")
        print(f"Time for batch {i}: {time.time() - row_start_time:.2f} seconds")
        print("*" * 20)
    
    print(f"Total time: {time.time() - all_start_time:.2f} seconds")
    return similarity_array

def calculate_similarity_direct(vectors_table_padded):
    """直接计算相似度矩阵"""
    print("Calculating similarity matrix directly...")
    
    start_time = time.time()
    similarity_array = 1 - distance.cdist(vectors_table_padded, vectors_table_padded, metric='cosine')
    end_time = time.time()
    
    print(f"Similarity calculation completed in {end_time - start_time:.2f} seconds")
    print(f"Similarity matrix shape: {similarity_array.shape}")
    
    return similarity_array

def save_similarity_results(similarity_array):
    """保存相似度结果"""
    print("Saving similarity results...")
    
    # 保存为pickle文件
    similarity_pkl = os.path.join(WORKING_DIR, 'dataset', 'similarity_all.pkl')
    with open(similarity_pkl, 'wb') as handle:
        pickle.dump(similarity_array, handle, protocol=pickle.HIGHEST_PROTOCOL)
    
    # 保存为numpy文件
    similarity_npy = os.path.join(WORKING_DIR, 'dataset', 'similarity_all.npy')
    with open(similarity_npy, 'wb') as handle:
        np.save(handle, similarity_array)
    
    # 保存为文本文件
    similarity_txt = os.path.join(WORKING_DIR, 'dataset', 'similarity_all.txt')
    np.savetxt(similarity_txt, similarity_array, delimiter=' ', fmt='%.8f')
    
    print("Saved similarity results in multiple formats")

def main():
    """主函数"""
    print("Starting CodeBERT inference pipeline...")
    
    # 1. 加载模型
    tokenizer, model = load_model()
    
    # 2. 测试模型
    test_model(tokenizer, model)
    
    # 3. 加载数据
    print("Loading data...")
    df = pd.read_json(DATASET_PATH, lines=True)
    print(f"Loaded {len(df)} functions")
    print(f"Unique functions: {len(df['func'].unique())}")
    
    # 4. 创建嵌入向量
    num_passes = create_embeddings(tokenizer, model, df)
    
    # 5. 合并嵌入向量
    vectors_table_padded = combine_embeddings(num_passes)
    
    # 6. 清理内存
    del df, model, tokenizer
    gc.collect()
    
    # 7. 计算相似度矩阵
    # 根据数据大小选择计算方法
    if len(vectors_table_padded) > 10000:
        # 大数据集使用分块计算
        similarity_array = calculate_similarity_chunks(vectors_table_padded)
    else:
        # 小数据集直接计算
        similarity_array = calculate_similarity_direct(vectors_table_padded)
    
    # 8. 保存结果
    save_similarity_results(similarity_array)
    
    print("Pipeline completed successfully!")
    print(f"Final similarity matrix shape: {similarity_array.shape}")

if __name__ == "__main__":
    main()