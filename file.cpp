#include "file.hpp"

// readFile 函数的实现
bool Rfile(const string& filename, string& content) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        return false;
    }

    streampos size = file.tellg();
    content.resize(size);
    file.seekg(0, ios::beg);
    file.read(&content[0], size);
    file.close();
    return true;
}
bool Rfile(const string& filename, vector<uint8_t>& data) {
    ifstream in(filename, ios::binary);
    if (!in) {
        return false;
    }

    // 读取文件到vector中
    in.seekg(0, ios::end);
    data.resize(static_cast<size_t>(in.tellg()));
    in.seekg(0, ios::beg);
    in.read(reinterpret_cast<char*>(data.data()), data.size());
    return in.good();
}

// writeFile 函数的实现
bool Wfile(const string& filename, const string& content) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }

    try {
        file.write(content.c_str(), content.size());
        if (!file) {
            return false;
        }
    } catch (const exception& e) {
        return false;
    }

    file.close();
    return true;
}
bool Wfile(const string& filename, const vector<uint8_t>& data) {
    ofstream out(filename, ios::binary);
    if (!out) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    return out.good();
}

// 获取用户输入的文件路径，并去除可能的引号
string getInput() {
    string input;
    cin >> input;

    // 去除前后引号
    if (!input.empty() && input.front() == '"' && input.back() == '"') {
        input = input.substr(1, input.size() - 2);
    }
    return input;
}

