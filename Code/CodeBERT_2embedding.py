import os
import pandas as pd
import numpy as np
import pickle
import gc
import time
from transformers import AutoTokenizer, AutoModel
import torch
import shutil

import getAllData
import CodeBERT_1train

# 配置路径
PY_FILE_BASE_PATH = os.path.dirname(__file__)
PROJECT_DIR = os.path.join(PY_FILE_BASE_PATH, '..')
WORKING_DIR = os.path.join(PROJECT_DIR, 'CodeBERT')
DATASET_PATH = os.path.join(PROJECT_DIR, 'dataset')

NEED_STATE_DICT = True

# 设备检测
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f"Using device: {device}")
if torch.cuda.is_available():
    print(f"GPU: {torch.cuda.get_device_name(0)}")
    print(f"GPU Memory: {torch.cuda.get_device_properties(0).total_memory / 1024**3:.1f} GB")

def load_model(dataFile:str, modelName: str, need_state_dict: bool):
    """加载模型和分词器"""
    print("Loading tokenizer and model...")
    
    # 加载分词器
    tokenizer = AutoTokenizer.from_pretrained("microsoft/codebert-base")
    
    # 加载预训练模型
    model = AutoModel.from_pretrained("microsoft/codebert-base")
    
    if need_state_dict:
        print("Loading model state dictionary...")
        # 加载训练好的权重
        model_path = os.path.join(WORKING_DIR, 'code', 'saved_models', 'checkpoint-best-acc', modelName)
        if os.path.exists(model_path):
            model.load_state_dict(torch.load(model_path), strict=False)
            print("Loaded trained model weights")
        else:
            try:
                CodeBERT_1train.train(dataFile)
                model.load_state_dict(torch.load(model_path), strict=False)
                print("Loaded trained model weights after training")
            except Exception as e:
                raise RuntimeError(f'Failed to train model: {e}')
    
    # 将模型移到GPU
    model = model.to(device)
    model.eval()  # 设置为评估模式
    print(f"Model moved to {device}")
    
    return tokenizer, model

def test_model(tokenizer, model):
    """测试模型"""
    print("Testing model...")
    
    nl_tokens = tokenizer.tokenize("return maximum value")
    code_tokens = tokenizer.tokenize("def max(a,b): if a>b: return a else return b")
    
    tokens = [tokenizer.cls_token] + nl_tokens + [tokenizer.sep_token] + code_tokens + [tokenizer.eos_token]
    tokens_ids = tokenizer.convert_tokens_to_ids(tokens)
    
    print(f"Number of tokens: {len(tokens_ids)}")
    print(f"Input tensor shape: {torch.tensor(tokens_ids)[None,:].shape}")
    
    # 将输入数据移到GPU
    input_tensor = torch.tensor(tokens_ids)[None,:].to(device)
    
    with torch.no_grad():  # 推理时不需要计算梯度
        context_embeddings = model(input_tensor)[0]
        
    # 去掉批次维度
    context_embeddings = context_embeddings.squeeze(0)
    
    print(f"Raw model output shape: {context_embeddings.shape}")
    print(f"Context embeddings shape after [0]: {context_embeddings.shape}")
    
    # 测试平均池化
    pooled = torch.mean(context_embeddings, dim=0)
    print(f"After mean pooling (dim=0): {pooled.shape}")
    
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
            # context_embeddings = model(torch.tensor(tokenizer.convert_tokens_to_ids(tokens))[None,:])[0]
            # 将输入数据移到GPU
            input_tensor = torch.tensor(tokenizer.convert_tokens_to_ids(tokens))[None,:].to(device)
            
            # 生成嵌入向量（使用no_grad节省内存）
            with torch.no_grad():
                context_embeddings = model(input_tensor)[0]
                
            # 去掉批次维度
            context_embeddings = context_embeddings.squeeze(0)  # 现在是 [seq_len, 768]
            
            # 计算平均池化
            pooled_embedding = torch.mean(context_embeddings, dim=0)  # 沿着第0维（序列长度）求平均
            
            # 将结果移回CPU再转为numpy
            vectors_table_padded.append(pooled_embedding.cpu().detach().numpy())
        except Exception as e:
            print(f"\nError processing text: {str(e)}\n")
            # 清理GPU缓存
            if torch.cuda.is_available():
                torch.cuda.empty_cache()
            return
        
        # 创建填充向量
        # c = list(context_embeddings[-1,::].size())
        # target = torch.zeros(512, 768)
        # source = context_embeddings[-1,::]
        # target[:c[0]] = source
        # vectors_table_padded.append(np.hstack(target.detach().numpy()))
        # 计算平均池化
        # pooled_embedding = torch.mean(context_embeddings, dim=0)  # 沿着第0维（序列长度）求平均
        # vectors_table_padded.append(pooled_embedding.detach().numpy())
        
        print('.', end='', flush=True)
        
        # 每1000行保存一次
        if (len(vectors_table_padded) > 0) and (len(vectors_table_padded) % 1000 == 0):
            vectors_calculation_passes.append(time.time())
            
            # 保存块文件
            chunk_file = os.path.join(embed_chunks_dir, f'outputCodeEmbeddingCodeBERT_{len(vectors_calculation_passes)}.pkl')
            with open(chunk_file, 'wb') as handle:
                pickle.dump(vectors_table_padded, handle, protocol=pickle.HIGHEST_PROTOCOL)
            
            # 重置数组以节省内存
            vectors_table_padded = []
            
            # 清理GPU缓存
            if torch.cuda.is_available():
                torch.cuda.empty_cache()
            
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
        
        print(f"\nFinished pass: {len(vectors_calculation_passes)}")
        print(f"Processed {(len(vectors_calculation_passes) - 1) * 1000 + len(vectors_table_padded)} entries.\n")
        
        vectors_table_padded = []
    
    print(f"Finished processing in {len(vectors_calculation_passes)} passes")
    return len(vectors_calculation_passes)

