#!/usr/bin/env bash
###########################################################
# Change the following values to train a new model.
# type: the name of the new model, only affects the saved file name.
# dataset: the name of the dataset, as was preprocessed using preprocess.sh
# test_data: by default, points to the validation set, since this is the set that
#   will be evaluated after each training iteration. If you wish to test
#   on the final (held-out) test set, change 'val' to 'test'.
# type=java14m
# dataset_name=java14m

if [ $# -eq 0 ]; then
    echo "Usage: $0 <DATASET_NAME>"
    echo "Example: $0 devign"
    exit 1
fi

type=$1
dataset_name=$1
data_dir=data/${dataset_name}
data=${data_dir}/${dataset_name}
test_data=${data_dir}/${dataset_name}.val.c2v
model_dir=models/${type}

mkdir -p ${model_dir}
python -u code2vec.py --data ${data} --test ${test_data} --save ${model_dir}/saved_model
