#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <cassert>
#include <string.h>
//#include <unordered_set>
//#include <unordered_map>
//#include <bits/stdc++.h>

#define MP(A,B) make_pair(A,B)
#define PB(A) push_back(A)
#define SIZE(A) ((int)A.size())
#define LEN(A) ((int)A.length())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define fi first
#define se second

using namespace std;

template<typename T>inline bool upmin(T &x,T y) { return y<x?x=y,1:0; }
template<typename T>inline bool upmax(T &x,T y) { return x<y?x=y,1:0; }

typedef long long ll;
typedef unsigned long long ull;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod eps=1e-11;
const lod pi=acos(-1);
const int oo=1<<30;
const ll loo=1ll<<62;
const int mods=998244353;
const int MAXN=600005;
const int INF=0x3f3f3f3f;//1061109567
/*--------------------------------------------------------------------*/
inline int read()
{
	int f=1,x=0; char c=getchar();
	while (c<'0'||c>'9') { if (c=='-') f=-1; c=getchar(); }
	while (c>='0'&&c<='9') { x=(x<<3)+(x<<1)+(c^48); c=getchar(); }
	return x*f;
}

PR a[MAXN];
ll ans[MAXN];
int P[MAXN],s[MAXN<<2],Mn[MAXN<<2],n;
struct node
{
	int x;
	node(){}
	node(int x):x(x){}
	friend bool operator < (node a,node b) { return P[a.x]<P[b.x]; }
} L[MAXN<<2],R[MAXN<<2],mn[MAXN<<2],mx[MAXN<<2];
struct Node
{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
	Node(node x,node y):x(x.x),y(y.x){}
	inline int get() { return P[y]-P[x]; }
	friend bool operator < (Node a,Node b) { return a.get()<b.get(); }
} Ans[MAXN<<2],_Ans[MAXN<<2];

void print(int x)
{
	puts("-----------------------------------------------------------");
	printf("print %d:\n",x);
	puts("");
	printf("Ans:%d %d\n",Ans[x].x,Ans[x].y);
	printf("_Ans:%d %d\n",_Ans[x].x,_Ans[x].y);
	printf("s,Mn:%d %d\n",s[x],Mn[x]);
	printf("L,R,mn,mx:%d %d %d %d\n",L[x].x,R[x].x,mn[x].x,mx[x].x);
}
void up(int x)
{
	s[x]=s[x<<1]+s[x<<1|1];
	Mn[x]=min(Mn[x<<1],s[x<<1]+Mn[x<<1|1]);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
	
	Ans[x]=max(Ans[x<<1],Ans[x<<1|1]);
	_Ans[x]=max(_Ans[x<<1],_Ans[x<<1|1]);
	upmax(_Ans[x],Node(mn[x<<1|1],mx[x<<1]));
	upmax(Ans[x],Node(mn[x<<1],mx[x<<1|1]));
	upmax(Ans[x],Node(L[x<<1|1],R[x<<1]));
	
	L[x]=L[x<<1],R[x]=R[x<<1|1];
	if (Mn[x]!=Mn[x<<1]) 
	{
		upmax(Ans[x],_Ans[x<<1]);
		upmax(Ans[x],Node(L[x<<1|1],mx[x<<1]));
		upmin(L[x],min(L[x<<1|1],mn[x<<1]));
	}
	if (Mn[x]!=s[x<<1]+Mn[x<<1|1])
	{
		upmax(Ans[x],_Ans[x<<1|1]);
		upmax(Ans[x],Node(mn[x<<1|1],R[x<<1]));
		upmax(R[x],max(R[x<<1],mx[x<<1|1]));
	}
}
void build(int x,int l,int r)
{
	if (l==r) { s[x]=0,mn[x]=mx[x]=l,L[x]=n+1,R[x]=n+2,Ans[x]=_Ans[x]=Node(n+1,n+2); return;  }
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	up(x);
}
void update(int x,int l,int r,int y,int z)
{
	if (l==r) { s[x]=Mn[x]=z,mn[x]=n+1,mx[x]=n+2,L[x]=n+1,R[x]=n+2; return; }
	int mid=(l+r)>>1;
	if (y<=mid) update(x<<1,l,mid,y,z);
	else update(x<<1|1,mid+1,r,y,z);
	up(x);
}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i].fi=read(),a[i].se=read();
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++) P[i]=a[i].se; P[n+1]=INF,P[n+2]=-INF;
//	cout<<"P:";for (int i=1;i<=n;i++) cout<<P[i]<<" ";cout<<endl;
	build(1,1,n);
	for (int i=1;i<=n/2;i++) ans[i]=-1;
	for (int i=1;i<=n/2;i++)
	{
		Node p=Ans[1];
//		print(1);
		if (p.get()<=0) break;
//		cout<<p.x<<" "<<p.y<<endl;
		update(1,1,n,p.x,1),update(1,1,n,p.y,-1);
		ans[i]=ans[i-1]+p.get();
	}
	for (int i=1;i<=n/2;i++)
	{
		upmax(ans[i],ans[i-1]);
		printf("%lld\n",ans[i]);
	}
	return 0;
}