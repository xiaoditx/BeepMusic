#pragma once
#include<iostream>
#include<map>

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