#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e3+9;
const ll MOD = 1e9+7;
struct nst{
    int x,y; ll w;
    nst(int xx, int yy, ll ww){
        x=xx; y=yy; w=ww;
    }
    nst(){}
};
bool cmp(nst n1, nst n2){
    return n1.w < n2.w;
}
int tc, n, cor[MAXN];
bool mrk[MAXN], ok;
vector<int> G[MAXN];
ll a[MAXN];
ll fastxp(ll x, ll ep){
    if(ep==0)return 1;
    if(ep%2==1)return (x*fastxp(x,ep-1))%MOD;
    ll aux = fastxp(x, ep/2);
    return (aux*aux)%MOD;
}
void dfs(int u, int cu){
    mrk[u] = true;
    cor[u] = cu;
    for(int viz : G[u]){
        if(mrk[viz] && cor[viz]==cor[u])ok=false;
        if(!mrk[viz])dfs(viz, (cu+1)%2);
    }
}
int main(){
    cin>>tc;
    while(tc--){
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>a[i];
        }
        vector<nst> v;
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                v.push_back({i, j, min(fastxp(a[i], a[j]), fastxp(a[j], a[i]))});
        ll li = 1;
        ll ri = MOD-1;
        while(li!=ri){
            ll cand = (li+ri)/2;
            for(int i=0; i<n; i++){
                mrk[i] = false;
                G[i].clear();
            }
            for(nst ni : v){
                if(ni.w > cand){
                    G[ni.x].push_back(ni.y);
                    G[ni.y].push_back(ni.x);
                }
            }
            ok = true;
            for(int i=0; i<n; i++){
                if(mrk[i])continue;
                dfs(i, 0);
            }
            if(ok)ri = cand;
            else li = cand+1;
        }
        cout<<li<<endl;
    }
}