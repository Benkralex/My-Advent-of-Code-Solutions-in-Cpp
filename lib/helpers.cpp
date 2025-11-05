#include <vector>
#include <string>
#include <algorithm>

using std::vector, std::string;

vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    string current;
    for (char ch : str) {
        if (ch == delimiter) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else {
            current += ch;
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

vector<int> sVecToIVec(const vector<string>& strVec) {
    vector<int> intVec;
    for (const string& s : strVec) {
        intVec.push_back(std::stoi(s));
    }
    return intVec;
}

void sortVector(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

int maxElement(const vector<int>& vec) {
    return *std::max_element(vec.begin(), vec.end());
}