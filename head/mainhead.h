#ifndef A_H
#define A_H
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
#include<map>
#include<windows.h>
#include<algorithm>
#include<conio.h>
#include<iomanip>

extern void print_hello();

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

extern Note parseNote(const std::string& noteStr, int tempo);
extern std::vector<Note> parseSheetMusic(const std::string& sheet);
extern void playNotes(const std::vector<Note>& notes);

extern void displayUI(const std::string& sheet, const std::vector<Note>& notes);




extern void m_play(std::vector<Note>& notes);
extern void m_set_sheet(std::string* sheet);
extern void m_exit();
extern void m_help();
extern void m_default();
#endif