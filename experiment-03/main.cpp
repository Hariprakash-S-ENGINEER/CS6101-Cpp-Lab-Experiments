#include <cassert>
#include <cstddef>
#include <iostream>

class Matrix2x2 {
public:
    Matrix2x2(int a = 0, int b = 0, int c = 0, int d = 0)
        : data_{{a, b}, {c, d}} {}

    Matrix2x2 operator+(const Matrix2x2& other) const {
        Matrix2x2 result;
        for (std::size_t row = 0; row < 2; ++row)
            for (std::size_t col = 0; col < 2; ++col)
                result.data_[row][col] = data_[row][col] + other.data_[row][col];
        return result;
    }

    Matrix2x2 operator*(const Matrix2x2& other) const {
        Matrix2x2 result;
        for (std::size_t row = 0; row < 2; ++row)
            for (std::size_t col = 0; col < 2; ++col)
                for (std::size_t k = 0; k < 2; ++k)
                    result.data_[row][col] += data_[row][k] * other.data_[k][col];
        return result;
    }

    int* operator[](std::size_t row) { return data_[row]; }
    const int* operator[](std::size_t row) const { return data_[row]; }

    friend std::ostream& operator<<(std::ostream& out, const Matrix2x2& matrix) {
        for (const auto& row : matrix.data_)
            out << row[0] << ' ' << row[1] << '\n';
        return out;
    }

private:
    int data_[2][2];
};

int main() {
    const Matrix2x2 a(1, 2, 3, 4);
    const Matrix2x2 b(5, 6, 7, 8);
    const Matrix2x2 sum = a + b;
    const Matrix2x2 product = a * b;

    assert(sum[0][0] == 6 && sum[1][1] == 12);
    assert(product[0][0] == 19 && product[0][1] == 22);
    assert(product[1][0] == 43 && product[1][1] == 50);

    std::cout << "Matrix A:\n" << a << "Matrix B:\n" << b
              << "Addition:\n" << sum << "Multiplication:\n" << product
              << "All checks passed.\n";
}
