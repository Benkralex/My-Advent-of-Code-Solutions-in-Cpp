#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/stringRegexParser.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    string memory = join(lines, "\n");
    StringRegexParser parser(memory);
    vector<int> doInstructions = parser.getStartIndices("do\\(\\)");
    vector<int> dontInstructions = parser.getStartIndices("don\\'t\\(\\)");
    vector<int> mulValues = parser.getStartIndices("mul\\(\\d{1,3},\\d{1,3}\\)");
    vector<int> instructionIndices = doInstructions + dontInstructions + mulValues;

    if (debug) {
        std::cout << "do instructions at: ";
        for (const int& idx : doInstructions) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
        std::cout << "don't instructions at: ";
        for (const int& idx : dontInstructions) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
        std::cout << "mul instructions at: ";
        for (const int& idx : mulValues) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    }

    int total = 0;
    bool activeMul = true;
    sortVector(instructionIndices);
    for (const int& inst : instructionIndices) {
        if (contains(doInstructions, inst)) {
            activeMul = true;
            if (debug) {
                std::cout << "do at " << inst << "\n";
            }
        } else if (contains(dontInstructions, inst)) {
            activeMul = false;
            if (debug) {
                std::cout << "don't at " << inst << "\n";
            }
        } else if (activeMul) {
            // mul instruction
            size_t start = inst;
            size_t end = memory.find(')', start);
            string mulInst = memory.substr(start, end - start + 1);
            if (debug) {
                std::cout << "mul: \"" << mulInst << "\" with values ";
            }
            vector<int> values = sVecToIVec(splitString(mulInst.substr(4, mulInst.size() - 1), ','));
            total += values[0] * values[1];
            if (debug) {
                std::cout << values[0] << ", " << values[1] << "\n";
            }
        }
    }
    return total;
}

int main() {
    RunFramework rf(
        {"./2024/day3/inputs/example2.txt"},
        {48},
        "./2024/day3/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}