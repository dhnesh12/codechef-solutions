#include<bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll> >
using namespace std;
const ll MOD = 1e9+7;
const int K=3;

matrix identity()
{
    matrix A(K+1,vector <ll> (K+1));
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            if(i==j)
                A[i][j]=1;
            else
                A[i][j]=0;
        }
    }
    return A;
}

matrix multiply(matrix A,matrix B)
{
    matrix C( K+1 , vector<ll> (K+1));
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            for(int k=1;k<=K;k++){
                 C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

matrix power_mod(matrix A,int p)
{
    matrix ret =identity();
    while(p>0){
        if(p%2==1)
            ret = multiply(ret,A);
        p=p/2;
        A=multiply(A,A);
    }
    return ret;
}

matrix input()
{
    matrix A(K+1,vector<ll> (K+1));
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            cin>>A[i][j];
        }
    }
    return A;
}

void output(matrix A)
{
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}

int wall(int N)
{
    vector <ll> F1(K+1);
    F1[1] = 1;
    F1[2] = 5;
    F1[3] = 11;

    matrix T(K+1,vector <ll> (K+1));
    T[1][1] = 0; T[1][2] = 1; T[1][3] = 0;
    T[2][1] = 0; T[2][2] = 0; T[2][3] = 1;
    T[3][1] = 2; T[3][2] = 4; T[3][3] = 1;
    if(N==1)
        return 1;
    T = power_mod(T,N-1);

    ll res = 0;
    for(int i=1;i<=K;i++)
        res = ( res + (T[1][i]*F1[i])%MOD )%MOD;
    return res;
}

int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<wall(n)<<endl;
    }
    return 0;
}
