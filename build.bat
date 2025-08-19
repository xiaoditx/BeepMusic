@echo off
setlocal enabledelayedexpansion

:: һЩ���������Կ�����ֲ�������Ŀ��
set PROGRAM_NAME=BeepMusic
set OUTPUT_X64=%PROGRAM_NAME%_release_win_x64.exe
set OUTPUT_X86=%PROGRAM_NAME%_release_win_x86.exe

:: �������Ŀ¼
if not exist "release\" mkdir release

:: ����Ҫ�ļ�
if not exist "main.cpp" (
    echo ����: �Ҳ��� main.cpp
    goto :cleanUP
)
if not exist "resources.rc" (
    echo ����: �Ҳ��� resources.rc
    goto :cleanUP
)

:: ��������
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo ����: δ�ҵ� g++ ����������ȷ���Ѱ�װ�����ӵ� PATH
    goto :cleanUP
)

:: ���� 64 λ�汾

:: ===================================

echo ���ڱ��� 64 λ�汾...

echo ���ڱ�����Դ�ļ�
windres resources.rc -F pe-x86-64 -o resources_x64.o
:: �洢��ǰ�����루����ᱻechoˢ��0��
set RES64_ERR=%errorlevel%
echo ���뷵�أ�%RES64_ERR%

if %RES64_ERR% neq 0 (
    echo ����: ��Դ�ļ�64λ����ʧ��
    goto :cleanUP
)
echo ��Դ�ļ�����ɹ�

echo ���ڱ�����������
g++ -m64 -fdiagnostics-color=always src_c/*.cpp main.cpp resources_x64.o -I src_c -I head -o release/%OUTPUT_X64% -mconsole -O2
:: ���ɴ洢
set COMP64_ERR=%errorlevel%
echo ���뷵�أ�%COMP64_ERR%

if %COMP64_ERR% neq 0 (
    echo ����: x64�������ʧ��
    goto :cleanUP
)
echo ������ɣ������� release/%OUTPUT_X64%

:: ���� 32 λ�汾

:: ===================================

echo ���ڱ��� 32 λ�汾...
echo ���ڱ�����Դ�ļ�
windres resources.rc -F pe-i386 -o resources_x86.o
set RES32_ERR=%errorlevel%
echo ���뷵�أ�%RES32_ERR%
if %RES32_ERR% neq 0 (
    echo ����: ��Դ�ļ�32λ����ʧ��
    goto :cleanUP
)
echo ��Դ�ļ�����ɹ�

echo ���ڱ�����������
i686-w64-mingw32-g++ -m32 -fdiagnostics-color=always main.cpp resources_x86.o src_c/*.cpp -I src_c -I head -o release/%OUTPUT_X86% -mconsole -O2
set COMP32_ERR=%errorlevel%
echo ���뷵�أ�%COMP32_ERR%
if %COMP32_ERR% neq 0 (
    echo ����: x86�������ʧ��
    goto :cleanUP
)
echo ������ɣ������� release/%OUTPUT_X86%

:: ������ʱ�ļ�
del resources_x64.o 2>nul
del resources_x86.o 2>nul

echo.
echo ����ɹ�!
echo �����ļ�:
echo   - %OUTPUT_X64% (64λ����̨����)
echo   - %OUTPUT_X86% (32λ����̨����)
pause
exit /b 0

:cleanUP
del resources_x64.o 2>nul
del resources_x86.o 2>nul
echo.
echo ��������з���������������ʱ�ļ�
pause
exit /b 1