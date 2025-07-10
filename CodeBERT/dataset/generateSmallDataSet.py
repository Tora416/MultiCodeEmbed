TEST_DATASET_PATH = "test2.jsonl"
TRAIN_DATASET_PATH = "train2.jsonl"
VALID_DATASET_PATH = "valid2.jsonl"
FULL_SIZE = 1000

import os
now_path = os.path.dirname(os.path.abspath(__file__))

with open(now_path + "/" + TEST_DATASET_PATH, "r") as f:
    test_data = f.readlines()
    test_data = test_data[:FULL_SIZE//10]
    with open(now_path + "/" + "test_small.jsonl", "w") as f2:
        for i in test_data:
            f2.write(i)

with open(now_path + "/" + TRAIN_DATASET_PATH, "r") as f:
    train_data = f.readlines()
    train_data = train_data[:(FULL_SIZE//10)*8]
    with open(now_path + "/" + "train_small.jsonl", "w") as f2:
        for i in train_data:
            f2.write(i)

with open(now_path + "/" + VALID_DATASET_PATH, "r") as f:
    valid_data = f.readlines()
    valid_data = valid_data[:FULL_SIZE//10]
    with open(now_path + "/" + "valid_small.jsonl", "w") as f2:
        for i in valid_data:
            f2.write(i)