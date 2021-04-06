#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
char a[25],b[25];
long long mem[25],m;
long long rec(char *s,long long n,long long idx)
{
    if(idx==0) return 1;
    long long ans=0;
    char kb;
    ans=(ans+mem[idx-1]*24%MOD)%MOD;
    s[idx]='A';
    if(n-idx+1>=m)
    {
        kb=s[idx+m];
        s[idx+m]='\0';
        s[idx]='A';
        if(strcmp(a,s+idx)>0||strcmp(s+idx,b)>0)
            ans=(ans+rec(s,n,idx-1))%MOD;
        s[idx]='B';
        if(strcmp(a,s+idx)>0||strcmp(s+idx,b)>0)
            ans=(ans+rec(s,n,idx-1))%MOD;
        s[idx+m]=kb;
    }
    else
    {
        s[idx]='A';ans=(ans+rec(s,n,idx-1))%MOD;
        s[idx]='B';ans=(ans+rec(s,n,idx-1))%MOD;
    }
    return ans;
}
char s[25];
int main()
{
    long long all,t,kb,i,n;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld%s%s",&n,&m,a,b);
        mem[0]=1;
        for(i=1;i<m;i++) mem[i]=mem[i-1]*26%MOD;
        for(i=m;i<=n;i++)
            mem[i]=rec(s,i,i);
        printf("%lld\n",mem[n]);
    }
}
