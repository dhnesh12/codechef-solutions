#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    //int vis[26]{};
	    //int min_diff[26];
	    //fill(min_diff,min_diff+26,INT_MAX);
	    int last_index[26];
	    fill(last_index,last_index+26,-1);
	    int min_diff = INT_MAX;
	    int n;
	    cin>>n;
	    string s;
	    cin>>s;
	    for(int i=0;i<n;i++){
	        if(last_index[s[i]-'a']>-1){
	            min_diff = min(min_diff,i-last_index[s[i]-'a']);
	            last_index[s[i]-'a'] = i;
	        }
	        else{
	            //vis[s[i]-'a'] = 1;
	            last_index[s[i]-'a'] = i;
	        }
	    }
	   // int mid{INT_MAX};
	   // for(int i=0;i<26;i++){
	   //     mid = min(mid,min_diff[i]);
	   // }
	    if(min_diff == INT_MAX) cout<<0<<endl;
	    else cout<<n-min_diff<<endl;
	}
	return 0;
}
