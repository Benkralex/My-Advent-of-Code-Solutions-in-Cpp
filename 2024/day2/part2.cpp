#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

bool isReportSave(const vector<int>& report) {
    bool increases = report[0] < report[1];
    for (size_t i = 0; i <= report.size() - 2; ++i) {
        int diff = report[i] - report[i + 1];
        if (std::abs(diff) == 0 || std::abs(diff) > 3) {
            return false;
        }
        if (increases && diff > 0) {
            return false;
        }
        if (!increases && diff < 0) {
            return false;
        }
    }
    return true;
}

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
        bool safe = isReportSave(report);
        if (!safe) {
            if (debug) std::cout << "\n";
            for (size_t i = 0; i < report.size(); ++i) {
                vector<int> modifiedReport = report;
                modifiedReport.erase(modifiedReport.begin() + i);
                safe = isReportSave(modifiedReport);
                if (debug) {
                    std::cout << "    Testing ";
                    for (int r : modifiedReport) std::cout << r << " ";
                    std::cout << "with removed index " << i << ": " << (safe ? "safe" : "not safe") << "\n";
                    
                }
                if (safe) break;
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
        {4},
        "./2024/day2/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}