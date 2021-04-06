

// discountjaws.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int opsize[1001], poz[1001][31];
int nop;

int isPrime(int P)
{
    for (int i = 2; i * i <= P; i++)
    {
        if (P % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void solve(int i, int j)
{
    int len = j - i + 1;
    if (len == 1)
    {
        return;
    }
    for (int P = len; P >= 2; P--)
    {
        if ((len % P == 0) and isPrime(P))
        {
            int Q = len / P, k, l;
            for (k = i; k <= j; k += Q)
            {
                solve(k, k + Q - 1);
            }
            for (k = 0; k < Q; k++)
            {
                nop++;
                opsize[nop] = P;
                for (l = 1; l <= P; l++)
                {
                    poz[nop][l] = i + k + (l - 1) * Q;
                }
            }
            break;
        }
    }
}

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int N, i, j;
        cin >> N;
        for (i = 1; i <= N; i++)
        {
            cin >> j;
        }
        nop = 0;
        solve(1, N);
        cout << nop << "\n";
        for (i = 1; i <= nop; i++)
        {
            cout << opsize[i];
            for (int j = 1; j <= opsize[i]; j++)
            {
                cout << " " << poz[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
