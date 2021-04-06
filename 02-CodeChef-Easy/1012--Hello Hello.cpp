#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		ll a,b,u,n;
		double tarifa;
		scanf("%lf %lld %lld",&tarifa,&u,&n);
		//ll tarifa = a*100+b;
		double ahorro = 0;
		ll ans = 0;
		for(ll i = 0; i < n; i++){
			double m,cos;
			double r;
			scanf("%lf %lf %lf",&m,&r,&cos);
			//r = a*100+b;
			//cos *= 100;
			if(r*m*u + cos < tarifa*u*m){
				if((tarifa*u*m - (r*m*u + cos))/m > ahorro){
					ahorro = tarifa*u*m - (r*m*u + cos);
					ahorro /= m;
					ans = i+1;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}