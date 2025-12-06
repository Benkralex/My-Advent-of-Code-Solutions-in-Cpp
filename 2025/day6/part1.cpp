#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/matrix.cpp"

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    Matrix matrix(lines.size(), lines[0].size());
    for (size_t r = 0; r < lines.size(); ++r) {
        for (size_t c = 0; c < lines[0].size(); ++c) {
            matrix[r][c] = lines[r][c];
        }
    }
    matrix.transpose();
    vector<vector<string>> operations;
    int opIdx = 0;
    for (size_t r = 0; r < matrix.numRows(); ++r) {
        bool isEmptyRow = true;
        for (size_t c = 0; c < matrix.numCols(); ++c) {
            if (matrix[r][c] != ' ') {
                isEmptyRow = false;
                break;
            }
        }
        if (isEmptyRow) {
            opIdx++;
            continue;
        }
        if (opIdx >= operations.size()) {
            operations.push_back({});
        }
        operations[opIdx].push_back(charVecToString(matrix[r]));
    }

    long finalAnswer = 0;

    for (size_t i = 0; i < operations.size(); ++i) {
        if (debug) std::cout << "Operation " << i << ":\n";
        Matrix opMatrix(operations[i].size(), operations[i][0].size());
        for (size_t r = 0; r < operations[i].size(); ++r) {
            for (size_t c = 0; c < operations[i][0].size(); ++c) {
                opMatrix[r][c] = operations[i][r][c];
            }
        }
        opMatrix.transpose();
        if (debug) {
            for (size_t r = 0; r < opMatrix.numRows() - 1; ++r) {
                std::cout << "\"";
                for (size_t c = 0; c < opMatrix.numCols(); ++c) {
                    std::cout << opMatrix[r][c];
                }
                std::cout << "\"\n";
            }
        }
        string operatorStr = charVecToString(opMatrix[opMatrix.numRows() - 1]);
        operatorStr = replace(operatorStr, " ", "");
        if (debug) {
            std::cout << "Operator:  \"" << operatorStr << "\"\n";
        }
        long answer = 0;
        if (operatorStr == "*") answer++;
        for (size_t r = 0; r < opMatrix.numRows() - 1; ++r) {
            long num = std::stol(charVecToString(opMatrix[r]));
            if (operatorStr == "+") {
                answer += num;
            } else if (operatorStr == "*") {
                answer *= num;
            }
        }
        if (debug) {
            std::cout << "Result: \"" << answer << "\"\n";
        }
        finalAnswer += answer;
    }
    return finalAnswer;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day6/inputs/example1.txt"},
        {4277556},
        "./2025/day6/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}