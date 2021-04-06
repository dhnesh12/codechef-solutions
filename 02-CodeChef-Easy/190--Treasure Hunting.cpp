#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define endl '\n'
using namespace std;
int dist[(1<<14)][15][15];
int maze[15][15];
int dirs[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
struct node{
	int x,y,cval;
};
bool isSafe(node n1,int n){
	if(n1.x>=0 && n1.x<n && n1.y>=0 && n1.y<n && maze[n1.x][n1.y]!=-2)
		return true;
	return false;
}
int bfs(int n,int c){
	queue<node> q;
	node s; s.x=0;s.y=0;s.cval=0;
	q.push(s);
	dist[0][0][0]=0;
	int ans=INF;
	while(!q.empty()){
		node front=q.front();q.pop();
		for(int k=0;k<4;k++){
			int nx=front.x+dirs[k][0],ny=front.y+dirs[k][1];
			int ncval=front.cval;
			if(maze[nx][ny]>=0) ncval|=(1<<maze[nx][ny]);
			node ns; ns.x=nx;  ns.y=ny;  ns.cval=ncval;
			if(isSafe(ns,n)){
				if(dist[ncval][nx][ny]>dist[front.cval][front.x][front.y]+1){
					dist[ncval][nx][ny]=dist[front.cval][front.x][front.y]+1;
					if(nx==n-1 && ny==n-1 && ncval==((1<<c)-1))
						ans=min(ans,dist[ncval][nx][ny]);
					q.push(ns);
				}
			}
		}
	}
	return ans>=INF?-1:ans;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t,n;
	string s;
	cin>>t;
	while(t--){
		cin>>n;
		int c=0;
		for(int i=0;i<n;i++){
			cin>>s;
			for(int j=0;j<n;j++){
				if(s[j]=='.') maze[i][j]=-1;
				if(s[j]=='#') maze[i][j]=-2;
				if(s[j]=='*') maze[i][j]=c++;
			}
		}
		memset(dist,INF,sizeof(dist));
		cout<<bfs(n,c)<<endl;
	}
}