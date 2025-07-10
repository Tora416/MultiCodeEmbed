@echo off
REM Simple script for Java 8-14 where Nashorn is included.
REM All complex workarounds are no longer needed.

java -Xms8G -Xmx12G -jar build\shadow\lib-0.6.jar %*

if %errorlevel% neq 0 (
    echo.
    echo [FAILURE] Command finished with error code: %errorlevel%
) else (
    echo.
    echo [SUCCESS] Command completed successfully.
)