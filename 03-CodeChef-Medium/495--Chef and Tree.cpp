/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>F[N],G[N];
int n,m,a[N],sum[N],Ans[N],Root[N];
struct Tree{
	int tot,ch[N*M][2];
	void Clear(){tot=0;}
	int NewNode(){tot++;ch[tot][0]=ch[tot][1]=0;return tot;}
	void Insert(int &root,int x){
		if(!root)root=NewNode();int p=root;
		for(int i=29;i>=0;i--){
			int c=(x>>i)&1;
			if(!ch[p][c])ch[p][c]=NewNode();
			p=ch[p][c];
		}
	}
	int Query(int p,int x){
		int ans=0;
		for(int i=29;i>=0;i--){
			int c=(x>>i)&1;
			if(ch[p][c^1]){ans+=(1<<i);p=ch[p][c^1];}
			else p=ch[p][c];
		}
		return ans;
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		ch[x][0]=Merge(ch[x][0],ch[y][0]);
		ch[x][1]=Merge(ch[x][1],ch[y][1]);
		return x;
	}
}tree;
void DFS(int x,int fa){
	F[x].push_back(sum[x]);
	tree.Insert(Root[x],sum[x]);
	for(auto y:G[x])if(y!=fa){
		sum[y]=sum[x]^a[y];DFS(y,x);Ans[x]=max(Ans[x],Ans[y]);
		if(F[x].size()<F[y].size()){swap(F[x],F[y]);swap(Root[x],Root[y]);}
		for(auto tmp:F[y]){Ans[x]=max(Ans[x],tree.Query(Root[x],tmp^a[x]));F[x].push_back(tmp);}
		Root[x]=tree.Merge(Root[x],Root[y]);
	}
	Ans[x]=max(Ans[x],tree.Query(Root[x],sum[fa]));
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();
		for(int i=1;i<=n;i++){a[i]=read();sum[i]=a[i];}
		for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
		DFS(1,0);
		for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
		for(int i=1;i<=n;i++){G[i].clear();F[i].clear();Ans[i]=Root[i]=0;}tree.Clear();
	}
	return 0;
}