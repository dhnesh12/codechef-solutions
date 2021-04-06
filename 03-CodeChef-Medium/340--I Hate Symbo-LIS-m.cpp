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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,a[N],b[N],st[N];
struct Node{
	int val,pos;
	friend Node operator+(Node A,Node B){
		Node C=(Node){max(A.val,B.val),inf};
		if(A.val==C.val)C.pos=min(C.pos,A.pos);
		if(B.val==C.val)C.pos=min(C.pos,B.pos);
		return C;
	}
}F1[N],F2[N];
struct Tree{
	Node c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int x=1;x<=m;x++)c[x]=(Node){0,0};}
	void Add(int x,Node y){for(;x<=m;x+=lowbit(x))c[x]=c[x]+y;}
	Node Ask(int x){Node ans=(Node){0,0};for(;x>=1;x-=lowbit(x))ans=ans+c[x];return ans;}
}tree;
int main(){
//	freopen("lis.in","r",stdin);
//	freopen("lis.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=b[i]=read();
		sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
		for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		tree.Clear();
		for(int i=1;i<=n;i++){F1[i]=tree.Ask(a[i]-1);tree.Add(a[i],(Node){F1[i].val+1,a[i]});}
		tree.Clear();
		for(int i=n;i>=1;i--){F2[i]=tree.Ask(m-a[i]);tree.Add(m-a[i]+1,(Node){F2[i].val+1,a[i]});}
		int Ans=0,Num=0;
		for(int i=1;i<=n;i++)Ans=max(Ans,F1[i].val+F2[i].val+1);
		for(int i=1;i<=n;i++)if(F1[i].val+F2[i].val+1==Ans&&b[F1[i].pos]<Ans&&Ans<=b[a[i]])Num=max(Num,b[a[i]]-Ans);
		printf("%d\n",Ans+Num);
	}
	return 0;
}