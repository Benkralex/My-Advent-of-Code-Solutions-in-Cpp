#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<int> listA;
    vector<int> listB;
    int total = 0;
    for (const string& line : lines) {
        vector<string> nums = splitString(line, ' ');
        listA.push_back(std::stoi(nums[0]));
        listB.push_back(std::stoi(nums[1]));
    }

    // Calculate frequency of each number in listA
    int maxValA = maxElement(listA);
    std::vector<int> frequencyListA(maxValA + 1, 0);
    for (int i : listA) {
        frequencyListA[i]++;
    }
    
    // Calculate frequency of each number in listB
    int maxValB = maxElement(listB);
    std::vector<int> frequencyListB(maxValB + 1, 0);
    for (int i : listB) {
        frequencyListB[i]++;
    }

    // Calculate the total simialrity score
    for (int i = 0; i <= maxValA; i++) {
        total += frequencyListA[i] * i * frequencyListB[i];
    }
    return total;
}

int main() {
    RunFramework rf(
        {"./2024/day1/inputs/example1.txt"},
        {31},
        "./2024/day1/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}