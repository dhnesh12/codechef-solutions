#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define MAX 100001
#define MOD 1000000007
// #define MOD 998244353
#define pb push_back
#define F first
#define S second
#define INF 2e18
#define PII pair<int,int>
#define PLL pair<long long, long long>

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin>>t;
    while(t--)
    {
        int n, k; cin>>n>>k;
        set<PII> s;
         
        int x; 
        for(int i=0; i<n+1; i++)
        {
            cin>>x;
            s.insert({x, i});
        }
        while(s.size())
        {
        	if(s.size()==1)
        	{
        		auto it = *s.begin();
        		cout<<it.S<<" "<<k<<" 0 0"<<endl;
        		s.erase(it);
        	}
        	else
        	{
        		auto it1 = *s.begin();
        		auto it2 = s.end();
        		it2--;
        		auto i = *it2;
        		cout<<it1.S<<" "<<it1.F<<" "<<i.S<<" "<<k - it1.F;
        		cout<<'\n';
        		s.erase(it1);
        		s.erase(i); 
        		if(i.F>k-it1.F)
        		{
        			s.insert({i.F - k + it1.F, i.S});
        		}
        	}
        }
    }
        
    return 0;
}