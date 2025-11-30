#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

bool Rfile(const string& filename, string& content);
bool Rfile(const string& filename, vector<uint8_t>& data);
bool Wfile(const string& filename, const string& content);
bool Wfile(const string& filename, const vector<uint8_t>& data);

string getInput();

#endif // FILE_H
