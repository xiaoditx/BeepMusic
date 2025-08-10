#include "../head/function.h"
#include<vector>
#include<string>

void y_print(const char* str, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(str);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
bool hotkey() {
    if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x53)) {
        return true;
    } else {
        DWORD er_code = GetLastError();
        std::string message;
        
        wchar_t* er_message = nullptr;
        DWORD result = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            er_code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPWSTR>(&er_message),
            0, NULL
        );

        if (result > 0 && er_message != nullptr) {
            // 将宽字符串转换为UTF-8
            int utf8_size = WideCharToMultiByte(
                CP_UTF8, 0, 
                er_message, -1, 
                NULL, 0, 
                NULL, NULL
            );
            
            if (utf8_size > 0) {
                std::vector<char> buffer(utf8_size);
                WideCharToMultiByte(
                    CP_UTF8, 0, 
                    er_message, -1, 
                    buffer.data(), utf8_size, 
                    NULL, NULL
                );
                message = buffer.data();
            } else {
                message = "Failed to convert error message to UTF-8";
            }
            
            LocalFree(er_message); // 释放系统分配的内存
        } else {
            message = "未知错误: 无法获取系统错误描述";
        }

        // 使用ANSI转义序列输出彩色错误信息
        printf("\n\033[1;4;5;31m注册热键时错误,可能会引起暂停失效\n错误代码: %lu\n错误信息: %s\033[0m", 
               er_code, message.c_str());
        
        return false;
    }
}