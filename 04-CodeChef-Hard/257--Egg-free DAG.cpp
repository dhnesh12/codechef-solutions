#include<stdio.h>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
#define R register int
#define I inline
#define N 200001
vector<int>G[N],B[N];
int ord[N],pos[N],s[N],e[N],deg[N],t[N];
set<int>Q[N];
I void GetOrder(int&n){
	int m=0;
	for(R i=0;i!=n;i++){
		B[i].clear();
	}
	for(int i=1;i<=n;i++){
		B[0].push_back(i);
	}
	for(R i=n;i!=0;i--){
		int p=0;
		while(p==0){
			while(B[m].empty()==false){
				if(ord[B[m].back()]==0){
					p=B[m].back();
					break;
				}else{
					B[m].pop_back();
				}
			}
			if(p==0){
				m--;
			}
		}
		ord[p]=i;
		pos[i]=p;
		for(vector<int>::iterator T=G[p].begin();T!=G[p].end();T++){
			if(ord[*T]==0){
				deg[*T]++;
				B[deg[*T]].push_back(*T);
				if(deg[*T]>m){
					m=deg[*T];
				}
			}
		}
	}
}
I bool Check(int&n){
	for(R i=1;i<=n;i++){
		int ct=0;
		for(vector<int>::iterator T=G[pos[i]].begin();T!=G[pos[i]].end();T++){
			if(ord[*T]>i){
				t[ct]=*T;
				ct++;
			}
		}
		if(ct!=0){
			for(R j=1;j!=ct;j++){
				if(Q[t[0]].count(t[j])==0){
					return false;
				}
			}
		}
	}
	return true;
}
I void Solve(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(R i=1;i<=n;i++){
		G[i].clear();
		ord[i]=deg[i]=0;
		Q[i].clear();
	}
	for(R i=0;i!=m;i++){
		scanf("%d%d",s+i,e+i);
		G[s[i]].push_back(e[i]);
		G[e[i]].push_back(s[i]);
		Q[s[i]].insert(e[i]);
		Q[e[i]].insert(s[i]);
	}
	GetOrder(n);
	if(Check(n)==false){
		puts("No solution");
	}else{
		for(R i=0;i!=m;i++){
			if(ord[s[i]]<ord[e[i]]){
				putchar('^');
			}else{
				putchar('v');
			}
		}
		puts("");
	}
}
int main(){
	int t;
	scanf("%d",&t);
	for(R i=0;i!=t;i++){
		Solve();
	}
	return 0;
}