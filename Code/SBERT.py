"""
SBERT Embedding
"""

import json
import pandas as pd
from sentence_transformers import SentenceTransformer
import os
import time
import warnings
import numpy as np
warnings.filterwarnings('ignore')

import getAllData

# 配置路径
PY_FILE_BASE_PATH = os.path.dirname(__file__)
DATA_DIR = os.path.join(PY_FILE_BASE_PATH, '../dataset')
OUTPUT_DIR = os.path.join(PY_FILE_BASE_PATH, '../SBERT/output')
SBERT_MODEL = 'all-MiniLM-L6-v2'  # 使用的SBERT模型名称，由SBERT.net提供

class SBERTEmbedding:
    """基于SBERT的代码嵌入类"""
    
    def __init__(self, model_name: str = SBERT_MODEL):
        """
        初始化嵌入类
        
        Args:
            model_name: SBERT模型名称
        """
        self.model_name = model_name
        self.model = None
        self.data = None
        self.similarity_matrix = None
        
    def load_model(self):
        """加载SBERT模型"""
        print(f"加载SBERT模型: {self.model_name}")
        try:
            self.model = SentenceTransformer(self.model_name)
            print("✓ 模型加载成功")
            return True
        except Exception as e:
            print(f"✗ 模型加载失败: {e}")
            return False

    def load_data(self, jsonl_file: str, data_dir: str = DATA_DIR):
        """
        加载并合并JSONL文件
        
        Args:
            jsonl_file: JSONL文件名
            data_dir: 数据目录
        """
        print("加载数据文件...")
        data = []
        file_path = os.path.join(data_dir, jsonl_file)
        if not os.path.exists(file_path):
            print(f"警告: 文件不存在 {file_path}")
            return False

        print(f"读取文件: {jsonl_file}")
        with open(file_path, "r", encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if line:
                    data.append(json.loads(line))
        
        # 创建DataFrame
        self.data = pd.DataFrame(data)
        print(f"✓ 数据加载完成，共 {len(self.data)} 条记录")

        return True
    
    def compute_embeddings(self, dataset_name: str, save_to_file: bool = True):
        """
        计算代码文本的嵌入向量和相似度矩阵
        
        Args:
            save_to_file: 是否保存到文件
        """
        if self.model is None:
            print("错误: 模型未加载")
            return False
            
        if self.data is None:
            print("错误: 数据未加载")
            return False
        
        print("计算代码嵌入向量...")
        start_time = time.time()
        
        # 获取代码文本
        sentences = self.data['func'].tolist()
        
        # 计算嵌入向量
        embeddings = self.model.encode(sentences, convert_to_tensor=True, show_progress_bar=True)
        
        if save_to_file:
            # 保存嵌入向量到文件
            embedding_file = os.path.join(OUTPUT_DIR, f'{dataset_name}_SBERT_embeddings.npy')
            os.makedirs(OUTPUT_DIR, exist_ok=True)
            with open(embedding_file, 'wb') as f:
                np.save(f, embeddings.cpu().numpy())
            print(f"✓ 嵌入向量已保存到: {embedding_file}， 耗时: {time.time() - start_time:.2f}秒")
        
        return True
    

def main():
    """主函数"""
    print("开始基于SBERT的嵌入计算...")
    
    # 初始化分类器
    classifier = SBERTEmbedding()
    
    # 加载模型
    if not classifier.load_model():
        print("模型加载失败，程序退出")
        return
    
    # 加载数据
    jsonl_files = getAllData.get_all_data_files()
    for file in jsonl_files:
        if not classifier.load_data(file):
            print(f"数据加载失败: {file}")
            return
        
        # 计算嵌入
        if not classifier.compute_embeddings(file.split('.')[0]):
            print(f"嵌入计算失败: {file}")
            return
    
    
if __name__ == "__main__":
    main()