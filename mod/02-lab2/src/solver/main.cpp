#include <iostream>
#include <vector>

class Matrix {
public:
    Matrix(int rows, int columns) : data(rows, std::vector<double>(columns, 0)), _rows(rows), _cols(columns) {}

    explicit Matrix(std::vector<std::vector<double>> _data) : data(std::move(_data)) {
        _rows = (int) data.size();
        _cols = (int) data[0].size();
    }

    double get(const int row, const int column) const {
        return this->data[row][column];
    }

    void set(const int row, const int column, double value) {
        this->data[row][column] = value;
    }

    int rows() const {
        return _rows;
    }

    int columns() const {
        return _cols;
    }

private:
    int _rows, _cols;
    std::vector<std::vector<double>> data;
};

Matrix inputMatrix() {
    int rows, columns;
    std::cout << "Input row count: ";
    std::cin >> rows;
    std::cout << "Input column count: ";
    std::cin >> columns;

    auto m = Matrix(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double value;
            std::cin >> value;
            m.set(i, j, value);
        }
    }
    return m;
}


void outputMatrix(const Matrix &m) {
    for (int i = 0; i < m.rows(); ++i) {
        for (int j = 0; j < m.columns(); ++j) {
            std::cout << m.get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    auto m = Matrix({{1, 2,  3,  4},
                     {5, 6,  7,  8},
                     {9, 10, 11, 12}});
    outputMatrix(m);
    return 0;
}
