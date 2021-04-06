#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ll long long
#define int long long
#define M 1000000007
#define sz(a) (ll)a.size()
#define pll pair<ll,ll>
#define rep(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define sep(i,a,b) for(ll i=(ll)a;i>=(ll)b;i--)
#define mll map<ll,ll>
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(a) a.begin(),a.end()
#define F first
#define S second
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ll a[1<<18+1], b[1<<18+1], p[1<<18+1], pp[1<<18+1], q[1<<18+1];
const int N = 1<<18+5;
pair<int, int> seg[4*N];
void build(int i, int l, int r){
    seg[i] = {-100000000000ll, -1000000000000000000ll};
    if(l == r)
        return;
    int mid = (l + r) / 2;
    build(2 * i, l, mid);
    build(2 * i + 1, mid + 1, r);
}
void update(int i, int l, int r, int x, int y, pair<int,int> ln)
{
    if(x > r or l > y)
        return;
    int mid = (l + r) / 2;
    if(l >= x and y >= r){
        long long lnl = ln.first * 1ll * l + ln.second, lnr = ln.first * 1ll * r + ln.second;
        long long segl = seg[i].first * 1ll * l + seg[i].second, segr = seg[i].first * 1ll * r + seg[i].second;
        if(segl >= lnl and segr >= lnr)
            return;
        if(lnl >= segl and lnr >= segr){
            seg[i] = ln;
            return;
        }
        bool m = (ln.first * 1ll * mid + ln.second > seg[i].first * 1ll * mid + seg[i].second);
        if(m)
            swap(seg[i], ln);
        if((lnl > segl) ^ m)
            update(2 * i, l, mid, x, y, ln);
        else
            update(2 * i + 1, mid + 1, r, x, y, ln);
    }
    update(2 * i, l, mid, x, y, ln);
    update(2 * i + 1, mid + 1, r, x, y, ln); 
}
long long query(int i, int l, int r, int x){
    if(l == r)
        return seg[i].first * 1ll * x + seg[i].second;
    int mid = (l + r) / 2;
    if(x <= mid)
        return max(seg[i].first * 1ll * x + seg[i].second, query(2 * i, l, mid, x));
    else
        return max(seg[i].first * 1ll * x + seg[i].second, query(2 * i + 1, mid + 1, r, x));
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        rep(i,1,n+1)
            cin>>a[i];
        rep(i,1,n+1)
            cin>>b[i];
        rep(i,n+1,2*n+1){
            a[i]=a[i-n];
            b[i]=b[i-n];
        }
        rep(i,1,2*n+1){
            p[i]=p[i-1]+a[i];
            pp[i]=pp[i-1]+(i*a[i]);
            q[i]=q[i-1]+b[i];
        }
        build(1,0,2*n);
        update(1,0,2*n,0,n,{-p[0],-p[0]+pp[0]-q[0]});
        ll ans=-1000000000000000000LL;
        rep(i,1,2*n+1){
            ans=max(ans,(i+1)*p[i]-pp[i]+q[i]+query(1,0,2*n,i));
            update(1,0,2*n,i,min(i+n,2*n),{-p[i],-p[i]+pp[i]-q[i]});
        }
        cout<<ans<<"\n";
    }
}

