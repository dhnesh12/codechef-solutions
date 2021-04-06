#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

int A[1000], N, K;
int res[999][2];

void read(){
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; i++)
		scanf("%d", A+i);
}

void solve(){
	pair<unsigned int, int> pos[1000];
	long long goal=2*K;
	for(int i=0; i<N; i++)
		pos[i]=make_pair(A[i], i);
	sort(pos, pos+N);
	int front=0, back=N-1, cur=N-2;
	while(back-front+1>2){
		unsigned int hi=pos[back].first, lo=pos[front].first;
		int p1=2*hi/5+3*lo/5;
		int p2=3*hi/5+2*lo/5;
		if(goal<2*p1 || back-front+1<4){
			res[cur][0]=N+cur-1;
			res[cur--][1]=pos[front++].second;
			goal=max(0ll, 2*(goal-lo));
		}else if(goal>2*p2){
			res[cur][0]=N+cur-1;
			res[cur--][1]=pos[back--].second;
			goal=min(2000000000ll, 2*(goal-hi));
		}else{
			res[cur][0]=N+cur-1;
			res[cur][1]=N+cur-2;
			res[cur-1][0]=pos[front++].second;
			res[cur-1][1]=pos[back--].second;
			cur-=2;
			goal=2*goal-(lo+hi);
		}
	}
	res[0][0]=pos[front].second;
	res[0][1]=pos[back].second;
}

void print(){
	for(int i=0; i<N-1; i++)
		printf("%d %d\n", res[i][0]+1, res[i][1]+1);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; i++){
		read();
		solve();
		print();
	}
	return 0;
}
