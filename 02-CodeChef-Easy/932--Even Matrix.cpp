#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int mat[n][n],k=1;
	    for(int i=0;i<n;i++){
	        for(int j=0;j<n;j++){
	            mat[i][j] = k++;
	        }
	        if(i%2 && n%2==0) reverse(mat[i],mat[i]+n);
	    }
	    for(int i=0;i<n;i++){
	        for(int j=0;j<n;j++){
	            cout<<mat[i][j]<<" ";
	        }
	        cout<<endl;
	    }
	}
	return 0;
}
