#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ll n,m,k;
	cin>>n>>m>>k;
	ll str[k+1][2];ll end[k+1][2];vector <ll> yarr;ll sm=0;
	for (int i=0;i<(int)k;i++){
		cin>>str[i][0]>>str[i][1];yarr.push_back(str[i][1]);sm+=str[i][1];
		cin>>end[i][0]>>end[i][1];yarr.push_back(end[i][1]);sm+=end[i][1];
	}
	sort(yarr.begin(),yarr.end());
	ll op[]={sm/(2*k),yarr[k-1],yarr[k]};
	ll dr=yarr[k-1]+yarr[k];dr/=2;
	ll z=LLONG_MAX;
	for (ll i=yarr[k-1];i<=yarr[k];i++){
		ll med=i;
		if (med>=1 and med<=m){
			ll ans=0;
			for (ll i=0;i<k;i++){
				ll sy=str[i][1];
				ll ey=end[i][1];
				ll sx=str[i][0];
				ll ex=end[i][0];

				ll dd=abs(sx-ex)+2*abs(med-ey)+2*abs(med-sy);
				ll zz=2*abs(sx-ex)+2*abs(ey-sy);
				ans+=min(zz,dd);
				
			}
			z=min(ans,z);
		}
	}
	cout<<z<<'\n';
	return 0;
}