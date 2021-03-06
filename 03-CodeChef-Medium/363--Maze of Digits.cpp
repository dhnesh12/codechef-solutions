#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
using namespace std;
const int MAXN=105;
string map[MAXN];
int dir[5]={1,0,-1,0,1};
int f[MAXN][MAXN][MAXN];
int T,N,M,X,sx,sy;
int bfs(int y,int x,int v)
{
	int nx,ny,nv;
	queue<int> Q;
	memset(f,0x33,sizeof(f));
	f[y][x][v]=0;
	Q.push(y),Q.push(x),Q.push(v);
 	while(!Q.empty())
 	{
		y=Q.front(),Q.pop();
		x=Q.front(),Q.pop();
		v=Q.front(),Q.pop();
 		for(int i=0;i<4;i++)
 		{
			ny=y+dir[i];
			nx=x+dir[i+1];
			if(ny>=0 && ny<=N && nx>=0 && nx<=M)
			if(map[ny][nx]!='#')
			{
				nv=v+map[ny][nx]-'0';
				if(nv==X)
				return f[y][x][v]+1;
				if(nv>X)
				continue;
				if(f[ny][nx][nv]>f[y][x][v]+1)
				{
					f[ny][nx][nv]=f[y][x][v]+1;
					Q.push(ny),Q.push(nx),Q.push(nv);
				}
			}
		}
	}
	return -1;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>N>>M;
		for(int i=0;i<=N;i++)
		{
			cin>>map[i];
			for(int j=0;j<=M;j++)
			{
				if(map[i][j]=='*')
				sy=i,sx=j,map[i][j]='0';
				else if(map[i][j] == '.')
				map[i][j]='0';
			}
		}
		cin>>X;
		cout<<bfs(sy,sx,0)<<endl;
	}
	return 0;
}