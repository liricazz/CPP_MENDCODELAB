#include <iostream>
using namespace std;

class Matrix {
private:
    int** data;
    int rows, cols;
    static int totalMatrices;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        cout << "  [Конструктор] Создаем матрицу " << r << "x" << c << endl;
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
        totalMatrices++;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        cout << "  [Копирование] Копируем матрицу" << endl;
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        totalMatrices++;
    }

    ~Matrix() {
        cout << "  [Деструктор] Удаляем матрицу " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        totalMatrices--;
    }

    Matrix& operator=(const Matrix& other) {
        cout << "  [Присваивание] Присваиваем матрицу" << endl;
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

    int* operator[](int i) {
        if (i < 0 || i >= rows) throw "Индекс строки вне диапазона";
        return data[i];
    }

    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw "Матрицы разного размера!";
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) {
            throw "Нельзя умножить - несовместимые размеры!";
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    operator bool() {
        if (rows != cols) {
            cout << "  Матрица не квадратная, считаем вырожденной" << endl;
            return false;
        }
        if (rows == 2) {
            int det = data[0][0] * data[1][1] - data[0][1] * data[1][0];
            cout << "  Определитель = " << det << endl;
            return det != 0;
        }
        return true;
    }

    static int getCount() { return totalMatrices; }

    void fill(int value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = value;
            }
        }
    }

    void set(int i, int j, int value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            data[i][j] = value;
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            cout << "  ";
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int Matrix::totalMatrices = 0;

int main() {

    try {
        cout << "1. Создание матриц:" << endl;
        Matrix A(2, 2);
        Matrix B(2, 2);

        cout << "\n2. Заполнение матриц:" << endl;
        A.fill(2);
        B.fill(3);

        cout << "Матрица A:" << endl;
        A.print();
        cout << "Матрица B:" << endl;
        B.print();

        cout << "\n3. Оператор индексирования:" << endl;
        cout << "A[0][0] = " << A[0][0] << endl;
        cout << "A[1][1] = " << A[1][1] << endl;

        cout << "\n4. Изменение элемента через оператор []:" << endl;
        A[0][1] = 5;
        cout << "Матрица A после изменения A[0][1] = 5:" << endl;
        A.print();

        cout << "\n5. Сложение матриц A + B:" << endl;
        Matrix C = A + B;
        C.print();

        cout << "\n6. Умножение матриц:" << endl;
        Matrix D(2, 3);
        D.fill(1);
        Matrix E(3, 2);
        E.fill(2);

        cout << "Матрица D (2x3):" << endl;
        D.print();
        cout << "Матрица E (3x2):" << endl;
        E.print();

        Matrix F = D * E;
        cout << "Результат D * E (2x2):" << endl;
        F.print();

        cout << "\n7. Проверка на невырожденность:" << endl;
        Matrix G(2, 2);
        G.set(0, 0, 1);
        G.set(0, 1, 2);
        G.set(1, 0, 3);
        G.set(1, 1, 4);

        cout << "Матрица G:" << endl;
        G.print();
        if (G) {
            cout << "  Матрица G невырожденная" << endl;
        } else {
            cout << "  Матрица G вырожденная" << endl;
        }

        Matrix H(2, 2);
        H.set(0, 0, 1);
        H.set(0, 1, 2);
        H.set(1, 0, 2);
        H.set(1, 1, 4);

        cout << "\nМатрица H:" << endl;
        H.print();
        if (H) {
            cout << "  Матрица H невырожденная" << endl;
        } else {
            cout << "  Матрица H вырожденная" << endl;
        }

        cout << "\n8. Статистика:" << endl;
        cout << "Всего создано матриц: " << Matrix::getCount() << endl;

        cout << "\n9. Проверка исключений:" << endl;
        try {
            cout << "  Пытаемся сложить матрицы разных размеров..." << endl;
            Matrix X(2, 2);
            Matrix Y(3, 3);
            Matrix Z = X + Y;
        } catch (const char* msg) {
            cout << "  Ошибка: " << msg << endl;
        }

        try {
            cout << "\n  Пытаемся умножить несовместимые матрицы..." << endl;
            Matrix X(2, 3);
            Matrix Y(2, 3);
            Matrix Z = X * Y;
        } catch (const char* msg) {
            cout << "  Ошибка: " << msg << endl;
        }

        cout << "\n10. Демонстрация работы деструкторов:" << endl;
        {
            Matrix temp(1, 1);
            temp.fill(42);
            cout << "  Временная матрица создана, значение: " << temp[0][0] << endl;
        }

    } catch (const char* msg) {
        cout << "Ошибка: " << msg << endl;
    }

    cout << "\nМатриц осталось: " << Matrix::getCount() << endl;

    return 0;
}