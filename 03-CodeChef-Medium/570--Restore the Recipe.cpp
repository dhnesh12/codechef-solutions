#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 444444
#define inf 1000000000000000000LL
int n,i,j,k,x[maxn],y[maxn],z[maxn],f[maxn],t[maxn],p[maxn],u[maxn],ii,v[maxn],m,g,cc[maxn],sz;
long long d[maxn],ma,mi;
inline void addedge(int x,int y,int z){t[++ii]=y;p[ii]=f[x];f[x]=ii;v[ii]=z;}
inline int read(){
	char ch;int res=0,fla=0,mu=1;
	while(1){
		ch=getchar();
		if(ch==10||ch==13||ch==32)if(fla)return res*mu;else continue;
		if(ch=='-')mu=-1;else res=res*10+ch-'0';
		fla=1;
	}
}
void dfs(int k){
	u[k]=1;int q=f[k];
	while(q){
		if(!u[t[q]]){//visit
			d[t[q]]=d[k]+v[q];
			dfs(t[q]);
		}
		q=p[q];//next edge
	}
}
int main(){
	n=read();m=read();
	for(i=0;i<m;i++){
		x[i]=read();y[i]=read();z[i]=read();
		addedge(x[i]-1,y[i],z[i]);
		addedge(y[i],x[i]-1,-z[i]);
	}
	for(i=0;i<=n;i++)if(!u[i])dfs(i);
	for(i=0;i<m;i++)if(d[y[i]]-d[x[i]-1]!=z[i]){
		puts("-1");
		return 0;
	}
	for(i=1;i<=n;i++)printf("%d ",d[i]-d[i-1]);
	return 0;
}
