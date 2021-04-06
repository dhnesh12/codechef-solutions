#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
#define int ll
const int MX=1e5+10;
int a[MX];
signed main(){
	int N,K;
	cin>>N>>K;
	for(int i=1;i<=N;i++)cin>>a[i];
	set<pair<int,pair<int,int>>> S;
	int sum=accumulate(a+1,a+N+1,0LL);
	S.insert({sum,{1,N}});
	for(int i=0;i<K;i++){
		auto hi=*S.rbegin();
		S.erase(hi);
		auto p=hi.second;
		int val=hi.first;
		int L=p.first;int R=p.second;

		cout<<val<<" ";
		if(L!=R){
			S.insert({val-a[L],{L+1,R}});
			S.insert({val-a[R],{L,R-1}});
		}
	}
}
