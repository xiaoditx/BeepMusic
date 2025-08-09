#include "../head/function.h"

void y_print(const char* str, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(str);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
bool hotkey(){
    if(RegisterHotKey(NULL,1,MOD_ALT | MOD_CONTROL,0x53)){

    }else{
        int Error=GetLastError();
        printf("\n\033[1;4;5;31m注册热键时错误，可能会引起暂停失效\n，错误代码%d\033[0m",Error);
    }
    return true;// 此功能开发阶段的最后一定要删除此内容！！
}