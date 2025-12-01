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
        int leftToRotate = rot;
        while (leftToRotate != 0) {
            if (leftToRotate > 0) {
                value = (value + 1) % 100;
                leftToRotate--;
            } else {
                value = (value - 1 + 100) % 100;
                leftToRotate++;
            }
            if (value == 0) {
                count++;
            }
        }
        if (debug) {
            std::cout << "Rotation: " << rot << ", New Value: " << value << ", Count: " << count << "\n";
        }
    }
    return count;
}

int main() {
    RunFramework rf(
        {"./2025/day1/inputs/example1.txt"},
        {6},
        "./2025/day1/inputs/input.txt",
        solve,
        true
    );
    rf.runInput();
    return 0;
}