#include<bits/stdc++.h>

#define pb push_back
#define all(v) (v).begin(),(v).end()
#define ll long long int
#define rep(i,x,y) for(ll i=x;i<y;i++)
#define sz(a) (ll)(a.size())
#define MOD 1000000007
#define fi first
#define se second
#define pii pair<ll,ll>

using namespace std;
const ll hell = (ll)(1e18+100LL);
const double pi = acos(-1.0);

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll t,i,j,k,m,n,x,y,z;
	t=1;
	cin>>t;
	while(t--){
		ll flag=0,K;
		cin>>n;
		vector<ll>ar(n+1);
		set<ll>S;
		for(i=0;i<=n+5;i++)S.insert(i);
		for(i=1;i<=n;i++){
			cin>>ar[i];
			if(S.find(ar[i])!=S.end()){
				S.erase(S.find(ar[i]));
			}
		}

		ll mex = *S.begin();
		vector<ll>dp(n+5,0),pre(n+5,0);
		S.clear();
		for(i=0;i<=n+5;i++)S.insert(i);

		j=1;pre[0]=1;ll a=0;
		//map<ll,ll>mp;
		vector<ll>mp(n+10,0);
		for(i=1;i<=n;i++){
			mp[ar[i]]++;
			if(a==0){
				if(S.find(ar[i])!=S.end()){
					S.erase(S.find(ar[i]));
				}
			}
			x = *S.begin();
			if(mex==x || a==1){
				a=1;
				while(j<i){
					if(ar[j]>mex||mp[ar[j]]>1){
						mp[ar[j]]--;
						j++;
					}else{
						break;
					}
				}
				//cout<<i<<" "<<j<<"\n";
				dp[i] = pre[j-1];
			}
			pre[i] = (dp[i] + pre[i-1])%MOD;
			//cout<<dp[i]<<" ";

		}

		cout<<dp[n]<<"\n";
		
	}
	return 0;
}