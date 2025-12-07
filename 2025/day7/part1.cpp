#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/matrix.cpp"

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    Matrix matrix(lines.size(), lines[0].size());
    for (size_t r = 0; r < lines.size(); ++r) {
        for (size_t c = 0; c < lines[r].size(); ++c) {
            matrix[r][c] = lines[r][c];
        }
    }
    Field start = matrix.findChar('S')[0];
    vector<Field> beamHeads = {start};
    int beamSplitCount = 0;
    for (size_t step = 0; step < matrix.numRows()-1; ++step) {
        if (debug) {
            for (size_t r = 0; r < matrix.numRows(); ++r) {
                for (size_t c = 0; c < matrix.numCols(); ++c) {
                    bool isBeamHead = false;
                    for (const Field& head : beamHeads) {
                        if (head.rowIdx == r && head.colIdx == c) {
                            isBeamHead = true;
                            break;
                        }
                    }
                    if (isBeamHead) {
                        std::cout << 'O';
                    } else {
                        std::cout << matrix[r][c];
                    }
                }
                std::cout << "\n";
            }
        }
        vector<Field> newBeamHeads;
        for (const Field& head : beamHeads) {
            char nextField = matrix[head.rowIdx + 1][head.colIdx];
            if (nextField == '.') {
                newBeamHeads.push_back(Field(head.rowIdx + 1, head.colIdx));
            } else if (nextField == '^') {
                beamSplitCount++;
                newBeamHeads.push_back(Field(head.rowIdx + 1, head.colIdx - 1));
                newBeamHeads.push_back(Field(head.rowIdx + 1, head.colIdx + 1));
            }
        }
        newBeamHeads.erase(unique(newBeamHeads.begin(), newBeamHeads.end(), [](const Field& a, const Field& b) {
            return a.rowIdx == b.rowIdx && a.colIdx == b.colIdx;
        }), newBeamHeads.end());
        beamHeads = newBeamHeads;
    }
    return beamSplitCount;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day7/inputs/example1.txt"},
        {21},
        "./2025/day7/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}