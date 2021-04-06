#include <iostream>
#include<vector>
#include<utility>
using namespace std;

int main() {
	int size,a,b,rem,max,player,sum=0,sum1=0;
	cin>>size;
	vector <int> v1,v2;
	vector <pair<int,int>>v3;
	for(int i=0;i<size;i++)
	{
	  cin>>a>>b;
	  sum+=a;
	  sum1+=b;
	  v1.push_back(sum);
	  v2.push_back(sum1);
	}
	for(int i=0;i<v1.size();i++)
	{
	  if(v1[i]>v2[i])
	  {
	    rem=v1[i]-v2[i];
	    v3.push_back(make_pair(1,rem));
	  }
	  else if(v2[i]>v1[i])
	  {
	    rem=v2[i]-v1[i];
	    v3.push_back(make_pair(2,rem));
	  }
	}
	for(int i=0;i<v3.size();i++)
	{
	  if(i==0)
	  {
	    player=v3[0].first;
	    max=v3[0].second;
	  }
	  if(v3[i].second>max)
	  {
	    max=v3[i].second;
	    player=v3[i].first;
	  }
	}
	cout<<player<<" "<<max;
	return 0;
}
