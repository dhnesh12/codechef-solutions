#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db double
#define ld long double
#define pii pair<int,int> 
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,b,a) for(int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(int i=(a);i<(b);++i)
#define fore(i,a) for(int i=0;i<a.size();++i) 
#define ls ch[x][0]
#define rs ch[x][1]
inline int rd()
{
	int x=0,w=1;char c=getchar();while(!isdigit(c)&&c!='-')c=getchar();
	if(c=='-')w=-1,c=getchar();while(isdigit(c))x=x*10+c-48,c=getchar();return x*w;
}
const int N=35,inf=2e9;
#define sqr(x) ((x)*(x))
int n,m,a[N][N][N],cnt[N][N][N][N];
vi gtmx(const vi&a,const vi&b)
{
	int na=a.size(),nb=b.size();vi c(na+nb-1,-inf);
	rep0(i,0,na)rep0(j,0,nb)c[i+j]=max(c[i+j],a[i]+b[j]);
	return c;
}
vi gtmn(const vi&a,const vi&b)
{
	int na=a.size(),nb=b.size();vi c(na+nb-1,inf);
	rep0(i,0,na)rep0(j,0,nb)c[i+j]=min(c[i+j],a[i]+b[j]);
	return c;
}
pair<vi,vi>sol(int x,int y,int z,int o)
{
	if(o==1)return mp((vi){1,1},(vi){1,1});
	vi mx,mn;int t=cnt[x][y][z][o];
	rep(dx,0,1)rep(dy,0,1)rep(dz,0,1)
	{
		pair<vi,vi>w=sol(x+dx*o/2,y+dy*o/2,z+dz*o/2,o/2);
		if(!dx&&!dy&&!dz)mx=w.X,mn=w.Y;
		else mx=gtmx(mx,w.X),mn=gtmn(mn,w.Y);
	}
	if(t==o*o*o||t==0)mx[0]=1;
	t=min(t,o*o*o-t);
	rep0(i,t,mn.size())mn[i]=1;
	return mp(mx,mn);
}
int init(int x,int y,int z,int o)
{
	if(o==1){cnt[x][y][z][o]=a[x][y][z];return cnt[x][y][z][o];}
	rep(dx,0,1)rep(dy,0,1)rep(dz,0,1)cnt[x][y][z][o]+=init(x+dx*o/2,y+dy*o/2,z+dz*o/2,o/2);
	return cnt[x][y][z][o];
} 
int main()
{
	n=rd();m=rd();
	rep(i,1,n)rep(j,1,n)rep(k,1,n)a[i][j][k]=rd();
	init(1,1,1,n);pair<vi,vi>ans=sol(1,1,1,n);
	printf("%d %d\n",ans.Y[m],ans.X[m]);return 0;
}