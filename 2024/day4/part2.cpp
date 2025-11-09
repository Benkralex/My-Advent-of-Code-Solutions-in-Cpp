#include "../../lib/runFramework.cpp"
#include "../../lib/loadFile.cpp"
#include "../../lib/matrix.cpp"
#include "../../lib/helpers.cpp"

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

    vector<Field> fields = matrix.findChar('A');
    if (debug) {
        std::cout << "Total A found: " << fields.size() << "\n";
    }
    for (const Field& f : fields) {
        if (debug) {
            std::cout << "Found A at (" << f.rowIdx << ", " << f.colIdx << ")\n";
        }
        vector<char> diagonal = matrix.getDiagonalSourroundingField(f);
        int mCount = 0;
        int sCount = 0;
        for (char ch : diagonal) {
            if (ch == 'M') {
                mCount++;
            } else if (ch == 'S') {
                sCount++;
            }
        }
        string diagonalStr = join(diagonal, "");
        if (mCount == 2 && sCount == 2 && (contains(diagonalStr, "MM") || contains(diagonalStr, "SS"))) {
            if (debug) {
                std::cout << "  Valid X-MAS found\n";
            }
            count++;
        }
    }

    return count;
}

int main() {
    RunFramework rf(
        {"./2024/day4/inputs/example2.txt"},
        {9},
        "./2024/day4/inputs/input.txt",
        solve
    );
    rf.runInput();
    return 0;
}