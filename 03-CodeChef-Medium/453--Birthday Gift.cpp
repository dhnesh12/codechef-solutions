#include <stdio.h>
#include <limits.h>
#define si(i) scanf("%d", &i)
#define MIN(a,b) a>b?b:a
 
int m, n, d, t;
int memo[100][100], toll[100][100], c[100][100];
 
int sp(){
	int i,j,k;
	for(k=0; k<m; k++) for (i=0; i<m; i++) for(j=0; j<m; j++)
		c[i][j] = MIN(c[i][j], c[i][k]+c[k][j]);
} 
 
int getMin(){
	int min = INT_MAX, k, i, j, l, currentRoad=INT_MAX;
	for(j=0; j<n; j++){
		for(i=0; i<m; i++){
			memo[i][j] = INT_MAX;
			if(j == 0){
				memo[i][j] = toll[i][j];
				if(n==1) min = MIN(memo[i][j], min);
			}else{
				for(l=0; l<m; l++){
					memo[i][j] = MIN(memo[i][j], memo[l][j-1]+c[l][i]);
				}
				memo[i][j] += toll[i][j];
				if(j==n-1){
					min = MIN(memo[i][j], min);
				}
			}
		}
	}
	return min;
}
 
 
int solve(){
	int min = INT_MAX, i, k;
	sp();
	min = getMin();
	return min;	
}
 
int main(void){
	int i,j,k;
	si(t);
	while(t--){
		si(d); si(n); si(m);
		for(i=0; i<m; i++){
			for(j=0; j<n; j++){
				si(toll[i][j]);
			}
		}
		for(i=0; i<m; i++){
			for(j=0; j<m; j++){
				si(c[i][j]);
			}
		}
		k= d - solve();
		
		if(k<0) printf("-1\n");
		else printf("%d\n",k);
	}			
	return 0;
}