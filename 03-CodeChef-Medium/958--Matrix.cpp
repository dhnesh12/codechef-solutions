#include <bits/stdc++.h>
using namespace std;


int c[2005];

int main(){
	int n, m, i, j;
	cin>>n>>m;
	char a[n][m];
	for(i= 0; i< n; i++){
		for(j= 0; j< m; j++){
			cin>>a[i][j];
		}
	}
	long long int s= 0;
	for(i= n- 1; i>= 0; i--){
		for(j= 0; j< m; j++){
			if(a[i][j]== '1'){
				++c[j];
			}
			else{
				c[j]= 0;
			}
		}
		int last= 0;
		for(j= 0; j< m; j++){
			s+= min(last+ 1, c[j]);
			last= min(last+ 1, c[j]);
		}
	}
	cout<<s<<" ";
}