#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pi pair<int,int>
#define rep(i,n,m) for(int i=n;i<m;i++)
#define f first
#define s second
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,res=0,ans=0;
        cin>>n>>m;
        vector<pi> a(n);
        rep(i,0,n)
        {
            cin>>a[i].f>>a[i].s;
            res=max(res,a[i].f*a[i].s);
        }
        if(m>=(n-1))
        {
            cout<<res<<'\n';
            continue;
        }
        sort(a.begin(),a.end());
        m=n-m;
        multiset<int> s;
        for(int i=n-1;i>=(n-m);i--)
        s.insert(a[i].s);
        ans=max(ans,a[n-m].f*(*s.begin()));
        for(int i=n-m-1;i>=0;i--)
        {
            if(a[i].s>(*s.begin()))
            {
                s.erase(s.begin());
                s.insert(a[i].s);
            }
            ans=max(ans,a[i].f*(*s.begin()));
        }
        assert(ans>=0 and res>=0);
        cout<<ans<<'\n';
    }
    return 0;
}