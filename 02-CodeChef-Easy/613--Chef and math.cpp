#include<bits/stdc++.h>
using namespace std;
void ways(vector<int> arr,int n,int target,int k,int &count){
	if(target==0 && k==0){
		count++;
		return;
	}
	if(n==0 || k==0||target<0){
		return;
	}
	ways(arr,n-1,target,k,count);
	ways(arr,n,target-arr[n-1],k-1,count);
}
int fib(int target,int k){
	vector<int> ans;
	
	ans.push_back(1);
	ans.push_back(2);
	int i=2;
	while(ans[i-1]+ans[i-2]<=target){
		ans.push_back(ans[i-1]+ans[i-2]);
		i++;
	}
	
	int count=0;
	ways(ans,i,target,k,count);
	return count;
	
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		cout<<fib(n,k)<<endl;
	}
	
}