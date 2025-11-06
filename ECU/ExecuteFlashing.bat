@echo off

set VFLASHPROJECT=D:\HIL\w\vecs-1-3-hil\vecs-1-3-hil\ECU\vFlash\Demo.vflash

echo ---------------------------------------------------
echo Vector vFlash Continuous Integration Example
echo ---------------------------------------------------
echo.

echo ------------------------------------
echo Start ECU Simulation
echo ------------------------------------
REM start C:\Users\Public\Documents\Vector\vFlash\10\Demos\CAN\Simulation\DiagnosticImitator.exe
echo.

echo ------------------------------------
echo Flash ECU
echo ------------------------------------
.\vFlash\Release\vFlashCIAutomationExampleConsoleApp.exe "path=%VFLASHPROJECT%"
set retVal=%ERRORLEVEL%
echo.

echo ------------------------------------
echo Interpret Return Code
echo ------------------------------------
echo "Return Code: %retVal%" 
IF %retVal% == 0 (
    echo "Success"
) ELSE ( 
    IF %retVal% == 10 (
        echo "PathFailure"
    ) ELSE ( 
        IF %retVal% == 20 (
            echo "InitializeFailure"
        ) ELSE ( 
            IF %retVal% == 30 (
                echo "LoadProjectFailure"
            ) ELSE ( 
                IF %retVal% == 40 (
                    echo "ReprogrammingFailure"
                ) ELSE ( 
                    IF %retVal% == 50 (
                        echo "UnloadFailure"
                    ) ELSE ( 
                        IF %retVal% == 60 (
                            echo "DeinitializeFailure"
                        ) ELSE ( 
                            echo "Unknown"
                        ) 
                    ) 
                ) 
            ) 
        ) 
    ) 
) 
echo.

REM Check for any error
if %errorlevel% neq 0 (
    echo Error detected, exiting with code %errorlevel%.
    exit /b %errorlevel%
)

echo ------------------------------------
echo Stop ECU Simulation
echo ------------------------------------
REM taskkill /im DiagnosticImitator.exe /F
echo.