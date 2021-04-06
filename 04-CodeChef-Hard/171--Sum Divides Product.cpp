#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
 
#define MAX_MOB (1<<16)
#define MAX_PRIM (1<<21)
char mobius[MAX_MOB];
int primitive[MAX_PRIM];
 
void calc_mobius(){
	mobius[1]=1;
	for(int i=2; i<MAX_MOB; i++){
		mobius[i]=-1;
		for(int j=2; j*j<=i; j++)
			if(!(i%j)){
				if(!((i/j)%j))
					mobius[i]=0;
				else
					mobius[i]=-mobius[i/j];
				break;
			}
	}
}
 
void calc_primitive(){
	int st[30][2]={{1,1}};
	for(int d=0; d>=0; ){
		st[d][1]+=st[d][0];
		unsigned int p=(st[d][0]+st[d][1])*st[d][1];
		if(p>=MAX_PRIM)
			d--;
		else{
			primitive[p]++;
			st[d+1][0]=st[d][1];
			st[d+1][1]=st[d][0];
			d++;
		}
	}
	for(int i=1; i<MAX_PRIM; i++)
		primitive[i]+=primitive[i-1];
}
 
int count1(int N){
	int res=0;
	for(int i=1; i*i<N; i++){
		res+=min(i-1, N/i-i);
	}
	return res;
}
 
int countprimitive(int N){
	if(N<MAX_PRIM)
		return primitive[N];
	int res=0;
	for(int i=1; i*i<=N; i++){
		if(mobius[i])
			res+=mobius[i]*count1(N/(i*i));
	}
	return res;
}
 
unsigned int count(int N){
	unsigned int res=0;
	int i;
	for(i=1; i*i<=N; i++){
		int d=N/i;
		if(d!=i)
			res+=countprimitive(N/i);
		res+=(N/i-N/(i+1))*countprimitive(i);
	}
	return res;
}
 
int main(){
	int T, N;
	calc_mobius();
	calc_primitive();
	scanf("%d", &T);
	for(int i=0; i<T; i++){
		scanf("%d", &N);
		printf("%u\n", count(N));
	}
	return 0;
}
 