#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;
typedef pair<ll, int> pli;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

int a[1000005];
ll dp[35];
ll sum[1<<15];
unordered_map<int, vector<int> > val1, val2;

void rec(vector<int> &a, int b){
    if(b == -1 || sz(a) == 0) return;
    int one = 0, zero = 0;
    vector<int> x, y;
    // printf("b=  %d\n", b);
    for(int i=0;i<sz(a);i++){
        if((a[i]>>b)&1){
            dp[b] += zero;
            x.eb(a[i]);
            one++;
        }
        else{
            dp[b] -= one;
            y.eb(a[i]);
            zero++;
        }
    }
    rec(x, b-1);
    rec(y, b-1);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        val1.clear(), val2.clear();
        memset(dp, 0, sizeof(dp));
        int n, k, p;
        scanf("%d%d%d", &n, &k, &p);
        vector<int> x;
        for(int i=1;i<=n;i++) scanf("%d", &a[i]), x.eb(a[i]);
        rec(x, k-1);

        if(k <= 10){
            vector<pli> v;
            for(int i=0;i<(1<<k);i++){
                ll ans = 0;
                for(int j=0;j<k;j++){
                    if((i>>j)&1){
                        ans += dp[j];
                    }
                }
                v.eb(mp(ans, i));
            }
            sort(all(v));
            printf("%d\n", v[p-1].se);
        }
        else{
            int m1 = k/2, m2 = k-k/2;
            vector<ll> h;
            h.eb(-1e18);
            for(int i=0;i<(1<<m1);i++){
                ll val = 0;
                for(int j=0;j<m1;j++){
                    if((i>>j)&1) val += dp[j];
                }
                val1[val].eb(i);
                h.eb(val);
            }
            sort(all(h));
            h.erase(unique(all(h)), h.end());

            for(int i=0;i<(1<<m2);i++){
                ll val = 0;
                for(int j=0;j<m2;j++){
                    if((i>>j)&1) val += dp[m1+j];
                }
                val2[val].eb(i<<m1);
            }

            memset(sum, 0, sizeof(sum));
            for(int i=1;i<sz(h);i++){
                sum[i] = sz(val1[h[i]]);
                sum[i] = sum[i-1] + sum[i];
            }

            ll lo = -1e12, hi = 1e12, ans1 = -1, ans2 = -1;
            while(lo <= hi){
                ll mid = (lo+hi)/2;
                ll res = 0;

                for(auto it:val2){
                    ll val = it.fi;
                    int idx = upper_bound(all(h), mid-val) - h.begin() - 1;
                    res += sz(it.se)*1ll*sum[idx];
                }
                if(res >= p){
                    ans1 = mid, hi = mid-1;
                    ans2 = res;
                }
                else{
                    lo = mid+1;
                }
            }
            p = ans2-p+1;
            int ans = 0;
            for(int i=(1<<m2)-1;i>=0;i--){
                ll val = 0;
                for(int j=0;j<m2;j++){
                    if((i>>j)&1) val += dp[m1+j];
                }
                ll rem = ans1-val;
                if(val1.count(rem)){
                    if(sz(val1[rem]) >= p){
                        ans = (i<<m1) | (val1[rem][sz(val1[rem])-1-p+1]);
                        break;
                    }
                    else{
                        p -= sz(val1[rem]);
                    }
                }
            }
            printf("%d\n", ans);
        }
    }
}