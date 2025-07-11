import os

DATA_DIR = os.path.join(os.path.dirname(__file__), '..', 'dataset')

def get_all_data_files(data_dir: str=DATA_DIR):
    """
    获取数据目录下的所有JSONL文件
    
    Args:
        data_dir: 数据目录路径
        
    Returns:
        list: JSONL文件列表
    """
    if not os.path.exists(data_dir):
        print(f"错误: 数据目录不存在 {data_dir}")
        return []
    
    jsonl_files = [f for f in os.listdir(data_dir) if f.endswith('.jsonl')]
    if not jsonl_files:
        print("警告: 未找到任何JSONL文件")
    
    return jsonl_files
