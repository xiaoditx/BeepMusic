#include"../head/mainhead.h"

void handlePlay(const std::vector<Note>& notes) {
    std::cout << "\n  播放中... (按任意键停止)\n";
    playNotes(notes);
    std::cout << "按任意键以继续..." << std::endl;
    _getch();
}

void handleInput(std::string& sheet) {
    std::cout << "\n  输入新曲谱: ";
    std::string user_in;
    std::getline(std::cin, user_in);
    std::transform(user_in.begin(), user_in.end(), user_in.begin(), toupper);
    if (user_in != "RETURN") {
        sheet = user_in;
    }
}

void handleHelp() {
    std::cout << "\nCtrl+Alt+Shift+S可以暂停音乐哦\n其他的没写(\n";
    std::cout << "按任意键以继续..." << std::endl;
    _getch();
}

void handleInvalidInput() {
    std::cout << "\n  无效选项，重新选择\n";
    Sleep(1000);
}