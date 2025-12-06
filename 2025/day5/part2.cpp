#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

using std::pair;

bool rangesIntersect(const pair<long, long>& r1, const pair<long, long>& r2) {
    long start = std::max(r1.first, r2.first);
    long end = std::min(r1.second, r2.second);
    if (start > end) {
        return false;
    }
    return true;
}

long rangeLength(const pair<long, long>& range) {
    return range.second - range.first + 1;
}

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<pair<long, long>> freshRanges;
    for (const string line : lines) {
        if (line.empty()) {
            break;
        }

        vector<long> range = sVecToLVec(splitString(line, '-'));
        pair<long, long> newRange = {range[0], range[1]};
        bool continueMerging = true;
        while (continueMerging) {
            bool merged = false;
            for (const auto existingRange : freshRanges) {
                if (rangesIntersect(existingRange, newRange)) {
                    if (debug) {
                        std::cout << "Merging ranges: " << existingRange.first << "-" << existingRange.second << " and " << newRange.first << "-" << newRange.second << "\n";
                    }
                    long newStart = std::min(existingRange.first, newRange.first);
                    long newEnd = std::max(existingRange.second, newRange.second);
                    freshRanges.erase(std::remove(freshRanges.begin(), freshRanges.end(), existingRange), freshRanges.end());
                    newRange = {newStart, newEnd};
                    merged = true;
                    break;
                }
            }
            if (!merged) {
                continueMerging = false;
            }
        }
        freshRanges.push_back(newRange);
    }
    long answer = 0;
    for (const auto range : freshRanges) {
        answer += rangeLength(range);
    }
    return answer;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day5/inputs/example1.txt"},
        {14},
        "./2025/day5/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}