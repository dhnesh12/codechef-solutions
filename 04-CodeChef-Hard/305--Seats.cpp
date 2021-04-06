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
#include<set>
#define ll long long
#define set_it set<ll>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const ll INF=4e18;
const int N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<ll>S;
ll n,a[N];
int m,tot;
struct Node{
	ll l,r,val;
	friend bool operator==(Node A,Node B){return A.l==B.l&&A.r==B.r;}
	friend bool operator<(Node A,Node B){return A.val!=B.val?A.val<B.val:(A.l!=B.l?A.l>B.l:A.r>B.r);}
};
struct Heap{
	priority_queue<Node>q1,q2;
	void Insert(Node A){q1.push(A);}
	void Delete(Node A){q2.push(A);}
	Node Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.top();
	}
}F;
Node GetNode(ll l,ll r){
	if(l<1)return (Node){l,r,r};
	if(r>n)return (Node){l,r,n-l+1};
	return (Node){l,r,((l+r)>>1)-l+1};
}
int main(){
//	freopen("seat.in","r",stdin);
//	freopen("seat.out","w",stdout);
	n=read();m=read();S.insert(-INF-1);S.insert(INF+1);F.Insert(GetNode(-INF,INF));
	while(m--){
		int op=read();
		if(op==1){
			tot++;Node A=F.Top();F.Delete(A);
			a[tot]=(A.l<1?1:(A.r>n?n:((A.l+A.r)>>1)));
			S.insert(a[tot]);set_it p=S.find(a[tot]);set_it l=--p,r=++++p;
			if(a[tot]!=1&&a[tot]-(*l)-1)F.Insert(GetNode((*l)+1,a[tot]-1));
			if(a[tot]!=n&&(*r)-a[tot]-1)F.Insert(GetNode(a[tot]+1,(*r)-1));
			printf("%lld\n",a[tot]);
		}
		if(op==2){
			int x=read();
			set_it p=S.find(a[x]);set_it l=--p,r=++++p;
			if(a[x]!=1&&a[x]-(*l)-1)F.Delete(GetNode((*l)+1,a[x]-1));
			if(a[x]!=n&&(*r)-a[x]-1)F.Delete(GetNode(a[x]+1,(*r)-1));
			F.Insert(GetNode((*l)+1,(*r)-1));S.erase(a[x]);
		}
	}
	return 0;
}