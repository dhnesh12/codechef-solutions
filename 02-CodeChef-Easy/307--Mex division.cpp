#include <bits/stdc++.h>
using namespace std;
const int MaxN=5*1e5+5;
const   long long base=1000000007;
int n,K,a[MaxN],d[MaxN];
typedef long long ll;
ll f[MaxN],s[MaxN];

void process()
{
    f[0]=s[0]=1;
    for(int i=1;i<=n;i++)
    {
        f[i]=s[i-1];
        s[i]=(s[i-1]+f[i])%base;
    }
//    for(int i=1;i<=n;i++)
//        cout<<f[i]<<" "<<s[i]<<endl;
}
int cnt;

void ins(int x)
{
    if (x>K) return;
    d[x]++;
    if (d[x]==1) cnt++;
}

void del(int x)
{
    if (x>K)return;
    d[x]--;
    if (d[x]==0) cnt--;
}

void process2()
{
    int l=1;
    f[0]=s[0]=1;
    for(int i=1;i<=n;i++)
        if (i<K)
        {
            f[i]=s[i-1];
            s[i]=(s[i-1]+f[i])%base;
            ins(a[i]);
        }
        else
        {
            ins(a[i]);
            while(cnt==K+1)
            {
                del(a[l]);l++;
            }
            f[i]=(s[i-1]-s[l-2]+base)%base;
            s[i]=(s[i-1]+f[i])%base;
        }
//    for(int i=1;i<=n;i++)
//        cout<<f[i]<<endl;
}

void Xuli()
{
    if (K>n) process();
    else
        process2();
    printf("%lld",f[n]);
}

int main()
{
//    freopen("MEXDIV.inp","r",stdin);
//    freopen("MEXDIV.out","w",stdout);
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    Xuli();
}
