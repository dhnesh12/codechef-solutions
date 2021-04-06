#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define endl '\n'
#define all(c) c.begin(),c.end()
#define IOS     ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define F first
#define S second
#define I insert
#define Fill(a, b) memset(a, b, sizeof(a))
#define int ll
#define mod1            1000000007
#define mod2             998244353
#define N 100005
#define loop(i, a, b)		for(ll i=a; i<b; i++)
#define For(i, b)		for(ll i=0; i<b; i++)
#define input(arr,n)  for(ll i=0;i<n;++i) cin>>arr[i];


signed main()
{
    IOS
    ll T;
    cin>>T;
    while(T--){
        ll n,x;
        cin>>n>>x;
        ll a[n+1]={0};
        loop(i,1,n+1) cin>>a[i];
        ll ans=0;
        if(n%2) ans+=a[(n+1)/2];
        priority_queue<ll> q; 
        ll s=n/2;
        ll end=s+1;
        if(n%2) end++;
        while((s>0) and (end<=n)){
            q.push(a[s]);
            q.push(a[end]);
            ans+=q.top();
            q.pop();
            s--;
            end++;
        }
        if(ans>=x){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
   return 0;
}