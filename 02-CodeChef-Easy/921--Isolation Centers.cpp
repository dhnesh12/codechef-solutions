#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define mod 1000000007
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin >> t;
	while(t--)
	{
	    int n , q;cin>>n>>q;
	    string s;
	    cin>>s;
	    unordered_map<char , int>mp;
	    for(auto it : s)
	    {
	        mp[it]++;
	    }
	    while(q--)
	    {
	        int p;cin>>p;
	        int cnt = 0;
	        for(auto it : mp)
	        {
	            if(it.second > p)
	            {
	                cnt+=(it.second-p);
	            }
	        }
	        cout<<cnt<<endl;
	    }
	}
	return 0;
}
	  