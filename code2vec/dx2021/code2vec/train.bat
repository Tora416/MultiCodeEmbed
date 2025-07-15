@echo off
REM ###########################################################
REM Change the following values to train a new model.
REM type: the name of the new model, only affects the saved file name.
REM dataset: the name of the dataset, as was preprocessed using preprocess.bat
REM test_data: by default, points to the validation set, since this is the set that
REM   will be evaluated after each training iteration. If you wish to test
REM   on the final (held-out) test set, change 'val' to 'test'.
REM type=java14m
REM dataset_name=java14m

if "%1"=="" (
    echo Usage: %0 ^<DATASET_NAME^>
    echo Example: %0 devign
    exit /b 1
)

SET type=%1
SET dataset_name=%1
SET data_dir=data\%dataset_name%
SET data=%data_dir%\%dataset_name%
SET test_data=%data_dir%\%dataset_name%.val.c2v
SET model_dir=models\%type%

SET PYTHON=..\..\..\.venv\Scripts\python.exe
REM ###########################################################

REM Create model directory if it doesn't exist
if not exist "%model_dir%" mkdir "%model_dir%"

echo Starting training...
echo Model type: %type%
echo Dataset: %dataset_name%
echo Data directory: %data_dir%
echo Test data: %test_data%
echo Model directory: %model_dir%
echo.

REM Run training with unbuffered output (-u flag equivalent)
%PYTHON% -u code2vec.py --data "%data%" --test "%test_data%" --save "%model_dir%\saved_model"

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Training failed with error code: %errorlevel%
    exit /b 1
) else (
    echo.
    echo [SUCCESS] Training completed successfully!
    echo Model saved to: %model_dir%\saved_model
)
