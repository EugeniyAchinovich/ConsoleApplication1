#include <iostream>
#include <cstddef>
#include <cmath>

/*
    Класс Matrix представляет матрицы и операции с ними

    Сложение, умножение на скаляр и копирование матриц осуществляются перегруженными операторами
    Вычисление определителя и транспонирование осуществляется соответствующими методами в классе
*/


class Matrix
{
private:
    int n;
    int m;
    int** value;

    int _GetDeterminant(int);

public:
    Matrix(const int, const int, int**);
    ~Matrix();

    int GetDeterminant();
    void Print();
    Matrix Transpose();

    const Matrix operator=(const Matrix&);
    const Matrix operator+(const Matrix&);
    const Matrix operator*(const int);
};


Matrix::Matrix(const int n, const int m, int** array = NULL)
{
    this->n = n;
    this->m = m;
    this->value = new int* [n];

    for (int i = 0; i < m; i++)
        value[i] = new int[n];


    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            this->value[i][j] = array ? array[i][j] : 0;
}

Matrix::~Matrix()
{

}

const Matrix Matrix::operator=(const Matrix& B)
{
    if (this->n != B.n || this->m != B.m) {
        std::cout << "Error: arrays must have the same size" << std::endl;
        return B;
    }

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->value[i][j] = B.value[i][j];
}

const Matrix Matrix::operator+(const Matrix& B)
{
    if (this->n != B.n || this->m != B.m) {
        std::cout << "Error: arrays must have the same size" << std::endl;
        return B;
    }

    Matrix A(this->n, this->m);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            A.value[i][j] = this->value[i][j] + B.value[i][j];

    return A;
}

const Matrix Matrix::operator*(const int a)
{
    Matrix A(this->n, this->m);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            A.value[i][j] = this->value[i][j] * a;

    return A;
}

Matrix Matrix::Transpose()
{
    Matrix B(this->m, this->n, this->value);

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->value[i][j] = B.value[j][i];

    return B;
}

void Matrix::Print()
{
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {
            std::cout << value[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int Matrix::GetDeterminant()
{
    if (this->n != this->m) {
        std::cout << "\nError: Cannot calculate determinant of non-square matrix" << std::endl;
        return -1;
    }
    _GetDeterminant(this->n);
}

int Matrix::_GetDeterminant(int n)
{
    if (n == 1)
        return this->value[0][0];
    else if (n == 2)
        return this->value[0][0] * this->value[1][1] - this->value[0][1] * this->value[1][0];
    else {
        int d = 0;
        for (int k = 0; k < n; k++) {
            int** m = new int* [n - 1];
            for (int i = 0; i < n - 1; i++) {
                m[i] = new int[n - 1];
            }
            for (int i = 1; i < n; i++) {
                int t = 0;
                for (int j = 0; j < n; j++) {
                    if (j == k)
                        continue;
                    m[i - 1][t] = this->value[i][j];
                    t++;
                }
            }
            d += pow(-1, k + 2) * this->value[0][k] * _GetDeterminant(n - 1);
        }
        return d;
    }
}

int main()
{
    int** arr = new int* [3];
    for (int i = 0; i < 3; i++)
        arr[i] = new int[3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)          // Инициализация массива
            arr[i][j] = i + 1;


    Matrix M(2, 5);                          // Создание пустой матрицы 2x5


    std::cout << "Matrix M:" << std::endl;
    M.Print();                               // Вывод на экран пустой матрицы


    Matrix A(3, 3, arr);                     // Создание матрицы A 3x3, заполненной значениями массива
    std::cout << "\nMatrix A:" << std::endl;
    A.Print();                               // Вывод матрицы A


    A = A.Transpose();                       // Транспонирование матрицы A
    std::cout << "\nTransposed Matrix A:" << std::endl;
    A.Print();                               // Вывод матрицы транспонированной матрицы A


    Matrix B(3, 3, arr);                     // Создание второй матрицы B 3x3, заполненной значениями массива
    Matrix C = A + B;                        // Сложение матриц A и B. Результат (сумма) - матрица C

    std::cout << "\nC = A + B =" << std::endl;
    C.Print();                               // Вывод полученной матрицы C


    C = C * -3;                              // Умножение матрицы С на скаляр
    std::cout << "\nC * -3 =" << std::endl;
    C.Print();                               // Вывод умноженной матрицы C

    int d = B.GetDeterminant();              // Вычисление определителя матрицы B и вывод его на экран
    std::cout << "\nDet B = " << d;

    d = M.GetDeterminant();                  // Попытка вычислить определитель неквадратной матрицы M.
                                             // Результат - вывод сообщения о невозможности вычисления определителя.

    return 0;
}
