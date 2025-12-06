#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>

using std::vector, std::string, std::pow;

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

long iVecToLong(const vector<int>& intVec) {
    long longNum = 0;
    int j = intVec.size();
    for (int i : intVec) {
        j--;
        longNum += i * (long)pow(10, j);
    }
    return longNum;
}

vector<long> sVecToLVec(const vector<string>& strVec) {
    vector<long> longVec;
    for (const string& s : strVec) {
        longVec.push_back(std::stol(s));
    }
    return longVec;
}

void sortVector(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

void sortVectorOpposite(vector<int>& vec) {
    std::sort(vec.begin(), vec.end(), std::greater<int>());
}

int maxElement(const vector<int>& vec) {
    return *std::max_element(vec.begin(), vec.end());
}

string join(const vector<string>& vec, const string& delimiter) {
    return std::accumulate(vec.begin(), vec.end(), delimiter);
}

string join(const vector<char>& vec, const string& delimiter) {
    return std::accumulate(vec.begin(), vec.end(), delimiter);
}

template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> result = a;
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

template <typename T>
int search(const vector<T>& a, const T& b) {
    auto idx = std::find(a.begin(), a.end(), b);
    if (idx == a.end()) {
        return -1;
    }
    return idx - a.begin();
}

template <typename T>
bool contains(const vector<T>& a, const T& b) {
    return std::find(a.begin(), a.end(), b) != a.end();
}

bool contains(const string& str, const string& substring) {
    return str.find(substring) != string::npos;
}

template <typename T>
vector<T> reverse(const vector<T>& vec) {
    vector<T> revVec = vec;
    std::reverse(revVec.begin(), revVec.end());
    return revVec;
}

vector<string> splitStringIntoChars(const string& str) {
    vector<string> result;
    for (char ch : str) {
        result.push_back(string(1, ch));
    }
    return result;
}

string replace(const string& str, const string& from, const string& to) {
    string result = str;
    size_t start_pos = result.find(from);
    while (start_pos != string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos = result.find(from, start_pos + to.length());
    }
    return result;
}

template <typename T>
vector<vector<T>> transpose(const vector<vector<T>>& matrix) {
    if (matrix.empty()) return {};
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    vector<vector<T>> transposed(cols, vector<T>(rows));
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            transposed[c][r] = matrix[r][c];
        }
    }
    return transposed;
}

string operator+(const string& a, const char& b) {
    return a + string(1, b);
}

string charVecToString(const vector<char>& charVec) {
    string result;
    for (char ch : charVec) {
        result += ch;
    }
    return result;
}

string trimString(const string& str) {
    string strCopy = str;
    const char* whitespace = " \t\n\r\f\v";
    strCopy.erase(0, str.find_first_not_of(whitespace));
    strCopy.erase(str.find_last_not_of(whitespace) + 1);
    return strCopy;
}