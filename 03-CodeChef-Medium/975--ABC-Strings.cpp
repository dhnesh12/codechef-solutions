#include<bits/stdc++.h>
using namespace std;


int main(){
	string s;
	cin>>s;
	map<pair<int,int>,int>mp;
	long int a=0,b=0,c=0,ans=0;

	mp[{0,0}]++;

	for(int i=0;i<s.length();i++){

		if(s[i]=='A')a++;
		if(s[i]=='B')b++;
		if(s[i]=='C')c++;

		ans +=mp[{a-b,a-c}];
		mp[{a-b,a-c}]++;

	}

	cout<<ans<<endl;
}