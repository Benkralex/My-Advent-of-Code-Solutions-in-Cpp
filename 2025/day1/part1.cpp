#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<int> rotations;
    for (const string& line : lines) {
        char dir = line[0];
        int value = std::stoi(line.substr(1));
        if (dir == 'L') {
            rotations.push_back(-value);
        } else if (dir == 'R') {
            rotations.push_back(value);
        }
    }
    int count = 0;
    int value = 50;
    for (const int rot : rotations) {
        value += rot;
        value = value % 100;
        if (debug) {
            std::cout << "Rotation: " << rot << ", New Value: " << value << "\n";
        }
        if (value == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    RunFramework rf(
        {"./2025/day1/inputs/example1.txt"},
        {3},
        "./2025/day1/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}