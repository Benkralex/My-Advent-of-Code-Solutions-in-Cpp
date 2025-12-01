#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/matrix.cpp"

vector<long> makeOneBlink(const vector<long>& stones, bool debug) {
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
    return newStones;
}

vector<long> makeTwoBlinks(const vector<long>& stones, bool debug) {
    vector<long> newStones;
    for (const long& stone : stones) {
        string stoneStr = std::to_string(stone);
        if (stone == 0) {
            if (debug) {
                std::cout << "Stone 0 becomes 2024\n";
            }
            newStones.push_back((long int) 2024);
        } else if (stoneStr.length() % 4 == 0) {
            for (int i = 0; i < 4; ++i) {
                string part = stoneStr.substr(i * (stoneStr.length() / 4), stoneStr.length() / 4);
                newStones.push_back((long int) std::stoi(part));
            }
        } else if (stoneStr.length() % 2 == 0) {
            string leftPart = stoneStr.substr(0, stoneStr.length() / 2);
            string rightPart = stoneStr.substr(stoneStr.length() / 2, stoneStr.length());
            if (debug) {
                std::cout << "Splitting " << stone << " into " << leftPart << " and " << rightPart << "\n";
            }
            newStones.push_back((long int) std::stoi(leftPart) * (long int) 2024);
            newStones.push_back((long int) std::stoi(rightPart) * (long int) 2024);
        } else {
            if (debug) {
                std::cout << "Multiplying " << stone << " by 2024: " << stone * 2024 << "\n";
            }
            newStones = newStones + makeOneBlink({stone * 2024}, debug);
        }
    }
    return newStones;
}

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<long> stones = sVecToLVec(splitString(lines[0], ' '));

    int blinks = 75;
    while (blinks > 0) {
        if (blinks >= 2) {
            stones = makeTwoBlinks(stones, debug);
            blinks -= 2;
        } else {
            stones = makeOneBlink(stones, debug);
            blinks -= 1;
        }
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