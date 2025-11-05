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
        if (debug) std::cout << "Nums: " << nums[0] << ", " << nums[1] << std::endl;
        listA.push_back(std::stoi(nums[0]));
        listB.push_back(std::stoi(nums[1]));
    }
    sortVector(listA);
    sortVector(listB);
    for (size_t i = 0; i < listA.size(); ++i) {
        total += std::abs(listA[i] - listB[i]);
    }
    return total;
}

int main() {
    RunFramework rf(
        {"./2024/day1/inputs/example1.txt"},
        {11},
        "./2024/day1/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}