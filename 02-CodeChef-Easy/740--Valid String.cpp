#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	long long t;
	cin>>t;
	while(t--){
	    long long n,c;
	    cin>>n>>c;
	    string s;
	    cin>>s;
	    vector<long long> v;
	    for(long long i=0;i<n;i++){
	        if(s[i]=='1'){
	            v.push_back(i);
	        }
	    }
	    long long cnt=0;
	    for(long long i=0;i+1<v.size();i++){
	        if((v[i+1]-v[i]-1)>c){
	            cnt++;
	        }
	    }
	    if(!v.empty() && n-v.back()-1+v[0]>c){
	        cnt++;
	    }
	    if(cnt<=1){
	        cout<<"YES"<<endl;
	    }
	    else{
	        cout<<"NO"<<endl;
	    }
	    
	}
	return 0;
}
