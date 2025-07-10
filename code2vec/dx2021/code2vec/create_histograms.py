# 创建文件：create_histograms.py
import sys
from collections import Counter

def create_histograms(train_file, target_histogram_file='devign.histo.tgt.c2v', origin_histogram_file='devign.histo.ori.c2v', path_histogram_file='devign.histo.path.c2v'):
    targets = []
    words = []
    paths = []
    
    with open(train_file, 'r') as f:
        for line in f:
            parts = line.strip().split(' ')
            if len(parts) < 2:
                continue
                
            # Target (first part)
            targets.append(parts[0])
            
            # Contexts (remaining parts)
            for context in parts[1:]:
                context_parts = context.split(',')
                if len(context_parts) >= 3:
                    words.append(context_parts[0])  # start
                    paths.append(context_parts[1])  # path
                    words.append(context_parts[2])  # end
    
    # Write histograms
    with open(target_histogram_file, 'w') as f:
        for target, count in Counter(targets).items():
            f.write(f"{target} {count}\n")
    
    with open(origin_histogram_file, 'w') as f:
        for word, count in Counter(words).items():
            f.write(f"{word} {count}\n")
    
    with open(path_histogram_file, 'w') as f:
        for path, count in Counter(paths).items():
            f.write(f"{path} {count}\n")

if __name__ == "__main__":
    create_histograms(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])