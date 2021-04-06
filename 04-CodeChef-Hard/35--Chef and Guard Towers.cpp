#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define REP(i,n) for(int i=1;i<=(n);++i)
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;

const int maxn=400005;
int n;
class Point{
public:
	ll x,y;
	Point(ll _x=0,ll _y=0):x(_x),y(_y){}
	Point operator + (const Point &o)const{return Point(x+o.x,y+o.y);}
	Point operator - (const Point &o)const{return Point(x-o.x,y-o.y);}
	Point operator - ()const{return Point(-x,-y);}
	ll operator * (const Point &o)const{return x*o.y-y*o.x;}
	bool operator < (const Point &o)const{return (*this)*o>0;}
	bool operator == (const Point &o)const{return (*this)*o==0;}
};
ll ans;

int tot,rt[2];
class node{
public:
	int l,r,valL,valR,tagL,tagR,sz;
	ll sumL,sumR;
	ull pri;
	Point p;
}t[maxn];
int newnode(Point _p,int _valL,int _valR){
	tot++;
	t[tot].l=t[tot].r=t[tot].tagL=t[tot].tagR=0;
	t[tot].pri=1uLL*rand()*rand()*rand()*rand()*rand()*rand();
	t[tot].p=_p;
	t[tot].valL=t[tot].sumL=_valL;
	t[tot].valR=t[tot].sumR=_valR;
	t[tot].sz=1;
	return tot;
}

namespace Treap{
	#define ls t[cur].l
	#define rs t[cur].r
	void applyL(int cur,int _val){
		t[cur].valL+=_val;
		t[cur].sumL+=1LL*t[cur].sz*_val;
		t[cur].tagL+=_val; 
	}
	void applyR(int cur,int _val){
		t[cur].valR+=_val;
		t[cur].sumR+=1LL*t[cur].sz*_val;
		t[cur].tagR+=_val;
	}
	void pushdown(int cur){
		if(t[cur].tagL){
			if(ls)applyL(ls,t[cur].tagL);
			if(rs)applyL(rs,t[cur].tagL);
			t[cur].tagL=0;
		}
		if(t[cur].tagR){
			if(ls)applyR(ls,t[cur].tagR);
			if(rs)applyR(rs,t[cur].tagR);
			t[cur].tagR=0;
		}
	}
	void pushup(int cur){
		t[cur].sumL=t[ls].sumL+t[rs].sumL+t[cur].valL;
		t[cur].sumR=t[ls].sumR+t[rs].sumR+t[cur].valR;
		t[cur].sz=t[ls].sz+t[rs].sz+1;
	}
	void split(int cur,int &x,int &y,Point _p,bool equ){
		if(cur)pushdown(cur);
		if(!cur)x=y=0;
		else if(t[cur].p<_p||(equ&&t[cur].p==_p)){
			x=cur;
			split(rs,t[x].r,y,_p,equ);
			pushup(x);
		}
		else{
			y=cur;
			split(ls,x,t[y].l,_p,equ);
			pushup(y);
		}
	}
	void merge(int &cur,int x,int y){
		if(x)pushdown(x);
		if(y)pushdown(y);
		if(!x||!y)cur=x?x:y;
		else if(t[x].pri<t[y].pri){
			cur=x;
			merge(rs,t[x].r,y);
		}
		else{
			cur=y;
			merge(ls,x,t[y].l);
		}
		if(cur)pushup(cur);
	}
	#undef ls
	#undef rs
}

int main(){
	srand(20160516);
	scanf("%d",&n);
	REP(i,n){
		Point p;
		scanf("%lld%lld",&p.x,&p.y);
		int tp;
		if(p.y>0||(p.y==0&&p.x>0))tp=0;
		else tp=1;
		int a=0,b=0,c=0;
		Treap::split(rt[tp^1],a,b,-p,false);
		Treap::split(b,b,c,-p,true);
		ans+=1LL*t[a].sz*t[c].sz;
		int tmpL=t[a].sz,tmpR=t[c].sz;
		ans+=t[a].sumL; 
		ans+=t[c].sumR;
		if(a)Treap::applyR(a,1);
		if(c)Treap::applyL(c,1);
		Treap::merge(a,a,b);
		Treap::merge(rt[tp^1],a,c);
		a=0;b=0;
		Treap::split(rt[tp],a,b,p,false);
		Treap::merge(a,a,newnode(p,tmpL,tmpR));
		Treap::merge(rt[tp],a,b);
		printf("%lld\n",ans);
		fflush(stdout);
	}
	return 0;
}