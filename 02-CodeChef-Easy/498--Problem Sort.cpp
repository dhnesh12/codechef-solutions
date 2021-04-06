#include <stdio.h>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

bool sortbysec(const pair<int,int> &a,const pair<int,int> &b)
{
	return a.second<b.second;
}

int main()
{
	int p,s,i,j,n,x;
	cin>>p>>s;
	n=p;
	int ns[s],sk[s];
	j=1;
	multimap<int,int> v;
	while(n--)
	{int c=0;
	map<int,int> m;
		for(i=0;i<s;i++)
		cin>>sk[i];
		for(i=0;i<s;i++)
		{
			cin>>x;
			m[sk[i]]=x;
		}
		map<int,int> ::iterator itr;
		map<int,int> ::iterator itr1;
	//	for(itr=m.begin();itr!=m.end();itr++)
	//	cout<<itr->first<<" "<<itr->second<<endl;
		for(itr=m.begin(),itr1=++m.begin();itr!=m.end() && itr1!=m.end();itr++,itr1++)
		{
			if((itr)->second > (itr1)->second)
			c++;
		}
	//	cout<<c<<endl;
		v.insert(make_pair(c,j));
		j++;
}
//	sort(v.begin(),v.end(),sortbysec);
	multimap<int,int> :: iterator it;
	for(it=v.begin();it!=v.end();it++)
	cout<<it->second<<endl;
	return 0;
}