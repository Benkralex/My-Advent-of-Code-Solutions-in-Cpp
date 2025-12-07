#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/matrix.cpp"
#include <unordered_map>

using std::unordered_map, std::pair;

unordered_map<Field, long> cache;

long followPath(Matrix& matrix, const Field& start, bool debug) {
    if (cache.find(start) != cache.end()) {
        return cache[start];
    }
    if (matrix.numRows() <= start.rowIdx + 1) {
        return 1;
    }
    char nextField = matrix[start.rowIdx + 1][start.colIdx];
    long i;
    if (nextField == '.') {
        i = followPath(matrix, Field(start.rowIdx + 1, start.colIdx), debug);
    } else if (nextField == '^') {
        i = followPath(matrix, Field(start.rowIdx + 1, start.colIdx - 1), debug);
        i += followPath(matrix, Field(start.rowIdx + 1, start.colIdx + 1), debug);
    }
    cache[start] = i;
    return i;
}

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
    return followPath(matrix, start, debug);
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day7/inputs/example1.txt"},
        {40},
        "./2025/day7/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}