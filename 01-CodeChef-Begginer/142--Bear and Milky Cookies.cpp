#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
    	int n;
    	cin>>n;
    	string s[n];
    	for(int i=0; i<n; i++){
    		cin>>s[i];
    	}
    	int flag=0;
    	if((n==1 && s[n-1]=="cookie")  || s[n-1]=="cookie"){
    		flag=1;
    		cout<<"NO\n";
    	}else{
    	for(int i=0; i<n-1; i++){
    		if(s[i]=="cookie" && s[i+1]!="milk"){
    			flag=1;
    			cout<<"NO\n";
    			break;
    		}
    	}
    	}
    	if(flag==0){
    		cout<<"YES\n";
    	}
    }
    return 0;
}