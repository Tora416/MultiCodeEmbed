import os
import sys
import subprocess
import pandas as pd
from sklearn.model_selection import train_test_split

import getAllData

SEED = 114

def build_astminer():
    """
    Build astminer.
    """
    # Gradle build command
    print("Building astminer...")
    py_path = os.path.dirname(__file__)
    if sys.platform.startswith('win'):
        gradle_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'gradlew.bat')
    else:
        gradle_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'gradlew')
    cmd = [gradle_path, 'shadowJar']

    subprocess.run(cmd, cwd=os.path.dirname(gradle_path), check=True)
    
    print("Build completed successfully.")
    return

def prepare_datasets():
    """
    Prepare datasets for code2vec using astminer.
    """
    print("Preparing datasets for code2vec...")
    
    py_path = os.path.dirname(__file__)
    all_datasets = getAllData.get_all_data_files()
    for dataset in all_datasets:
        if dataset.endswith('train.jsonl') or dataset.endswith('valid.jsonl') or dataset.endswith('test.jsonl'):
            dataset = dataset[:-6]  # Remove .jsonl extension
            if sys.platform.startswith('win'):
                cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.bat')
            else:
                cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.sh')
            
            cmd = [cli_path, dataset, dataset]
            subprocess.run(cmd, cwd=os.path.dirname(cli_path), check=True)

    print("Dataset preparation completed successfully.")
    return

def split_data_for_training(dataPath, train_ratio=0.8):
    """
    Split the dataset into training, validation sets.
    """
    df = pd.read_json(dataPath, lines=True)
    dataset_name = os.path.basename(dataPath).replace('.jsonl', '')

    another_ratio = (1 - train_ratio) / 2

    train_dfs = []
    valid_dfs = []
    test_dfs = []
    
    # 按类别分组处理
    for target_class in df['target'].unique():
        class_df = df[df['target'] == target_class].copy()
        class_size = len(class_df)
        # print(f"Class '{target_class}' has {class_size} samples.")

        # 打乱该类别的数据
        class_df = class_df.sample(frac=1, random_state=SEED).reset_index(drop=True)
        
        if class_size <= 2:
            raise ValueError(f"Class '{target_class}' has too few samples ({class_size}). At least 3 samples are required for splitting.")
        else:
            # 3个或更多样本：按比例分配，但保证每个分割至少1个
            valid_size = max(1, round(class_size * another_ratio))
            test_size = max(1, round(class_size * another_ratio))
            train_size = class_size - valid_size - test_size

            # 执行分割
            train_dfs.append(class_df.iloc[:train_size])
            if valid_size > 0:
                valid_dfs.append(class_df.iloc[train_size:train_size + valid_size])
            if test_size > 0:
                test_dfs.append(class_df.iloc[train_size + valid_size:train_size + valid_size + test_size])
    
    # 合并所有类别的分割结果
    train_df = pd.concat(train_dfs, ignore_index=True) if train_dfs else pd.DataFrame()
    valid_df = pd.concat(valid_dfs, ignore_index=True) if valid_dfs else pd.DataFrame()
    test_df = pd.concat(test_dfs, ignore_index=True) if test_dfs else pd.DataFrame()
    
    # 最后打乱整个数据集
    train_df = train_df.sample(frac=1, random_state=SEED).reset_index(drop=True) if len(train_df) > 0 else train_df
    valid_df = valid_df.sample(frac=1, random_state=SEED).reset_index(drop=True) if len(valid_df) > 0 else valid_df
    test_df = test_df.sample(frac=1, random_state=SEED).reset_index(drop=True) if len(test_df) > 0 else test_df

    dataBasePath = os.path.dirname(dataPath)
    train_df.to_json(os.path.join(dataBasePath, f'{dataset_name}_train.jsonl'), lines=True, orient='records')
    valid_df.to_json(os.path.join(dataBasePath, f'{dataset_name}_valid.jsonl'), lines=True, orient='records')
    test_df.to_json(os.path.join(dataBasePath, f'{dataset_name}_test.jsonl'), lines=True, orient='records')

    return dataBasePath

def split_all_data():
    """
    Split all datasets into training, validation, and test sets.
    """
    all_data = getAllData.get_all_data_files()
    py_path = os.path.dirname(__file__)
    base_path = os.path.join(py_path, '..', 'dataset')
    for data in all_data:
        if data.endswith('.jsonl') and '_train' not in data and '_valid' not in data and '_test' not in data: # Ensure we only process original datasets
            data_path = os.path.join(base_path, data)
            split_data_for_training(data_path)
            
def delete_temp_splits():
    """
    Delete temporary split files.
    """
    py_path = os.path.dirname(__file__)
    base_path = os.path.join(py_path, '..', 'dataset')
    for file in getAllData.get_all_data_files():
        if file.endswith('_train.jsonl') or file.endswith('_valid.jsonl') or file.endswith('_test.jsonl'):
            os.remove(os.path.join(base_path, file))
    print("Temporary split files deleted.")
            
def main():
    split_all_data()
    build_astminer()
    prepare_datasets()
    delete_temp_splits()
    print("All tasks completed successfully.")

if __name__ == '__main__':
    main()