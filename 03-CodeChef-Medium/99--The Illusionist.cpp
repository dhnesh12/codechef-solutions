//teja349
#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip> 
//setbase - cout << setbase (16); cout << 100 << endl; Print
using namespace std;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define fd(i,a,b) for(i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define vi vector< int >
#define vl vector< ll >
#define ss second
#define ff first
#define ll long long
#define pii pair< int,int >
#define pll pair< ll,ll >
#define sz(a) a.size()
#define inf (1000*1000*1000+5)
#define all(a) a.begin(),a.end()
#define tri pair<int,pii>
#define vii vector<pii>
#define vll vector<pll>
#define viii vector<tri>
#define mod (1000*1000*1000+7)
#define pqueue priority_queue< int >
#define pdqueue priority_queue< int,vi ,greater< int > >

//std::ios::sync_with_stdio(false);   
ll iinf;
vector<vi> adj(12345);
ll a[12345];
ll pre[2123],post[2123],timer=0;
ll rev[2123];
ll subtree[2123];
ll dfs(ll cur,ll dep){
	subtree[cur]=1;
	pre[cur]=timer++;
	rev[timer-1]=cur;
	ll i;
	rep(i,adj[cur].size()){
		dfs(adj[cur][i],dep+1);
		subtree[cur]+=subtree[adj[cur][i]];
	}
	post[cur]=timer-1;
	return 0;
}
ll dp[2123][2123],visit[2123][2123];
ll compute(ll pos,ll left){
	if(pos==timer){
		if(left==0)
			return 0;
		return iinf;
	}
	if(visit[pos][left])
		return dp[pos][left];
	dp[pos][left]=compute(pos+1,left);
	visit[pos][left]=1;
	ll cur=rev[pos];
	if(subtree[cur]<=left){
		dp[pos][left]=min(dp[pos][left],a[cur]+compute(post[cur]+1,left-subtree[cur]));
	}
	return dp[pos][left];
}
int main(){
    std::ios::sync_with_stdio(false);
    ll t;
    cin>>t;
    iinf=inf;
    iinf*=100000;
    while(t--){
    	timer=0;
    	ll n,k;
    	cin>>n>>k;
    	ll i,j;
    	rep(i,n+10){
    		adj[i].clear();
    	}
    	rep(i,n+10){
    		rep(j,n+10){
    			visit[i][j]=0;
    		}
    	}
    	int val;
    	f(i,1,n){
    		cin>>val>>a[i];
    		val--;
    		adj[val].pb(i);
    	}
    	dfs(0,0);
    	k=n-k;
    	cout<<compute(0,k)<<endl;
    }
    return 0;     
}

