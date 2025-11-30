#ifndef COMPRESS_EXTRACT_H
#define COMPRESS_EXTRACT_H

#include <string>
#include <bitset>
#include <fstream>
#include <map>
#include "file.hpp"
#include "huffman_tree.hpp"
#include "frequency.hpp"

using namespace std;

bool compress(const string& filePath);

bool extract(const string& filePath);

#endif // COMPRESS_EXTRACT_H
