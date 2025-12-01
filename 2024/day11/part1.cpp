#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/matrix.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<long> stones = sVecToLVec(splitString(lines[0], ' '));

    int blinks = 25;
    for (int blink = 0; blink < blinks; ++blink) {
        vector<long> newStones;
        for (const long& stone : stones) {
            string stoneStr = std::to_string(stone);
            if (stone == 0) {
                if (debug) {
                    std::cout << "Stone 0 becomes 1\n";
                }
                newStones.push_back((long int) 1);
            } else if (stoneStr.length() % 2 == 0) {
                string leftPart = stoneStr.substr(0, stoneStr.length() / 2);
                string rightPart = stoneStr.substr(stoneStr.length() / 2, stoneStr.length());
                if (debug) {
                    std::cout << "Splitting " << stone << " into " << leftPart << " and " << rightPart << "\n";
                }
                newStones.push_back((long int) std::stoi(leftPart));
                newStones.push_back((long int) std::stoi(rightPart));
            } else {
                if (debug) {
                    std::cout << "Multiplying " << stone << " by 2024: " << stone * 2024 << "\n";
                }
                newStones.push_back(stone * (long int) 2024);
            }
        }
        stones = newStones;
    }
    return stones.size();
}

int main() {
    RunFramework rf(
        {"./2024/day11/inputs/example1.txt"},
        {55312},
        "./2024/day11/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}