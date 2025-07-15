REM ###########################################################
REM Change the following values to preprocess a new dataset.
REM TRAIN_DIR, VAL_DIR and TEST_DIR should be paths to      
REM   directories containing sub-directories with .java files
REM   each of {TRAIN_DIR, VAL_DIR and TEST_DIR} should have sub-dirs,
REM   and data will be extracted from .java files found in those sub-dirs).
REM DATASET_NAME is just a name for the currently extracted 
REM   dataset.                                              
REM MAX_CONTEXTS is the number of contexts to keep for each 
REM   method (by default 200).                              
REM WORD_VOCAB_SIZE, PATH_VOCAB_SIZE, TARGET_VOCAB_SIZE -   
REM   - the number of words, paths and target words to keep 
REM   in the vocabulary (the top occurring words and paths will be kept). 
REM   The default values are reasonable for a Tesla K80 GPU 
REM   and newer (12 GB of board memory).
REM NUM_THREADS - the number of parallel threads to use. It is 
REM   recommended to use a multi-core machine for the preprocessing 
REM   step and set this value to the number of cores.
REM PYTHON - python3 interpreter alias.

if "%1"=="" (
    echo Usage: %0 ^<DATASET_NAME^>
    echo Example: %0 devign
    exit /b 1
)

SET TRAIN_DIR=my_train_dir
SET VAL_DIR=my_val_dir
SET TEST_DIR=my_test_dir
SET DATASET_NAME=%1
SET MAX_CONTEXTS=200
SET WORD_VOCAB_SIZE=20000
SET PATH_VOCAB_SIZE=20000
SET TARGET_VOCAB_SIZE=5000
SET NUM_THREADS=16
SET PYTHON=..\..\..\.venv\Scripts\python.exe
REM ###########################################################

SET TRAIN_DATA_FILE=raws\%DATASET_NAME%_train.raw.txt
SET VAL_DATA_FILE=raws\%DATASET_NAME%_valid.raw.txt
SET TEST_DATA_FILE=raws\%DATASET_NAME%_test.raw.txt

REM Create directories if they don't exist
if not exist "data" mkdir data
if not exist "data\%DATASET_NAME%" mkdir "data\%DATASET_NAME%"

SET TARGET_HISTOGRAM_FILE=data\%DATASET_NAME%\%DATASET_NAME%.histo.tgt.c2v
SET ORIGIN_HISTOGRAM_FILE=data\%DATASET_NAME%\%DATASET_NAME%.histo.ori.c2v
SET PATH_HISTOGRAM_FILE=data\%DATASET_NAME%\%DATASET_NAME%.histo.path.c2v

echo Creating histograms from the training data

%PYTHON% create_histograms.py %TRAIN_DATA_FILE% %TARGET_HISTOGRAM_FILE% %ORIGIN_HISTOGRAM_FILE% %PATH_HISTOGRAM_FILE%

echo [Python preprocessing] Creating histograms from the training data...

REM Run Python preprocessing
%PYTHON% preprocess.py --train_data %TRAIN_DATA_FILE% --test_data %TEST_DATA_FILE% --val_data %VAL_DATA_FILE% --max_contexts %MAX_CONTEXTS% --word_vocab_size %WORD_VOCAB_SIZE% --path_vocab_size %PATH_VOCAB_SIZE% --target_vocab_size %TARGET_VOCAB_SIZE% --word_histogram %ORIGIN_HISTOGRAM_FILE% --path_histogram %PATH_HISTOGRAM_FILE% --target_histogram %TARGET_HISTOGRAM_FILE% --output_name data\%DATASET_NAME%\%DATASET_NAME%

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Python preprocessing failed with error code: %errorlevel%
    exit /b 1
)

REM If all went well, the raw data files can be deleted, because preprocess.py creates new files 
REM with truncated and padded number of paths for each example.
echo Cleaning up temporary files...
del "%TRAIN_DATA_FILE%" "%VAL_DATA_FILE%" "%TEST_DATA_FILE%" "%TARGET_HISTOGRAM_FILE%" "%ORIGIN_HISTOGRAM_FILE%" "%PATH_HISTOGRAM_FILE%" 2>nul

echo.
echo [SUCCESS] Preprocessing completed successfully!
