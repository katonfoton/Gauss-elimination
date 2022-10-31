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

    cout << "������� ���������� �����\n";
    cin >> m;
    cout << "������� ���������� ��������\n";
    cin >> n;
    a = new double[m * n];
    cout << "������� �������� �������:\n";
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cin >> a[i * n + j];
        }
    }
    rank = gaussMethod(m, n, a);
    cout << "����������� ��� �������: \n";
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

// ���������� ������������ �������  � ������������ ���� ������� ������ � ������� ������������� ������������ �������� � �������.
int gaussMethod(int m, int n, double* a)
{
    int i, j, k, l;
    double r;
    double eps = 0.0000006;
    i = 0; j = 0;

    while (i < m && j < n)
    {
        //���������: ����� ������� � �������� 0..j-1 ��� �������� � ������������ ����, � ������
        //� �������� i-1 �������� ��������� ������� � ������ � �������, ������� ��� j

        //���� ������������ ������� � j-� �������, ������� � i-� ������
        r = 0.0;
        for (k = i; k < m; ++k)
        {
            if (fabs(a[k * n + j]) > r)
            {
                l = k; //�������� ����� ������
                r = fabs(a[k * n + j]); //� ������������ �������
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
            // ������ ������� i-� � l-� ������
            for (k = j; k < n; ++k)
            {
                r = a[i * n + k];
                a[i * n + k] = a[l * n + k];
                a[l * n + k] = (-r);// ������ ���� ������
            }
        }

        //�����������: fabs(a[i*n + j]) > eps
        r = a[i * n + j];
        if (fabs(r) <= eps)
        {
            cout << "������\n";
        }

        //�������� j-� �������, ������� �� ������ i+1, �������� ������������ �������������� 2-�� ����
        for (k = i + 1; k < m; ++k)
        {
            double c = (-a[k * n + j]) / r;
            //� k-� ������ ���������� i-�, ���������� �� c
            a[k * n + j] = 0.0;
            for (l = j + 1; l < n; ++l)
            {
                a[k * n + l] += c * a[i * n + l];
            }
        }
        ++i; ++j; //��������� � ���������� ������
    }
    return i;
}