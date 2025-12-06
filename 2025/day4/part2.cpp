#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/matrix.cpp"

vector<Field> getRemovableRoles(Matrix& matrix) {
    vector<Field> removable;
    for (const Field f : matrix.findChar('@')) {
        vector<char> surrounding = matrix.getSourroundingFields(f);
        int count = 0;
        for (const char ch : surrounding) {
            if (ch == '@') {
                count++;
            }
        }
        if (count < 4) {
            removable.push_back(f);
        }
    }
    return removable;
}

long solve(string path, bool debug) {
    FileLoader loader(path);
    vector<string> lines = loader.getLines();
    int answer = 0;
    int width = lines[0].size();
    int height = lines.size();
    Matrix matrix(height, width, '.');
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            matrix[r][c] = lines[r][c];
        }
    }
    vector<Field> removable = getRemovableRoles(matrix);
    while (!removable.empty()) {
        for (const Field f : removable) {
            matrix[f.rowIdx][f.colIdx] = '.';
            answer++;
        }
        removable = getRemovableRoles(matrix);
    }
    return answer;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day4/inputs/example1.txt"},
        {43},
        "./2025/day4/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}