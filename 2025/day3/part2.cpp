#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include <algorithm>

long max(const vector<int>& numbers, bool debug, int length = 12) {
    vector<int> currentMax;
    int searchStart = 0;
    for (int i = 0; i < length; ++i) {
        int remaining = length - i - 1;
        int searchEnd = numbers.size() - remaining;
        auto beginIt = numbers.begin() + searchStart;
        auto endIt = numbers.begin() + searchEnd;
        auto maxNumIt = std::max_element(beginIt, endIt);
        int maxNum = *maxNumIt;
        currentMax.push_back(maxNum);
        searchStart = std::distance(numbers.begin(), maxNumIt) + 1;
    }
    return iVecToLong(currentMax);
}

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    long total = 0;
    for (const string& line : lines) {
        int oldTotal = total;
        if (debug) {
            std::cout << "Processing line: " << line << " ";
        }
        vector<int> numbers = sVecToIVec(splitStringIntoChars(line));
        vector<int> sortedNumbers = numbers;
        sortVectorOpposite(sortedNumbers);
        if (numbers == sortedNumbers) {
            if (debug) {
                std::cout << "is sorted. ";
            }
            for (size_t i = 0; i < 12 && i < numbers.size(); ++i) {
                total += pow(10, (11 - i)) * numbers[i];
            }
            if (debug) {
                std::cout << "Added to total: " << total - oldTotal << "\n";
            }
            continue;
        }
        
        long maxJoltage = max(numbers, false);
        total += maxJoltage;
        if (debug) {
            std::cout << "Added to total: " << maxJoltage << "\n";
        }
    }
    return total;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day3/inputs/example1.txt", "./2025/day3/inputs/example2.txt"},
        {3121910778619, 664466221211},
        "./2025/day3/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}