#include <bits/stdc++.h> 
#include <bits/stl_vector.h>
#define ll unsigned long long
#define f(a,b,c) for(ll a=b;a<c;a++)
const ll MOD = 998244353;
const int N = 50,M = 50;
using namespace std;
vector <int> dp[101][101],b,c;
vector <int> dfs(int st,int en){
	if(dp[st+1][en+1].size()!=0){return dp[st+1][en+1];}vector <int> ret;
	if(st>en){ret.push_back(b[st]);return dp[st+1][en+1]=ret;}
	f(i,st,en+1){vector <int> a=dfs(st,i-1); vector <int> d=dfs(i+1,en);for(int j: a){
			for(int k: d){if (c[i] == 0){ret.push_back(j&k);} else if (c[i] == 1){ret.push_back(j|k);}
				else{ret.push_back(j^k);}}}}
	return dp[st+1][en+1]=ret;}
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL); int t; cin>>t;
	while(t--){f(i,0,101){f(j,0,101){dp[i][j].clear();}}b.clear(); c.clear(); int n; string a; cin>>a;
	    n=a.length();
	    f(i,0,n){
			if(a[i]<='9'&&a[i]>='0'){b.push_back(0);int bs = b.size()-1;
				while(a[i]<='9'&&a[i]>='0'){b[bs]=b[bs]*10+(a[i]-'0');i++;}i--;}
			else{if (a[i] == '&'){c.push_back(0);}else if (a[i] == '|'){c.push_back(1);}
				else if (a[i] == '^'){c.push_back(2);}}}
		vector<int> an = dfs(0,b.size()-2); int ans=0;for (int i: an){ans = max(ans,i);}cout << ans << endl;}}