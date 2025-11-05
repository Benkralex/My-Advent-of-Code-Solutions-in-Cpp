#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string, std::vector;

class FileLoader {
private:
    string filePath;
public:
    FileLoader(const string& path) : filePath(path) {}

    vector<string> getLines() {
        vector<string> lines;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: could not open file '" << filePath << "'\n";
            return lines;
        }

        string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    vector<::string> getRows() {
        vector<string> rows;
        vector<string> lines = getLines();
        for (const string line : lines) {
            int index = 0;
            for (char ch : line) {
                rows[index] += ch;
                index++;
            }
        }
        return rows;
    }
};