#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <string>

#include"file.hpp"
#include"frequency.hpp"

using namespace std;

class TreeNode {
public:
    char character;  // 字符
    int freq;       // 频率
    TreeNode* left;
    TreeNode* right;

    TreeNode(char ch, int freq) : character(ch), freq(freq), left(nullptr), right(nullptr) {}
    TreeNode(char ch) : character(ch), freq(0), left(nullptr), right(nullptr) {}
    TreeNode() = default;

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }

    ~TreeNode() {
        delete left;
        delete right;
    }

};

TreeNode* buildHuffmanTree(const map<char, int>& freqMap);

void huffmancode(TreeNode* root, map<char, string>& hcodes);

void savehufftree(TreeNode* root, string filename1, string filename2);

TreeNode* htreebyfile(const string& Struct_content, const string& ASCII_content);

#endif // HUFFMAN_TREE_H


