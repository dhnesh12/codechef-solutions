#include<iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int *arr, n, max = 0;
        cin >> n;
        arr = new int[n];
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
            if (arr[i] > max)
            {
                max = arr[i];
            }
        }
        cout << n - max<< endl;
    }
    return 0;
}