#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'

const int MOD=1e9+7;
 
 
int add(int x, int y)
{
	return (x + y) % MOD;
}
 
int sub(int x, int y)
{
	return add(x, MOD - y);
}
 
int mul(int x, int y)
{
	return (x * 1ll * y) % MOD;
}
 
int binpow(int x, int y)
{
	int z = 1;
	while(y > 0)
	{
		if(y % 2 == 1)
			z = mul(z, x);
		x = mul(x, x);
		y /= 2;
	}
	return z;
}
 
int inv(int x)
{
	return binpow(x, MOD - 2);
}
 
int fact[100];
int ifact[100];
int C(int n, int k)
{
	return mul(fact[n], mul(ifact[k],  ifact[n - k]));
}


vector<vector<int>>adj;
bool vis[55];

int node=0;
int ed=0;

void dfs(int v){
	vis[v]=1;
	node++;
	ed+=adj[v].size();
	for(auto u:adj[v]){
		if(vis[u]==1){
			continue;
		}
		dfs(u);
	}
}
 
main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	fact[0]=1;
	ifact[0]=1;
	for(int i=1; i<100; i++){
		fact[i]=mul(i, fact[i-1]);
		ifact[i]=inv(fact[i]);
	}
	
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		adj.clear();
		adj.resize(n+1);
		for(int i=1; i<=n; i++){
			vis[i]=0;
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				char c;
				cin>>c;
				if(c=='0' && i!=j){
					adj[i].pb(j);
				}
			}
		}
		int cyc[55];
		int lin[55];
		for(int i=0; i<55; i++){
			cyc[i]=0;
			lin[i]=0;
		}
		
		for(int i=1; i<=n; i++){
			if(vis[i]){
				continue;
			}
			node=0;
			ed=0;
			dfs(i);
			if(ed==2*node){
				cyc[node]++;
			}
			else{
				lin[node]++;
			}
		}
		
		int rem=n;
		int ans=1;
		for(int i=1; i<=n; i++){
			int num=lin[i];
			
			if(num==0){
				continue;
			}
			if(i==1){
				ans=mul(ans, fact[rem]);
				
				ans=mul(ans, ifact[num]);
				
				ans=mul(ans, binpow(ifact[i], num));
				
				ans=mul(ans, ifact[rem-num*i]);
				
				rem-=num*i;
			}
			else{
				
				ans=mul(ans, fact[rem]);
				ans=mul(ans, ifact[num]);
				
				ans=mul(ans, ifact[rem-num*i]);
				ans=mul(ans, inv(binpow(2LL, num)));
				rem-=num*i;
			}
		}
		
		for(int i=3; i<=n; i++){
			int num=cyc[i];
			if(num==0){
				continue;
			}
			
			ans=mul(ans, fact[rem]);
			
			ans=mul(ans, ifact[num]);
			
			ans=mul(ans, ifact[rem-num*i]);
			ans=mul(ans, binpow(inv(i), num));
			
			ans=mul(ans, inv(binpow(2LL, num)));
			rem-=num*i;
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
