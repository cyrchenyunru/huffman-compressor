#include "huffman_tree.hpp"

// 自定义比较函数，用于构建最小堆
struct Compare {
    bool operator()(const TreeNode* l, const TreeNode* r) {
        return l->freq > r->freq;
    }
};

TreeNode* buildHuffmanTree(const map<char, int>& freqMap) {
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> p;

    // 将所有节点加入优先队列
    for (const auto& pair : freqMap) {
        p.push(new TreeNode(pair.first, pair.second));
    }
    // 构建哈夫曼树
    while (p.size() > 1) {
        TreeNode* left = p.top(); p.pop();
        TreeNode* right = p.top(); p.pop();

        TreeNode* sum = new TreeNode('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        p.push(sum);
    }

    return p.empty() ? nullptr : p.top();
}

// 迭代实现哈夫曼编码
void huffmancode(TreeNode* root, map<char, string>& hcodes) {
    if (root == nullptr) return;

    stack<pair<TreeNode*, string>> s;
    s.push(make_pair(root, ""));

    while (!s.empty()) {
        auto current = s.top();
        s.pop();

        TreeNode* node = current.first;
        string code = current.second;

        if (node->character != '\0') {
            hcodes[node->character] = code;
        }

        if (node->left) {
            s.push(make_pair(node->left, code + "0"));
        }
        if (node->right) {
            s.push(make_pair(node->right, code + "1"));
        }
    }
}

// 迭代实现先序遍历
bool preTrav(TreeNode* root, string& hstruct, string& hascii) {
    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();

        if (node != nullptr) {
            if(node->isLeaf()){
                hstruct += '0';
                hascii += node->character;
            } else{
                hstruct += '1';
            }

            if (node->right) {
                s.push(node->right);
            }
            if (node->left) {
                s.push(node->left);
            }
        }
    }
    return true;
}

void savehufftree(TreeNode* root, string filename1, string filename2){
    string H_Struct,H_ASCII;
    preTrav(root, H_Struct, H_ASCII);
    Wfile(filename1, H_Struct);
    Wfile(filename2, H_ASCII);
}

TreeNode* htreebyfile(const string& Struct_content, const string& ASCII_content){
    stack<TreeNode*> nodeStack;
    TreeNode *root = new TreeNode();
    nodeStack.push(root);
    int asciiIndex = 0; // 用于跟踪ASCII_content中的索引

    for(size_t i = 0; i < Struct_content.size(); i++){
        TreeNode* node = nodeStack.top();
        nodeStack.pop();
        if(Struct_content[i] == '1'){
            node->left = new TreeNode();
            node->right = new TreeNode();
            nodeStack.push(node->right);
            nodeStack.push(node->left);
        }
        else if(Struct_content[i] == '0'){
            node->character = ASCII_content[asciiIndex++];
        }
        else {
            return nullptr;
        }
    }
    return root;
}
