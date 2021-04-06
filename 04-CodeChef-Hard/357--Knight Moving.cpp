#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define fi first
#define se second 
#define MP make_pair
#define N   1100000
#define M   1100
#define eps 1e-8
#define MOD 1000000007
#define pi  acos(-1)

class Point
{
    public: 
    int x,y;
};

ll dp[M*2+1][M*2+1];
bool vis[M*2+1][M*2+1];
bool flag[M*2+1];
ll fac[N],inv[N];
Point b[20],A,B,d;
ll f[20];
int K;

int read()
{ 
   int v=0,f=1;
   char c=getchar();
   while(c<48||57<c) {if(c=='-') f=-1; c=getchar();}
   while(48<=c&&c<=57) v=(v<<3)+v+v+c-48,c=getchar();
   return v*f;
}

void add(ll &a,ll &b)
{
    if(a==-1||b==-1) a=-1;
     else a=(a+b)%MOD;
}
 
bool depend(Point &a,Point &b) //线性相关 
{
    //printf("%d %d %d %d\n",a.x,b.y,a.y,b.x); 
    return a.x*b.y==a.y*b.x;
}

bool operator < (Point &a,Point &b)
{
    return a.x+a.y<b.x+b.y;
}

void swap_xy()
{
    swap(A.x,A.y);
    swap(B.x,B.y);
    swap(d.x,d.y);
    for(int i=1;i<=K;i++) swap(b[i].x,b[i].y);
}

int solve_depend()
{
    //printf("YES\n");
    //printf("%d %d\n",d.x,d.y);
    if(!depend(A,d)||!depend(B,d)) return 0;
    //A,B中可能有0
    if(!A.x&&!A.y&&!B.x&&!B.y) 
    {
        if(!d.x&&!d.y) return -1;
        return 0;
    }
    if(!A.x)
    {
        if(A.y) swap_xy();
         else if(B.x) swap(A,B);
          else
          {
                  swap(A,B);
                  swap_xy();
          }    
    }
    memset(dp,0,sizeof(dp));
    memset(vis,0,sizeof(vis));
    memset(flag,0,sizeof(flag));
    for(int i=1;i<=K;i++)
     if(depend(b[i],A)&&depend(b[i],B)) flag[b[i].x+M]=1;
    if((!A.x&&!A.y)||(!B.x&&!B.y)) dp[0][M]=-1;
     else dp[0][M]=1;
    vis[0][M]=true; 
    ll ans=0;
    for(int i=0;i<M*2;i++)
    {
        for(int j=-M;j<=M;j++)
        {
            int v=j+M;
            if(!flag[v])    //无障碍 
            {
                if(!vis[i][v]) continue;
                if(j>500||j<-500||i>1000) dp[i][v]=-1; //若能绕回dest必定有无数种,若回不来那-1也没用
                if(v+A.x>=0&&v+A.x<=2*M)    //A
                {
                    add(dp[i+1][v+A.x],dp[i][v]);
                    vis[i+1][v+A.x]=true;
                }
                if(A.x!=B.x&&v+B.x>=0&&v+B.x<=2*M) //B
                {
                    add(dp[i+1][v+B.x],dp[i][v]);
                    vis[i+1][v+B.x]=true;
                }
            }
        }
        add(ans,dp[i][d.x+M]);
    }
    return ans;
}

bool change(Point &p)
{
    int k=A.y*B.x-A.x*B.y;
    int a=p.y*B.x-p.x*B.y;
    int b=p.x*A.y-p.y*A.x;
    //printf("%d %d %d\n",k,a,b);
    if(a%k||b%k) return false;
    p.x=a/k; p.y=b/k;
    return true;
}

ll C(int x,int y)
{
    return fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}

ll calc(Point &a,Point &b)
{
    int x=b.x-a.x;
    int y=b.y-a.y;
    if(x<0||y<0) return 0;
    return C(x+y,x);
}

int solve_independ()
{
    if(!change(d)) return 0;    //终点在变换后不是整点
    if(d.x<0||d.y<0) return 0;     //终点在变换后不是整点
    int n=0;
    for(int i=1;i<=K;i++)     //障碍变换 
     if(change(b[i]))
      if(b[i].x>=0&&b[i].y>=0) b[++n]=b[i];
    sort(b+1,b+n+1);     //障碍排序 
    Point O=(Point){0,0};
    ll ans=calc(O,d);
    
    for(int i=1;i<=n;i++)
    {
        f[i]=calc(O,b[i]);
        for(int j=1;j<i;j++) 
         f[i]=(f[i]-f[j]*calc(b[j],b[i])%MOD)%MOD;
        ans=(ans-f[i]*calc(b[i],d)%MOD)%MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    return ans;
}
    
int solve()
{
    if(depend(A,B)) return solve_depend();
    else return solve_independ();
}

int main()
{
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    fac[0]=1;
    for(int i=1;i<=N-1;i++) fac[i]=fac[i-1]*i%MOD;
    inv[0]=inv[1]=1;
    for(int i=2;i<=N-1;i++) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    for(int i=1;i<=N-1;i++) inv[i]=inv[i-1]*inv[i]%MOD; 
    int cas;
    scanf("%d",&cas);
    while(cas--)
    {
        scanf("%d%d%d",&d.x,&d.y,&K);
        scanf("%d%d%d%d",&A.x,&A.y,&B.x,&B.y);
        for(int i=1;i<=K;i++) scanf("%d%d",&b[i].x,&b[i].y);
        printf("%d\n",solve());
    }      
    return 0;
}
