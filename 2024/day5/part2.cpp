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

void makeValidManual(vector<int>& manual, const vector<Rule>& rules) {
    std::sort(manual.begin(), manual.end(), [rules](int a, int b) { 
        for (const Rule& rule : rules) {
            if (rule.before == a && rule.after == b) return true;
            if (rule.before == b && rule.after == a) {
                return false;
            }
        }
        return true;
    });
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
    for (vector<int>& manual : saftyManuals) {
        vector<Rule> usedRules;
        for (const Rule& rule : rules) {
            int beforeIdx = search(manual, rule.before);
            int afterIdx = search(manual, rule.after);
            if (beforeIdx != -1 && afterIdx != -1) {
                usedRules.push_back(rule);
            }
        }
        vector<int> originalManual = manual;
        makeValidManual(manual, usedRules);
        if (originalManual != manual) {
            if (debug) {
                std::cout << "Corrected manual: ";
                for (int val : manual) {
                    std::cout << val << " ";
                }
                std::cout << "\n";
            }
            count += manual[manual.size() / 2];
        }
    }
    return count;
}

int main() {
    RunFramework rf(
        {"./2024/day5/inputs/example1.txt"},
        {123},
        "./2024/day5/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}