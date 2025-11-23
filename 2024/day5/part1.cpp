#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/matrix.cpp"

class Rule {
public:
    int before;
    int after;
    Rule(int b, int a) : before(b), after(a) {}
    Rule(vector<int> v) {
        before = v[0];
        after = v[1];
    }
};

bool isValidManual(const vector<int>& protocol, const vector<Rule>& rules) {
    for (const Rule& rule : rules) {
        int beforeIdx = search(protocol, rule.before);
        int afterIdx = search(protocol, rule.after);
        if (beforeIdx == -1 || afterIdx == -1) {
            continue;
        }
        if (beforeIdx >= afterIdx) {
            return false;
        }
    }
    return true;
}

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    vector<Rule> rules;
    vector<vector<int>> saftyManuals;
    bool parsingRules = true;
    for (const string& line : lines) {
        if (line.empty()) {
            parsingRules = false;
            continue;
        }
        if (parsingRules) {
            rules.push_back(Rule(sVecToIVec(splitString(line, '|'))));
            if (debug) {
                std::cout << "Parsed rule: before=" << rules.back().before << ", after=" << rules.back().after << "\n";
            }
        } else {
            saftyManuals.push_back(sVecToIVec(splitString(line, ',')));
            if (debug) {
                std::cout << "Parsed manual: ";
                for (int val : saftyManuals.back()) {
                    std::cout << val << " ";
                }
                std::cout << "\n";
            }
        }
    }
    int count = 0;
    for (const auto& manual : saftyManuals) {
        if (isValidManual(manual, rules)) {
            count += manual[manual.size() / 2];
        }
    }
    return count;
}

int main() {
    RunFramework rf(
        {"./2024/day5/inputs/example1.txt"},
        {143},
        "./2024/day5/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}