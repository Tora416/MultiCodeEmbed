import os
import sys
import subprocess
import shutil

import getAllData

PY_FILE_PATH = os.path.dirname(__file__)
V_PY_PATH = os.path.join(PY_FILE_PATH, '..', '.venv', 
                         'Scripts' if sys.platform.startswith('win') else 'bin', 
                         'python.exe' if sys.platform.startswith('win') else 'python3')

def main():
    all_datasets = getAllData.get_all_data_files()
    for dataset in all_datasets:
        if dataset.endswith('.jsonl') and '_train' not in dataset and '_valid' not in dataset and '_test' not in dataset:
            dataset_name = dataset[:-6]  # Remove .jsonl extension
            print(f"Processing dataset: {dataset_name}")
            
            C2V_PATH = os.path.join(PY_FILE_PATH, '..', 'code2vec', 'dx2021', 'code2vec')
            # copy dictionaries
            src = os.path.join(C2V_PATH, 'models', f'{dataset_name}', 'dictionaries.bin')
            dst = os.path.join(C2V_PATH, 'dictionaries.bin')
            if os.path.exists(src):
                if os.path.exists(dst):
                    os.remove(dst)
                shutil.copy2(src, dst)
                print("Moved dictionaries.bin to code2vec directory.")
            else:
                print("dictionaries.bin not found, skipping move.")
            
            # release model
            cmd = [V_PY_PATH, 'code2vec.py', 
                   '--load', os.path.join('models', f'{dataset_name}', 'saved_model'), 
                   '--release']
            subprocess.run(cmd, cwd=C2V_PATH, check=True)
            
            # remove dictionaries
            dictionaries_path = os.path.join(C2V_PATH, 'dictionaries.bin')
            if os.path.exists(dictionaries_path):
                os.remove(dictionaries_path)
                print("Removed dictionaries.bin from code2vec directory.")
            else:
                print("dictionaries.bin not found in code2vec directory, skipping remove.")
            
if __name__ == "__main__":
    main()
