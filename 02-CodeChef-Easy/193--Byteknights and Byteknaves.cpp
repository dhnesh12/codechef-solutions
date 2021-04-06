//https://youtu.be/z5IAJmUZBGw
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef long long unsigned llu;
typedef pair<long long, long long> pll;
const long long inf = 2000000000000000000LL;    // 2e18
#define pi                  acos(-1.0)
#define fastio              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define nl                  "\n"
#define ff                  first
#define ss                  second
#define pb                  push_back
#define in                  insert
#define all(x)              x.begin(),x.end()
#define mx 100001
int arr[mx];
int tree[mx * 3];
void init(int node, int b, int e)
{
    if (b == e) {
        tree[node] = arr[b];
        return;
    }
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    init(Left, b, mid);
    init(Right, mid + 1, e);
    tree[node] = tree[Left] + tree[Right];
}
int query(int node, int b, int e, int i, int j)
{
    if (i > e || j < b)
        return 0;
    if (b >= i && e <= j)
        return tree[node];
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    int p1 = query(Left, b, mid, i, j);
    int p2 = query(Right, mid + 1, e, i, j);
    return p1 + p2;
}
void update(int node, int b, int e, int i, int newvalue)
{
    if (i > e || i < b)
        return;
    if (b >= i && e <= i) {
        tree[node] = newvalue;
        return;
    }
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    update(Left, b, mid, i, newvalue);
    update(Right, mid + 1, e, i, newvalue);
    tree[node] = tree[Left] + tree[Right];
}
int main()
{
    fastio;
    ll tt=1,i,j,k,l,m,n,o,p,q,temp,ans=0,flag=0,mod=1000000007;
    string s,s1,s2,t,t1,t2;
    cin>>tt;
    while(tt--){
        cin>>n;
        ll a[n+10]={};
        vector<pll>v;
        for(i=0;i<n;i++){
            cin>>j>>k;
            v.pb({j,k});
            //cout<<v[i].ff<<" / "<<v[i].ss<<nl;
            a[j]++;
            a[k+1]--;
        }
        for(i=1;i<=n;i++){
            a[i]+=a[i-1];
        }
        set<ll>s;
        memset(arr,0,sizeof(arr));
        for(i=0,ans=0;i<=n;i++){
            if(a[i]==i){
                 ans++;
                 s.in(i);
                 arr[i]++;
            }
        }
        cout<<ans<<nl;
        if(a[0]==0){
            for(i=0;i<n;i++) cout<<"0";
            cout<<nl;
            continue;
        }
        init(1,1,n);
        for(i=1,temp=ans;i<=n;i++){
            j=v[i-1].ff;
            k=v[i-1].ss;
            l=0;
            l=query(1,1,n,j,k);
            //cout<<l<<" -"<<nl;
            if(l==temp){
                cout<<"1";
                continue;
            }else{
                cout<<"0";
                temp-=l;
                while(s.size()){
                    auto it=s.lower_bound(j);
                    if(it!=s.end() && *it<=k){
                        update(1,1,n,*it,0);
                        s.erase(it);
                    }else break;
                }
            }
        }
        cout<<nl;
    }
}
