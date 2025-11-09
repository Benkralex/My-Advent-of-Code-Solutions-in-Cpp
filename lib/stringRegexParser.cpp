#pragma once
#include <string>
#include <regex>

using std::string, std::regex, std::vector;

class StringRegexParser {
private:
    string str;
public:
    StringRegexParser(const string& str_)
        : str(str_) {}

    vector<int> getStartIndices(const string& pattern) {
        vector<int> indices;
        regex re(pattern);
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), re);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            indices.push_back(i->position());
        }
        return indices;
    }
};