#include <bits/stdc++.h>
using namespace std;
#define m 1000000007

int main() {
	// your code goes here
	string s;cin>>s;
	long long int x=0,ans=0;
	int n=s.size();
	for(int i=0;i<n; i++){
	    ans+=((x+1)%m)*('Z'-s[i]);
	    x= ((26*x)%m)+('Z'-s[i]);
	}
	cout<<ans%m;
	return 0;
}