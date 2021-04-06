#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
#define all(v) v.begin(),v.end()
#define mod 1000000000 
#define N 200010
#define inf 10000000000
#define pb(x) push_back(x)
 
signed main()
{
    fast
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i=0;i<n;i++)
        {
        	cin>>v[i];
        }
        
        vector<int> s;
        s.pb(0);
        int ans=0;
        for(int i=0;i<n;i++)
        {
        	int curr=v[i];
        	while(s.size()>0 && s.back()>curr)
        	{
        		ans++;
        		s.pop_back();
        	}
        	if(s.back()!=curr)
        	{
        		s.pb(curr);
        	}
        }
        ans-=2;
        cout<<ans+s.size()<<"\n";
    }
}