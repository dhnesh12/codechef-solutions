#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

multiset<int> cur[1000005];
set<int> zero;

pii st[4000005];
void update(int n, int s, int e, int idx, int v){
    if(s == e) st[n] = mp(v, s);
    else{
        int mid = (s+e)/2;
        if(idx <= mid) update(n+n, s, mid, idx, v);
        else update(n+n+1, mid+1, e, idx, v);
        st[n] = min(st[n+n], st[n+n+1]);
    }
}
pii query(int n, int s, int e, int l, int r){
    if(s > r || l > e) return mp(1e9, 1e9);
    if(l <= s && e <= r) return st[n];
    int mid = (s+e)/2;
    return min(query(n+n, s, mid, l, r), query(n+n+1, mid+1, e, l, r));
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i=1;i<=4*n;i++) st[i] = mp(1e9, 1e9);
    for(int i=0;i<=n+1;i++) zero.insert(i);
    for(int i=1;i<=q;i++){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int l, r;
            scanf("%d%d", &l, &r);
            if(*zero.lower_bound(l) > r) continue;
            pii q = query(1, 1, n, l, l);
            if(q.fi > r){
                update(1, 1, n, l, r);
                if(q.fi != 1e9) cur[l].insert(q.fi);
            }
            else cur[l].insert(r);
        }
        else{
            int p;
            scanf("%d", &p);
            int l = *(--zero.lower_bound(p))+1;
            int r = *zero.upper_bound(p)-1;
            zero.erase(zero.find(p));
            int ans = 0;
            while(1){
                pii q = query(1, 1, n, l, p);
                if(q.fi > r) break;
                ans++;
                if(cur[q.se].empty()) update(1, 1, n, q.se, 1e9);
                else{
                    update(1, 1, n, q.se, *cur[q.se].begin());
                    cur[q.se].erase(cur[q.se].begin());
                }
            }

            printf("%d\n", ans);
            fflush(stdout);
        }
    }
}