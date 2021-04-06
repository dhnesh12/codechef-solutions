#include <bits/stdc++.h>
using namespace std;

long S, M;

int modM(int n)
{
    if(n < 0)
        return M - (-n%M);
    else    
        return n%M;
}

int main() 
{
    int N;
    
    cin >> N >> S >> M;
    long funcVals[N+1];
    funcVals[1] = S;
    for(int i = 2; i <= N; i++)
        funcVals[i] = modM((S*funcVals[i-1])%M - funcVals[(i+1)/2]);
    cout << funcVals[N] << endl;
}
