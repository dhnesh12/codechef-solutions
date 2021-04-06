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
	    int ans[10]{};
	    string temp;
	    while(n--){
	        cin>>temp;
	        for(int i=0;i<10;i++){
	            if(ans[i] == temp[i]-48) ans[i] = 0;
	            else ans[i] = 1;
	        }
	    }
	    int count{};
	    for(int i=0;i<10;i++){
	        if(ans[i]) count++;
	    }
	    cout<<count<<endl;
	}
    //cout<<'1'-48;
	return 0;
}
