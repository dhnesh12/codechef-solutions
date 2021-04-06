#include<iostream>
#include<string>
#include<utility>
#include<algorithm>
#include<vector>
#include<set>

#define bp __builtin_popcount
#define pii pair<int,int>

using namespace std;

long long n,m,a,b;
vector<int>v[100];
long long memo[10000000];

long long dp(int st){
//	cout<<st<<endl;
	if(bp(st) == n){
		return 0;
	}
	if(memo[st]!=-1)return memo[st];
	long long res = 0,ma=99999999999999;
	for(int i = 0;i<n;i++){
		if(((1<<i)&st)!=0){
			for(int j = 0;j<(int)v[i].size();j++){
				if(((1<<v[i][j])&st) == 0){
					res++;
				}
			}
		}
	}
	long long curr;
	for(int i = 0;i<n;i++){
		curr = (1<<i);
		if((st&curr) == 0){
			ma = min(ma, dp(st^curr));
		}
	}
	return memo[st] = ma+res;
}

int main(){
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
	scanf("%lld %lld",&n,&m);
	for(int i = 0;i<=(1<<n);i++){
		memo[i]=-1;
	}
	for(int i=0;i<m;i++){
		scanf("%lld %lld",&a,&b);
		a--;
		b--;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	printf("%lld\n",dp(0));
	return 0;
}
