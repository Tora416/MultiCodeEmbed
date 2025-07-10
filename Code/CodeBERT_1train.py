vulsimPath = r"C:\1111school\FuCai_Lib\VulSim"
vulsimPythonPath = vulsimPath + r"\.venv\Scripts\python.exe"
trainPath = vulsimPath + r"\CodeBERT\dataset\train_small.jsonl"
validPath = vulsimPath + r"\CodeBERT\dataset\valid_small.jsonl"
testPath = vulsimPath + r"\CodeBERT\dataset\test_small.jsonl"

import os

# Preprocessing
# os.system(f'{vulsimPythonPath} {vulsimPath}\\CodeBERT\\dataset\\preprocess.py ')

# Training
os.system(f'{vulsimPythonPath} {vulsimPath}\\CodeBERT\\code\\run.py '
          f'--output_dir={vulsimPath}\\CodeBERT\\code\\saved_models '
          f'--model_type=roberta '
          f'--tokenizer_name=microsoft/codebert-base '
          f'--model_name_or_path=microsoft/codebert-base '
          f'--do_train '
          f'--train_data_file={trainPath} '
          f'--eval_data_file={validPath} '
          f'--test_data_file={testPath} '
          '--epoch 5 '
          '--block_size 400 '
          '--train_batch_size 32 '
          '--eval_batch_size 64 '
          '--learning_rate 2e-5 '
          '--max_grad_norm 1.0 '
          '--evaluate_during_training '
          '--seed 123456 > ' + vulsimPath + r'\CodeBERT\code\train.log' + ' | type ' + vulsimPath + r'\CodeBERT\code\train.log' + ' 2>&1')