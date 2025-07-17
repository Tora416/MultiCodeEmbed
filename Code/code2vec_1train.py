import os
import sys
import subprocess

import getAllData

PY_FILE_PATH = os.path.dirname(__file__)
C2V_PATH = os.path.join(PY_FILE_PATH, '..', 'code2vec', 'dx2021', 'code2vec')

def run_preprocess_script(dataset_name):
    """
    Run the preprocess script for the given dataset.
    """
    print(f"Running preprocess script for {dataset_name}...")
    
    if sys.platform.startswith('win'):
        script_path = os.path.join(C2V_PATH, 'preprocess.bat')
    else:
        script_path = os.path.join(C2V_PATH, 'preprocess.sh')
    cmd = [script_path, dataset_name]
    
    subprocess.run(cmd, cwd=os.path.dirname(script_path), check=True)
    
    print(f"Preprocessing for {dataset_name} completed successfully.")
    return

def run_train_script(dataset_name):
    """
    Run the train script for the given dataset.
    """
    print(f"Running train script for {dataset_name}...")
    
    if sys.platform.startswith('win'):
        script_path = os.path.join(C2V_PATH, 'train.bat')
    else:
        script_path = os.path.join(C2V_PATH, 'train.sh')
    cmd = [script_path, dataset_name]
    
    subprocess.run(cmd, cwd=os.path.dirname(script_path), check=True)
    
    print(f"Training for {dataset_name} completed successfully.")
    return

def move_dictionaries(dataset_name):
    """
    Move dictionaries.bin to the model directory.
    """
    src = os.path.join(C2V_PATH, 'dictionaries.bin')
    dst = os.path.join(C2V_PATH, 'models', f'{dataset_name}', 'dictionaries.bin')

    if os.path.exists(src):
        if os.path.exists(dst):
            os.remove(dst)
        os.rename(src, dst)
        print("Moved dictionaries.bin to model directory.")
    else:
        print("dictionaries.bin not found, skipping move.")

def main():
    """
    Main function to run preprocessing and training for all datasets.
    """
    all_datasets = getAllData.get_all_data_files()  # Get the list of all datasets
    
    for dataset in all_datasets:
        if dataset.endswith('.jsonl') and '_train' not in dataset and '_valid' not in dataset and '_test' not in dataset:
            dataset_name = dataset[:-6] # Remove .jsonl extension
            print(f"Processing dataset: {dataset_name}")
            run_preprocess_script(dataset_name)
            run_train_script(dataset_name)
            move_dictionaries(dataset_name)

if __name__ == "__main__":
    main()