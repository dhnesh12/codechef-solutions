#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,i,j;
	cin>>n;
	string s;
	set<string> unblock;
	set<string> block;
	pair<char,string> in;
	for(i=0;i<n;i++)
	{
		cin>>in.first;
		cin>>in.second;
		if(in.first=='+')
		unblock.insert(in.second);
		else
		block.insert(in.second);
	}
int noo=0;
	set<string> :: iterator it,itr;
	set<string> ans;
	for(it=block.begin();it!=block.end();it++)
	{
		for(i=1;i<=it->length();i++){
		string p=it->substr(0,i);
		int flag=0;
		for(itr=unblock.begin();itr!=unblock.end();itr++)
		{
			if(*it==itr->substr(0,it->length()))
			{
				noo=-1;
				break;
			}
			string q=itr->substr(0,i);
			if(p==q)
			{
				flag=1;
				break;
			}
		}
		if(flag!=1){
		ans.insert(p);
		break;}
		if(noo==-1)
		break;
	}
	if(noo==-1)
	break;
	}
	if(noo==-1)
	cout<<"-1\n";
	else{
	cout<<ans.size()<<endl;
	for(it=ans.begin();it!=ans.end();it++)
	cout<<*it<<endl;}

	return 0;
}