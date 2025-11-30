#ifndef HUSHCOMPARE_H
#define HUSHCOMPARE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

// 计算文件的哈希值（仅适用于文本文件）
size_t calculateFileHash(const std::string& filePath);

// 比较两个文件的哈希值
bool compareFilesByHash(const std::string& file1Path, const std::string& file2Path);

#endif // HUSHCOMPARE_H
