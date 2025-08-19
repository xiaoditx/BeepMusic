@echo off
setlocal enabledelayedexpansion

:: 一些变量（可以快速移植到别的项目）
set PROGRAM_NAME=BeepMusic
set OUTPUT_X64=%PROGRAM_NAME%_release_win_x64.exe
set OUTPUT_X86=%PROGRAM_NAME%_release_win_x86.exe

:: 创建输出目录
if not exist "release\" mkdir release

:: 检查必要文件
if not exist "main.cpp" (
    echo 错误: 找不到 main.cpp
    goto :cleanUP
)
if not exist "resources.rc" (
    echo 错误: 找不到 resources.rc
    goto :cleanUP
)

:: 检查编译器
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误: 未找到 g++ 编译器，请确保已安装并添加到 PATH
    goto :cleanUP
)

:: 编译 64 位版本

:: ===================================

echo 正在编译 64 位版本...

echo 正在编译资源文件
windres resources.rc -F pe-x86-64 -o resources_x64.o
:: 存储当前错误码（否则会被echo刷成0）
set RES64_ERR=%errorlevel%
echo 编译返回：%RES64_ERR%

if %RES64_ERR% neq 0 (
    echo 错误: 资源文件64位编译失败
    goto :cleanUP
)
echo 资源文件编译成功

echo 正在编译软件主体
g++ -m64 -fdiagnostics-color=always src_c/*.cpp main.cpp resources_x64.o -I src_c -I head -o release/%OUTPUT_X64% -mconsole -O2
:: 依旧存储
set COMP64_ERR=%errorlevel%
echo 编译返回：%COMP64_ERR%

if %COMP64_ERR% neq 0 (
    echo 错误: x64程序编译失败
    goto :cleanUP
)
echo 编译完成，已生成 release/%OUTPUT_X64%

:: 编译 32 位版本

:: ===================================

echo 正在编译 32 位版本...
echo 正在编译资源文件
windres resources.rc -F pe-i386 -o resources_x86.o
set RES32_ERR=%errorlevel%
echo 编译返回：%RES32_ERR%
if %RES32_ERR% neq 0 (
    echo 错误: 资源文件32位编译失败
    goto :cleanUP
)
echo 资源文件编译成功

echo 正在编译软件主体
i686-w64-mingw32-g++ -m32 -fdiagnostics-color=always main.cpp resources_x86.o src_c/*.cpp -I src_c -I head -o release/%OUTPUT_X86% -mconsole -O2
set COMP32_ERR=%errorlevel%
echo 编译返回：%COMP32_ERR%
if %COMP32_ERR% neq 0 (
    echo 错误: x86程序编译失败
    goto :cleanUP
)
echo 编译完成，已生成 release/%OUTPUT_X86%

:: 清理临时文件
del resources_x64.o 2>nul
del resources_x86.o 2>nul

echo.
echo 编译成功!
echo 生成文件:
echo   - %OUTPUT_X64% (64位控制台程序)
echo   - %OUTPUT_X86% (32位控制台程序)
pause
exit /b 0

:cleanUP
del resources_x64.o 2>nul
del resources_x86.o 2>nul
echo.
echo 编译过程中发生错误，已清理临时文件
pause
exit /b 1