#include<bits/stdc++.h>

using namespace std;

int main(){
	int t;
	cin >> t;

	while(t--){
		int n;
		cin >> n;

		int a[n], lsb[n];
		long long unsigned int ans[32]={0};
		
		for(int i=0; i<n; i++){
			cin >> a[i];
		} 

		for(int j=0; j<32; j++){
			for(int i=0; i<n; i++){
				lsb[i] = a[i] & 1;
				a[i] = (a[i] >> 1);
			}

			// ans[j] += a[0];
			int t[n]={0};
			
			t[0]=lsb[0];
			ans[j]+=t[0];
			
			for(int i=1; i<n; i++){
				if(lsb[i]==0){
					t[i]=t[i-1];
				}
				else if(lsb[i]==1){
					t[i] = (i-t[i-1]+1);
				}
				ans[j]+=t[i];
			}
		}

		long long unsigned int sol=0;
		for(int i = 0; i<32; i++){
			// cout<< ans[i] << endl;
			sol+=((1<<i)*ans[i]);
		}

		cout << sol << endl;
	}

	
	return 0;
}