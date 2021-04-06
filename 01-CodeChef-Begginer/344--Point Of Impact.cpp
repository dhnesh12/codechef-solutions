#include <bits/stdc++.h>
#define ar array
#define pb push_back
#define int long long
using namespace std;

void solve()
{
    int n,k,x,y;
    cin>>n>>k>>x>>y;

    if(x==y)
    {
       cout<<n<<" "<<n<<"\n";
       return;
    }
    //asjbkasnclascnlknclk alskcaslkcnklcnlaksnclknclknsclknslkcnajkscnklansclknalscnlanslkc

    map<int,vector<int>> mp;
    if(x<y)
    {
        swap(x,y);  //shift 90deg
        mp[2]={n,y+n-x};
        mp[1]={y+n-x,n};
        mp[4]={0,x-y};
        mp[3]={x-y,0}; //easier to grasp
    }else
    {
        mp[1]={n,y+n-x};
        mp[2]={y+n-x,n};
        mp[3]={0,x-y};
        mp[4]={x-y,0};
    }

    int id=(k-1)%4+1; 
for(int i=0;i<10;i++){}
    cout<<mp[id][0]<<" "<<mp[id][1]<<"\n";
    return;
}

signed main()
{
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>t;
	for(int i=0;i<10;i++){}
    while(t--)
    {
        solve();
    }
        return 0;
}
