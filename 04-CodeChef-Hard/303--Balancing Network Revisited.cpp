#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m;
char s[N];
int g[N][2],bel[N],e[N],F[N],tag[N];
inline int get(int x){return g[bel[x]][1]==x;}
inline int gt(int x){if(s[x])return s[x];if(!F[x])return s[x]='0';return s[x]=gt(F[x])^tag[x];}
int T;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;++i)g[i][1]=bel[i]=i,g[i][0]=0;
		for(int i=1;i<=m+1;++i)F[i]=tag[i]=e[i]=s[i]=0;
		for(int i=1,X,Y;i<=m;++i){
			cin>>X>>Y;
			int x=bel[X],y=bel[Y];
			int _x=get(X),_y=get(Y);
			if(x==y){
				s[e[x]]='0',e[x]=i;
				if(g[x][1]==X)swap(g[x][0],g[x][1]);
			}else if(!g[x][0]&&!g[y][0]){
				bel[X]=y,g[y][0]=X,g[x][1]=0;
				e[y]=i;
			}else if(!g[x][0]&&g[y][0]){
				s[e[y]]=!_y+'0';
				e[y]=0;
				g[x][!_x]=Y,g[y][_y]=0;
				swap(g[x][0],g[x][1]);
				e[x]=i;
				if(g[y][1]==0)swap(g[y][0],g[y][1]);
			}else if(!g[y][0]&&g[x][0]){
				s[e[x]]=!_x+'0';
				e[x]=0;
				g[y][!_y]=X,g[x][_x]=0;
				e[y]=i;
				if(g[x][1]==0)swap(g[x][0],g[x][1]);
			}else{
				F[e[x]]=e[y],tag[e[x]]=_x^_y^1;
				swap(g[x][!_x],g[y][_y]);
				e[x]=i;
				if(_x)swap(g[x][0],g[x][1]);
			}
			if(g[x][0])bel[g[x][0]]=x;
			if(g[x][1])bel[g[x][1]]=x;
			if(g[y][0])bel[g[y][0]]=y;
			if(g[y][1])bel[g[y][1]]=y;
		}
		for(int i=1;i<=m;++i)if(!s[i])s[i]=gt(i);
		for(int i=1;i<=m;++i)if(s[i]=='1')s[i]='v';else s[i]='^';
		cout<<(s+1)<<'\n';
	}
	return 0;
}