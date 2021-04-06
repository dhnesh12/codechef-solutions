
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

bool ok(string s)
{
	int length = s.length();
	for(int i=0;i<length;i++)
	{
        if(s[i] != s[length-i-1])
        {
            return false;
	   }
	}
	return true;
}

int fun(string set[], int set_size)
{
	int maxi=99999;
	vector<int>vec;
	vec.clear();
    ll pow_set_size = pow(2,set_size);
    int counter, j;
    string str="";
    for(counter = 0; counter < pow_set_size; counter++)
    {
      for(j = 0; j < set_size; j++)
       {
          if(counter & (1<<j))
          {
            str+=set[j];
            vec.push_back(j);
          }
       }
       int x=vec.size();
       if(ok(str))
       	maxi=min(maxi,(set_size - x));
       vec.clear();
       str="";
    }
    return maxi;
}

int main() {

	string s[1000];
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
			cin>>s[i];
		cout<<fun(s,n)<<"\n";
	}
	return 0;
}