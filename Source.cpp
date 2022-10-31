#include <iostream>
#include <iomanip>
#include <math.h> 
#include <stdlib.h> 
#include <stdio.h> 
using namespace std;

int gaussMethod(int m, int n, double* a);

int main()
{
    setlocale(LC_ALL, "Russian");
    int m, n, i, j, rank;
    double* a;
    double det;

    cout << "Введите количество строк\n";
    cin >> m;
    cout << "Введите количество столбцов\n";
    cin >> n;
    a = new double[m * n];
    cout << "Введите элементы матрицы:\n";
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cin >> a[i * n + j];
        }
    }
    rank = gaussMethod(m, n, a);
    cout << "Ступенчатый вид матрицы: \n";
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cout << setw(10) << fixed << setprecision(3) << a[i * n + j] << " ";
        }
        cout << "\n";
    }
    delete[] a;

    return 0;
}

// Приведение вещественной матрицы  к ступенчатому виду методом Гаусса с выбором максимального разрешающего элемента в столбце.
int gaussMethod(int m, int n, double* a)
{
    int i, j, k, l;
    double r;
    double eps = 0.0000006;
    i = 0; j = 0;

    while (i < m && j < n)
    {
        //Инвариант: минор матрицы в столбцах 0..j-1 уже приведен к ступенчатому виду, и строка
        //с индексом i-1 содержит ненулевой элемент в стобце с номером, меньшим чем j

        //Ищем максимальный элемент в j-м столбце, начиная с i-й строки
        r = 0.0;
        for (k = i; k < m; ++k)
        {
            if (fabs(a[k * n + j]) > r)
            {
                l = k; //Запомним номер строки
                r = fabs(a[k * n + j]); //и максимальный элемент
            }
        }

        if (r <= eps)
        {
            for (k = i; k < m; ++k)
            {
                a[k * n + j] = 0.0;
            }
            ++j;
            continue;
        }

        if (l != i)
        {
            // Меняем местами i-ю и l-ю строки
            for (k = j; k < n; ++k)
            {
                r = a[i * n + k];
                a[i * n + k] = a[l * n + k];
                a[l * n + k] = (-r);// Меняем знак строки
            }
        }

        //Утверждение: fabs(a[i*n + j]) > eps
        r = a[i * n + j];
        if (fabs(r) <= eps)
        {
            cout << "Ошибка\n";
        }

        //Обнуляем j-й столбец, начиная со строки i+1, применяя элементарные преобразования 2-го рода
        for (k = i + 1; k < m; ++k)
        {
            double c = (-a[k * n + j]) / r;
            //К k-й строке прибавляем i-ю, умноженную на c
            a[k * n + j] = 0.0;
            for (l = j + 1; l < n; ++l)
            {
                a[k * n + l] += c * a[i * n + l];
            }
        }
        ++i; ++j; //Переходим к следующему минору
    }
    return i;
}