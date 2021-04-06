#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb push_back
#define VEC vector
#define For(i,a,b) for(int i=a;i<=b;i++)
#define For_(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,k) memset(a,k,sizeof(a))
#define sqr(a) ((a)*(a))

#define getc getchar_unlocked
//#define getc getchar
inline void read(int &x)//mini fast input function
{
    scanf("%d",x);
}
const int maxn=100010;
const int INF=0x3fffffff;
char S[maxn],T[maxn];
int F1[maxn],F2[maxn];
int A,B,K;
int n,m;
inline int min(int a,int b,int c)
{
    if(b<a)a=b;if(c<a)a=c;
    return a;
}
int Solve()
{
    if(n<m)swap(n,m),swap(S,T);
    if(K<A*(n-m))return -1;
    else if(A==0)return 0;
    else if(B==0)return A*(n-m);
    int delta=(K-A*(n-m))/(2*A);
    int *f1=F1,*f2=F2;
    for(int i=0;i<=n;i++)f1[i]=f2[i]=INF;
    for(int i=0;i<=m;i++)
    {
        int fr=max(i-delta,0);
        int la=min(n,i+n-m+delta);
        f1[0]=i;
        if(fr)
            f1[fr]=min(f2[fr-1]+(S[fr]==T[i]?0:B),f2[fr]+A);
        for(int j=fr+1;j<=la;j++)
            f1[j]=min(f2[j-1]+(S[j]==T[i]?0:B),f2[j]+A,f1[j-1]+A);
        if(la!=n)
            f1[la]=min(f2[la-1]+(S[la]==T[i]?0:B),f1[la-1]+A);
        swap(f1,f2);
    }
    return f2[n]<=K?f2[n]:-1;
}
int main()
{

    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",S+1);n=strlen(S+1);
        scanf("%s",T+1);m=strlen(T+1);
        scanf("%d%d%d",&A,&B,&K);
        cerr << 1 << endl;
        printf("%d\n",Solve());
    }
    return 0;
}
