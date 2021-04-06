#include <bits/stdc++.h>
using namespace std;
const int md=(int)1e9+123;
inline void add(int &a,int b){
	a+=b;
	if(a>=md)
		a-=md;
}
inline void sub(int &a,int b){
	a-=b;
	if(a<0)
		a+=md;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tt;cin>>tt;
	while(tt--){
		int n;cin>>n;
		vector<int> a(n);
		int sum=0;
		for(int i=0;i<n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		vector<int> dp(sum+1,0);
		dp[0]=1;
		
		for(int x:a){
			for(int i=sum-x;i>=0;i--){
				add(dp[i+x],dp[i]);
			}
		}
		int ans=-1,aid=-1;
		for(int id=0;id<n;id++){
			int x=a[id];
			for(int i=0;i<=sum-x;i++){
				sub(dp[i+x],dp[i]);
			}
			int rm=sum-x;
			for(int i=rm/2;i>=0;i--){
				if(dp[i]>0){
					int cur=i+x;
					if(cur>ans){
						ans=cur;
						aid=id;
					}
				}
			}
			for(int i=sum-x;i>=0;i--){
				add(dp[i+x],dp[i]);
			}
		}
		const int N=500*500+10;
		vector<bitset<N>> aux(1);
		aux[0][0]=1;
		for(int i=0;i<n;i++){
			aux.push_back(aux.back());
			if(i!=aid){
				aux[i+1]|=(aux[i]<<a[i]);
			}
		}
		int j=ans-a[aid];
		vector<int> mine;
		vector<int> his;
		for(int i=n;i>0;i--){
			if(i-1==aid){
				continue;
			}
			if(aux[i-1][j]==1){
				his.push_back(i-1);
				
			}else{
				mine.push_back(i-1);
				j-=a[i-1];
			}
		}
		assert(j==0);
		mine.push_back(aid);
		vector<int> my_start(mine.size());
		vector<int> his_start(his.size());
		for(int i=0;i<(int)mine.size();i++){
			my_start[i]=(i==0?0:my_start[i-1]+a[mine[i-1]]);
		}
		for(int i=0;i<(int)his.size();i++){
			his_start[i]=(i==0?0:his_start[i-1]+a[his[i-1]]);
		}
		vector<int> res;
		int pm=0,ph=0;
		while(pm<(int)mine.size()||ph<(int)his.size()){
			if(ph==(int)his.size()||(pm< (int) mine.size()&& my_start[pm]<=his_start[ph])){
				res.push_back(mine[pm++]);
			}
			else{
				res.push_back(his[ph++]);
			}
		}
		assert((int)res.size()==n);
		for(int i=0;i<n;i++){
			if(i>0){
				cout<<" ";
				
			}
			cout<<res[i]+1;
		}
		cout<<'\n';
	}
	return 0;
}