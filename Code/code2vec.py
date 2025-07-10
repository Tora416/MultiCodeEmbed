import pandas as pd
import numpy as np
from scipy import spatial
import os
from tqdm import tqdm
import argparse

BASE_PATH = "code2vec/dx2021/code2vec/"

class Code2VecSimilarityAnalyzer:
    def __init__(self, data_dir=BASE_PATH + "data/devign", output_dir=BASE_PATH + "output"):
        """
        初始化分析器
        
        Args:
            data_dir: 数据目录路径
            output_dir: 输出目录路径
        """
        self.data_dir = data_dir
        self.output_dir = output_dir
        self.vectors_data = None
        self.labels_data = None
        self.similarity_matrix = None
        
        # 创建输出目录
        os.makedirs(output_dir, exist_ok=True)
        
    def load_vectors(self):
        """加载并合并向量文件"""
        print("Step 1: Loading vector files...")
        
        vector_files = [
            f"{self.data_dir}/devign.train.c2v.vectors",
            f"{self.data_dir}/devign.val.c2v.vectors", 
            f"{self.data_dir}/devign.test.c2v.vectors"
        ]
        
        all_data = []
        for file_path in vector_files:
            if os.path.exists(file_path):
                print(f"Loading {file_path}...")
                with open(file_path, 'r', encoding='utf-8') as f:
                    data = f.read().strip()
                    if data:
                        all_data.append(data)
            else:
                print(f"Warning: {file_path} not found!")
        
        if not all_data:
            raise FileNotFoundError("No vector files found!")
        
        # 合并所有数据
        merged_data = '\n'.join(all_data)
        
        # 保存合并后的文件
        embeddings_file = f"{self.output_dir}/embeddings.txt"
        with open(embeddings_file, 'w', encoding='utf-8') as f:
            f.write(merged_data)
        
        # 读取为DataFrame
        self.vectors_data = pd.read_csv(embeddings_file, sep=" ", header=None)
        print(f"Loaded vectors shape: {self.vectors_data.shape}")
        
        return self.vectors_data
    
    def load_labels(self):
        """加载并合并标签文件"""
        print("Step 2: Loading label files...")
        
        label_files = [
            f"{self.data_dir}/devign.train.c2v",
            f"{self.data_dir}/devign.val.c2v",
            f"{self.data_dir}/devign.test.c2v"
        ]
        
        all_labels = []
        for file_path in label_files:
            if os.path.exists(file_path):
                print(f"Loading labels from {file_path}...")
                df = pd.read_csv(file_path, sep=" ", header=None)
                all_labels.append(df[0])  # 第一列是标签
            else:
                print(f"Warning: {file_path} not found!")
        
        if not all_labels:
            raise FileNotFoundError("No label files found!")
        
        # 合并所有标签
        merged_labels = pd.concat(all_labels, axis=0, ignore_index=True)
        
        # 转换标签
        replace_dict = {'safe': 'Good', 'vuln': 'Bad'}
        merged_labels = merged_labels.replace(replace_dict)
        
        self.labels_data = merged_labels.to_frame(name='GroundTruth')
        self.labels_data['Index'] = range(len(self.labels_data))
        
        print(f"Loaded labels shape: {self.labels_data.shape}")
        print(f"Label distribution: {self.labels_data['GroundTruth'].value_counts().to_dict()}")
        
        return self.labels_data
    
    def calculate_similarity_matrix(self, batch_size=1000, resume_from=0):
        """
        计算相似性矩阵
        
        Args:
            batch_size: 批处理大小
            resume_from: 从哪个索引开始计算（用于恢复中断的计算）
        """
        print("Step 3: Calculating similarity matrix...")
        
        if self.vectors_data is None:
            raise ValueError("Vectors not loaded. Call load_vectors() first.")
        
        n_samples = len(self.vectors_data)
        print(f"Computing similarity for {n_samples} samples...")
        
        similarity_file = f"{self.output_dir}/similarity_matrix.txt"
        
        # 如果文件存在且resume_from > 0，说明要恢复计算
        mode = 'a' if resume_from > 0 and os.path.exists(similarity_file) else 'w'
        
        with open(similarity_file, mode) as f:
            if mode == 'w':
                f.write("")  # 清空文件
            
            # 使用进度条
            for i in tqdm(range(resume_from, n_samples), desc="Computing similarities"):
                similarities = []
                
                vector_i = self.vectors_data.iloc[i].values
                
                for j in range(n_samples):
                    vector_j = self.vectors_data.iloc[j].values
                    
                    # 计算余弦相似度
                    similarity = 1 - spatial.distance.cosine(vector_i, vector_j)
                    similarities.append(similarity)
                
                # 写入文件
                f.write(' '.join(map(str, similarities)) + '\n')
                
        print("Similarity matrix calculation completed!")
        return similarity_file
    
    def load_similarity_matrix(self):
        """加载相似性矩阵"""
        print("Step 4: Loading similarity matrix...")
        
        similarity_file = f"{self.output_dir}/similarity_matrix.txt"
        if not os.path.exists(similarity_file):
            raise FileNotFoundError(f"Similarity matrix file not found: {similarity_file}")
        
        self.similarity_matrix = pd.read_csv(similarity_file, sep=" ", header=None)
        print(f"Similarity matrix shape: {self.similarity_matrix.shape}")
        
        return self.similarity_matrix
    
    def find_top_similar(self, top_k=5):
        """
        找到每个样本最相似的top_k个样本
        
        Args:
            top_k: 返回最相似的k个样本
        """
        print(f"Step 5: Finding top {top_k} similar samples for each sample...")
        
        if self.similarity_matrix is None:
            self.load_similarity_matrix()
        
        if self.labels_data is None:
            self.load_labels()
        
        results = []
        n_samples = len(self.similarity_matrix)
        
        for i in tqdm(range(n_samples), desc="Processing samples"):
            similarities = self.similarity_matrix.iloc[i].values
            
            # 获取最相似的top_k+1个（包括自己）
            top_indices = np.argsort(similarities)[-top_k-1:]
            top_indices = top_indices[::-1]  # 降序排列
            
            # 移除自己
            if i in top_indices:
                top_indices = top_indices[top_indices != i][:top_k]
            else:
                top_indices = top_indices[:top_k]
            
            # 构建结果行
            result_row = [
                i,  # 当前样本索引
                self.labels_data.iloc[i]['GroundTruth']  # 当前样本标签
            ]
            
            # 添加相似样本信息
            for idx in top_indices:
                result_row.extend([
                    similarities[idx],  # 相似度分数
                    idx,  # 相似样本索引
                    self.labels_data.iloc[idx]['GroundTruth']  # 相似样本标签
                ])
            
            results.append(result_row)
        
        # 创建列名
        columns = ['Index', 'GroundTruth']
        for i in range(top_k):
            columns.extend([f'neighbor_{i+1}_similarity', f'neighbor_{i+1}_index', f'neighbor_{i+1}_label'])

        results_df = pd.DataFrame(results, columns=columns)
        
        # 保存结果
        results_file = f"{self.output_dir}/top_similar_results.txt"
        results_df.to_csv(results_file, sep=' ', header=False, index=False)
        
        print(f"Results saved to: {results_file}")
        return results_df
    
    def calculate_weighted_scores(self, results_df=None, weights=None):
        """
        计算加权分数
        
        Args:
            results_df: 相似性结果DataFrame
            weights: 权重列表，默认为[5,4,3,2,1]
        """
        print("Step 6: Calculating weighted scores...")
        
        if results_df is None:
            results_file = f"{self.output_dir}/top_similar_results.txt"
            if os.path.exists(results_file):
                results_df = pd.read_csv(results_file, sep=" ", header=None)
            else:
                raise FileNotFoundError("No results file found!")
        
        if weights is None:
            weights = [5, 4, 3, 2, 1]  # 默认权重
        
        n_samples = len(results_df)
        good_scores = []
        bad_scores = []
        confidences = []
        results = []
        
        for i in tqdm(range(n_samples), desc="Calculating weighted scores"):
            good_score = 0
            bad_score = 0
            
            row = results_df.iloc[i]
            
            # 计算加权分数（假设前5个相似样本）
            for j, weight in enumerate(weights):
                if len(row) > 4 + j * 3:  # 检查是否有足够的列
                    similarity = row.iloc[2 + j * 3]  # 相似度分数
                    label = row.iloc[4 + j * 3]  # 标签
                    
                    if label == 'Bad':
                        bad_score += weight * similarity
                    else:
                        good_score += weight * similarity
            
            good_scores.append(good_score)
            bad_scores.append(bad_score)
            
            if good_score > bad_score:
                results.append(0) # Good
            else:
                results.append(1) # Bad
                
            confidence = max(good_score, bad_score) / (good_score + bad_score) if (good_score + bad_score) > 0 else 0.5
            confidences.append(confidence)
        
        # 添加到结果DataFrame
        results_df['GoodScore'] = good_scores
        results_df['BadScore'] = bad_scores
        results_df['Confidence'] = confidences

        # 添加最终分类结果
        results_df['Predicted'] = ['Good' if x == 0 else 'Bad' for x in results]
        
        # 重新排列列顺序，将重要信息放在前面
        # 获取当前所有列
        all_columns = results_df.columns.tolist()
        
        # 构建新的列顺序
        priority_columns = ['Index', 'GroundTruth', 'Predicted', 'Confidence', 'GoodScore', 'BadScore']
        neighbor_columns = [col for col in all_columns if col.startswith('neighbor_')]
        
        # 最终列顺序
        new_column_order = priority_columns + neighbor_columns
        
        # 重新排列
        results_df = results_df[new_column_order]
        
        # 保存最终结果
        final_results_file = f"{self.output_dir}/final_results.csv"
        results_df.to_csv(final_results_file, index=False)

        print(f"Final results saved to: {final_results_file}")
        
        # 打印统计信息
        print("\n=== Analysis Summary ===")
        print(f"Total samples processed: {len(results_df)}")
        print(f"Average Good score: {np.mean(good_scores):.4f}")
        print(f"Average Bad score: {np.mean(bad_scores):.4f}")
        
        return results_df
    
    def evaluate_results(self, results_df):
        """
        评估分类结果
        
        Args:
            results_df: 分类结果DataFrame
        """
        from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
        
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
    
    def run_full_analysis(self, top_k=5, weights=None, calculate_similarity=True, resume_from=0):
        """
        运行完整分析流程
        
        Args:
            top_k: 返回最相似的k个样本
            weights: 权重列表
            calculate_similarity: 是否重新计算相似性矩阵
            resume_from: 从哪个索引开始计算相似性矩阵
        """
        print("Starting full Code2Vec similarity analysis...")
        
        # 1. 加载向量
        self.load_vectors()
        
        # 2. 加载标签
        self.load_labels()
        
        # 3. 计算或加载相似性矩阵
        if calculate_similarity:
            self.calculate_similarity_matrix(resume_from=resume_from)
        else:
            self.load_similarity_matrix()
        
        # 4. 找到最相似的样本
        results_df = self.find_top_similar(top_k=top_k)
        
        # 5. 计算加权分数
        final_results = self.calculate_weighted_scores(results_df, weights=weights)
        
        # 6. 统计评价结果
        _ = self.evaluate_results(final_results)
        
        print("Full analysis completed!")
        return final_results

def main():
    parser = argparse.ArgumentParser(description='Code2Vec Similarity Analysis')
    parser.add_argument('--data_dir', default=(BASE_PATH + 'data/devign'), help='Data directory path')
    parser.add_argument('--output_dir', default=(BASE_PATH + 'output'), help='Output directory path')
    parser.add_argument('--top_k', type=int, default=5, help='Number of top similar samples')
    parser.add_argument('--skip_similarity', action='store_true', help='Skip similarity calculation')
    parser.add_argument('--resume_from', type=int, default=0, help='Resume similarity calculation from index')
    
    args = parser.parse_args()
    
    # 创建分析器
    analyzer = Code2VecSimilarityAnalyzer(
        data_dir=args.data_dir,
        output_dir=args.output_dir
    )
    
    # 运行分析
    results = analyzer.run_full_analysis(
        top_k=args.top_k,
        calculate_similarity=not args.skip_similarity,
        resume_from=args.resume_from
    )
    
    print(f"Analysis completed! Results saved in '{args.output_dir}' directory.")

if __name__ == "__main__":
    main()