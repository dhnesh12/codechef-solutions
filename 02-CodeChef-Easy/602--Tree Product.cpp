#include<bits/stdc++.h>
using namespace std;
long long int fun(long long int *arr,double *fake,long long int n){
	long long int mod=1000000007;
	long long int value=0;
	for(int i=n-1;i>=1;i--){
		if((2*i+1)<n){
			if(fake[2*i]>=fake[2*i+1]){
				fake[i]=fake[i]+fake[2*i];
				arr[i]=(arr[i]*arr[2*i])%mod;
			}
			else{
				fake[i]=fake[i]+fake[2*i+1];
				arr[i]=(arr[i]*arr[2*i+1])%mod;
			}
		}
	}
	return arr[1];
}
int main(void){
	int h;
	cin>>h;
	while(h){
		int n=pow(2,h);
		long long int arr[n];
		double fake[n];
		for(int i=1;i<n;i++){
			cin>>arr[i];
			fake[i]=log(arr[i]);
		}
		long long int ans=fun(arr,fake,n);
		cout<<ans<<endl;
		cin>>h;
	}
}