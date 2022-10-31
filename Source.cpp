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

// Ïðèâåäåíèå âåùåñòâåííîé ìàòðèöû  ê ñòóïåí÷àòîìó âèäó ìåòîäîì Ãàóññà ñ âûáîðîì ìàêñèìàëüíîãî ðàçðåøàþùåãî ýëåìåíòà â ñòîëáöå.
int gaussMethod(int m, int n, double* a)
{
    int i, j, k, l;
    double r;
    double eps = 0.0000006;
    i = 0; j = 0;

    while (i < m && j < n)
    {
        //Èíâàðèàíò: ìèíîð ìàòðèöû â ñòîëáöàõ 0..j-1 óæå ïðèâåäåí ê ñòóïåí÷àòîìó âèäó, è ñòðîêà
        //ñ èíäåêñîì i-1 ñîäåðæèò íåíóëåâîé ýëåìåíò â ñòîáöå ñ íîìåðîì, ìåíüøèì ÷åì j

        //Èùåì ìàêñèìàëüíûé ýëåìåíò â j-ì ñòîëáöå, íà÷èíàÿ ñ i-é ñòðîêè
        r = 0.0;
        for (k = i; k < m; ++k)
        {
            if (fabs(a[k * n + j]) > r)
            {
                l = k; //Çàïîìíèì íîìåð ñòðîêè
                r = fabs(a[k * n + j]); //è ìàêñèìàëüíûé ýëåìåíò
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
            // Ìåíÿåì ìåñòàìè i-þ è l-þ ñòðîêè
            for (k = j; k < n; ++k)
            {
                r = a[i * n + k];
                a[i * n + k] = a[l * n + k];
                a[l * n + k] = (-r);// Ìåíÿåì çíàê ñòðîêè
            }
        }

        //Óòâåðæäåíèå: fabs(a[i*n + j]) > eps
        r = a[i * n + j];
        if (fabs(r) <= eps)
        {
            cout << "Îøèáêà\n";
        }

        //Îáíóëÿåì j-é ñòîëáåö, íà÷èíàÿ ñî ñòðîêè i+1, ïðèìåíÿÿ ýëåìåíòàðíûå ïðåîáðàçîâàíèÿ 2-ãî ðîäà
        for (k = i + 1; k < m; ++k)
        {
            double c = (-a[k * n + j]) / r;
            //Ê k-é ñòðîêå ïðèáàâëÿåì i-þ, óìíîæåííóþ íà c
            a[k * n + j] = 0.0;
            for (l = j + 1; l < n; ++l)
            {
                a[k * n + l] += c * a[i * n + l];
            }
        }
        ++i; ++j; //Ïåðåõîäèì ê ñëåäóþùåìó ìèíîðó
    }
    return i;
}
