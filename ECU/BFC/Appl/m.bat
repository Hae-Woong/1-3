@echo off
REM Set BFC Bazel target and output directories
set TARGET=//:BFC
set BAZEL_OUTPUT_DIR=..\..\..\bazel-out\x64_windows-dbg\bin\ECU\BFC\Appl\BFC
set OUTPUT_DIR=.\HIL_ECU

REM Run Bazel Clean
bazel clean

REM Run Bazel build
bazel build %TARGET%
IF %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

REM Ensure the output directory exists
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM Copy the Bazel output files to the output directory
xcopy /E /I /Y "%BAZEL_OUTPUT_DIR%" "%OUTPUT_DIR%"
IF %ERRORLEVEL% NEQ 0 (
    echo Copy failed!
    exit /b %ERRORLEVEL%
)

.\..\..\..\..\..\..\..\..\HexView\hexview.exe .\HIL_ECU\BFC.hex /S /CR:0xAF400000,0x2 /XS -o .\HIL_ECU\BFC.hex
.\..\..\..\..\..\..\..\..\HexView\hexview.exe .\HIL_ECU\BFC.hex /S /FR:0xA00A0000,0x18 /FP:4A65E9EC00090AA00200000000000AA00000260000000AA0 /XS -o .\HIL_ECU\BFC.hex
.\..\..\..\..\..\..\..\..\HexView\hexview.exe .\HIL_ECU\BFC.hex /S /FA /FP:FF /XS -o .\HIL_ECU\BFC.hex

set RETURN_CODE=0
exit /b %RETURN_CODE%