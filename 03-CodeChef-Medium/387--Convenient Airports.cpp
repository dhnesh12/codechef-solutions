#include<bits/stdc++.h>
#define M 100006
using namespace std;
bool s1;
char o;
int Read() {
	bool fl=1;
	while(!isdigit(o=getchar()))if(o=='-')fl=0;
	int res=o^48;
	while(isdigit(o=getchar()))res=(res<<3)+(res<<1)+(o^48);
	return fl?res:-res;
}
struct edge{
	int u,v;
}Q[M<<1],Ans[M<<2];
int f[M],mark[M<<1],W[M<<2],A[M],B[M],C[M];
vector<int>son[M];
int getfa(int x){return x==f[x]?x:f[x]=getfa(f[x]);}
bool cmp(int a,int b){return son[a].size()>son[b].size();}
bool s2;
int main() {
//	printf("%.6lf\n",(&s2-&s1)/1024.0/1024);
	int T=Read();
	while(T--){
		int n=Read(),m=Read(),tot=0,tail=0,len=0,ans=0;
		A[1]=0;
		for(int i=1;i<=n;++i)f[i]=i;
		for(int i=1;i<=m;++i){
			Q[i].u=Read(),Q[i].v=Read();
			if(getfa(Q[i].u)==getfa(Q[i].v))continue;
			mark[i]=1;
			B[Q[i].u]=Q[i].v,B[Q[i].v]=Q[i].u,C[Q[i].u]=C[Q[i].v]=i;
			f[getfa(Q[i].u)]=getfa(Q[i].v);
		}
		for(int i=1;i<=m;++i){
			if(mark[i])continue;
			int u=getfa(Q[i].u);
			son[u].push_back(Q[i].u);
			son[u].push_back(Q[i].v);
		}
		for(int i=1;i<=n;++i){
			if(f[i]!=i)continue;
			A[++tail]=i;
		}
		sort(A+1,A+tail+1,cmp);
		for(int i=0;i<son[A[1]].size();++i)W[++tot]=son[A[1]][i];
		for(int i=2;i<=tail;++i){
			int u=A[i];
			if(son[u].size()){
				Ans[++len]={W[tot--],son[u][0]};
				for(int j=1;j<son[u].size();++j)W[++tot]=son[u][j];
			}
			else {
				if(tot){
					Ans[++len]={W[tot--],u},ans++;
					if(B[u])Ans[++len]={W[tot--],B[u]},ans--,mark[C[u]]=0;
				}
				else Ans[++len]={A[1],u},ans+=2;
			}
		}
		ans+=tot&1;
		for(int i=2;i<=tot;i+=2)Ans[++len]={W[i],W[i-1]};
		for(int i=1;i<=m;++i)if(mark[i])Ans[++len]=Q[i];
		printf("%d %d\n",ans,len);
		for(int i=1;i<=len;++i)printf("%d %d\n",Ans[i].u,Ans[i].v);
		for(int i=1;i<=n;++i)son[i].clear(),B[i]=C[i]=0;
		for(int i=1;i<=m;++i)mark[i]=0;
	}
	return 0;
}