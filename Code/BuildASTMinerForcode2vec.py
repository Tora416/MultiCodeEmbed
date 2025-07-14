import os
import sys
import subprocess

import getAllData

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
        if dataset.endswith('.jsonl'):
            dataset = dataset[:-6]  # Remove .jsonl extension
            if sys.platform.startswith('win'):
                cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.bat')
            else:
                cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.sh')
            
            cmd = [cli_path, dataset]
            subprocess.run(cmd, cwd=os.path.dirname(cli_path), check=True)

    print("Dataset preparation completed successfully.")
    return

if __name__ == '__main__':
    build_astminer()
    prepare_datasets()
    print("All tasks completed successfully.")