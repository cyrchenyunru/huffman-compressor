# huffman-compressor
An efficient lossless file compression and decompression tool based on Huffman coding, supporting both Chinese and English text processing and hash-based file verification. It balances high compression ratio with data integrity, making it ideal for space optimization of various text files.

## 项目介绍
哈夫曼编码是经典的无损数据压缩算法，核心思想为**频率越高的字符分配越短的编码**，从而减少数据存储的总位数。本项目完整实现了从字符频率统计、哈夫曼树构建、编码生成到文件压缩/解压的全流程，同时加入哈希值文件对比功能，验证压缩前后数据一致性，适用于纯文本文件（UTF-8 编码）的压缩需求。

### 核心功能
✅ 支持中英文文本文件压缩（UTF-8 编码兼容）  
✅ 支持压缩文件的完整解压，确保数据无丢失  
✅ 基于哈希值的文件校验，快速验证解压后文件与原文件一致性  
✅ 输出字符频率统计文件，便于分析数据特征  
✅ 命令行交互界面，操作简洁直观

## 技术原理
### 1. 核心流程
压缩流程：读取文件 → 统计字符频率 → 构建哈夫曼树 → 生成前缀编码 → 二进制压缩 → 写入压缩文件
解压流程：读取压缩文件 → 重建哈夫曼树 → 解码二进制数据 → 恢复原始内容 → 写入解压文件
校验流程：计算文件哈希值 → 对比哈希结果 → 验证内容一致性

### 2. 关键技术
- **字符频率统计**：支持 UTF-8 多字节字符，使用 `map`/`unordered_map` 存储字符与对应频率
- **哈夫曼树构建**：通过最小堆（优先队列）高效合并低频节点，生成最优编码树
- **编码生成**：深度优先搜索（DFS）遍历哈夫曼树，为每个字符分配唯一前缀码
- **哈希校验**：逐行计算文件哈希值并累积，快速对比文件内容（支持大文件高效校验）

## 快速开始
### 1.环境要求
- 操作系统：Windows（测试环境）
- 编译器：支持 C++11 及以上标准的编译器

### 2.编译运行
下载整个项目zip文件解压缩后，运行main.cpp文件即可

### 3.使用指南
程序启动后将显示交互菜单，按提示操作：
1. 压缩文件
2. 解压文件
3. 检验
4. 退出
请输入操作(1 or 2 or 3 or 4): 
压缩文件：输入待压缩文件路径（如 hamlet.txt），压缩后生成 xxx.zip（压缩文件）、xxx_char_frequency.txt（频率统计）、xxxconfig1.txt/xxxconfig2.txt（哈夫曼树配置）
解压文件：输入压缩文件路径（如 hamlet.zip），解压后生成 xxx_extract.txt（解压文件）
文件校验：分别输入原文件和解压文件路径，程序将通过哈希值对比判断内容是否一致

## 测试结果
测试文件类型	     原文件大小	   压缩文件大小	 压缩率	 解压一致性
英文文本（Hamlet）	  177KB	       108KB	     61.02%	  ✅ 一致
中英文文本（斗破苍穹）15.79MB	     11.56MB	   73.22%	  ✅ 一致

## 项目结构
huffman-compressor/
├── main.cpp          # 主程序（菜单交互、逻辑调度）
├── compress_extract.cpp  # 压缩/解压核心函数声明
├── file.cpp          # 文件读写工具函数
├── huffman_tree.cpp  # 哈夫曼树构建与编码生成
├── frequency.cpp     # 字符频率统计函数
├── hushcompare.cpp   # 哈希值文件对比函数
├── compress_extract.hpp  # 压缩/解压核心函数声明的hpp文件声明
├── file.hpp          # 文件读写工具函数的hpp文件声明
├── huffman_tree.hpp  # 哈夫曼树构建与编码生成的hpp文件声明
├── frequency.hpp     # 字符频率统计函数的hpp文件声明
├── hushcompare.hpp   # 哈希值文件对比函数的hpp文件声明
└── README.md         # 项目说明文档

## 改进方向
1.支持更多文件格式（如二进制文件、图片）
2.优化大文件处理（分块读取、异步 I/O 减少内存占用）
3.引入多线程加速压缩 / 解压（CPU 密集型任务并行化）
4.增强错误处理（异常捕获、资源自动释放）
哈夫曼编码算法理论基础
C++ 标准库及相关工具函数支持
