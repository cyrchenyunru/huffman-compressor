#include "compress_extract.hpp"
#include <cstdint>
#include <locale>
#include <codecvt>
#include <fstream>
#include <string>
#include <map>
#include <iostream>


// 用于去除最后一个字符c打头的后缀（去除扩展名）
string removeExtension(const string& filename, char c) {
    size_t lastc = filename.find_last_of(c);

    // 如果没有找到c，则直接返回原文件名
    if (lastc == string::npos) {
        return filename;
    }

    // 否则，去除后缀
    return filename.substr(0, lastc);
}

// 将二进制字符串转换为字节数组
vector<uint8_t> binaryStringToBytes(const string& binaryString) {
    vector<uint8_t> bytes;
    size_t length = binaryString.length();
    uint8_t byte = 0;
    int bitCount = 0;

    for (size_t i = 0; i < length; ++i) {
        // 从右边开始填充byte变量
        if (binaryString[i] == '1') {
            byte |= (1 << bitCount);
        }
        ++bitCount;
        if (bitCount == 8) {
            bytes.push_back(byte);
            byte = 0;
            bitCount = 0;
        }
    }

    // 处理最后一组不足8位的情况
    if (bitCount > 0) {
        bytes.push_back(byte); // 最后一个字节可能不足8位
    }

    return bytes;
}
// 函数用于计算UTF-8字符的长度
size_t utf8CharLength(unsigned char c) {
    if ((c & 0x80) == 0x00) return 1; // 1-byte character
    if ((c & 0xE0) == 0xC0) return 2; // 2-byte character
    if ((c & 0xF0) == 0xE0) return 3; // 3-byte character
    if ((c & 0xF8) == 0xF0) return 4; // 4-byte character
    return 0; // Invalid UTF-8 byte
}

// 函数用于提取UTF-8字符
std::string extractUtf8Char(const std::string& text, size_t& pos) {
    unsigned char firstByte = static_cast<unsigned char>(text[pos]);
    size_t length = utf8CharLength(firstByte);
    if (length == 0 || pos + length > text.size()) {
        throw std::runtime_error("Invalid UTF-8 sequence");
    }
    std::string result = text.substr(pos, length);
    pos += length;
    return result;
}

// 统计UTF-8字符频率
std::map<std::string, int> countCharacterFrequencies(const std::string& text) {
    std::map<std::string, int> frequencyMap;
    for (size_t i = 0; i < text.size(); ) {
        std::string utf8Char = extractUtf8Char(text, i);
        ++frequencyMap[utf8Char];
    }
    return frequencyMap;
}

// 输出字符频率到文件
void outputCharacterFrequencies(const string& filePath, const string& fileContent) {
    auto frequency_map = countCharacterFrequencies(fileContent);

    string freqFileName = removeExtension(filePath, '.') + "_char_frequency.txt";
    std::ofstream freqFile(freqFileName);
    if (!freqFile.is_open()) {
        std::cout << "无法打开字符频率文件：" << freqFileName << std::endl;
        return;
    }

    for (const auto& pair : frequency_map) {
        freqFile << pair.first << ": " << pair.second << std::endl;
    }
    freqFile.close();
}

bool compress(const string& filePath) {
    // 1.读取文件内容到字符串中
    string file;
    if(!Rfile(filePath, file)) {
        cout << "读取待压缩文件失败：" << filePath << endl;
        return false;
    }

    // 2.记录频率并将结果存储到映射map中
    map<char, int> frequency_map = countfreq(file);

    // 3.输出字符频率统计结果到文件
    outputCharacterFrequencies(filePath, file);
    // 4.建立哈夫曼树
    TreeNode* root = buildHuffmanTree(frequency_map);
    if(!root) {
        cout << "创建哈夫曼树失败!" << endl;
        return false;
    }

    // 5.创建 config1.txt 和config2.txt 分别存储哈夫曼树的结构和叶节点信息
    string filenameWithoutExtension = removeExtension(filePath, '.');
    string newFileName1 = filenameWithoutExtension + "config1.txt";
    string newFileName2 = filenameWithoutExtension + "config2.txt";

    savehufftree(root, newFileName1, newFileName2);

    // 6.得到huffman编码并得到文件二进制的压缩
    map<char, string> huffmanCodes;
    huffmancode(root, huffmanCodes);
    string compressFile = filenameWithoutExtension + ".bin";
    string resultbinary;
    for(char i : file){
        resultbinary += huffmanCodes[i];
    }

    // 7.将二进制字符串转换为字节数组减少空间
    vector<uint8_t> bytes = binaryStringToBytes(resultbinary);
    // 计算最后一个字节的有效长度
    int lastByteLength = (resultbinary.length() % 8) ? (resultbinary.length() % 8) : 8;

    // 在文件开头添加标志位
    vector<uint8_t> fileData;
    fileData.push_back(static_cast<uint8_t>(lastByteLength)); // 标志位
    fileData.insert(fileData.end(), bytes.begin(), bytes.end());

    //8.将字节字符串写入压缩文件
    if(!Wfile(compressFile, fileData)) {
        cout << "写入文件失败：" << compressFile << endl;
        return false;
    }

    //释放huffman树内存
    delete root;
    return true;
}

