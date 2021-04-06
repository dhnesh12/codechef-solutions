#include<bits/stdc++.h>
#define st first
#define nd second
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define umax(x,y) x=max(x,y)
#define umin(x,y) x=min(x,y)
#define ll long long 
#define ii pair<int,int>
#define iii pair<int,ii>
#define iiii pair<ii,ii>
#define sz(x) ((int) x.size())
#define orta ((bas+son)/2)
#define all(x) x.begin(),x.end()
#define pw(x) (1<<(x))
#define inf 2000000009
#define MOD 1000000007 
#define N 100005
#define M 1000003
#define LOG 19
#define KOK 250
#define EPS 0.0000001
using namespace std;

int n;
ll S[N<<2],lazy[N<<2];

void push(int node) {

	if(lazy[node]) {

		S[node<<1]=S[node<<1|1]=
		lazy[node<<1]=lazy[node<<1|1]=lazy[node];

		lazy[node]=0;

	}

}

ll get(int node,int bas,int son,int l,int r) {

	if(bas>r || son<l) return 0;

	if(bas>=l && son<=r) return S[node];

	push(node);

	return get(node<<1,bas,orta,l,r)|get(node<<1|1,orta+1,son,l,r);

}

void up(int node,int bas,int son,int l,int r,ll cl) {

	if(bas>r || son<l) return ;
	
	if(bas>=l && son<=r) {

		lazy[node]=S[node]=cl;

		return ;

	}

	push(node);

	up(node<<1,bas,orta,l,r,cl);
	up(node<<1|1,orta+1,son,l,r,cl);

	S[node]=S[node<<1]|S[node<<1|1];

}

void get_sub(int node) {

	ll mask=0;

	int l=node,r=node;

	while(l<=n) {

		umin(r,n);

		mask|=get(1,1,n,l,r);

		l=l<<1;
		r=r<<1|1;

	}

	printf("%d\n",__builtin_popcountll(mask));

}

void solve(int x,int y) {

	ll mask=0;

	while(1) {

		if(x>y) swap(x,y);

		mask|=get(1,1,n,y,y);

		if(x==y) break ;

		y>>=1;

	}

	printf("%d\n",__builtin_popcountll(mask));

}

void sub(int node,int beg,int k,int l,int r) {

	while(l<=n && beg<=k) {

		umin(r,n);

		up(1,1,n,l,r,(ll)1<<beg);

		++beg;

		l=l<<1;
		r=r<<1|1;

	}

}

void up_sub(int node,int beg,int k,int l,int r) {

	while(node && beg<=k) {

		up(1,1,n,node,node,beg?(ll)1<<beg:0);

		if(l) sub(node<<1,beg+1,k,node<<1,node<<1);

		if(r) sub(node<<1|1,beg+1,k,node<<1|1,node<<1|1);
	
		l=(node&1);
		r=!l;
		node=node>>1;
		beg++;

	}

}

int main() {

	int q;

	scanf("%d %d",&n,&q);

	while(q--) {

		int t;

		scanf("%d",&t);

		if(t==1) {

			int x,k;

			scanf("%d %d",&x,&k);

			up_sub(x,0,k,1,1);

		}
		else if(t==2) {

			int x,y;

			scanf("%d %d",&x,&y);

			solve(x,y);

		}
		else {

			int x;

			scanf("%d",&x);

			get_sub(x);

		}

	}

}