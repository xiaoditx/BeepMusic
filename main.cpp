#include "inc_and_func.h"

// 音符结构体
struct Note {
    double freq;       // 频率(Hz)
    int duration_ms;   // 时长(毫秒)
    bool is_rest;      // 是否休止符
    std::string notation;   // 原始记谱
    bool hasTie;       // 是否有延音线
};

// 中音区音符频率 (C4-B4)
const std::map<char, double> BASE_FREQ = {
    {'1', 261.63}, // C4
    {'2', 293.66}, // D4
    {'3', 329.63}, // E4
    {'4', 349.23}, // F4
    {'5', 392.00}, // G4
    {'6', 440.00}, // A4
    {'7', 493.88}  // B4
};

// 解析单个音符
Note parseNote(const std::string& noteStr, int tempo) {
    if (noteStr.empty()) {
        return {0, 0, true, "", false};
    }

    // 解析音高调整
    int octaveShift = 0;
    double semitoneShift = 0.0; // 升半音
    size_t pos = 0;

    // 解析升半音
    if (pos < noteStr.size() && noteStr[pos] == '#') {
        semitoneShift = 1.0;
        pos++;
    }

    // 解析八度调整
    while (pos < noteStr.size() && (noteStr[pos] == '+' || noteStr[pos] == '-')) {
        octaveShift += (noteStr[pos] == '+') ? 1 : -1;
        pos++;
    }

    // 解析音符数字
    char noteChar = (pos < noteStr.size()) ? noteStr[pos] : '0';
    pos++;

    // 检查延音线
    bool hasTie = false;
    if (pos < noteStr.size() && noteStr[pos] == '~') {
        hasTie = true;
        pos++;
    }

    // 解析时值符号
    int dots = 0;
    int dashes = 0;
    int underlines = 0;

    while (pos < noteStr.size()) {
        switch (noteStr[pos]) {
            case '.': dots++; break;
            case '-': dashes++; break;
            case '_': underlines++; break;
        }
        pos++;
    }

    // 计算频率
    double freq = 0.0;
    if (noteChar == '0') {
        freq = 0; // 休止符
    } else if (BASE_FREQ.find(noteChar) != BASE_FREQ.end()) {
        freq = BASE_FREQ.at(noteChar) * pow(2.0, octaveShift);
        // 应用升半音
        if (semitoneShift > 0) {
            freq *= pow(2.0, semitoneShift/12.0);
        }
    }

    // 计算时值（拍）
    double duration_beats = pow(2.0, dashes) / pow(2.0, underlines);
    if (dots == 1) duration_beats *= 1.5;    // 附点
    else if (dots >= 2) duration_beats *= 1.75; // 双附点

    // 转换为毫秒
    int duration_ms = static_cast<int>((duration_beats * 60 * 1000) / tempo);

    // 创建并返回Note对象
    Note result;
    result.freq = freq;
    result.duration_ms = duration_ms;
    result.is_rest = (noteChar == '0');
    result.notation = noteStr;
    result.hasTie = hasTie;
    return result;
}

// 解析并播放简谱
std::vector<Note> parseSheetMusic(const std::string& sheet) {
    // 默认速度
    int tempo = 60;

    // 查找并设置速度
    size_t tempoPos = sheet.find("t=");
    std::string notesPart = sheet;
    if (tempoPos != std::string::npos) {
        size_t endPos = sheet.find(';', tempoPos);
        if (endPos != std::string::npos) {
            tempo = stoi(sheet.substr(tempoPos + 2, endPos - tempoPos - 2));
            notesPart = sheet.substr(endPos + 1);
        }
    }

    // 分割音符
    std::istringstream iss(notesPart);
    std::vector<Note> notes;
    std::string token;

    while (iss >> token) {
        // 跳过空标记
        if (token.empty()) continue;

        Note note = parseNote(token, tempo);
        notes.push_back(note);
    }

    // 处理延音线
    std::vector<Note> mergedNotes;
    for (size_t i = 0; i < notes.size(); i++) {
        if (notes[i].hasTie && i + 1 < notes.size() && 
            !notes[i+1].is_rest && !notes[i].is_rest &&
            abs(notes[i].freq - notes[i+1].freq) < 1.0) {
            // 合并延音线连接的两个音符
            Note merged = notes[i];
            merged.duration_ms += notes[i+1].duration_ms;
            merged.notation = notes[i].notation + "~" + notes[i+1].notation;
            merged.hasTie = notes[i+1].hasTie; // 检查下一个音符是否还有延音线

            mergedNotes.push_back(merged);
            i++; // 跳过下一个音符
        } else {
            mergedNotes.push_back(notes[i]);
        }
    }

    return mergedNotes;
}

