#include <bits/stdc++.h>
using namespace std;
#define fi first
//#define endl "\n"
#define se second
#define ll long long
#define inf 0x3f3f3f3f
#define fast    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int N = 4e5+5;
const ll mod =   1e9+7;
ll m,n;
ll a1[N],a2[N];ll ans=1;
ll go(ll x){
 for(int i=1;i<n;i++){
		if(a1[i]+x>a2[i+1])
		return 0;
	}
	ll var=0,v=0;
	if(x+a2[1]<=a1[2])
	var=a2[1];
	else
	var=a1[2]-x;
	var=max(var,a1[1]);v=var;
	for(int i=2;i<=n;i++){
		if(var+x>=a1[i]&&var+x<=a2[i]){
			var+=x;
		}
		else if(var+x<a1[i])
		var=a1[i];
		else
		return 0;
	}
	if((v-var+m)%m>=x)
	return 1;
	return 0;
}
int main()
{  fast
cin>>m>>n;
for(int i=1;i<=n;i++)
cin>>a1[i]>>a2[i];
ll lo=1;ll hi=m-1;
while(lo<=hi){
	ll mid=(lo+hi)/2;
	if(go(mid)){
		ans=mid;lo=mid+1;
	}
	else
	hi=mid-1;
}
cout<<ans;
}