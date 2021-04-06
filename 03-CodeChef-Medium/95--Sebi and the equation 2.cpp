#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
using namespace std;

ll A,B,C;

ll N;

ll ans1,ans2;

int T;

ll gcd(ll x,ll y){
	return y==0 ? x : gcd(y,x % y);
}

void exgcd(ll a,ll b,ll &x,ll &y){  
    if(b==0){  
        x=1;
		y=0;  
        return ;  
    }  
    exgcd(b,a%b,x,y);  
    ll temp;  
    temp=y;  
    y=x-a/b*y;  
    x=temp;  
} 

ll calc(ll x,ll y){
	ll p1,p2;
	exgcd(x,y,p1,p2);
	return (p1 % y+y) % y;
}
int main(){
	scanf("%d",&T);
	while (T--) {
		scanf("%lld%lld%lld%lld",&A,&B,&C,&N);
		ans1=ans2=0;
		ll l=(A+B)*N+A*B+C;
		for(ll i=1;i*i<=l;i++) {
			ll d=i;
			ll P=A+B;
			ll Q=A*B+C;
			Q=((d-Q) % d+d) % d;
			ll g=gcd(P,d);
			if (Q % g!=0) continue;
			P/=g;
			Q/=g;
			d/=g;
			ll x=calc(P,d);
			for(ll n=Q*x % d;n<=N;n+=d) {
				ll X=B+i;
				ll Y=A+((A+B)*n+A*B+C) / i;
				if ((X & Y)==0 && (X & n)==0 && (Y & n)==0) {
					if (X+n<=N && Y+n<=N && X<=Y) {
						ans1+=X+n;
						ans2+=Y+n;
					}
				}
				Y=A+i;
				X=B+((A+B)*n+A*B+C) / i;
				if ((X & Y)==0 && (X & n)==0 && (Y & n)==0) {
					if (X+n<=N && Y+n<=N && X>Y) {
						ans1+=X+n;
						ans2+=Y+n;
					}
				}
			}
		}
		printf("%lld %lld\n",ans1,ans2);
	}
	return 0;
}