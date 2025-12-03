#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    int total = 0;
    for (const string& line : lines) {
        vector<int> numbers = sVecToIVec(splitStringIntoChars(line));
        int lastElement = numbers.back();
        numbers.erase(numbers.end() - 1);
        int maxNum = maxElement(numbers);
        numbers.push_back(lastElement);

        while (numbers[0] != maxNum) {
            numbers.erase(numbers.begin());
        }
        numbers.erase(numbers.begin());
        int secondMax = maxElement(numbers);
        if (debug) {
            std::cout << "Line: " << line << " | Max: " << maxNum << " | Second Max: " << secondMax << std::endl;
        }
        total += maxNum * 10 + secondMax;
    }
    return total;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day3/inputs/example1.txt"},
        {357},
        "./2025/day3/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}