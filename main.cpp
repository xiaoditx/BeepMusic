#include "head/mainhead.h"
#include "head/function.h"

// 本文件盛放main函数
int main() {
    // 设置控制台输出为UTF-8
    // SetConsoleOutputCP(65001);//疑似不大直观
    SetConsoleOutputCP(CP_UTF8);
    //print_hello();// 测试用的来着，不删了吧，注释掉留个纪念
    //初始化与变量准备
    if(!hotkey()){
        Sleep(5000);
    }
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

            case 'I':{ // 自定义乐谱
                std::cout << "\n  输入新曲谱: ";
                std::string user_in;
                std::getline(std::cin,user_in);
                std::transform(user_in.begin(),user_in.end(),user_in.begin(),toupper);
                if(user_in!="RETURN"){
                    sheet=user_in;
                }
                break;
            }
            case 'Q': // 退出
                return 0;

            case 'H': // 帮助信息
                std::cout<<"\nCtrl+Alt+Shift+S可以暂停音乐哦\n其他的没写(\n";
                std::cout<<"按任意键以继续..."<<std::endl;
                _getch();//等待用户输入
                break;
            default:
                std::cout << "\n  无效选项，重新选择\n";
                Sleep(1000);
                break;
        }
    }

    return 0;
}