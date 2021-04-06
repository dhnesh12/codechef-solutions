#include <cstdio>
#include <algorithm>
using namespace std ;
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define drep(i,a,b) for(int i=a;i>=b;i--)
const int N=205 ;
struct node {
	int s,x,d,p ;
	void read() {
		scanf("%d%d%d%d",&s,&x,&d,&p) ;
	}
} a[N],b[N] ;
bool pcmp(node a,node b) {
	return a.p>b.p ;
}
bool scmp(node a,node b) {
	return a.s>b.s ;
}
int S[N*2],T[N*2],n ;
int play(int x) {
	int m=0,res=0 ;
	rep(i,1,x) T[++m]=a[i].s,T[++m]=a[i].d ;
	sort(T+1,T+m+1) ;
	m=unique(T+1,T+m+1)-T-1 ;
	rep(i,1,m-1) S[i]=T[i+1]-T[i] ;
	rep(i,1,x) b[i]=a[i] ;
	sort(b+1,b+x+1,scmp) ;
	rep(i,1,x) {
		int cur=b[i].x ;
		drep(j,m-1,1) if (cur>0 && b[i].s<=T[j] && T[j]<b[i].d) {
			if (cur>S[j]) {
				cur-=S[j] ;
				S[j]=0 ;
			}
			else {
				S[j]-=cur ;
				cur=0 ;
			}
		}
		res+=cur ;
	}
	return res ;
}
int main() {
	int cas ; scanf("%d",&cas) ;
	while (cas--) {
		ll ans=0 ;
		scanf("%d",&n) ;
		rep(i,1,n) a[i].read() ;
		sort(a+1,a+n+1,pcmp) ;
		rep(i,2,n) {
			int t=play(i) ;
			ans+=a[i].p*(ll)t ;
			a[i].x-=t ;
		}
		printf("%lld\n",ans) ;
	}
	return 0 ;
} 