<!-- markdownlint-disable -->

<div align="center">

<img alt="LOGO" src="./Icons/result.png" width="256" height="256" />

# BeepMusic

V 2.1.2.0 终端版本（其实只有终端版，嘻嘻）

<br>
<div>
    <img alt="C++" src="https://img.shields.io/badge/C++-17-%2300599C?logo=cplusplus">
</div>
<div>
    <img alt="platform" src="https://img.shields.io/badge/platform-Windows-blueviolet">
</div>
<div>
    <img alt="license" src="https://img.shields.io/github/license/xiaoditx/BeepMusic">
    <img alt="commit" src="https://img.shields.io/github/commit-activity/m/xiaoditx/BeepMusic">
</div>
<div>
    <img alt="stars" src="https://img.shields.io/github/stars/xiaoditx/BeepMusic?style=social">
    <img alt="GitHub all releases" src="https://img.shields.io/github/downloads/xiaoditx/BeepMusic/total?style=social">
</div>
</div>
<br>

<!-- markdownlint-restore -->

[跳转到开发者帮助](#开发者帮助)

## 功能介绍

一款可以将简谱转换为频率和时长的软件，转换结果可供Beep函数使用，使蜂鸣器实现奏乐效果

## 自行编译方式

- **法一**：运行根目录下的`build.bat`文件，该文件会在release目录下生成两个可执行文件，分别是64位和32位，前者需要安装有`g++`，后者需要安装有`i686-w64-mingw32-g++`，如果没有前者，编译不进行，没有后者，则只编译64位版本
- **法二**：运行MakeExe.bat，生成调试版
- **法三**：使用编辑器打开build.bat，把不想要的位数版本删掉（在文档下方，已用注释分割出）

## 简谱表示规则

**基本音符**：1(do), 2(re), 3(mi), 4(fa), 5(sol), 6(la), 7(si), 0(休止符)

**前缀**：调整音高，`+`升高八度，`-`降低八度（可叠加，如`++5`）

**后缀**：

用于调整单个音的时值

- `_`：减时线（每增加一个，时值减半）

- `-`：增时线（每增加一个，时值加倍）

- `.`：附点（时值增加50%，最多两个）

- `~`：延音线（连接相同音高的连续音符使之合并）

**速度设置**：`t=x;`（x拍/分钟，默认60），此值为BPM值，简谱一般会提供，不提供的也有参考信息进行查询，一些专业软件也提供检测功能

## 示例

《call of silence》

参考[Call of Silence简谱](https://www.cangqiang.com.cn/d/39975.html)，基本遵循原谱内容，在后半部分和前面的细节部分做了一定的调整

下面是标准的速度版本：

```
t=72; -6_ 3_ 3. 3_ -7. -6__ 1-. -6_ 3_ 3. 3_ 7. +1__ 3-. 6_ +3_ +3. +3_ 7. +1__ 5-. 5_ 3__ 5-. +2_ +1__ +2.. +1__. 6-. 0--- 3_ 2_ 2_ 1_ 1_ 5_ 1 -7_ 1-. 3_ 2_ 2_ 1_ 1_ 3_ 2 3_ 1-. 3_ 2_ 2_ 1_ 1_ 5_ 5_ 5_ -7_ 1-. -6_ 1_ 2 2_ 1_ 2_ 3_ 2_ 2 1. 0 0_ +1_ 7_ 3__ 6. 0_ +1_. 7_ 3__ 1. 0_ +1_ 7_ 3__ 6 6__  7 +2__ +1. 0_ +1_ 7 3__ 6_. 0_ +1_ 7_ 3__ 1_- 0_ +1_ 7_ +1__ +2 +3_ +3_. +1_ 7-
```

对于外放，蜂鸣器可能会吞掉一些声音，`t=45;`可能更合适

## 软件操作

初始输出如下：

```
===============================================
        C++ 简谱转Beep播放器 (增强版)
===============================================

 当前曲谱: t=120; 1 2 3 4 5 6 7 #1 +1

 音符解析结果:
 =============================================
  记谱    频率(Hz)   时长(ms)   类型
  ------------------------------------------
  1         261       500       音符
  2         293       500       音符
  3         329       500       音符
  4         349       500       音符
  5         392       500       音符
  6         440       500       音符
  7         493       500       音符
  #1        277       500       音符 (升半音)
  +1        523       500       音符
 =============================================

 控制选项:
  [P] 播放音乐        [H] 帮助文本
  [I] 自定义曲谱      [Q] 退出程序
 请选择:
```
其中

- 按下`P`，播放当前乐谱
- 按下`H`，可查看帮助文本
- 按下`I`，可输入自定义曲谱
- 按下`Q`，退出软件

按下`I`后，如果是误触，可以输入return（大小写不敏感）来退出录入状态，原本的曲谱可以保留

软件初次启动时会注册Ctrl+Alt+Shift+S的热键，乐曲播放时可使用此热键停止

默认设置下，按下`P`会看到这样的输出：

```cpp
 请选择:
  播放中... (按任意键停止)
  Play: 1        => Freq: 261   Hz, Duration: 500ms
  Play: 2        => Freq: 293   Hz, Duration: 500ms
  Play: 3        => Freq: 329   Hz, Duration: 500ms
  Play: 4        => Freq: 349   Hz, Duration: 500ms
  Play: 5        => Freq: 392   Hz, Duration: 500ms
  Play: 6        => Freq: 440   Hz, Duration: 500ms
  Play: 7        => Freq: 493   Hz, Duration: 500ms
  Play: #1       => Freq: 277   Hz, Duration: 500ms
  Play: +1       => Freq: 523   Hz, Duration: 500ms
按任意键以继续...
```

`play`表示发出声响的音符，后面跟着音符的原文是便于查找，`Freq`标记声音频率，`Duration`标记持续时间

特殊的，如下

```
0
Rest: 0 => Duration: 1000ms
```
对于休止符，输出`Rest`，`Freq`参数会被省略

----

## 播放帮助

对于连续播放短声音困难的硬件，建议使用耳机将蜂鸣器转为电脑内音，经过测试，通常的设备在播放「千本桜」（t=180）时，即使使用耳机，仍然会有声音是无法放出的，因此可以采用`t=45;`参数播放，录制结果后对结果加速4.2倍左右

## 开发者帮助

`HELPS`文件夹下是项目帮助，有些教程文档（我怕我自己忘了怎么写了放进去的），其中[Introduce.md](./HELPS/Introduce.md)会介绍项目的整体结构、各个文件的功能
