#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

float probability(int **arr, int N, int j, int K)
{
    int sum = 0;
    for(int i = 0; i < K; i++)
    {
        sum += arr[N][i];
    }
    if(N == 0)
    {
        return arr[N][j]/sum;
    }
    else
    {
        return (arr[N][j] + probability(arr, N-1, j, K))/(sum + 1);
    }

}


int main()
{
    int N, K;
    cin >> N >> K;
    int **arr;
    arr = new int *[N];
    for(int i = 0; i < N; i++)
    {
        arr[i] = new int [K];
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < K; j++)
        {
            cin >> arr[i][j];
        }
    }
    for(int i = 0; i < K; i++)
    {
        cout << probability(arr, N-1, i, K) << " ";
    }
    return 0;
}