def combine_embeddings(num_passes, dataName, need_state_dict: bool):
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
    
    # 保存为npy格式
    if need_state_dict:
        embedding_npy_file = os.path.join(WORKING_DIR, 'dataset', f'{dataName}_CodeBERT_embeddings.npy')
    else:
        embedding_npy_file = os.path.join(WORKING_DIR, 'dataset', f'{dataName}_CodeBERT_base_embeddings.npy')
    with open(embedding_npy_file, 'wb') as handle:
        np.save(handle, vectors_table_padded)
    
    print("Saved all embedding files")
    return vectors_table_padded


def main(need_state_dict: bool = NEED_STATE_DICT):
    """主函数"""
    print("Starting CodeBERT inference pipeline...")
    
    # 0. 查询所有数据集
    dataAll = getAllData.get_all_data_files()

    for dataFile in dataAll:
        if not dataFile.endswith('.jsonl'):
            print(f"Skipping non-JSONL file: {dataFile}")
            continue
        
        print(f"\nProcessing file: {dataFile}")
        
        # 1. 加载模型
        dataName = dataFile.replace('.jsonl', '')
        modelName = f"{dataName}_model.bin"
        tokenizer, model = load_model(dataFile, modelName, need_state_dict)
        
        # 2. 测试模型
        test_model(tokenizer, model)
        
        # 3. 加载数据
        print("Loading data...")
        df = pd.read_json(os.path.join(DATASET_PATH, dataFile), lines=True)
        print(f"Loaded {len(df)} functions")
        print(f"Unique functions: {len(df['func'].unique())}")
        
        # 4. 创建嵌入向量
        num_passes = create_embeddings(tokenizer, model, df)
        
        # 5. 合并嵌入向量
        _ = combine_embeddings(num_passes, dataName, need_state_dict)

        # 6. 清理内存
        del df, model, tokenizer
        gc.collect()
        if os.path.exists(os.path.join(WORKING_DIR, 'dataset', 'embed_chunks')):
            shutil.rmtree(os.path.join(WORKING_DIR, 'dataset', 'embed_chunks'))
        print("Cleared memory and temporary files")

if __name__ == "__main__":
    main()