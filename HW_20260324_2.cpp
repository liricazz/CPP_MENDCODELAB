#include <iostream>
#include <stdexcept>
using namespace std;

namespace MatrixSpace {

class IndexOutOfRange : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: индекс выходит за пределы матрицы!";
    }
};

class Matrix {
private:
    int** data;
    int rows;
    int cols;
    static int matrixCount;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw invalid_argument("Размеры матрицы должны быть положительными!");
        }
        
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols]();
        }
        matrixCount++;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        matrixCount++;
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        matrixCount--;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            data = new int*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    int& operator()(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw IndexOutOfRange();
        }
        return data[row][col];
    }
    
    const int& operator()(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw IndexOutOfRange();
        }
        return data[row][col];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Размеры матриц не совпадают!");
        }
        
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Несовместимые размеры для умножения!");
        }
        
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    class Iterator {
    private:
        Matrix& matrix;
        int row;
        int col;
        
    public:
        Iterator(Matrix& m, int r, int c) : matrix(m), row(r), col(c) {}
        
        bool hasNext() const {
            return row < matrix.rows;
        }
        
        int& next() {
            if (row >= matrix.rows) {
                throw out_of_range("Нет больше элементов!");
            }
            int& value = matrix.data[row][col];
            col++;
            if (col >= matrix.cols) {
                col = 0;
                row++;
            }
            return value;
        }
    };

    Iterator getIterator() {
        return Iterator(*this, 0, 0);
    }

    void fill(int value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = value;
            }
        }
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    static int getMatrixCount() { return matrixCount; }
};

int Matrix::matrixCount = 0;

}

int main() {
    using namespace MatrixSpace;
    
    try {
        cout << "Введите размеры первой матрицы (строки столбцы): ";
        int r1, c1;
        cin >> r1 >> c1;
        Matrix A(r1, c1);
        
        cout << "Введите элементы первой матрицы:" << endl;
        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c1; j++) {
                int val;
                cin >> val;
                A(i, j) = val;
            }
        }
        
        cout << "Введите размеры второй матрицы (строки столбцы): ";
        int r2, c2;
        cin >> r2 >> c2;
        Matrix B(r2, c2);
        
        cout << "Введите элементы второй матрицы:" << endl;
        for (int i = 0; i < r2; i++) {
            for (int j = 0; j < c2; j++) {
                int val;
                cin >> val;
                B(i, j) = val;
            }
        }

        cout << "\n МАТРИЦА A " << endl;
        A.print();
        cout << "\n МАТРИЦА B " << endl;
        B.print();

        try {
            Matrix C = A + B;
            cout << "\n СУММА A + B " << endl;
            C.print();
        } catch (const exception& e) {
            cout << "\nСложение невозможно: " << e.what() << endl;
        }

        try {
            Matrix D = A * B;
            cout << "\n ПРОИЗВЕДЕНИЕ A * B:" << endl;
            D.print();
        } catch (const exception& e) {
            cout << "\nУмножение невозможно: " << e.what() << endl;
        }

        cout << "\n ОБХОД МАТРИЦЫ A С ПОМОЩЬЮ ИТЕРАТОРА:" << endl;
        auto it = A.getIterator();
        while (it.hasNext()) {
            cout << it.next() << " ";
        }
        cout << endl;

        cout << "\n СТАТИСТИКА: " << endl;
        cout << "Всего матриц создано: " << Matrix::getMatrixCount() << endl;
        
    } catch (const IndexOutOfRange& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    return 0;
}