#pragma once
#include<string>
// 音符结构体
struct Note {
    double freq;       // 频率(Hz)
    int duration_ms;   // 时长(毫秒)
    bool is_rest;      // 是否休止符
    std::string notation;   // 原始记谱
    bool hasTie;       // 是否有延音线
};