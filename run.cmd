@echo off

REM Function to download, execute, and delete a file
:DownloadAndRun
REM Check if the correct number of arguments is passed
if "%~2"=="" (
    echo Usage: DownloadAndRun URL FILENAME
    exit /b 1
)

REM Set the URL and filename from the arguments
set "URL=%~1"
set "FILENAME=%~2"

REM Use PowerShell to download the file
powershell -Command "Invoke-WebRequest -Uri '%URL%' -OutFile '%FILENAME%'"

REM Check if the download was successful
if exist "%FILENAME%" (
    REM Run the downloaded file
    call "%FILENAME%"
    
    REM Delete the file after execution
    del "%FILENAME%"
) else (
    echo Failed to download %FILENAME% from %URL%
)

REM Return from the function
exit /b

REM Main script - Calls to the function with different URLs and filenames
call :DownloadAndRun "http://example.com/script1.cmd" "script1.cmd"
call :DownloadAndRun "http://example.com/script2.cmd" "script2.cmd"
call :DownloadAndRun "http://example.com/script3.cmd" "script3.cmd"

REM Add more calls as needed
