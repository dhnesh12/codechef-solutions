#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

int n;
int x[10005], y[10005];
int x2[10005], y2[10005], x3[10005], y3[10005];
pii p[10005];

int ft[20005];
void update(int i, int v){
    for(;i<=20001;i+=(i&-i)){
        ft[i] += v;
    }
}
int query(int i){
    int ans = 0;
    for(;i>0;i-=(i&-i)){
        ans+=ft[i];
    }
    return ans;
}
vector<int> add1[20005], add2[20005], del1[20005], del2[20005];
bool check(int d){
    memset(ft, 0, sizeof(ft));
    vector<int> X, Y;
    for(int i=1;i<=n+n;i++){
        add1[i].clear();
        add2[i].clear();
        del1[i].clear();
        del2[i].clear();
    }
    for(int i=1;i<=n;i++){
        X.eb(x[i]);
        X.eb(x[i]-d);
        Y.eb(y[i]);
        Y.eb(y[i]-d);
    }
    sort(all(X));
    sort(all(Y));
    X.erase(unique(all(X)), X.end());
    Y.erase(unique(all(Y)), Y.end());
    for(int i=1;i<=n;i++){
        x2[i] = lower_bound(all(X), x[i]-d) - X.begin() + 1;
        x3[i] = lower_bound(all(X), x[i]) - X.begin() + 1;
        y2[i] = lower_bound(all(Y), y[i]-d) - Y.begin() + 1;
        y3[i] = lower_bound(all(Y), y[i]) - Y.begin() + 1;
        add1[x2[i]].eb(i);
        del1[x3[i]].eb(i);
    }
    for(int i=1;i<=n+n;i++){
        for(int j=0;j<sz(add1[i]);j++){
            int idx = add1[i][j];
            update(y2[idx], 1);
            update(y3[idx]+1, -1);
        }
        for(int j=0;j<sz(add1[i]);j++){
            int idx = add1[i][j];
            int q = query(y2[idx]);
            if(q >= 3){
                int k = upper_bound(all(X), X[i-1]+d) - X.begin() - 1;
                add2[i].eb(y2[idx]);
                del2[k+1].eb(y2[idx]);
            }
            q = query(y3[idx]);
            if(q >= 3){
                int k = upper_bound(all(X), X[i-1]+d) - X.begin() - 1;
                add2[i].eb(y3[idx]);
                del2[k+1].eb(y3[idx]);
            }
        }
        for(int j=0;j<sz(del1[i]);j++){
            int idx = del1[i][j];
            int q = query(y2[idx]);
            if(q >= 3){
                int k = upper_bound(all(X), X[i-1]+d) - X.begin() - 1;
                add2[i].eb(y2[idx]);
                del2[k+1].eb(y2[idx]);
            }
            q = query(y3[idx]);
            if(q >= 3){
                int k = upper_bound(all(X), X[i-1]+d) - X.begin() - 1;
                add2[i].eb(y3[idx]);
                del2[k+1].eb(y3[idx]);
            }
        }
        for(int j=0;j<sz(del1[i]);j++){
            int idx = del1[i][j];
            update(y2[idx], -1);
            update(y3[idx]+1, 1);
        }
    }
    memset(ft, 0, sizeof(ft));
    int cnt = 0;
    for(int i=1;i<=n+n;i++){
        for(int j=0;j<sz(add2[i]);j++){
            int y = add2[i][j];
            update(y, 1);
        }
        for(int j=0;j<sz(del1[i]);j++){
            int idx = del1[i][j];
            int q = query(y3[idx]) - query(y2[idx]-1);
            if(q >= 1) cnt++;
        }
        for(int j=0;j<sz(del2[i]);j++){
            int y = del2[i][j];
            update(y, -1);
        }
    }
    return cnt == n;
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            scanf("%d%d", &x[i], &y[i]);
            p[i] = mp(x[i], y[i]);
        }
        sort(p+1, p+1+n);
        for(int i=1;i<=n;i++) x[i] = p[i].fi, y[i] = p[i].se;
        int lo = 0, hi = 1e9, ans;
        while(lo <= hi){
            int mid = (lo+hi)/2;
            if(check(mid)) ans = mid, hi = mid-1;
            else lo = mid+1;
        }
        printf("%d\n", ans);
    }   
}