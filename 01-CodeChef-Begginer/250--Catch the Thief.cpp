#include<bits/stdc++.h>
#define ll long long
#define io ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ll t;cin>>t;while(t--)
#define endl "\n"
#define floop(i,n) for(int i=0;i<n;i++)
#define bloop(i,n) for(int i=n-1;i>=0;i--)
#define Afloop(i,a,n) for(int i=a;i<=n;i++)
#define Abloop(i,a,n) for(int i=n;i>=a;i--)
#define MOD 1e9+7
#define no "No"
#define yes "Yes"
#define pb push_back
#define mp make_pair
#define nvect vector<ll>
#define vectp vector<pair<ll,ll>>
#define vectors vector<pair<ll,ll>>
#define pairs pair<ll,ll>
#define f first
#define s second
#define ins insert
#define low INT_MIN
#define high INT_MAX
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
using namespace std;
void solve(){
	//answer here
	ll x,y,k,n;
	cin>>x>>y>>k>>n;
	if(abs(x-y)%(2*k)==0)
	cout<<yes<<endl;
	else
	cout<<no<<endl;

}
int main(){
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "rt", stdin);
//     freopen("output.txt", "wt", stdout);
// #endif
	io{
		solve();
	}
}