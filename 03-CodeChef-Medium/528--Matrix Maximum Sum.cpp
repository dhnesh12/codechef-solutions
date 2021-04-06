#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define mst(a,b) memset(a,b,sizeof(a))
#define lowbit(x) ((x)&(-x))
#define X first
#define Y second
using namespace __gnu_pbds;
using namespace std;
typedef long long LL;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 100000+10;
int n;
int a[maxn],r[maxn],c[maxn],le[maxn],ri[maxn],sum[maxn];
void update(int l,int r,int val){
    sum[l]=((1ll*sum[l]+val)%mod+mod)%mod;
    sum[r+1]=((1ll*sum[r+1]-val)%mod+mod)%mod;
}
stack<int> stk;
void solve(int *res){
    for (int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=i;
    }
    while (!stk.empty()) stk.pop();
    for (int i=1;i<=n;i++){
        le[i]=i; ri[i]=n;
        while (!stk.empty() && a[stk.top()]<=a[i]){
            ri[stk.top()]=i-1;
            le[i]=le[stk.top()];
            stk.pop();
        }
        stk.push(i);
    }
//    for (int i=1;i<=n;i++) cout<<le[i]<<" "<<ri[i]<<"\n";
//    cout<<"\n";
    mst(sum,0);
    for (int i=1;i<=n;i++){
        int mn=min(i-le[i],ri[i]-i),len=ri[i]-le[i]+1;
        update(1,mn+1,a[i]);
        update(len-mn+1,len+1,-a[i]);
    }
    for (int i=1;i<=n;i++){
        sum[i]=(1ll*sum[i-1]+sum[i])%mod;
    }
    int s=0;
    for (int i=1;i<=n;i++){
        s=(1ll*s+sum[i])%mod;
        res[i]=s;
//        cout<<res[i]<<" ";
    }
}
int main() {
#ifdef local
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    solve(r);
    solve(c);
    for (int i=1;i<=n;i++){
        if (i>1) cout<<" ";
        cout<<1ll*r[i]*c[i]%mod;
    }
    cout<<"\n";
    return 0;
}
