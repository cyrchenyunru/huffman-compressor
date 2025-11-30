#include "hushcompare.hpp"

// 计算文件的哈希值（仅适用于文本文件）
size_t calculateFileHash(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件");
    }

    size_t hashValue = 0;
    std::string line;
    while (std::getline(file, line)) {
        hashValue ^= std::hash<std::string>{}(line);
    }

    return hashValue;
}

// 比较两个文件的哈希值
bool compareFilesByHash(const std::string& file1Path, const std::string& file2Path) {
    try {
        size_t hash1 = calculateFileHash(file1Path);
        size_t hash2 = calculateFileHash(file2Path);

        return hash1 == hash2;
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return false;
    }
}
