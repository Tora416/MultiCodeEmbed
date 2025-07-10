"""
基于SBERT相似度的漏洞检测KNN分类器
使用预训练的SBERT模型计算代码相似度，然后基于K最近邻进行分类
"""

import json
import pandas as pd
import numpy as np
from sentence_transformers import SentenceTransformer, util
import os
import time
from sklearn.metrics import classification_report, accuracy_score, confusion_matrix
import warnings
warnings.filterwarnings('ignore')

# 配置路径
DATA_DIR = './DataSet'
OUTPUT_DIR = './SBERT/output'
# JSONL_FILES = ["train2.jsonl", "valid2.jsonl", "test2.jsonl"]
JSONL_MAX_SIZE = 2000 # 总数据量限制，为0代表不限制
JSONL_FILES = ["small.jsonl"]  # 小测试集
SBERT_MODEL = 'all-MiniLM-L6-v2'  # 使用的SBERT模型名称，由SBERT.net提供
K_NEIGHBORS = 5  # K最近邻的K值
WEIGHT_STRATEGY = 'distance'  # 权重策略: 'distance'(简单加权) 或 'uniform'(不加权)

class SBERTSimilarityClassifier:
    """基于SBERT相似度的分类器"""
    
    def __init__(self, model_name: str = SBERT_MODEL):
        """
        初始化分类器
        
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
    
    def load_data(self, jsonl_files: list, data_dir: str = DATA_DIR):
        """
        加载并合并JSONL文件
        
        Args:
            jsonl_files: JSONL文件列表
            data_dir: 数据目录
        """
        print("加载数据文件...")
        data = []
        
        for file in jsonl_files:
            file_path = os.path.join(data_dir, file)
            if not os.path.exists(file_path):
                print(f"警告: 文件不存在 {file_path}")
                continue
                
            print(f"  读取文件: {file}")
            with open(file_path, "r", encoding='utf-8') as f:
                for line in f:
                    line = line.strip()
                    if line:
                        data.append(json.loads(line))
        
        # 创建DataFrame
        if JSONL_MAX_SIZE > 0 and len(data) > JSONL_MAX_SIZE:
            print(f"▲ 数据量超出限制，将截断为 {JSONL_MAX_SIZE} 条记录")
            data = data[:JSONL_MAX_SIZE]
        self.data = pd.DataFrame(data)
        print(f"✓ 数据加载完成，共 {len(self.data)} 条记录")
        
        # 数据预处理
        self.data = self.data[['target', 'func']].copy()
        
        # 转换标签格式
        replace_dict = {0: 'Good', 1: 'Bad'}
        self.data['target'] = self.data['target'].replace(replace_dict)
        self.data = self.data.rename(columns={'target': 'GroundTruth'})
        
        # 添加索引
        self.data['Index'] = range(len(self.data))
        
        print(f"标签分布: {self.data['GroundTruth'].value_counts().to_dict()}")
        
        return True
    
    def compute_embeddings(self, save_to_file: bool = True):
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
        
        # 计算余弦相似度矩阵
        print("计算相似度矩阵...")
        cosine_scores = util.cos_sim(embeddings, embeddings)
        self.similarity_matrix = cosine_scores.cpu().detach().numpy()
        
        end_time = time.time()
        print(f"✓ 嵌入计算完成，耗时: {end_time - start_time:.2f}秒")
        print(f"相似度矩阵形状: {self.similarity_matrix.shape}")
        
        # 保存相似度矩阵到文件
        if save_to_file:
            output_path = os.path.join(OUTPUT_DIR, 'outputEmbedding.txt')
            os.makedirs(OUTPUT_DIR, exist_ok=True)
            
            print(f"保存相似度矩阵到: {output_path}")
            with open(output_path, 'w') as f:
                for i in range(len(self.similarity_matrix)):
                    for j in range(len(self.similarity_matrix)):
                        f.write(str(self.similarity_matrix[i][j]) + " ")
                    f.write("\n")
        
        return True
    
    def find_k_nearest_neighbors(self, query_idx: int, k: int = K_NEIGHBORS):
        """
        找到查询样本的K个最近邻
        
        Args:
            query_idx: 查询样本的索引
            k: 近邻数量
            
        Returns:
            list: 包含(相似度, 索引, 标签)的列表，按相似度降序排列
        """
        if self.similarity_matrix is None:
            raise ValueError("相似度矩阵未计算")
        
        # 获取与查询样本的相似度
        similarities = self.similarity_matrix[query_idx]
        
        # 找到最相似的k+1个样本（包括自己）
        top_indices = np.argsort(similarities)[-k-1:][::-1]
        
        # 移除自己
        if query_idx in top_indices:
            top_indices = top_indices[top_indices != query_idx]
        else:
            top_indices = top_indices[:-1]
        
        # 只保留k个邻居
        top_indices = top_indices[:k]
        
        # 构建结果
        neighbors = []
        for idx in top_indices:
            neighbors.append({
                'similarity': similarities[idx],
                'index': idx,
                'label': self.data.iloc[idx]['GroundTruth']
            })
        
        return neighbors
    
    def classify_sample(self, query_idx: int, k: int = K_NEIGHBORS, weight_strategy: str = WEIGHT_STRATEGY):
        """
        对单个样本进行分类
        
        Args:
            query_idx: 查询样本索引
            k: 近邻数量
            weight_strategy: 权重策略 ('distance' 或 'uniform')
            
        Returns:
            tuple: (预测标签, 置信度分数, 邻居信息)
        """
        neighbors = self.find_k_nearest_neighbors(query_idx, k)
        
        if weight_strategy == 'distance':
            # 基于距离的加权投票
            good_score = 0
            bad_score = 0
            
            for i, neighbor in enumerate(neighbors):
                # 权重递减: 最近邻权重最高
                weight = k - i
                if neighbor['label'] == 'Good':
                    good_score += weight * neighbor['similarity']
                else:
                    bad_score += weight * neighbor['similarity']
            
            predicted_label = 'Good' if good_score > bad_score else 'Bad'
            confidence = max(good_score, bad_score) / (good_score + bad_score) if (good_score + bad_score) > 0 else 0.5
            
        else:  # uniform
            # 简单多数投票
            labels = [neighbor['label'] for neighbor in neighbors]
            bad_count = labels.count('Bad')
            good_count = labels.count('Good')
            
            predicted_label = 'Bad' if bad_count > good_count else 'Good'
            confidence = max(bad_count, good_count) / len(labels)
        
        return predicted_label, confidence, neighbors, good_score, bad_score
    
    def classify_all_samples(self, k: int = K_NEIGHBORS, weight_strategy: str = WEIGHT_STRATEGY):
        """
        对所有样本进行分类
        
        Args:
            k: 近邻数量
            weight_strategy: 权重策略
            
        Returns:
            DataFrame: 包含分类结果的DataFrame
        """
        print(f"开始分类，K={k}, 权重策略={weight_strategy}")
        
        results = []
        total_samples = len(self.data)
        
        for i in range(total_samples):
            # 分类
            predicted_label, confidence, neighbors, good_score, bad_score = self.classify_sample(i, k, weight_strategy)
            
            # 收集结果
            result = {
                'Index': i,
                'GroundTruth': self.data.iloc[i]['GroundTruth'],
                'Predicted': predicted_label,
                'Confidence': confidence,
                'Neighbors': neighbors,
                'GoodScore': good_score,
                'BadScore': bad_score
            }
            
            results.append(result)
            
            # 显示进度
            if (i + 1) % 1000 == 0:
                print(f"已处理 {i + 1} / {total_samples} 样本")
        
        results_df = pd.DataFrame(results)
        print("✓ 分类完成")
        
        return results_df
    
    def evaluate_results(self, results_df: pd.DataFrame):
        """
        评估分类结果
        
        Args:
            results_df: 分类结果DataFrame
        """
        true_labels = results_df['GroundTruth'].tolist()
        predicted_labels = results_df['Predicted'].tolist()
        
        # 计算准确率
        accuracy = accuracy_score(true_labels, predicted_labels)
        
        # 生成分类报告
        report = classification_report(true_labels, predicted_labels, output_dict=True)
        
        # 混淆矩阵
        cm = confusion_matrix(true_labels, predicted_labels)
        
        print("\n=== 分类结果评估 ===")
        print(f"总样本数: {len(results_df)}")
        print(f"准确率: {accuracy:.4f}")
        print(f"平均置信度: {results_df['Confidence'].mean():.4f}")
        
        print("\n=== 分类报告 ===")
        for label in ['Good', 'Bad']:
            if label in report:
                metrics = report[label]
                print(f"{label}: 精确率={metrics['precision']:.4f}, 召回率={metrics['recall']:.4f}, F1={metrics['f1-score']:.4f}")
        
        print(f"\n=== 混淆矩阵 ===")
        print(f"实际\\预测\t{'Good':<8}\t{'Bad':<8}")
        labels = ['Good', 'Bad']
        for i, true_label in enumerate(labels):
            row = f"{true_label:<8}\t"
            for j, pred_label in enumerate(labels):
                row += f"{cm[i][j]:<8}\t"
            print(row)
        
        return {
            'accuracy': accuracy,
            'classification_report': report,
            'confusion_matrix': cm.tolist()
        }
    
    def save_results(self, results_df: pd.DataFrame, filename: str = 'similarity_classification_results.csv'):
        """
        保存分类结果
        
        Args:
            results_df: 分类结果DataFrame
            filename: 保存文件名
        """
        output_path = os.path.join(OUTPUT_DIR, filename)
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        
        # 准备保存的数据
        save_data = results_df.copy()
        
        # 展开邻居信息
        neighbor_cols = []
        max_neighbors = max(len(neighbors) for neighbors in save_data['Neighbors'])
        
        for i in range(max_neighbors):
            for field in ['similarity', 'index', 'label']:
                col_name = f'neighbor_{i+1}_{field}'
                neighbor_cols.append(col_name)
                save_data[col_name] = save_data['Neighbors'].apply(
                    lambda x: x[i][field] if i < len(x) else None
                )
        
        # 移除原始的Neighbors列
        save_data = save_data.drop('Neighbors', axis=1)
        
        # 保存到csv文件
        save_data.to_csv(output_path, index=False)
        print(f"✓ 结果已保存到: {output_path}")

def main():
    """主函数"""
    print("开始基于SBERT相似度的漏洞检测分类...")
    start_time = time.time()
    
    # 初始化分类器
    classifier = SBERTSimilarityClassifier()
    
    # 加载模型
    if not classifier.load_model():
        print("模型加载失败，程序退出")
        return
    
    # 加载数据
    if not classifier.load_data(JSONL_FILES):
        print("数据加载失败，程序退出")
        return
    
    # 计算嵌入和相似度矩阵
    if not classifier.compute_embeddings():
        print("嵌入计算失败，程序退出")
        return
    
    # 进行分类
    results_df = classifier.classify_all_samples(k=K_NEIGHBORS, weight_strategy=WEIGHT_STRATEGY)
    
    # 评估结果
    evaluation_results = classifier.evaluate_results(results_df)
    
    # 保存结果
    classifier.save_results(results_df)
    
    # 显示一些预测示例
    print("\n=== 预测示例 ===")
    for i in range(min(5, len(results_df))):
        row = results_df.iloc[i]
        print(f"样本 {i+1}:")
        print(f"  真实标签: {row['GroundTruth']}")
        print(f"  预测标签: {row['Predicted']}")
        print(f"  置信度: {row['Confidence']:.4f}")
        print(f"  预测{'正确' if row['GroundTruth'] == row['Predicted'] else '错误'}")
        print("-" * 50)
    
    total_time = time.time() - start_time
    print(f"\n程序运行完成，总耗时: {total_time:.2f}秒")

if __name__ == "__main__":
    main()