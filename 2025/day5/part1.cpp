#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

using std::pair;

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<pair<long, long>> freshRanges;
    vector<long> ingridients;
    bool parsingIngridients = false;
    for (const string line : lines) {
        if (line.empty()) {
            parsingIngridients = true;
            continue;
        }

        if (!parsingIngridients) {
            vector<long> range = sVecToLVec(splitString(line, '-'));
            freshRanges.push_back({range[0], range[1]});
        } else {
            ingridients.push_back(stol(line));
        }
    }
    int freshIngridientsCount = 0;
    for (const long ingridient : ingridients) {
        if (debug) {
            std::cout << "Checking ingridient: " << ingridient << "\n";
        }
        for (const auto range : freshRanges) {
            if (ingridient >= range.first && ingridient <= range.second) {
                if (debug) {
                    std::cout << "Ingridient " << ingridient << " is fresh in range " << range.first << "-" << range.second << "\n";
                }
                freshIngridientsCount++;
                break;
            }
        }
    }
    return freshIngridientsCount;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day5/inputs/example1.txt"},
        {3},
        "./2025/day5/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}