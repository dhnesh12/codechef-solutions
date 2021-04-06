#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())a
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define ar array
const int inf = 0x3f3f3f3f;
int mod = 1000000007; 
bool remender(ll a , ll b){return a%b;}

void solve(){
	int n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	if(k==n){
		cout<<n<<'\n';
		return;
	}
	int l[n],r[n];
	l[0]=(s[0]=='1' ? 1 : 0);
	for(int i = 1; i < n; i++){
		if(s[i]=='0')l[i]=0;
		else l[i]=l[i-1] + 1;
		//cout<<l[i]<<' ';
	}
	r[n-1]=(s[n-1]=='1' ? 1 : 0);
	for(int i = n-2; i >= 0; i--){
		if(s[i]=='0')r[i]=0;
		else r[i]=r[i+1]+1;
	}
	int ans = k + r[k];
	for(int i = 0; i < n-k; i++){
		//cout<<ans<<' ';
		if(i + k + 1 < n){
			ans=max(ans,l[i] + k + r[i + k + 1]);
		}
		else ans=max(ans,l[i] + k);
	}
	cout<<ans<<'\n';
}

int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
	int t;cin >> t;while(t--)
	solve();
	return 0;
}
