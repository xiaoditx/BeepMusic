#include "../head/note.h"
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>


// 控制台界面显示
void displayUI(const std::string& sheet, const std::vector<Note>& notes) {

    system("cls");

    // 显示标题
    std::cout << "\033[33m===============================================\033[0m\n";
    std::cout << "        \033[34mC++ 简谱转Beep播放器 (V2.1.1.3)\033[0m\n";// 发现每次都忘记改版本号
    std::cout << "\033[33m===============================================\033[0m\n\n";
    
    // 显示当前曲谱
    std::cout << " 当前曲谱: \033[32m" << sheet << "\033[0m\n\n";

    // 显示音符列表
    std::cout << " 音符解析结果:\n";
    std::cout << " \033[36m=============================================\033[0m\n";
    std::cout << "  记谱    频率(Hz)   时长(ms)   类型\n";
    std::cout << "  \033[36m------------------------------------------\033[0m\n";

    // 下面就是DeepSeek写的了，看不懂别找我，我对什么setw不(懒)感(得)兴(研)趣(究)

    for (const auto& note : notes) {
        std::cout << "\033[31m  " << std::setw(8) << std::left << note.notation << "\033[0m  ";

        std::cout<<"\033[32m";

        if (note.is_rest) {
            std::cout << std::setw(8) << " " << "  " 
                 << std::setw(8) << note.duration_ms << "  休止符\n";
        } else {
            std::cout << std::setw(8) << static_cast<int>(note.freq) << "  " 
                 << std::setw(8) << note.duration_ms << "  音符";

            if (note.notation.find('#') != std::string::npos) {
                std::cout << " (升半音)";
            }

            if (note.notation.find('~') != std::string::npos) {
                std::cout << " (延音)";
            }

            std::cout << "\n";
        }
    }

    std::cout<<"\033[0m";
    std::cout << " \033[36m=============================================\033[0m\n\n";

    // 显示控制选项
    std::cout << " 控制选项:\n";
    std::cout << "  [P] 播放音乐        [H] 帮助文本\n";
    std::cout << "  [I] 自定义曲谱      [Q] 退出程序\n";
    std::cout << " 请选择: ";
}