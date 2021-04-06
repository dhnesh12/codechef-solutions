#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define vl vector<ll> 
#define pb push_back
#define FASTANDFURIOUS ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define For(i,n) for(ll i=0;i<n;i++)
#define MOD 1000000007
#define MAX 1000001
#define pll pair <ll,ll>
#define pii pair <int,int>
#define dbg(x)    cout << #x << ": " << x << endl;
#define fi first
#define se second
#define read(n,v) For(i,n)cin>>v[i]
#define mxh priority_queue<int>
#define mnh priority_queue<int,vector<int>,greater<int>>
#define mkp make_pair
#define YES cout<<"YES\n";
#define NO cout<<"NO\n";
#define No cout<<"No\n";
#define Yes cout<<"Yes\n";
#define INF 1e18
using namespace std; 
ll ncr_2(ll n, ll k ){
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;
 
    ll result = n;
    for(ll i = 2; i <= k; ++i ) {
        result = result * (n-i+1);
        result /= i;
    }
    return result;
}
ll pow(int x, unsigned int y, int p){
    int res=1;
    x=x%p;
    if (x==0) return 0;
    while (y > 0){
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
ll _pow(int a, int b){
    if(!b)
        return 1;
    int temp = _pow(a, b / 2);
    temp = (temp * temp);
    if(b % 2)
        return (a * temp);
    return temp;
}
int invmod(int a,int m){
    return pow(a,m-2,m);
}
ll feelthepower(ll x,ll y){
    ll res = 1LL;
    while(y){
        if(y&1){
            res = (res*1LL*x)%MOD;
        }
        x = (x*1LL*x)%MOD;
        y/=2;
    }
    return res;
}
// ll ncr(int n,int r){
//     if(n<r)
//         return 0;
//     int ans=fac[n];
//     ans*=invmod(fac[n-r],MOD);
//     ans%=MOD;
//     ans*=invmod(fac[r],MOD);
//     ans%=MOD;
//     return ans;
// }

signed main(){
    FASTANDFURIOUS;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int tc=1;
    vi prime;
    rep(i,2,51){
        int cnt=0;
        for(int j = 2;j*j<=i;j++){
            if(i%j==0){
                cnt++;
                break;
            }
        }
        if(!cnt)prime.pb(i);
    }
    cin>>tc;
    For(ti,tc){
        int n;
        cin>>n;
        if(n==1){
            cout<<0<<endl;
            int x;
            cin>>x;
            cout<<x<<endl;
            continue;
        }
        vi v(n);
        For(i,n){
            cin>>v[i];
        }
        int flag=0;
        rep(i,0,n){
            bool ok = false;
            rep(j,0,n){
                if(i!=j){
                    if(__gcd(v[j],v[i])==1){
                        ok = true;
                    }
                }
            }
            if(!ok){
                flag=1;
                For(k,prime.size()){
                    int cnt=0;
                    rep(j,0,n){
                        if(v[j]%prime[k]==0){
                            cnt++;break;
                        }
                    }
                    if(!cnt){
                        v[i]=prime[k];
                        break;
                    }
                }
                break;
            }
        }
        if(flag){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
        for(auto x:v){
            cout<<x<<" ";
        }
        cout<<endl;
    }
}