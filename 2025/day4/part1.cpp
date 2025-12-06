#include "../../lib/runFrameworkLong.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/helpers.cpp"
#include "../../lib/matrix.cpp"

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
    for (const Field f : matrix.findChar('@')) {
        vector<char> surrounding = matrix.getSourroundingFields(f);
        int count = 0;
        for (const char ch : surrounding) {
            if (ch == '@') {
                count++;
            }
        }
        if (count < 4) {
            answer++;
        }
    }
    return answer;
}

int main() {
    RunFrameworkLong rf(
        {"./2025/day4/inputs/example1.txt"},
        {13},
        "./2025/day4/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}