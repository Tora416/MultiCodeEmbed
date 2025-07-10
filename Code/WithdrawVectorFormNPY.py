import numpy as np
import os
import sys

def withdraw_vector_form_npy(npy_path: str, output_path: str):
    with open(npy_path, 'rb') as f:
        data = np.load(f)
    os.makedirs(output_path, exist_ok=True)
    print(f"Data shape: {data.shape}")
    print(f"Data type: {data.dtype}")
    
    # 生成基础文件名
    base_filename = os.path.splitext(os.path.basename(npy_path))[0]
    
    # 保存为CSV格式（可直接阅读）
    csv_file = os.path.join(output_path, f'{base_filename}_vectors.csv')
    if len(data.shape) == 2:
        # 二维数组，每行是一个向量
        np.savetxt(csv_file, data, delimiter=',')
        print(f"Saved as CSV: {csv_file}")
    else:
        raise ValueError(f"Unsupported data shape: {data.shape}. Expected 2D array.")


def main(args):
    """
    Withdraw vector form from a NPY file and save it to a csv file.
    
    Args:
        args: Command line arguments containing the NPY file path and output directory.
    """
    npy_path = None
    output_path = None
    if len(args) < 2:
        print("Usage: python WithdrawVectorFormNPY.py <npy_path> <output_path>")
        npy_path = input("Enter the path to the NPY file: ")
        output_path = input("Enter the output directory to save vectors: ")
    else:
        npy_path = args[0]
        output_path = args[1]

    withdraw_vector_form_npy(npy_path, output_path)
    print(f"Vectors withdrawn and saved to {output_path}")
    
if __name__ == '__main__':
    main(sys.argv[1:])