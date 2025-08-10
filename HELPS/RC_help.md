在 Windows 资源文件 (.rc) 中，这些关键字用于定义可执行文件的版本信息结构，以下是详细解释：

### 核心结构解析

1. **`FILEFLAGSMASK`**  
   - 作用：指定哪些位在 `FILEFLAGS` 字段中是有效的
   - 值：通常设置为 `VS_FFI_FILEFLAGSMASK`（预定义值 `0x3FL`）
   - 含义：表示只检查 `FILEFLAGS` 的低 6 位

2. **`FILEFLAGS`**  
   - 作用：描述文件属性标志
   - 常用值：
     - `0x0L`：正式版
     - `VS_FF_DEBUG` (0x1L)：调试版本
     - `VS_FF_PRERELEASE` (0x2L)：预发布版
     - `VS_FF_PATCHED` (0x4L)：已修补版本
     - `VS_FF_PRIVATEBUILD` (0x8L)：私有构建
   - 示例：`0x0L` 表示标准发布版本

3. **`FILEOS`**  
   - 作用：指定文件支持的操作系统
   - 常用值：
     - `VOS_NT_WINDOWS32`：Windows NT 32 位系统
     - `VOS__WINDOWS32`：通用 Windows 32 位
     - `VOS_DOS_WINDOWS16`：Windows 3.x 16 位

4. **`FILETYPE`**  
   - 作用：定义文件类型
   - 常用值：
     - `VFT_APP`：应用程序 (EXE)
     - `VFT_DLL`：动态链接库
     - `VFT_DRV`：设备驱动
     - `VFT_FONT`：字体文件
     - `VFT_VXD`：虚拟设备驱动

5. **`FILESUBTYPE`**  
   - 作用：当 `FILETYPE` 需要细分时指定子类型
   - 对 `VFT_APP`：必须设为 `VFT2_UNKNOWN`（无子类型）
   - 对 `VFT_DRV`：可指定打印机/键盘等子类型
   - 对 `VFT_FONT`：可指定矢量/位图字体

### 信息块解析

6. **`BLOCK "StringFileInfo"`**  
   - 作用：包含所有语言特定的字符串信息
   - 结构：
     ```rc
     BLOCK "StringFileInfo"
     BEGIN
         BLOCK "<LangID><CodePage>"  // 如 "040904B0"
         BEGIN
             VALUE "Key", "Value"    // 实际显示的版本信息
         END
     END
     ```

7. **`BLOCK "VarFileInfo"`**  
   - 作用：定义文件的翻译信息（语言和代码页）
   - 结构：
     ```rc
     BLOCK "VarFileInfo"
     BEGIN
         VALUE "Translation", <LangID>, <CodePage>
     END
     ```
   - 示例：`VALUE "Translation", 0x0804, 1200` 表示简体中文 Unicode

### 关键概念说明

| 部分 | 功能 | 典型值 |
|------|------|--------|
| **文件属性区** | 定义二进制特性 | |
| `FILEFLAGSMASK` | 有效标志位掩码 | `VS_FFI_FILEFLAGSMASK` |
| `FILEFLAGS` | 实际版本标志 | `0x0L` (正式版) |
| `FILEOS` | 目标操作系统 | `VOS_NT_WINDOWS32` |
| `FILETYPE` | 文件类型 | `VFT_APP` (应用程序) |
| `FILESUBTYPE` | 文件子类型 | `VFT2_UNKNOWN` |
| **字符串信息区** | 用户可见信息 | |
| `StringFileInfo` | 多语言字符串容器 | |
| `<LangID><CodePage>` | 语言标识 | "080404B0" (简体中文) |
| **变量信息区** | 语言配置 | |
| `VarFileInfo` | 语言定义容器 | |
| `Translation` | 默认语言设置 | `0x0804, 1200` |

### 工作流程
1. 系统先读取 `VarFileInfo` 确定默认语言
2. 在 `StringFileInfo` 中查找匹配的 `LangID+CodePage` 块
3. 显示对应语言的字符串信息
4. 文件属性区 (`FILEOS`等) 提供系统级元数据

> ⚠️ 注意：当修改语言时，必须同步更新：
> 1. `StringFileInfo` 中的语言块 ID (如 080404B0)
> 2. `VarFileInfo` 中的 Translation 值
> 3. 实际字符串内容（如需本地化）

- [Windows 资源文件(.rc文件)](https://blog.csdn.net/fuhanghang/article/details/116302561)
- [关于资源文件](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-resource-files)