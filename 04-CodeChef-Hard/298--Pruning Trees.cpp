#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<bitset>
#include<map>
#include<set>
#include<queue>
#include<stack>
#define ll int
#define db double
#define mem(a) memset(a,0,sizeof(a))
#define exmem(a) memset(a,0x3f,sizeof(a))
#define maxn 105
#define maxm
#define mod
const ll inf=1e9;
using namespace std;
ll read(){
   ll a=0,f=1;char c=getchar();
   while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
   while(c>='0'&&c<='9'){a=a*10+c-'0';c=getchar();}
   return a*f;
}
ll n,cnt,h[maxn],D;
struct Edge{ll from,to,next,len;}e[maxn<<1];
void Add(ll f,ll t,ll l){e[++cnt]=(Edge){f,t,h[f],l};h[f]=cnt;}
void Madd(ll f,ll t,ll l){Add(f,t,l);Add(t,f,l);}
ll dis[maxn],d[maxn][maxn];
bool mp[maxn][maxn];
void Dis_Dfs(ll u,ll fa){
	ll v;
	for(int i=h[u];i;i=e[i].next){
		v=e[i].to;
		if(v==fa)continue;
		dis[v]=dis[u]+e[i].len;
		Dis_Dfs(v,u);
	}
}
void Pre(){
	for(int i=1;i<=n;i++)d[i][i]=0;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(d[k][i]<=D&&d[k][j]<=D)mp[i][j]=1;
			}
		}
	}
	dis[1]=0;Dis_Dfs(1,0);
}
ll tmp[maxn],f[maxn][maxn];
void Test(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<f[i][j]<<" ";
		}puts("");
	}puts("");
}
void Dfs(ll u,ll fa){
	ll v;f[u][u]=0;
	for(int i=h[u];i;i=e[i].next){
		v=e[i].to;if(v==fa)continue;
		Dfs(v,u);
//		Test();puts("!!!");
//		cout<<u<<": ";
//		for(int j=1;j<=n;j++)cout<<f[u][j]<<" ";puts("");
		memset(tmp,0x3f,sizeof(tmp));
		for(int A=1;A<=n;A++){
			for(int B=1;B<=n;B++){
				if(mp[A][B]&&dis[A]>=dis[B])tmp[A]=min(tmp[A],f[u][A]+f[v][B]);
				else tmp[A]=min(tmp[A],f[u][A]+f[v][B]+e[i].len);//,cout<<A<<" "<<B<<" "<<u<<" "<<v<<" "<<f[u][A]<<" "<<f[v][B]<<" "<<e[i].len<<" "<<tmp[A]<<endl;
				if(mp[B][A]&&dis[B]>=dis[A])tmp[B]=min(tmp[B],f[u][A]+f[v][B]);
			}
		}
		memcpy(f[u],tmp,sizeof(f[u]));
//		Test();puts("");
//		cout<<u<<": ";
//		for(int j=1;j<=n;j++)cout<<f[u][j]<<" ";puts("");
	}
}
ll T;
int main(){
	T=read();
	ll A,B,C,sum;
	while(T--){
		cnt=0;mem(h);memset(f,0x3f,sizeof(f));mem(mp);
		memset(d,0x3f,sizeof(d));
		n=read();D=read();sum=0;
		for(int i=1;i<n;i++){
			A=read()+1;B=read()+1;C=read();sum+=C;
			Madd(A,B,C);d[A][B]=d[B][A]=C;
		}
		Pre();
		Dfs(1,0);
		ll ans=inf;
		for(int i=1;i<=n;i++)ans=min(ans,f[1][i]);
		printf("%d\n",sum-ans);
	}
	return 0;
}
/*
3
5 10
0 1 10
1 2 9
1 3 10
3 4 9
10 1
0 1 1
0 2 1
1 3 1
1 4 1
2 5 1
2 6 1
2 7 1
6 8 1
6 9 1
7 2
0 1 1
0 2 2
1 3 1
1 4 2
2 5 2
2 6 7
*/