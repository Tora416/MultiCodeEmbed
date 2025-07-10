import os
import pandas as pd

PY_FILE_BASE_PATH = os.path.dirname(__file__)
RAW_DATASET_PATHS = {
    'c': os.path.join(PY_FILE_BASE_PATH, '..', 'dataset', 'dataset_raw', 'a_github_c'),
    'cpp': os.path.join(PY_FILE_BASE_PATH, '..', 'dataset', 'dataset_raw', 'gcj_cpp'),
    'java': os.path.join(PY_FILE_BASE_PATH, '..', 'dataset', 'dataset_raw', 'java40'),
}

def walk_raw_dataset(path: str):
    """
    Walk through the raw dataset directory and yield file paths.
    """
    for root, dirs, _ in os.walk(path):
        for dir in dirs:
            childPath = os.path.join(root, dir)
            for cRoot, _, files in os.walk(childPath):
                for file in files:
                    try:
                        try:
                            with open(os.path.join(cRoot, file), 'r', encoding='utf-8') as f:
                                content = f.read()
                        except UnicodeDecodeError:
                            with open(os.path.join(cRoot, file), 'r', encoding='gbk') as f:
                                content = f.read()
                        yield (os.path.basename(cRoot), content)  # 每找到一个文件就返回
                    except Exception as e:
                        raise Exception(f"Error reading file {os.path.join(cRoot, file)}: {e}")
                    
def structure_dataset(dataset_message: tuple):
    """
    Structure the dataset based on the provided dataset message.
    """
    datasetName, datasetPath = dataset_message
    data_list = []

    for target, content in walk_raw_dataset(datasetPath):
        data_list.append({'target': target, 'func': content})

    dataset = pd.DataFrame(data_list)
    
    dataset.to_json(os.path.join(PY_FILE_BASE_PATH, '..', 'dataset', f"{datasetName}.jsonl"), lines=True, orient='records')
    return

def preprocess():
    """
    Preprocess the raw datasets and save them in structured format.
    """
    for datasetName, datasetPath in RAW_DATASET_PATHS.items():
        print(f"Processing dataset: {datasetName} from {datasetPath}")
        structure_dataset((datasetName, datasetPath))
    return

if __name__ == '__main__':
    preprocess()
    print("Preprocessing completed.")