#include <iostream>
#include <string>
#include <fstream>
#include "compress_extract.hpp"
#include "file.hpp"
#include "huffman_tree.hpp"
#include "frequency.hpp"
#include "hushcompare.hpp"

using namespace std;

// 显示菜单并获取用户的选择
int showMenuAndGetChoice() {
    int choice;
    while (true) {
        cout << "1. 压缩文件\n";
        cout << "2. 解压文件\n";
        cout << "3. 检验\n";
        cout << "4. 退出\n";
        cout << "请输入操作(1 or 2 or 3 or 4): ";

        if (cin >> choice) {
            if (choice == 1 || choice == 2 || choice == 3||choice==4) {
                return choice;
            }
            cout << "非法输入，请再次尝试\n";
        } else {
            cin.clear(); // 清除错误标志
            cout << "非法输入，请输入一个操作.\n";
            return 0;
        }
    }
}

// 主函数
int main() {
    while (true) {
        int choice = showMenuAndGetChoice();

        string filePath;

        if (choice == 1) {
            cout << "请输入待压缩文件地址: ";
            filePath = getInput();
            if (compress(filePath)) {
                cout << "文件压缩成功!\n";
            } else {
                cout << "文件压缩失败!\n";
            }
        } else if (choice == 2) {
            cout << "请输入待解压文件地址: ";
            filePath = getInput();
            if (extract(filePath)) {
                cout << "文件解压成功!\n";
            } else {
                cout << "文件解压失败!\n";
            }
        } else if (choice == 3) {
            std::string originalFilePath ;
            std::string decompressedFilePath;
            cout << "请输入原文件地址：\n";
            cin>>originalFilePath;
            cout << "请输入解压缩文件地址：\n";
            cin>>decompressedFilePath;
            if (compareFilesByHash(originalFilePath, decompressedFilePath)) {
                std::cout << "解压前后文件内容相同" << std::endl;
            } else {
                std::cout << "解压前后文件内容不同" << std::endl;
            }
        }else if (choice == 4) break;
        char continueChoice;
        cout << "是否继续操作?(y/n): ";
        cin >> continueChoice;
        cout << endl;

        if (continueChoice != 'y' && continueChoice != 'Y') {
            break;
        }
        system("cls");
    }

    cout << "程序结束.\n";
    return 0;
}
