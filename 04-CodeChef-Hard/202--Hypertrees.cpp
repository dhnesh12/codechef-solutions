//Tester's solution

#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>
using namespace std;
 
// answers generated offline, algorithm below
long long answer[18]={
	0,0,0,
	1,
	6,
	25,
	495,
	5586,
	93268,
	2052513,
	43258365,
	1167393700,
	34010847486LL,
	1078391538159LL,
	38595111963499LL,
	1476893151785520LL,
	61479081902937000LL,
	2761923686066698561LL,
};
 
int main(){
	int T, N;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		printf("%lld\n", answer[N]);
	}
	return 0;
}
 
// disjoint set find
int find(int n, int *parent){
	if(parent[n]==n)
		return n;
	return parent[n]=find(parent[n], parent);
}
 
// disjoint set union
void un(int i, int j, int *parent){
	i=find(i, parent);
	j=find(j, parent);
	parent[i]=j;
}
 
// is graph connected when "skip" vertex is removed
int isconnected(int v[][2], int n, int len, int skip=-1){
	int parent[17];
	for(int i=0; i<n; i++)
		parent[i]=i;
	for(int i=0; i<len; i++){
		if(v[i][0]==skip || v[i][1]==skip)
			continue;
		un(v[i][0], v[i][1], parent);
	}
	int count=0;
	for(int i=0; i<n; i++)
		if(parent[i]==i && i!=skip)
			count++;
	return count==1;
}
 
// is graph biconnected
int isbiconnected(int v[][2], int N, int e){
	if(!isconnected(v, N, e))
		return 0;
	for(int i=0; i<N; i++)
		if(!isconnected(v, N, e, i))
			return 0;
	return 1;
}
 
long long nCr[18][18];
long long primitive[18];
long long biconnected[9][15];
int ee[17*8][2];
 
map<int, long long> dp;
// number of ways to break hypertree into biconnected components
long long dfs2(int *group, int *size, int comp){
	if(comp==1)
		return 1;
	sort(size, size+comp);
	int mask=0;
	for(int i=0; i<comp; i++)
		mask=(mask<<size[i])+1;
	if(dp.count(mask))
		return dp[mask];
	long long &res=dp[mask];
	int g=3;
	while(!group[g]){
		g++;
	}
	int perm[18];
	for(int i=0; i<comp; i++)
		perm[i]=0;
	for(int i=0; i<g; i++)
		perm[comp-1-i]=1;
	group[g]--;
	do{
		int next[17], pos=1;
		next[0]=0;
		long long m=1;
		for(int i=0; i<comp; i++){
			if(perm[i]){
				next[0]+=size[i];
				m*=size[i];
			}else
				next[pos++]=size[i];
		}
		res+=dfs2(group, next, comp-g+1)*m;
	}while(next_permutation(perm, perm+comp));
	group[g]++;
	res*=primitive[g];
	assert(!(res%group[g]));
	res/=group[g];
	return res;
}
 
// count biconnected graphs (not hypergraphs) with a particular
// number of vertices and edges
// this implementation is poorly optimized
void dfs0(int v[][2], int N, int e, int elim, int start=0){
	if(isbiconnected(v, N, e))
		biconnected[N][e]++;
	if(e==elim)
		return;
	for(; start<N*(N-1)/2; start++){
		v[e][0]=ee[start][0];
		v[e][1]=ee[start][1];
		dfs0(v, N, e+1, elim, start+1);
	}
}
 
// classify hypertrees by biconnected components
long long dfs1(int *count, int N, int upper, int lower=3){
	int size[17];
	for(int i=0; i<17; i++)
		size[i]=1;
	dp.clear();
	long long res=dfs2(count, size, N);
	for(int i=lower; 2*i-1<=upper; i++){
		count[upper]--;
		count[i]++;
		count[upper+1-i]++;
		res+=dfs1(count, N, upper+1-i, i);
		count[upper+1-i]--;
		count[i]--;
		count[upper]++;
	}
	return res;
}
 
// number of ways to put labeled balls into labeled boxes
// so that each box has at least one ball
long long dfs4(int balls, int boxes, int filled=0){
	if(!balls)
		return filled==boxes;
	return filled*dfs4(balls-1, boxes, filled)+(boxes-filled)*dfs4(balls-1, boxes, filled+1);
}
 
// count the total number of hypertrees on N vertices
long long solve(int N){
	int cnt[18]={0};
	cnt[N]=1;
	return dfs1(cnt, N, N);
}
 
int main2(){
	for(int i=0; i<18; i++)
	for(int j=0; j<18; j++){
		if(j==0)
			nCr[i][j]=1;
		else if(j>i)
			nCr[i][j]=0;
		else
			nCr[i][j]=nCr[i-1][j]+nCr[i-1][j-1];
	}
	for(int i=0, p=0; i<17; i++)
	for(int j=0; j<i; j++){
		ee[p][0]=j;
		ee[p][1]=i;
		p++;
	}
	int vv[17][2];
	primitive[3]=1;
	for(int i=4; i<=17; i++)
		primitive[i]=i*(i-1)/2;
	for(int i=3; i<=8; i++){
		dfs0(vv, i, 0, 17-i);
		for(int j=i; j<=17-i && j<=2*i; j++){
			for(int k=j; k+i<=17; k++){
				primitive[k+i]+=biconnected[i][j]*dfs4(k, j)*nCr[k+i][i];
			}
		}
	}
	
	for(int i=3; i<=17; i++){
		printf("%lld\n", solve(i));
	}
	return 0;
}