#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/matrix.cpp"

int solve(string path, bool debug) {
    FileLoader loader(path);
    int count = 0;
    vector<string> lines = loader.getLines();
    Matrix matrix(lines.size(), lines[0].size());
    for (size_t r = 0; r < lines.size(); ++r) {
        for (size_t c = 0; c < lines[r].size(); ++c) {
            matrix[r][c] = lines[r][c];
        }
    }

    count += matrix.searchHorizontal("XMAS");
    count += matrix.searchVertical("XMAS");
    count += matrix.searchDiagonalOne("XMAS");
    count += matrix.searchDiagonalTwo("XMAS");
    return count;
}

int main() {
    RunFramework rf(
        {"./2024/day4/inputs/example1.txt", "./2024/day4/inputs/example2.txt"},
        {4, 18},
        "./2024/day4/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}