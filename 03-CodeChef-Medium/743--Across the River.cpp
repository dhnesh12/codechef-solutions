#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ul ;
typedef long long ll ;
typedef pair<ll, ll>  p ;
typedef pair< p , ll > edge ;
//#define Euc_D(x1,y1,x2,y2) (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
#define vi vector< ll >
#define vl vector< ll >
#define sci(x) ll x; scanf("%d",&x)
#define scu(x) ul x ; scanf("%llu", &x)
#define scl(x) ll x ; scanf("%lld", &x)
#define pr(x) prllf("%llu", x)
#define rep(i , a , b , n) for(ll i = a; i < b ; i += n )
#define f first
// #define s second
#define pb push_back
#define mp make_pair
#define tc(t) scu(t); while ( t-- )
#define nl '\n'
#define MOD 1000000007
// just type fast; at the beginning to do both these
#define fast ios::sync_with_stdio(false); cin.tie(0)
#define inf 0x3f3f
ll Euc_D(ll x1, ll y1, ll x2, ll y2){
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}
bool is_edge(ll dx, ll dy, ll r){
    return dx*dx+dy*dy <= r*r;
}
int main()
{
    fast;
    ll T;
    cin>>T;
    //T = 1;
    while(T--){
        ll n,m,w;
        cin>>n>>m>>w;
        vector<pair<ll,ll> >coord(n);
        for(ll i=0;i<n;i++){
            ll x,y;
            cin>>x>>y;
            coord[i] = mp(x,y);
        }
        vector<ll>R(m),C(m);
        for(ll i=0;i<m;i++){
            cin>>R[i]>>C[i];
        }
        vector<pair<ll,ll> >stacks(m);
        for(int i=0;i<m;i++){
            stacks[i] = mp(R[i],C[i]);
        }
        sort(stacks.begin(), stacks.end());
        for(int i=0;i<m;i++){
            R[i] = stacks[i].first;
            C[i] = stacks[i].second;
          //  cout<<R[i]<<" : "<<C[i]<<"\n";
        }
        stacks.clear();
        stack<pair<ll,ll> >St;
        St.push(mp(R[0],C[0]));
        for(int i=1;i<m;i++){
            while(!St.empty()&&C[i]<St.top().second)
                St.pop();
            St.push(mp(R[i],C[i]));
        }
        m = St.size();
        for(int i=m-1;i>=0;i--){
            R[i] = St.top().first;
            C[i] = St.top().second;
            St.pop();
        }
        /*for(int i=0;i<m;i++){
            cout<<R[i]<<" : "<<C[i]<<"\n";
        }*/
        ll edges[n][n][m];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ll b = m-1;
                for(int a=0;a<m;a++){
                    if(!is_edge(coord[i].first-coord[j].first, coord[i].second-coord[j].second, R[a]+R[b])){
                        edges[i][j][a] = -1;
                        continue;
                    }
                    while(b-1>=0&&is_edge(coord[i].first-coord[j].first, coord[i].second-coord[j].second, R[a]+R[b-1]))
                        b--;
                    edges[i][j][a] = b;
                }
            }
        }
        ll dp[n][m];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                dp[i][j] = LONG_LONG_MAX;

        // dist, n, m
        set<pair<ll,pair<ll,ll> > >S;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(coord[i].second <= R[j]){
                    dp[i][j] = C[j];
                    S.insert(mp(C[j],mp(i,j)));
                }
            }
        }
        ll cost_w = LONG_LONG_MAX;

        while(!S.empty()){
            ll cost = S.begin()->first;
            ll u = S.begin()->second.first;
            ll p = S.begin()->second.second;
            //dp[u][p] = min(dp[u][p],cost);
            S.erase(S.begin());
            //cout<<u<<" "<<p<<" "<<cost<<"\n";
            // check for crossing
            if(coord[u].second+R[p]>=w){
                if(cost_w > cost){
                    cost_w = cost;
                }
            }
            ll next;
            if(p+1<m){
                next = dp[u][p]+C[p+1]-C[p];
                if(dp[u][p+1]>next){
                    dp[u][p+1] = next;
                    S.insert(mp(dp[u][p+1],mp(u,p+1)));
                }
            }
            // add neighbours
            for(int i=0;i<n;i++){
                if(i==u)
                    continue;
                if(edges[u][i][p]>=0){
                    ll l = edges[u][i][p];
                    next = dp[u][p]+C[l];
                    if(dp[i][l]>next){
                        dp[i][l] = next;
                        S.insert(mp(dp[i][l], mp(i,l)));
                    }
                }
            }
        }
        ll d = cost_w;
        if(d==LONG_LONG_MAX){
            cout<<"impossible\n";
        }
        else
        cout<<d<<"\n";
    }
    return 0;
}
