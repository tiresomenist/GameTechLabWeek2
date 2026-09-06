@echo off
setlocal
pushd "%~dp0.."
where cl >nul 2>nul
if errorlevel 1 (
    echo Run this script from a Visual Studio Developer Command Prompt.
    popd
    exit /b 1
)
if not exist obj\QuaternionTests mkdir obj\QuaternionTests
cl /nologo /EHsc /std:c++20 /utf-8 /I GameTechlabWeek2 /Foobj\QuaternionTests\ /Feobj\QuaternionTests\check.exe tests\QuaternionTests.cpp GameTechlabWeek2\FQuaternion.cpp GameTechlabWeek2\Matrix.cpp GameTechlabWeek2\FVector.cpp
if errorlevel 1 (
    popd
    exit /b 1
)
obj\QuaternionTests\check.exe
set testExit=%errorlevel%
popd
exit /b %testExit%
