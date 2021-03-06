#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
using namespace std;
// }}}
// pre-written code {{{
#define REP(i,n) for(int i=0;i<(int)(n);++i)
#define RREP(i,a,b) for(int i=(int)(a);i<(int)(b);++i)
#define FOR(i,c) for(typeof((c).begin()) i=(c).begin();i!=(c).end();++i)
//#define IFOR(i,it,c) for(__typeof((c).begin())it=(c).begin();it!=(c).end();++it,++i)
#define ALL(c) (c).begin(), (c).end()
#define MP make_pair
 
#define EXIST(e,s) ((s).find(e)!=(s).end())
 
#define RESET(a) memset((a),0,sizeof(a))
#define SET(a) memset((a),-1,sizeof(a))
#define PB push_back
 
 
typedef long long Int;
typedef unsigned long long uInt;
typedef long double rn;
 
typedef pair<int,int> pii;
 
#ifdef DEBUG
#include"debug.h"
#include"print.h"
#endif
// }}}
 
int ct=0;
 
int N,B;
Int M,L;
int S[32];
Int x;
 
Int dp[32][1024];
//map<vector<int>, Int> dp;
 
int peak[1024];
 
//Int calc(const vector<int> &v){
Int calc(int p,int q){
//	map<vector<int>,Int>::iterator it=dp.find(v);
	if(dp[p][q]>=0)return dp[p][q];
//	if(it!=dp.end())return it->second;
	if(p==0 and q==0)return dp[p][q]=x;
//	vector<int> v0=v,v1=v;
//	v0[v0.size()-1]--;
	/*
	if(v0[v0.size()-1]==0)v0.pop_back();
	else{
		int i=v0.size()-1;
		for(;i>0 and v0[i-1]>v0[i];i--){
			swap(v0[i-1],v0[i]);
		}
	}
	*/
//	sort(ALL(v0));
	int p1,q1;
	p1=p-1;q1=q;
	if(peak[q]>p1)p1=peak[q],q1=p+q-1-p1;
	Int x0=calc(p1,q1);
//	if(v.size()==1){
	if(q==0){
		Int t=(x0+B)/(B+1);
		t=max(x0-L*B,t);
		return dp[p][q]=t;
	}
	/*
	v1[v1.size()-2]--;
	if(v1[v1.size()-2]==0){
		swap(v1[v1.size()-1],v1[v1.size()-2]);
		v1.pop_back();
	}else{
		int i=v1.size()-2;
		for(;i>0 and v1[i-1]>v1[i];i--){
			swap(v1[i-1],v1[i]);
		}
	}
	*/
//	sort(ALL(v1));
	Int x1=calc(p,q-1);
	Int u=x0+x1*B;
	Int result=(u+B)/(B+1);
	result=max(x0-L*B,result);
	return dp[p][q]=result;
}
 
bool judge(Int x){
	::x=x;
	memset(dp,-1,sizeof(dp));
//	dp.clear();
//	REP(i,N)v.push_back(S[i]);
	Int t=calc(S[N-1],accumulate(S,S+N-1,0));
	return t<=M;
}
 
Int bs(){
	Int l=0,r=1e+15;
	while(r-l>1){
		//		cout<<l<<" "<<r<<endl;
		if(judge((l+r)/2)){
			l=x;
		}else{
			r=x;
		}
	}
	return l;
}
 
void main2(){
	scanf("%d%d%lld%lld",&N,&B,&M,&L);
	REP(i,N)scanf("%d",S+i);
	sort(S,S+N);
	if(N>1){
		vector<int> v;
		REP(i,N-1)v.push_back(S[i]);
		while(1){
			int s=accumulate(ALL(v),0);
			peak[s]=v.back();
			if(s==0)break;
			v.back()--;
			sort(ALL(v));
		}
	}
	printf("%lld\n",bs());
}
 
//{{{ main function
int main() {
	int T;scanf("%d", &T);
	for(ct=0;ct<T;ct++){
		//		printf("Case %d: ",ct+1);
		main2();
	}
	return 0;
}