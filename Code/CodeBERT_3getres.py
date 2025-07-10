import pandas as pd
import numpy as np
import os
import json
import time
from sklearn.metrics import classification_report, accuracy_score, confusion_matrix

WORKING_DIR = r".\CodeBERT"
DATA_PATH = os.path.join(WORKING_DIR, 'dataset')
DATASET = 'small.jsonl'
SIMILARITY_FILE = 'similarity_all.npy'
OUTPUT_PATH = os.path.join(WORKING_DIR, 'output', 'codebert_similarity_results.csv')

def load_similarity_data():
    """加载相似度数据"""
    # 确保数据目录存在
    if not os.path.exists(DATA_PATH):
        raise FileNotFoundError(f"Data path {DATA_PATH} does not exist.")
    
    # 加载相似度矩阵
    try:
        similarity_all = np.load(os.path.join(DATA_PATH, SIMILARITY_FILE))
        print(f"Loaded similarity data with shape: {similarity_all.shape}")
    except Exception as e:
        raise RuntimeError(f"Failed to load similarity data: {str(e)}")
    
    return pd.DataFrame(similarity_all)

def load_dataset_target():
    """加载数据集的标签"""
    dataset_path = os.path.join(DATA_PATH, DATASET)
    
    if not os.path.exists(dataset_path):
        raise FileNotFoundError(f"Dataset file {dataset_path} does not exist.")
    
    try:
        df = pd.read_json(dataset_path, lines=True)
        print(f"Loaded dataset with {len(df)} entries.")
    except Exception as e:
        raise RuntimeError(f"Failed to load dataset: {str(e)}")
    
    df = df[['target']].copy()
    df.rename(columns={'target': 'GroundTruth'}, inplace=True)
    df['GroundTruth'] = df['GroundTruth'].replace({0: 'Good', 1: 'Bad'})
    
    return df

def KNN(similarity_data, dataset_target, k=5):
    """K个最近邻居"""
    if len(similarity_data) != len(dataset_target):
        raise ValueError("Length of similarity data and dataset target must match.")
    
    # 计算每个函数的KNN
    knn_results = []
    for i in range(len(similarity_data)):
        # 获取当前函数的相似度
        current_similarities = similarity_data.iloc[i]
        # 找到K个最近邻
        knn_indices = current_similarities.nlargest(k + 1).index[1:k + 1]
        now_n_neighbors = []
        for idx in knn_indices:
            a_neighbor = {
                'index': idx,
                'label': dataset_target.iloc[idx]['GroundTruth'],
                'similarity': current_similarities[idx]
            }
            now_n_neighbors.append(a_neighbor)
        knn_results.append(now_n_neighbors)

    return knn_results

def multi_vote(knn_results, dataset_target):
    """对KNN结果进行多重投票"""
    final_predictions = []

    for i, neighbors in enumerate(knn_results):
        good_score = 0
        bad_score = 0
        prediction = ''
        
        for j, neighbor in enumerate(neighbors):
            weight = 5 - j
            if neighbor['label'] == 'Good':
                good_score += weight * neighbor['similarity']
            else:
                bad_score += weight * neighbor['similarity']

        if good_score > bad_score:
            prediction = 'Good'
        else:
            prediction = 'Bad'
            
        confidence = max(good_score, bad_score) / (good_score + bad_score) if (good_score + bad_score) > 0 else 0.5
            
        now_result = {
            'Index': i,
            'GroundTruth': dataset_target.iloc[i]['GroundTruth'],
            'Predicted': prediction,
            'Confidence': confidence,
            'GoodScore': good_score,
            'BadScore': bad_score
        }

        for k2, neighbor in enumerate(neighbors):
            now_result[f"Neighbor_{k2}_similarity"] = neighbor['similarity']
            now_result[f"Neighbor_{k2}_index"] = neighbor['index']
            now_result[f"Neighbor_{k2}_label"] = neighbor['label']

        final_predictions.append(now_result)

    return final_predictions

def save_results(results_df, output_file=OUTPUT_PATH):
    """保存结果到CSV文件"""
    results_df.to_csv(output_file, index=False)
    print(f"Results saved to {output_file}")

def evaluate_results(results):
    """
    评估分类结果
    """
    results_df = pd.DataFrame(results)
    
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
        
    return results_df

def main():
    similarity_data = load_similarity_data()
    dataset_target = load_dataset_target()
    knn_results = KNN(similarity_data, dataset_target)
    final_results = multi_vote(knn_results, dataset_target)
    results_df = evaluate_results(final_results)
    save_results(results_df)

if __name__ == "__main__":
    start_time = time.time()
    main()
    end_time = time.time()
    print(f"Total execution time: {end_time - start_time:.2f} seconds")