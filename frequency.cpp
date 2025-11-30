#include "frequency.hpp"

map<char, int> countfreq(const string& s) {
    map<char, int> freqMap;
    for (char c : s) {
        ++freqMap[c];
    }
    return freqMap;
}
