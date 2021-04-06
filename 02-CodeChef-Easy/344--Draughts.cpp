#include<bits/stdc++.h>
#include<stdlib.h>
#define pb push_back
#define gc getchar_unlocked
//#define gc() getchar_unlocked();
#define pc putchar_unlocked
#define lli long long int
using namespace std;

 inline int read_int() {
   register char c = gc();
  while(c<'0' || c>'9') c = gc();
  int ret = 0;
  while(c>='0' && c<='9') {
    ret = 10 * ret + c - 48;
    c = gc();
  }
  return ret;
}
inline void print(lli a)
{
	char s[20];int i=0;
	do{s[i++]=a%10+'0';a/=10;}while(a);
	i--;
	while(i>=0)pc(s[i--]);
}
vector<int> v[50002];
lli c=0,cnt=0,tmp=0;
bool vis[50002]={0},a[50002];
inline void edge(int x,int y)
{
    v[x].pb(y);
    v[y].pb(x);
}
void dfs(int s)
{
    tmp++;
    vis[s]=1;
    if(a[s]==1)
    {
        c++;
        cnt+=tmp;
        tmp=0;
    }
    for(int i=0;i<v[s].size();i++)
    {
        if(!vis[v[s][i]])
            dfs(v[s][i]);
    }
    tmp--;
    if(tmp<0)
        tmp=0;
}
int main()
{
    lli n,m,va=0,x,y,ans=0;
    n=read_int();
    m=read_int();
    for(int i=1;i<=n;i++)
        a[i]=read_int();
    for(int i=0;i<m;i++)
    {
        x=read_int();
        y=read_int();
        edge(x,y);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]&&a[i])
        {
            c=0,tmp=0,cnt=0;
            dfs(i);
            va+=(c*(c-1))/2;
            if(cnt>1)
                ans+=cnt;
        }
    }
    print(va);pc(' ');print(ans);pc('\n');
    return 0;
}
