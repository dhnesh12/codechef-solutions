#include <iostream>
using namespace std;

void Byteland(int sec)
{
    long long int Bit = 1, Nibble = 0, Byte = 0;
    int time = 2;
    int oper = 1;

    for (int i = 0; i < sec; i++)
    {
        if (i == time && oper == 1)
        {
            Nibble = Bit;
            Bit = 0;
            oper = 2;
            time += 8;
        }
        else if (i == time && oper == 2)
        {
            Byte = Nibble;
            Nibble = 0;
            oper = 3;
            time += 16;
        }
        else if (i == time && oper == 3)
        {
            Bit = 2 * Byte;
            Byte = 0;
            oper = 1;
            time += 2;
        }
    }

    cout << Bit << " " << Nibble << " " << Byte << endl;
}


int main()
{
    int N, T;
    cin >> T;

    while (T--)
    {
        cin >> N;
        Byteland(N);
    }
}