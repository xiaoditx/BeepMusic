#include"../head/mainfunc.h"
#include<conio.h>
#include<windows.h>
#include<algorithm>

void handlePlay(const std::vector<Note>& notes) {
    std::cout << "\n  播放中... (按任意键停止)\n";
    playNotes(notes);// 播放当前音符列表
    std::cout << "按任意键以继续..." << std::endl;
    _getch();// _getch在控制台可以伪装一切按键操作（仅字母键），嘻
}

void handleInput(std::string& sheet) {
    std::cout << "\n  输入新曲谱: ";
    std::string user_in;// 这个名字应该都能看懂吧
    std::getline(std::cin, user_in);// 整行读入（一开始写是cin读的还好奇为什么只发出来一个音...）
    std::transform(user_in.begin(), user_in.end(), user_in.begin(), toupper);
    // 全部转换到大写（欸不对，play_core没适配？）（好了改回来了）
    if (user_in != "RETURN") sheet = user_in;// 终止输入指令
    // 我还考虑加入一个“不采纳指令”，这样就可以加在任意位置而不需要删掉一整行再打return了
}

void handleHelp() {
    std::cout << "\nCtrl+Alt+Shift+S可以暂停音乐哦\n其他的没写(\n";
    // 什么？其它的帮助？看readme啊，真懒啊，杂鱼~
    std::cout << "按任意键以继续..." << std::endl;
    _getch();
}

void handleInvalidInput() {
    std::cout << "\n  无效选项，重新选择\n";
    Sleep(1000);
    // 后期要改成自定义指令咯
}