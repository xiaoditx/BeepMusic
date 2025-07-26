#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <windows.h> // for Beep

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
void parseNote(const std::string& noteStr, int tempo, double& freq, int& duration_ms) {
    if (noteStr.empty()) {
        freq = 0;
        duration_ms = 0;
        return;
    }

    // 解析音高调整
    int octaveShift = 0;
    size_t pos = 0;
    while (pos < noteStr.size() && (noteStr[pos] == '+' || noteStr[pos] == '-')) {
        octaveShift += (noteStr[pos] == '+') ? 1 : -1;
        pos++;
    }

    // 解析音符数字
    char noteChar = (pos < noteStr.size()) ? noteStr[pos] : '0';
    pos++;

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
    if (noteChar == '0') {
        freq = 0; // 休止符
    } else if (BASE_FREQ.find(noteChar) != BASE_FREQ.end()) {
        freq = BASE_FREQ.at(noteChar) * pow(2.0, octaveShift);
    } else {
        freq = 0; // 无效音符
    }

    // 计算时值（拍）
    double duration_beats = pow(2.0, dashes) / pow(2.0, underlines);
    if (dots == 1) duration_beats *= 1.5;    // 附点
    else if (dots >= 2) duration_beats *= 1.75; // 双附点

    // 转换为毫秒
    duration_ms = static_cast<int>((duration_beats * 60 * 1000) / tempo);
}

// 解析并播放简谱
void play(const std::string& sheet) {
    // 默认速度
    int tempo = 60;

    // 查找并设置速度
    size_t tempoPos = sheet.find("t=");
    std::string notesPart = sheet;
    if (tempoPos != std::string::npos) {
        size_t endPos = sheet.find(';', tempoPos);
        if (endPos != std::string::npos) {
            tempo = std::stoi(sheet.substr(tempoPos + 2, endPos - tempoPos - 2));
            notesPart = sheet.substr(endPos + 1);
        }
    }

    // 分割音符
    std::istringstream iss(notesPart);
    std::vector<std::string> notes;
    std::string note;
    while (iss >> note) {
        notes.push_back(note);
    }

    // 播放每个音符
    for (const auto& n : notes) {
        double freq;
        int duration_ms;
        parseNote(n, tempo, freq, duration_ms);

        if (freq > 0) {
            std::cout << "Play: " << n << " => Freq: " << static_cast<int>(freq)<< "Hz, Duration: " << duration_ms << "ms\n";
            Beep(static_cast<DWORD>(freq), static_cast<DWORD>(duration_ms));
        } else {
            std::cout << "Rest: " << n << " => Duration: " << duration_ms << "ms\n";
            Sleep(static_cast<DWORD>(duration_ms));
        }
    }
}

int main() {

    std::cout<<"Welcome"<<std::endl;
    while(true){
        std::string inp;
        if(inp=="exit"){
            break;
        }else{
            std::getline(std::cin,inp);
            play(inp);
        }
    }
    return 0;
}



// 示例：C大调音阶（速度120）
//std::string sheet = "t=120; 1 1 5 5 6 6 5- 4 4 3 3 2 2 1-";
//play(sheet);

// 示例：《小星星》片段
// std::string littleStar = "t=100; 1 1 5 5 6 6 5- 4 4 3 3 2 2 1-";
// play(littleStar);
