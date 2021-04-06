#include<bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);
#define endl '\n'
typedef long long ll;
typedef pair<int,int> pii;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost; // set
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_multiset; // multiset
*/
// direction array
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
// Bitmask
/*
bool check(int mask,int pos){return mask&(1<<pos);}
int SET(int mask,int pos){return mask|(1<<pos);}
int FLIP(int mask,int pos){return mask^(1<<pos);}
int reset(int mask,int pos){return mask&~(1 << pos);}
*/

ll dp[20][3][3][18*9+5][19][11];
ll const mod=1000000007;

vector<int>num;


ll solve(int pos,int first,int small,int boro,int cnt,int id)
{
	if(pos<0){
		//cout<<boro<<' '<<suto<<' '<<cnt<<' '<<id<<endl;
		//cout<<(boro-cnt*id)+(cnt*id-suto)<<endl;
		return ((ll)cnt*(ll)boro)%mod;
	}
	ll &re=dp[pos][first][small][boro][cnt][id];
	if(small && re!=-1){
		return re;
	}
	re=0;
	if(first){
		re=solve(pos-1,1,1,0,0,id)%mod;
	}
	int en=small?9:num[pos];
	for(int i=first;i<en;i++){
		re=re+solve(pos-1,0,1,boro+(i>id)*(i-id),cnt+(id==i),id)%mod;
		re%=mod;
	}
	int i=en;
	re=re+solve(pos-1,0,small,boro+(i>id)*(i-id),cnt+(id==i),id)%mod;
	re%=mod;
	return re%mod;
}



ll get(ll x)
{
	num.clear();
	while(x){
		num.push_back(x%10);
		x/=10;
	}
	ll sum=0;
	for(int i=0;i<10;i++){
		sum=(sum+solve(num.size()-1,1,0,0,0,i)%mod)%mod;
	}
	return sum;
}


int main()
{
	memset(dp,-1,sizeof dp);
	int t;
	ll l,r;
	cin>>t;
	while(t--){
		cin>>l>>r;
		cout<<(get(r)-get(l-1)+mod)%mod<<endl;
	}
}