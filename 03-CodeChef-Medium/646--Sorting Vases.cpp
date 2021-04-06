#include <bits/stdc++.h>
using namespace std;

int swapped(int* arr,int n,int mp[20][20]){
	int minn = n;
	bool flag = true;
	for(int i=0;i<n;i++){
		if(arr[i] != i+1){
			flag = false;
		}
	}
	if(flag) return 0;
	for(int i=0;i<n;i++){
		if(arr[i] != i+1){
			if(mp[i][arr[i]-1] == 0){
				swap(arr[i],arr[arr[i]-1]);
				minn = min(1+swapped(arr,n,mp),minn);
				swap(arr[i],arr[arr[i]-1]);
			}
			else{
				swap(arr[i],arr[arr[i]-1]);
				minn = min(swapped(arr,n,mp),minn);
				swap(arr[i],arr[arr[i]-1]);
			}
		}
	}
	return minn;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t,n,m;
	cin >> t;
	while(t--){
		cin >> n >> m;
		int arr[n],mp[20][20];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				mp[i][j] = 0;
			}
		}
		for(int i=0;i<n;i++){
			cin >> arr[i];
		}
		int a,b;
		for(int i=0;i<m;i++){
			cin >> a >> b;
			mp[a-1][b-1] = 1;
			mp[b-1][a-1] = 1;
		}
		cout << swapped(arr,n,mp) << endl;
	}	

	return 0;
}