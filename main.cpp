#include "head/function.h"
#include "head/mainfunc.h"
#include <conio.h>

// 本文件盛放main函数
int main() {
    // 设置控制台输出为UTF-8
    // SetConsoleOutputCP(65001);//疑似不大直观
    SetConsoleOutputCP(CP_UTF8);
    //print_hello();// 测试用的来着，不删了吧，注释掉留个纪念
    //初始化与变量准备
    if(!hotkey())Sleep(5000);// 热键注册失败的话会停五秒显示错误信息
    std::string sheet = "T=120; 1 2 3 4 5 6 7 #1 +1";//初始乐谱
    std::vector<Note> notes;//初始化notes变量，盛放转化后的乐谱
    //程序主循环
    while (true) {
        //分析当前的乐谱
        notes = parseSheetMusic(sheet);
        displayUI(sheet, notes);//展示分析结果
        //接受用户按键
        char choice=toupper(_getch());
        //分析按键
        switch (choice) {
            case 'P': handlePlay(notes); break;
            case 'I': handleInput(sheet); break;
            case 'Q': return 0;
            case 'H': handleHelp(); break;
            default: handleInvalidInput(); break;
        }
    }
    return 0;
}