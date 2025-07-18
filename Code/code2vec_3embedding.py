import os
import pandas as pd
import numpy as np
import sys
import subprocess
import shutil

import getAllData

PY_FILE_PATH = os.path.dirname(__file__)
DATA_PATH = os.path.join(PY_FILE_PATH, '..', 'code2vec', 'dx2021', 'code2vec', 'data')
DATASET_PATH = os.path.join(PY_FILE_PATH, '..', 'dataset')

class Code2VecDataOutput:
    def __init__(self, dataset_name):
        self.dataset_name = dataset_name[:-6]  # Remove the '.jsonl' suffix

    def merge_vectors_and_idx(self):
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.test.c2v.vectors"), "r") as f:
            vectors = f.readlines()
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.train.c2v.vectors"), "r") as f:
            vectors += f.readlines()
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.val.c2v.vectors"), "r") as f:
            vectors += f.readlines()
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.vectors"), "w") as f:
            f.writelines(vectors)
            
        with open(os.path.join(DATASET_PATH, "ranks", f"{self.dataset_name}_test_idx.jsonl"), "r") as f:
            idx = f.readlines()
        with open(os.path.join(DATASET_PATH, "ranks", f"{self.dataset_name}_train_idx.jsonl"), "r") as f:
            idx += f.readlines()
        with open(os.path.join(DATASET_PATH, "ranks", f"{self.dataset_name}_valid_idx.jsonl"), "r") as f:
            idx += f.readlines()
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.idx.jsonl"), "w") as f:
            f.writelines(idx)


    def format_vectors(self):
        # step1: read all vector lines
        with open(os.path.join(DATA_PATH, f"{self.dataset_name}", f"{self.dataset_name}.vectors"), "r") as f:
            vectors = f.readlines()
        vectors = [line.rstrip('\n') for line in vectors]
        
        # step2: create DataFrame with vectors
        df = pd.DataFrame({
            'vector': vectors
        })
        
        return df

    def preprocess_to_raw(self):
        py_path = os.path.dirname(__file__)
    
        if sys.platform.startswith('win'):
            cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.bat')
        else:
            cli_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'astminer', 'cli.sh')

        df = pd.read_json(os.path.join(DATASET_PATH, self.dataset_name + '.jsonl'), lines=True)
        df['target'] = df['target'].str.replace(' ', '_')
        df.to_json(os.path.join(DATASET_PATH, f"{self.dataset_name}_ns.jsonl"), orient='records', lines=True)

        cmd = [cli_path, self.dataset_name + '_ns', self.dataset_name + '_ns']
        try:
            subprocess.run(cmd, cwd=os.path.dirname(cli_path), check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error occurred while running {cmd}: {e}")
        finally:
            os.remove(os.path.join(DATASET_PATH, f"{self.dataset_name}_ns.jsonl"))

    def preprocess_to_c2v_train(self):
        py_path = os.path.dirname(__file__)
        c2v_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'code2vec')
        
        with open(os.path.join(c2v_path, 'raws', f'{self.dataset_name}_test.raw.txt'), 'w') as f:
            f.write('temp                    \n')
        
        with open(os.path.join(c2v_path, 'raws', f'{self.dataset_name}_valid.raw.txt'), 'w') as f:
            f.write('temp                    \n')
        
        os.rename(os.path.join(c2v_path, 'raws', f'{self.dataset_name}_ns.raw.txt'), os.path.join(c2v_path, 'raws', f'{self.dataset_name}_train.raw.txt'))
        
        if sys.platform.startswith('win'):
            script_path = os.path.join(c2v_path, 'preprocess.bat')
        else:
            script_path = os.path.join(c2v_path, 'preprocess.sh')
        cmd = [script_path, self.dataset_name]
        subprocess.run(cmd, cwd=os.path.dirname(script_path), check=True)
        
    def embedding(self):
        py_path = os.path.dirname(__file__)
        c2v_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'code2vec')
        if sys.platform.startswith('win'):
            v_py_path = os.path.join(py_path, '..', '.venv', 'Scripts', 'python.exe')
        else:
            v_py_path = os.path.join(c2v_path, '..', '.venv', 'bin', 'python')
            
        # copy dictionaries
        src = os.path.join(c2v_path, 'models', f'{self.dataset_name}', 'dictionaries.bin')
        dst = os.path.join(c2v_path, 'dictionaries.bin')
        if os.path.exists(src):
            if os.path.exists(dst):
                os.remove(dst)
            shutil.copy2(src, dst)
            print("Moved dictionaries.bin to code2vec directory.")
        else:
            print("dictionaries.bin not found, skipping move.")
        
        cmd1 = [v_py_path, 'code2vec.py', 
                   '--load', os.path.join('models', f'{self.dataset_name}', 'saved_model.release'),
                   '--export_code_vectors', 
                   '--test', os.path.join('data', f'{self.dataset_name}', f'{self.dataset_name}.train.c2v')]
        subprocess.run(cmd1, cwd=c2v_path, check=True)
        
        # remove dictionaries
        dictionaries_path = os.path.join(c2v_path, 'dictionaries.bin')
        if os.path.exists(dictionaries_path):
            os.remove(dictionaries_path)
            print("Removed dictionaries.bin from code2vec directory.")
        else:
            print("dictionaries.bin not found in code2vec directory, skipping remove.")
            
    def fill_blank_lines(self):
        py_path = os.path.dirname(__file__)
        c2v_path = os.path.join(py_path, '..', 'code2vec', 'dx2021', 'code2vec')
        ast_path = os.path.join(c2v_path, 'data', f'{self.dataset_name}', f'{self.dataset_name}.train.c2v')
        vectors_path = os.path.join(c2v_path, 'data', f'{self.dataset_name}', f'{self.dataset_name}.train.c2v.vectors')
        out_path = os.path.join(c2v_path, 'data', f'{self.dataset_name}', f'{self.dataset_name}.vectors')
        with open(ast_path, 'r') as f:
            lines = f.readlines()
        with open(vectors_path, 'r') as f:
            vectors = f.readlines()
        with open(out_path, 'w') as f:
            j = 0
            for i in range(len(lines)):
                if len(lines[i].split()) <= 1:
                    f.write('0.0')
                    for _ in range(2303):
                        f.write(' 0.0')
                    f.write('\n')
                else:
                    f.write(vectors[j])
                    j += 1

    def save_reordered_vectors(self, df):
        output_path = os.path.join(DATA_PATH, '..', 'output')
        vectors_list = []
        for vector_str in df['vector']:
            vector = [float(x) for x in vector_str.split()]
            vectors_list.append(vector)

        vectors_array = np.array(vectors_list)
        
        out_path = os.path.join(output_path, f"{self.dataset_name}_code2vec_embeddings.npy")
        np.save(out_path, vectors_array)
        
        return out_path
        
def main():
    all_datasets = getAllData.get_all_data_files()
    
    for dataset in all_datasets:
        if dataset.endswith('.jsonl'):
            print("Preprocess whole dataset:", dataset)
            code2vec_output = Code2VecDataOutput(dataset)
            code2vec_output.preprocess_to_raw()
            code2vec_output.preprocess_to_c2v_train()
            print("Embedding:", dataset)
            code2vec_output.embedding()
            print("Prepare to output:", dataset)
            code2vec_output.fill_blank_lines()
            df = code2vec_output.format_vectors()
            output_path = code2vec_output.save_reordered_vectors(df)
            print("Finished! Output path:", output_path)

if __name__ == "__main__":
    main()
    