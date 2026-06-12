@echo off
setlocal enabledelayedexpansion

:: Default argument
set "APP=%~1"
if "%APP%"=="" set "APP=all"

:: Validar entrada
call :validate_input
if errorlevel 1 exit /b 1

:: Compilar módulos
if /i "%APP%"=="all" (
    for %%M in (list queue stack tree) do call :build_module %%M
) else (
    call :build_module %APP%
)

:: Executar módulos
if /i "%APP%"=="all" (
    for %%M in (list queue stack tree) do call :exec_module %%M
) else (
    call :exec_module %APP%
)

:: Finaliza
echo ✅ Build finished!!!
exit /b 0

:: Funções
:validate_input
set "VALID=all list queue stack tree"
set "FOUND=0"
for %%V in (%VALID%) do (
    if /i "%%V"=="%APP%" set "FOUND=1"
)
if "%FOUND%"=="0" (
    echo ❌ Aplicação inválida: %APP%
    echo 📋 Aplicações válidas: %VALID%
    exit /b 1
)
exit /b 0

:build_module
set "module=%~1"
set "dir=%module%"
if not exist "%dir%" (
    echo ❌ Diretório não encontrado: %dir%
    exit /b 1
)
if not exist "%dir%\build" mkdir "%dir%\build"
echo 🔧 Compilando módulo: %module% (dir: %dir%)
pushd "%dir%"
set "sources="
for %%F in (src\*.c) do set "sources=!sources! %%F"
gcc test.c !sources! -Iinclude -o build\test
set "status=!errorlevel!"
popd
if not "%status%"=="0" exit /b %status%
exit /b 0

:exec_module
set "module=%~1"
set "dir=%module%"
if not exist "%dir%\build\test.exe" (
    echo ❌ Executável não encontrado: %dir%\build\test.exe
    exit /b 1
)
echo 🚀 Executando testes para módulo: %module% (dir: %dir%)
pushd "%dir%"
build\test
set "status=!errorlevel!"
popd
if not "%status%"=="0" exit /b %status%
exit /b 0
