#include <bits/stdc++.h>
#define MOD 1000000007
#define EPS ((long double)1e-12)
#define ll long long
#define ld long double
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define sz(x) ((long long)(x).size())
#define endl '\n'
#define DUMP_NAME(name,a) cout << "#dump " << (name) << " = " << (a) << "  "
#define dump(a) DUMP_NAME(#a, (a));
#define FOREACH(it,x) for(__typeof__((x).begin()) it = (x).begin();it!=(x).end();++it)
#define FOR(i,a,b) for(ll i=(ll)(a);i<=(ll)(b);++i)
#define ROF(i,a,b) for(ll i=(ll)(a);i>=(ll)(b);--i)
const ld PI = 3.141592653589793238L;
const ll N = 100005;
using namespace std;

ll n;
ll a[10005];
map<ll,ll> ind , r[N];
bool ari[10005] , geo[10005];

bool try_ari(){
    memset(ari,0,sizeof(ari));
    vector<ll> v;
    FOR(i,1,n) if(geo[i] == 0) v.pb(a[i]);

    if(sz(v) == 0){
        ari[1] = ari[2] = 1;
        return 1;
    }

    if(sz(v) == 1){
        ari[ind[v[0]]] = 1;
        if(ind[v[0]] == 1) ari[2] = 1;
        else ari[1] = 1;

        return 1;
    }

    ll rr = v[1] - v[0];
    FOR(k,1,3){
        if(rr % k != 0) continue;

        ll r = rr / k;
        bool found = 1;
        memset(ari,0,sizeof(ari));

        FOR(i,v[0],v[sz(v) - 1]){
            if(a[ind[i]] != i){
                found = 0;
                break;
            }

            ari[ind[i]] = 1;
            i += r - 1;
        }

        FOR(i,0,sz(v) - 1) if(ari[ind[v[i]]] == 0){
            found = 0;
            break;
        }

        if(found == 0) continue;

        return 1;
    }

    return 0;
}

bool try_geo(){
    memset(geo,0,sizeof(geo));
    vector<ll> v;
    FOR(i,1,n) if(ari[i] == 0) v.pb(a[i]);

    if(sz(v) == 0){
        geo[1] = geo[2] = 1;
        return 1;
    }

    if(sz(v) == 1){
        geo[ind[v[0]]] = 1;
        if(ind[v[0]] == 1) geo[2] = 1;
        else geo[1] = 1;

        return 1;
    }

    ll x1 = v[1] , x2 = v[0];
    ll g = __gcd(x1 , x2);
    x1 /= g , x2 /= g;

    FOR(p,1,16){
        ll tx1 = r[x1][p] , tx2 = r[x2][p];
        if(tx1 == 0 || tx2 == 0) continue;
        memset(geo,0,sizeof(geo));

        bool found = 1;

        ll i = v[0];
        while(i <= v[sz(v) - 1]){
            if(a[ind[i]] != i){
                found = 0;
                break;
            }

            geo[ind[i]] = 1;

            i *= tx1;
            if(i % tx2 != 0) break;
            i /= tx2;
        }

        FOR(i,0,sz(v) - 1) if(geo[ind[v[i]]] == 0){
            found = 0;
            break;
        }

        if(found == 0) continue;

        return 1;
    }

    return 0;
}

void print_ans(){
    FOR(i,1,n) if(ari[i] == 1) cout << a[i] << " ";
    cout << endl;
    FOR(i,1,n) if(geo[i] == 1) cout << a[i] << " ";
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    #endif
    //<<>>

    FOR(j,1,16) r[1][j] = 1;
    FOR(i,2,100000){
        ll ii = i , j = 1;
        while(ii <= 100000) r[ii][j] = i , ++j , ii *= i;
    }
    
    ll tc; cin >> tc;
    while(tc--){
        cin >> n;
        ind.clear();
        FOR(i,1,n) cin >> a[i] , ind[a[i]] = i;

        if(n == 2){
            cout << a[1] << " " << a[2] << endl;
            cout << a[1] << " " << a[2] << endl;
            continue;
        }

        // case A A
        if(true){
            memset(ari,0,sizeof(ari));
            ll x = a[1] , r = a[2] - a[1];
            
            while(true){
                if(a[ind[x]] != x) break;
                ari[ind[x]] = 1;
                x += r;
            }

            if(try_geo() == 1){
                print_ans();
                continue;
            }
        }
        
        // case G G
        if(true){
            memset(geo,0,sizeof(geo));
            ll x = a[1] , r1 = a[2] , r2 = a[1];
            ll g = __gcd(r1 , r2);
            r1 /= g , r2 /= g;

            while(true){
                if(a[ind[x]] != x) break;
                
                geo[ind[x]] = 1;

                x *= r1;
                if(x % r2 != 0) break;
                x /= r2;
            }

            if(try_ari() == 1){
                print_ans();
                continue;
            }
        }
        
        // case A . A
        if(true){
            memset(ari,0,sizeof(ari));
            ll x = a[1] , r = a[3] - a[1];
            
            while(true){
                if(a[ind[x]] != x) break;
                ari[ind[x]] = 1;
                x += r;
            }

            if(try_geo() == 1){
                print_ans();
                continue;
            }
        }
        
        // case G . G
        if(true){
            memset(geo,0,sizeof(geo));
            ll x = a[1] , r1 = a[3] , r2 = a[1];
            ll g = __gcd(r1 , r2);
            r1 /= g , r2 /= g;
            
            while(true){
                if(a[ind[x]] != x) break;
                
                geo[ind[x]] = 1;

                x *= r1;
                if(x % r2 != 0) break;
                x /= r2;
            }

            if(try_ari() == 1){
                print_ans();
                continue;
            }
        }
        
        // case . A A
        if(true){
            memset(ari,0,sizeof(ari));
            ll x = a[2] , r = a[3] - a[2];
            
            while(true){
                if(a[ind[x]] != x) break;
                ari[ind[x]] = 1;
                x += r;
            }

            if(try_geo() == 1){
                print_ans();
                continue;
            }
        }
        
        // case . G G
        if(true){
            memset(geo,0,sizeof(geo));
            ll x = a[2] , r1 = a[3] , r2 = a[2];
            ll g = __gcd(r1 , r2);
            r1 /= g , r2 /= g;
            
            while(true){
                if(a[ind[x]] != x) break;
                
                geo[ind[x]] = 1;

                x *= r1;
                if(x % r2 != 0) break;
                x /= r2;
            }

            if(try_ari() == 1){
                print_ans();
                continue;
            }
        }
        
    }

    return 0;
}