// 将二进制的标志位转化为十进制
int binaryStringToDecimal(const string& binaryStr) {
    if (binaryStr.length() != 8) {
        throw std::invalid_argument("二进制字符串长度必须为8！");
    }
    int decimal = 0;
    for (int i = 0; i < 8; ++i) {
        if (binaryStr[i] == '1') {
            decimal += (1 << i);
        } else if (binaryStr[i] != '0') {
            throw std::invalid_argument("二进制字符串包含非法输入！");
        }
    }
    return decimal;
}

// 将字节数组转换为二进制字符串
string bytesToBinaryString(const vector<uint8_t>& bytes) {
    string binaryString;
    for (auto byte : bytes) {
        for (int i = 0; i < 8; ++i) {
            binaryString += (byte >> i) & 1 ? '1' : '0';
        }
    }
    return binaryString;
}

bool extract(const string& filePath){
    // 1.搜索当前目录下有无哈夫曼树的结构和信息文件，没有则让用户手动输入两个文件地址
    string filenameWithoutExtension = removeExtension(filePath,'.');
    string newFileName1 = filenameWithoutExtension + "config1.txt";
    string newFileName2 = filenameWithoutExtension + "config2.txt";
    string Struct_content,ASCII_content;
    if(!Rfile(newFileName1,Struct_content) || !Rfile(newFileName2, ASCII_content)) {
        cout << "请输入存放哈夫曼树结构的文件地址：";
        newFileName1 = getInput();
        cout << "请输入存放哈夫曼树叶节点信息的文件地址：";
        newFileName2 = getInput();
        if(!Rfile(newFileName1,Struct_content) || !Rfile(newFileName2, ASCII_content)) {
            cout << "哈夫曼树结构文件或叶节点信息文件有误！" << endl;
            return false;
        }
    }

    // 2.创建哈夫曼树
    TreeNode *root = htreebyfile(Struct_content,ASCII_content);
    if(!root) {
        cout << "创建哈夫曼树失败！" << endl;
        return false;
    }

    // 3.读取源文件内容(二进制字符串)
    string source_content;
    vector<uint8_t> bytes;
    if(!Rfile(filePath,bytes)) {
        cout << "待解压的文件不存在！";
        return false;
    }
    source_content = bytesToBinaryString(bytes);
    //处理标志位和最后一位
    int lastByteLength = binaryStringToDecimal(source_content.substr(0,8));
    // 处理最后一个字节的有效长度
    source_content = source_content.substr(8, source_content.size() - 8 -(8 - lastByteLength));

    // 4.根据二进制字符串得到解压文件内容
    string destination_content;
    TreeNode *p = root;
    for(char i : source_content){
        switch (i)
        {
        case '0':
            p = p->left;
            break;
        case '1':
            p = p->right;
            break;
        default:
            cout << "待解压文件的内容有误！";
            return false;
        }
        if(p->isLeaf()){
            destination_content += p->character;
            p = root;
        }
    }

    // 5.写入目标文件
    string destination = filenameWithoutExtension + "_extract.txt";
    if(!Wfile(destination, destination_content)) {
        cout << "写入文件失败！ " << destination << endl;
        return false;
    }

    delete root;
    return true;
}
