#include"../head/playcore.h"
#include"../head/note.h"
#include<windows.h>
#include<cmath>
#include<vector>
#include<sstream>
#include<iomanip>


// 解析单个音符
Note parseNote(const std::string& noteStr, int tempo) {
    if (noteStr.empty()) {
        return {0, 0, true, "", false};
    }

    // 下面是音乐的事情了，这我就不清楚了，所以不会怎么加注释了

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
    // 默认速度60
    int tempo = 60;

    // 查找并设置速度
    size_t tempoPos = sheet.find("T=");
    // 记录曲谱（不是为什么要单独搞个变量，初版让DeepSeek写的我也没参与[算了还是往下看吧...]）
    std::string notesPart = sheet;

    if (tempoPos != std::string::npos) {
        size_t endPos = sheet.find(';', tempoPos);//记录分号位置(速度结尾位置)
        if (endPos != std::string::npos) {
            tempo = stoi(//获取用户自定义速度并记录进tempo
                sheet.substr(
                    tempoPos + 2,// 头+2，略过“t=”
                    endPos - tempoPos - 2// 尾-头+2，需要选取的长度
                )
                // 写麻烦了，设定上t=只能在开头出现的来着
            );
            notesPart = sheet.substr(endPos + 1);// 截取掉开头速度标记的曲谱
        }
    }


    // 下面开始分割音符喵

    // 定义iss，内容为notesPart，可以直接一个个读取（其实我一开始想的是sscanf但是既然大模型都那么说了，嘿嘿）
    std::istringstream iss(notesPart);
    std::vector<Note> notes;// 曲谱解析结果盛放在这里
    std::string token;// 单个音符存放变量（string还是有点太大了，要我说char[10]就行）

    while (iss >> token) {
        // 跳过空标记(诶这样还能读到空？算了可能是防御性编程，留着吧)
        if (token.empty()) continue;
        Note note = parseNote(token, tempo);// 根据音符和速度计算后存入note变量
        // 话说这里可以优化一下啊，tempo作为全局变量就可以不用传了来着
        notes.push_back(note);
    }

    // 处理延音线
    std::vector<Note> mergedNotes;// 存放延音线处理后的乐谱
    for (size_t i = 0; i < notes.size(); i++) {
        // notes[i]当前音符，notes[i+1]下一个音符
        // 我真得防御性编程了（指使用i+1[notes]）
        if (notes[i].hasTie && i + 1 < notes.size() && // 判断下一个位置有没有音符
            !notes[i+1].is_rest && !notes[i].is_rest && // 判断是不是前后都不是休止符
            abs(notes[i].freq - notes[i+1].freq) < 1.0) {// 你敢信我就鼠标在abs上悬浮一下就查了半天constexpr是什么
            
            // 合并延音线连接的两个音符
            Note merged = notes[i];
            merged.duration_ms += notes[i+1].duration_ms;// 合并时长
            merged.notation = notes[i].notation + "~" + notes[i+1].notation;
            merged.hasTie = notes[i+1].hasTie; // 如果下面的音符还有延音线就保留
            mergedNotes.push_back(merged);
            i++; // 跳过下一个音符
        } else {
            mergedNotes.push_back(notes[i]);// 直接放入
        }
    }

    return mergedNotes;// 返回结果
}

// 播放音符列表
void playNotes(const std::vector<Note>& notes) {
    for (const auto& note : notes) {
        MSG message_get;
        if(PeekMessage(&message_get,NULL,0,0,PM_REMOVE)){
            // 这个版本一定是Ctrl+Alt+Shift+S，后续还会有音符调整等等（不过我在考虑全部收进这一个快捷键）
            std::cout<<"当前播放已终止\n";
            break;
        }
        std::cout<<"test";
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

std::string interrupt(){
    // 空
    return "no";
}