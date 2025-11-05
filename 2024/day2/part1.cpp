#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    int safeReports = 0;
    for (string line : lines) {
        vector<int> report = sVecToIVec(splitString(line, ' '));
        if (debug) {
            std::cout << "Report ";
            for (int r : report) std::cout << r << " ";
        }
        bool increases = report[0] < report[1];
        bool safe = true;
        for (size_t i = 0; i <= report.size() - 2; ++i) {
            int diff = report[i] - report[i + 1];
            if (std::abs(diff) == 0 || std::abs(diff) > 3) {
                safe = false;
                break;
            }
            if (increases && diff > 0) {
                safe = false;
                break;
            }
            if (!increases && diff < 0) {
                safe = false;
                break;
            }
        }
        if (safe) {
            safeReports++;
            if (debug) std::cout << "is safe.\n";
        } else {
            if (debug) std::cout << "is not safe.\n";
        }
    }
    return safeReports;
}

int main() {
    RunFramework rf(
        {"./2024/day2/inputs/example1.txt"},
        {2},
        "./2024/day2/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}