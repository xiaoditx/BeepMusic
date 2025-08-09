# 项目结构介绍

结构与与功能

```text
root/
├── .vscode/                vscode配置文件
│   └── setting.json
│   └── tasks.json
├── head/
│   └── function.h          封装部分常用的函数（的声明部分）
│   └── mainhead.h          头文件（提供大部分cpp）+函数声明（提供main.cpp）
├── src_c/
│   ├── function.cpp        封装功能函数的定义，简化开发（如彩色输出）
│   ├── play_core.cpp       存放核心解析、演奏函数
│   ├── test.cpp            测试文件（保留做纪念也可随时启用进行测试）
│   └── UI.cpp              UI显示（其实就是输出看起来像是UI的东西）
├── 备忘.txt                更新备忘录，记录需要的功能等
├── BeepMusic_alpha.exe     开发调试版本的编译结果
├── introduce.md            本文件，项目介绍（开发版），向开发者介绍项目细节
├── LICENSE                 开源协议
├── main.cpp                主函数放置的文件，编译在此处进行
├── MakeExe.bat             编译用的批处理，不使用VScode的开发者可以借此编译
└── main.cpp
```