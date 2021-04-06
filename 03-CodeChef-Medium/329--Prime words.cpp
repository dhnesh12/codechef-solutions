#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<iterator>
#include<map>
#include<vector>
#include<list>
#include<set>
#include<queue>
#include<cassert>
#include<deque>
#include<stack>
#include<bitset>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iomanip>
#include<string>
#include<cmath>
#include<ctime>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define mod 531169
vector<int> extendedEuclid(int a,int b){
	if(!b){
		vector<int> ans(3);
		ans[0] = a;ans[1] = 1;ans[2] = 0;
		return ans;
	}
	else {
		vector<int> ans = extendedEuclid(b,a%b);
		int temp = ans[1];
		ans[1] = ans[2];
		ans[2] = temp - (a/b) * ans[1];
		return ans;
	}
}         
long long factmod[531200];
void pre(){
	factmod[1] = factmod[0] = 1;
	for(int i = 1 ;i<531169;++i) factmod[i+1]= (factmod[i] * (i+1)) % mod;
}
long long amodb(int a,int b){
	if(!b) return 1;
	long long tmp = 1,ret = a;
	while(b != 1){
		if(b%2) tmp = (tmp * ret) % mod , tmp %= mod;
		ret = (ret*ret) %mod;
		b /= 2;
	}
	return (ret * tmp) % mod;
}
int actmod(int r){
	long long fr = (amodb(factmod[mod - 1], r/mod)*factmod[r%mod]) % mod;
	return (fr * factmod[r/mod]) % mod;
}
int ncrmod(int n,int r){
	int p = n/mod - r/mod - (n-r)/mod;
	if(p>0) return 0;
	long long tmp = actmod(n);
	tmp = (tmp * extendedEuclid(actmod(r),mod)[1]) % mod;
	tmp = (tmp * extendedEuclid(actmod(n-r),mod)[1]) % mod;
	tmp = (tmp + mod)%mod;
	return tmp;
}
vector<pair<int,int> > v;
int a , b , n;
int total ;
long long ans;
void calc(int start,int tot,int factors){
	if(start == v.size()){
	
		if(!factors)return;
		if(factors %2)ans -= ncrmod((a+b)/tot,b/tot);
		else	      ans += ncrmod((a+b)/tot,b/tot);
		ans = (ans + mod) % mod;
		return ;
	}
	for(int i =0 ; i<=v[start].second;++i){
		calc(start+1,tot,factors+i);
		tot *=v[start].first;
	}
	return ;
}
int main(){
	int t;
	pre();
	scanf("%d",&t);
	while(t--){
		v.clear();
		scanf("%d%d",&a,&b);
		
		n = __gcd(a,b);
		int sq = (int)sqrt(n)+5;
		int tn = n;
		total = 0;
		for(int i = 2;i<sq;++i){
			if(tn%i==0){
				int cnt =0;
				while(tn%i==0)cnt++,tn/=i;
				v.push_back(make_pair(i,cnt));
				total += cnt;
			}
		}
		if(tn != 1)v.push_back(make_pair(tn,1)),total++;
		ans = ncrmod((a+b),b);
		calc(0,1,0);
		
		int prime = v.size();
		long long nans = ncrmod((a+b),b);
		for(int i = 0 ; i < (1<<prime); ++i){
			int cur = 1,num =0;
			for(int j = 0 ; j < prime ; ++j){
				if((i>>j)&1)cur *= v[j].first,num++;
			}
			if (cur == 1) continue;
			if(num%2) nans -= ncrmod((a+b)/cur,b/cur);
			else nans += ncrmod((a+b)/cur,b/cur);
			nans %= mod;
			nans = (nans + mod ) % mod;
		}
		cout << nans << endl;
		
	}
	return 0;
}