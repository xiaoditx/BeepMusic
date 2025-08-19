#include "../head/function.h"
#include<vector>
#include<string>

wchar_t* get_error_string(DWORD* result,DWORD er_code){
    wchar_t* er_message = nullptr;//准备指针
    *result = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | // 要求系统将搜索结果写入缓冲区
        FORMAT_MESSAGE_FROM_SYSTEM |     // 从系统消息资源表中来搜索所响应的消息
        FORMAT_MESSAGE_IGNORE_INSERTS,   // 这个我不知道是干啥的（老实）
        nullptr,er_code,GetUserDefaultLangID(),// 用户默认ID
        reinterpret_cast<LPWSTR>(&er_message),// 提供缓冲区的指针（的指针，也就是二级指针）
        // ↑ 很烦人的写法啊，说是要骗编译器让它认为是一级指针防止报错什么的
        // 具体报不报错我不清楚，懒得试，感兴趣的可以改成&er_message试试
        0, NULL
    );
    return er_message;
}

/*
1.MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT)        always simple Chinese
2.getUserDefaultLangID()                          auto mode
*/

std::string U16ToU8(DWORD result,wchar_t* er_message){
    std::string message;
    if (result > 0 && er_message != nullptr) {// 取到的结果有长度
        // 将宽字符串（UTF-16）转换为UTF-8
        // ↓获取所需长度
        int utf8_size = WideCharToMultiByte(CP_UTF8, 0, er_message, -1, NULL, 0, NULL, NULL);
        // ↑ 参二必须为0或WC_ERR_INVALID_CHARS，具体为啥我不知道（欸嘿
        if (utf8_size > 0) {// 转换结果是否为空
            std::vector<char> buffer(utf8_size);// 根据长度定义变量buffer作为缓冲区（吧）
            WideCharToMultiByte(
                CP_UTF8, 0,er_message,-1,buffer.data(),
                utf8_size, NULL,NULL
            );
            message = buffer.data();
        } else {
            message = "在将错误信息转换为UTF-8时出现错误";
        }
        LocalFree(er_message); // 释放系统分配的内存
    } else {
        message = "未知错误: 找不到对应的系统错误描述";
    }
    // 使用ANSI转义序列输出彩色错误信息
    return message;
}

void y_print(const char* str, int color)// 彩色输出
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// 句柄
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);// 设置控制台输出颜色
    printf(str);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);// 调回默认
}

bool hotkey() {// 速测热键并提供错误反馈
    if (RegisterHotKey(nullptr, 1/*这个值其实随便填的来着*/, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x53)) {
        return true;
    } else {
        DWORD er_code = GetLastError();// 获取错误码
        DWORD result_size;
        std::string message=U16ToU8(
            result_size,
            get_error_string(&result_size,er_code)
        );
        printf("\n\033[1;4;5;31m注册热键时错误,可能会引起暂停失效\n错误代码: %lu\n错误信息: %s\033[0m",er_code, message.c_str());
    }
    return 0;
}
