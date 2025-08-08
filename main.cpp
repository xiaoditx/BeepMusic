#include "head/mainhead.h"

// 本文件盛放main函数

int main() {
    // 设置控制台输出为UTF-8
    // SetConsoleOutputCP(65001);//疑似不大直观
    SetConsoleOutputCP(CP_UTF8);
    //print_hello();// 测试用的来着，不删了吧，注释掉留个纪念
    //初始化与变量准备
    std::string sheet = "t=120; 1 2 3 4 5 6 7 #1 +1";//初始乐谱
    std::vector<Note> notes;//初始化notes变量，盛放转化后的乐谱
    //程序主循环
    while (true) {
        //分析当前的乐谱
        notes = parseSheetMusic(sheet);
        displayUI(sheet, notes);//展示分析结果
        //接受用户按键
        char choice = _getch();
        choice = toupper(choice);
        //分析按键
        switch (choice) {
            case 'P': // 播放
                std::cout << "\n  播放中... (按任意键停止)\n";
                playNotes(notes);
                std::cout<<"按任意键以继续..."<<std::endl;
                _getch();//等待用户输入
                break;

            case 'I': // 自定义乐谱
                std::cout << "\n  输入新曲谱: ";
                std::getline(std::cin, sheet);
                break;

            case 'Q': // 退出
                return 0;

            case 'H': // 帮助信息

                std::cout<<"别看劳资喵,劳资也不会喵,代码全是人机DeepSeek写的我会(懒)个(得)毛(写)啊";

            default:
                std::cout << "\n  无效选项，重新选择\n";
                Sleep(1000);
                break;
        }
    }

    return 0;
}