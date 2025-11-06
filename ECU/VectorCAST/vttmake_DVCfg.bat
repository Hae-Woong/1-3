@echo off
set VCAST_KEEP_INSTRUMENTED_FILES=1
"%vVIRTUALtarget_InstallDir%\vttmake.exe" make .\..\LightControl-level3.vttmake	--excludeDVCfgCmd
set ERRORCODE=%ERRORLEVEL%

if %ERRORCODE% neq 0 (
    echo vttmake.exe failed with error code %ERRORCODE%
    exit /b %ERRORCODE%
) else (
    echo vttmake.exe completed successfully
)