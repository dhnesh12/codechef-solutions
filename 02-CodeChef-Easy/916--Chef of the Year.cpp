#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes herem>
	map<string,string> mp1;
	map <string,int> mp2,mp3;
	int n,m;
	string name,country;
	cin>>n>>m;
	while(n--)
	{
		cin>>name>>country;
		mp1.insert(make_pair(name,country));
		//mp2[country]++;
	}
	while(m--)
	{
		cin>>name;
		mp3[name]++;
		mp2[mp1[name]]++;
	}
	int max=-1;string ans;
	for(auto itr=mp2.begin();itr!=mp2.end();itr++)
	{
		if(itr->second>max)
		{
			max=itr->second;
			ans=itr->first;
		}
		if(itr->second==max)
		{
			if((itr->first.compare(ans)) < 0) 
			ans=itr->first;
		}
	}
	cout<<ans<<endl;
	max=-1;
		for(auto it=mp3.begin();it!=mp3.end();it++)
	{
		if(it->second>max)
		{
			max=it->second;
			ans=it->first;
		}
		if(it->second==max)
		{
			if((it->first.compare(ans)) < 0) 
			ans=it->first;
		}
	}
	cout<<ans<<endl;
	return 0;
}