# 项目结构介绍

结构与文件功能

```text
root/
├── .vscode/                vscode配置文件
│   ├── setting.json
│   └── tasks.json
├── head/
│   ├── function.h          封装部分常用的函数（的声明部分）
│   └── mainhead.h          头文件（提供大部分cpp）+函数声明（提供main.cpp）
├── HELPS/
│   ├── Color_Print.md      彩色输出帮助
│   ├── Hot_Key.md          热键帮助
│   ├── RC_help.md          resources.rc文件的一些帮助内容
│   └── README.md        项目介绍
├── Icons/
│   ├── favicon.ico         同上级目录的icon.ico，仅名称不同
│   ├── ori.jpg             软件图标原图
│   └── result.png          软件图标透明图
├── release/                编译结果（使用build.bat的）
│   ├── installer/                 用于放置安装包相关内容
│   │   ├── install_win_64.exe     安装包（编译结果） 
│   │   └── installer_creator.iss  源码（模板）
│   ├── BeepMusic_release_win_x64.exe
│   └── BeepMusic_release_win_x86.exe
├── src_c/
│   ├── config.cpp          配置文件读写
│   ├── function.cpp        封装功能函数的定义，简化开发（如彩色输出）
│   ├── mods.cpp            菜单栏选项对应激活的函数
│   ├── play_core.cpp       存放核心解析、演奏函数
│   ├── test.cpp            测试文件（保留做纪念也可随时启用进行测试）
│   └── UI.cpp              UI显示（其实就是输出看起来像是UI的东西）
├── tools/
│   └── XD开发工具-T1
│       ├── 开发工具.exe     热键查询+鼠标查询工具（之前用易语言写的小玩意）
│       ├── 源码.e           程序源码，遵守本仓库协议开源
│       ├── iext.fnr        支持库文件
│       └── krnln.fnr       支持库文件
├── 备忘.txt                 更新备忘录，记录需要的功能等
├── BeepMusic_alpha.exe     开发调试版本的编译结果
├── build.bat               编译最终版本用的批处理，该批处理会同时编译resources.rc
├── icon.ico                软件图标
├── LICENSE                 开源协议
├── main.cpp                主函数放置的文件，编译在此处进行
├── MakeExe.bat             生成调试版用的批处理，不使用VScode的开发者可以借此编译
├── README.md               本项目的readme
└── resources.rc            资源文件，放置图标信息、软件信息
```

# ini结构说明

还没写 