// 播放音符列表
void playNotes(const std::vector<Note>& notes) {
    for (const auto& note : notes) {
        if (note.is_rest) {
            std::cout << "  Rest: " << std::setw(8) << std::left << note.notation 
                 << " => Duration: " << note.duration_ms << "ms\n";
            Sleep(static_cast<DWORD>(note.duration_ms));
        } else {
            std::cout << "  Play: " << std::setw(8) <<std:: left << note.notation 
                 << " => Freq: " << std::setw(6) << static_cast<int>(note.freq) 
                 << "Hz, Duration: " << note.duration_ms << "ms\n";
            Beep(static_cast<DWORD>(note.freq), static_cast<DWORD>(note.duration_ms));
        }
    }
}

// 显示控制台界面
void displayUI(const std::string& sheet, const std::vector<Note>& notes) {
    system("cls");

    // 显示标题
    std::cout << "===============================================\n";
    std::cout << "        C++ 简谱转Beep播放器 (增强版)\n";
    std::cout << "===============================================\n\n";

    // 显示当前曲谱
    std::cout << " 当前曲谱: " << sheet << "\n\n";

    // 显示音符列表
    std::cout << " 音符解析结果:\n";
    std::cout << " =============================================\n";
    std::cout << "  记谱    频率(Hz)   时长(ms)   类型\n";
    std::cout << "  ------------------------------------------\n";

    for (const auto& note : notes) {
        std::cout << "  " << std::setw(8) << std::left << note.notation << "  ";

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

    std::cout << " =============================================\n\n";

    // 显示控制选项
    std::cout << " 控制选项:\n";
    std::cout << "  [P] 播放音乐        [S] 停止播放\n";
    std::cout << "  [R] 重新输入曲谱    [Q] 退出程序\n";
    std::cout << "  [1] 示例: 小星星   [2] 示例: 欢乐颂\n";
    std::cout << "  [3] 示例: 生日快乐 [4] 示例: 音阶\n\n";
    std::cout << " 请选择: ";
}

int main() {
    // 设置控制台输出为UTF-8
    SetConsoleOutputCP(65001);
    //初始化与变量准备
    std::string sheet = "t=120; 1 2 3 4 5 6 7 #1 +1";//初始乐谱
    std::vector<Note> notes;//乐谱经过转换会流向这个变量（容器？）
    //程序主循环
    while (true) {
        //先分析当前的乐谱
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

            case 'S': // 停止
                // Beep停止在Windows中没有直接API，这里只是跳过
                std::cout << "\n  停止播放\n";
                Sleep(1000);
                break;

            case 'R': // 重新输入
                std::cout << "\n  输入新曲谱 (如: t=100; 1 2 3 4 5 6 7): ";
                std::getline(std::cin, sheet);
                break;

            case '1': // 小星星
                sheet = "t=120; 1 1 5 5 6 6 5~ 4 4 3 3 2 2 1~";
                break;

            case '2': // 欢乐颂
                sheet = "t=100; 3 3 4 5~ 5 4 3 2~ 1 1 2 3~ 3. 2 2~";
                break;

            case '3': // 生日快乐
                sheet = "t=120; 5 5 6 5~ #1 7~ 5 5 6 5~ 2 #1~ 5 5 #5 #4~ #1 7 6~";
                break;

            case '4': // 音阶
                sheet = "t=180; 1 2 3 4 5 6 7 #1 +1 7 6 5 4 3 2 1";
                break;

            case 'Q': // 退出
                return 0;

            case 'H': // 帮助信息
                //还没写OvO

            default:
                std::cout << "\n  无效选项，请重新选择\n";
                Sleep(1000);
                break;
        }
    }

    return 0;
}