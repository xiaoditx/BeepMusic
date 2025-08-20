#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "note.h"

extern void print_hello();// 纪念品喵

// play_core的函数
extern Note parseNote(const std::string& noteStr, int tempo);
extern std::vector<Note> parseSheetMusic(const std::string& sheet);
extern void playNotes(const std::vector<Note>& notes);

// UI的函数
extern void displayUI(const std::string& sheet, const std::vector<Note>& notes);

// mods的函数
void handlePlay(const std::vector<Note>& notes);
void handleInput(std::string& sheet);
void handleHelp();
void handleInvalidInput();
