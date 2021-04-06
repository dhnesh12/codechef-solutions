#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); 
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mod 1000000007

typedef vector<int> vi;

int main() {
    fastio;
    int t;cin>>t;
    while(t--)
    {
        ll n,k;
        cin>>n>>k;
        ll a[k][2];
        unordered_set<ll> sum,diff;
        for(int i=0;i<k;i++)
        {
            cin>>a[k][0]>>a[k][1];
            sum.insert(a[k][0]+a[k][1]-2);
            diff.insert(a[k][0]-a[k][1]);
        }
        ll ans=0;
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<n;j++)
            {
                if(sum.find(i+j)==sum.end() && diff.find(i-j)==diff.end()) ans++;
            }
        }
        cout<<ans<<endl;
    }
	return 0;
}
