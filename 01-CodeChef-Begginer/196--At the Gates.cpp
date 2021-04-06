#include <iostream>
#include<bits/stdc++.h>
using namespace std;
void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n,k;
	    cin>>n>>k;
	    char a[n];
	    for(int i=0;i<n;i++) cin>>a[i];
	    int n_heads{},n_tails{};
	    for(int i=0;i<n-k;i++){
	        if(a[i] == 'H') n_heads++;
	        else n_tails++;
	    }
	    if(a[n-k] == 'H') swap(n_heads,n_tails);
	    cout<<n_heads<<endl;
	}
	return 0;
}
