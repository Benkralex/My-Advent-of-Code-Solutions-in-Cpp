#pragma once
#include "./stringRegexParser.cpp"
#include "./helpers.cpp"

class Field{
public:
    int rowIdx;
    int colIdx;
    Field(size_t rowIdx_, size_t colIdx_) 
        : rowIdx(rowIdx_), colIdx(colIdx_) {}
};

class Matrix {
private:
    std::vector<std::vector<char>> data;
    size_t rows;
    size_t cols;
public:
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        data.resize(r, std::vector<char>(c));
    }

    Matrix(size_t r, size_t c, char defaultVal) : rows(r), cols(c) {
        data.resize(r, std::vector<char>(c, defaultVal));
    }

    size_t numRows() const {
        return rows;
    }

    size_t numCols() const {
        return cols;
    }

    std::vector<char>& operator[](size_t index) {
        return data[index];
    }

    void transpose() {
        std::vector<std::vector<char>> transposed(cols, std::vector<char>(rows));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                transposed[j][i] = data[i][j];
            }
        }
        data = transposed;
        std::swap(rows, cols);
    }

    void rotate90Clockwise() {
        Matrix rotated(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                rotated[j][rows - 1 - i] = data[i][j];
            }
        }
        *this = rotated;
    }

    void rotate90CounterClockwise() {
        Matrix rotated(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                rotated[cols - 1 - j][i] = data[i][j];
            }
        }
        *this = rotated;
    }

    vector<Field> findChar(const char& q) {
        vector<Field> fields;
        for (size_t r = 0; r < numRows(); ++r) {
            for (size_t c = 0; c < numCols(); ++c) {
                if (data[r][c] == q) {
                    fields.push_back(Field(r, c));
                }
            }
        }
        return fields;
    }

    vector<char> getDiagonalSourroundingFields(const Field& f) {
        vector<char> diagonal;
        int r = f.rowIdx;
        int c = f.colIdx;
        vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
        };
        for (const auto& dir : directions) {
            int newR = r + dir.first;
            int newC = c + dir.second;
            if (newR >= 0 && newR < numRows() && newC >= 0 && newC < numCols()) {
                diagonal.push_back(data[newR][newC]);
            }
        }
        return diagonal;
    }

    vector<char> getVerticalSourroundingFields(const Field& f) {
        vector<char> vertical;
        int r = f.rowIdx;
        int c = f.colIdx;
        vector<std::pair<int, int>> directions = {
            {-1, 0}, {1, 0}
        };
        for (const auto& dir : directions) {
            int newR = r + dir.first;
            int newC = c + dir.second;
            if (newR >= 0 && newR < numRows() && newC >= 0 && newC < numCols()) {
                vertical.push_back(data[newR][newC]);
            }
        }
        return vertical;
    }

    vector<char> getHorizontalSourroundingFields(const Field& f) {
        vector<char> horizontal;
        int r = f.rowIdx;
        int c = f.colIdx;
        vector<std::pair<int, int>> directions = {
            {0, -1}, {0, 1}
        };
        for (const auto& dir : directions) {
            int newR = r + dir.first;
            int newC = c + dir.second;
            if (newR >= 0 && newR < numRows() && newC >= 0 && newC < numCols()) {
                horizontal.push_back(data[newR][newC]);
            }
        }
        return horizontal;
    }

    vector<char> getSourroundingFields(const Field& f) {
        vector<char> sourrounding;
        vector<char> diagonal = getDiagonalSourroundingFields(f);
        vector<char> vertical = getVerticalSourroundingFields(f);
        vector<char> horizontal = getHorizontalSourroundingFields(f);
        sourrounding.insert(sourrounding.end(), diagonal.begin(), diagonal.end());
        sourrounding.insert(sourrounding.end(), vertical.begin(), vertical.end());
        sourrounding.insert(sourrounding.end(), horizontal.begin(), horizontal.end());
        return sourrounding;
    }

    int searchHorizontal(const string& s) {
        int count = 0;
        for (size_t r = 0; r < numRows(); ++r) {
            string row = join(data[r], "") + "$" + join(reverse(data[r]), "");
            StringRegexParser parser(row);
            count += parser.getStartIndices(s).size();
        }
        return count;
    }

    int searchLeftToRight(const string& s) {
        int count = 0;
        for (size_t r = 0; r < numRows(); ++r) {
            string row = join(data[r], "");
            StringRegexParser parser(row);
            count += parser.getStartIndices(s).size();
        }
        return count;
    }

    int searchRightToLeft(const string& s) {
        int count = 0;
        for (size_t r = 0; r < numRows(); ++r) {
            string row = join(reverse(data[r]), "");
            StringRegexParser parser(row);
            count += parser.getStartIndices(s).size();
        }
        return count;
    }

    int searchVertical(const string& s) {
        Matrix transposed = *this;
        transposed.transpose();
        return transposed.searchHorizontal(s);
    }

    int searchTopToBottom(const string& s) {
        Matrix rotated = *this;
        rotated.rotate90CounterClockwise();
        return rotated.searchLeftToRight(s);
    }

    int searchBottomToTop(const string& s) {
        Matrix rotated = *this;
        rotated.rotate90CounterClockwise();
        return rotated.searchRightToLeft(s);
    }

    int searchDiagonalOne(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        size_t offset = rows - 1;
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + offset - r] = data[r][c];
            }
        }
        return shifted.searchVertical(s);
    }

    int searchTopLeftToBottomRight(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        size_t offset = rows - 1;
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + offset - r] = data[r][c];
            }
        }
        return shifted.searchTopToBottom(s);
    }

    int searchBottomRightToTopLeft(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        size_t offset = rows - 1;
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + offset - r] = data[r][c];
            }
        }
        return shifted.searchBottomToTop(s);
    }

    int searchDiagonalTwo(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + r] = data[r][c];
            }
        }
        return shifted.searchVertical(s);
    }

    int searchTopRightToBottomLeft(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + r] = data[r][c];
            }
        }
        return shifted.searchTopToBottom(s);
    }

    int searchBottomLeftToTopRight(const string& s) {
        Matrix shifted(rows, cols + (rows - 1), '$');
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                shifted[r][c + r] = data[r][c];
            }
        }
        return shifted.searchBottomToTop(s);
    }
};