#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"

using std::pair, std::to_string, std::stoi;

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> strRanges = splitString(loader.getLines()[0], ',');
    if (debug) {
        for (const string& strRange : strRanges) {
            std::cout << "Range: " << strRange << std::endl;
        }
    }
    vector<pair<long, long>> ranges;
    for (const string& strRange : strRanges) {
        vector<string> bounds = splitString(strRange, '-');
        if (debug) {
            std::cout << "Bounds: " << bounds[0] << " to " << bounds[1] << std::endl;
        }
        ranges.push_back({stoul(bounds[0]), stoul(bounds[1])});
    }
    
    long count = 0;
    for (const pair<long, long>& range : ranges) {
        for (long i = range.first; i <= range.second; ++i) {
            string number = to_string(i);
            for (size_t j = 1; j < number.size(); ++j) {
                if (number.size() % j != 0) continue;
                string pattern = number.substr(0, j);
                bool invalid = true;
                for (size_t k = 0; k < number.size(); k += j) {
                    if (number.substr(k, j) != pattern) {
                        invalid = false;
                        break;
                    }
                }
                if (invalid) {
                    count += i;
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day2/inputs/example1.txt"},
        {4174379265},
        "./2025/day2/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}