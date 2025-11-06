#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    string memory = join(lines, "\n");
    string tmp = "";
    int total = 0;
    for (char c : memory) {
        if (debug) {
            std::cout << "Processing char: " << c << ", tmp: " << tmp << "\n";
        }
        if (tmp.empty() && c == 'm') {
            tmp += c;
            continue;
        } else if (tmp.size() == 1 && c == 'u') {
            tmp += c;
            continue;
        } else if (tmp.size() == 2 && c == 'l') {
            tmp += c;
            continue;
        } else if (tmp.size() == 3 && c == '(') {
            tmp += c;
            continue;
        } else if (tmp.size() >= 4 && tmp.size() < 7 && isdigit(c)) {
            tmp += c;
            continue;
        } else if (tmp.size() >= 5 && tmp.size() <= 7 && c == ',') {
            tmp += c;
            continue;
        } else if (tmp.size() >= 6 && tmp.size() < 11 && isdigit(c)) {
            tmp += c;
            continue;
        } else if (tmp.size() >= 7 && c == ')') {
            tmp += c;
            if (debug) {
                std::cout << "Found mul instruction: " << tmp << "\n";
            }
            vector<int> values = sVecToIVec(splitString(tmp.substr(4, tmp.size() - 1), ','));
            if (debug) {
                std::cout << "Values: " << values[0] << ", " << values[1] << "\n";
            }
            total += values[0] * values[1];
            tmp = "";
            continue;
        } else {
            tmp = "";
        }
    }
    return total;
}

int main() {
    RunFramework rf(
        {"./2024/day3/inputs/example1.txt"},
        {161},
        "./2024/day3/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}