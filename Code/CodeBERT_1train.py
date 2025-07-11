import os
import subprocess
import sys
import pandas as pd
from sklearn.model_selection import train_test_split

PY_FILE_BASE_PATH = os.path.dirname(__file__)
PROJECT_DIR = os.path.join(PY_FILE_BASE_PATH, '..')
SEED = 42
EPOCH = '1'

def train_codebert(labelNum: int, pythonPath: str = None):
    """
    Train CodeBERT model using the specified training data.
    """
    if os.path.exists(os.path.join(PROJECT_DIR, '.venv')):  # Check if virtual environment exists
        pythonPath = os.path.join(PROJECT_DIR, '.venv', 'Scripts', 'python.exe')
    else:
        if pythonPath is None:
            pythonPath = 'python'  # Default to system Python if no virtual environment is found
        else:
            pythonPath = pythonPath

    trainPath = os.path.join(PROJECT_DIR, 'dataset', 'train.jsonl')
    validPath = os.path.join(PROJECT_DIR, 'dataset', 'valid.jsonl')
    runScript = os.path.join(PROJECT_DIR, "CodeBERT", "code", "run.py")
    outputDir = os.path.join(PROJECT_DIR, "CodeBERT", "code", "saved_models")
    logFile = os.path.join(PROJECT_DIR, 'CodeBERT', 'code', 'train.log')

    # 构建命令参数列表
    cmd = [
        pythonPath, runScript,
        f'--output_dir={outputDir}',
        '--model_type=roberta',
        '--tokenizer_name=microsoft/codebert-base',
        '--model_name_or_path=microsoft/codebert-base',
        '--do_train',
        f'--train_data_file={trainPath}',
        f'--eval_data_file={validPath}',
        # f'--test_data_file={testPath}',
        f'--num_labels={labelNum}',
        '--epoch', EPOCH,
        '--block_size', '400',
        '--train_batch_size', '32',
        '--eval_batch_size', '64',
        '--learning_rate', '2e-5',
        '--max_grad_norm', '1.0',
        '--evaluate_during_training',
        '--seed', '123456'
    ]

    # 确保目录存在
    os.makedirs(outputDir, exist_ok=True)
    os.makedirs(os.path.dirname(logFile), exist_ok=True)

    cmd = ' '.join(cmd)
    cmd += f' > {logFile} | type {logFile} 2>&1'  # Redirect output to log file

    print(f"Executing: {cmd}")

    try:
        result = subprocess.run(cmd, shell=True, text=True)

        if result.returncode == 0:
            print("Training completed successfully!")
        else:
            print(f"Training failed with exit code: {result.returncode}")
            
        return result.returncode
        
    except Exception as e:
        print(f"Error executing training: {e}")
        return 1
    
def generate_temp_file_for_codebert(dataFile: str):
    """
    Generate a temporary file for CodeBERT training.
    """
    dataPath = os.path.join(PROJECT_DIR, 'dataset', dataFile)
    pd_data = pd.read_json(dataPath, lines=True)

    pd_data['idx'] = range(len(pd_data))
    
    authors = {}
    next_author_id = 0
    for row in pd_data['target']:
        if row not in authors:
            authors[row] = next_author_id
            next_author_id += 1
            
    pd_data['target'] = pd_data['target'].apply(lambda x: authors[x])
    labelNum = len(authors)

    dataFileT = 'temp_' + dataFile
    dataPathT = os.path.join(PROJECT_DIR, 'dataset', dataFileT)
    pd_data.to_json(dataPathT, lines=True, orient='records')

    return dataFileT, dataPathT, labelNum

def split_data_for_training(dataPath, train_ratio=0.8):
    """
    Split the dataset into training, validation sets.
    """
    df = pd.read_json(dataPath, lines=True)
    
    train_df, valid_df = train_test_split(df, train_size=train_ratio, stratify=df['target'], random_state=SEED)
    
    dataBasePath = os.path.dirname(dataPath)
    train_df.to_json(os.path.join(dataBasePath, 'train.jsonl'), lines=True, orient='records')
    valid_df.to_json(os.path.join(dataBasePath, 'valid.jsonl'), lines=True, orient='records')

    return dataBasePath

def train(dataFile: str):
    """
    Train the CodeBERT model.
    """
    dataFileT, dataPathT, labelNum = generate_temp_file_for_codebert(dataFile)
    dataBasePath = split_data_for_training(dataPathT)
    train_codebert(labelNum)
    os.remove(dataPathT)  # Clean up temporary file
    os.remove(os.path.join(dataBasePath, 'train.jsonl'))
    os.remove(os.path.join(dataBasePath, 'valid.jsonl'))
    modelPath = os.path.join(PROJECT_DIR, 'CodeBERT', 'code', 'saved_models', 'checkpoint-best-acc')
    newName = dataFile.replace('.jsonl', '') + '_model.bin'
    os.rename(os.path.join(modelPath, 'model.bin'),
              os.path.join(modelPath, newName))  # Rename final model file

if __name__ == '__main__':
    train('c.jsonl')  # Example usage with 'c.jsonl' dataset