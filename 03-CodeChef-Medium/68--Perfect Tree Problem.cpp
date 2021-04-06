#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string.h>
#include <queue>

#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

#define MOD 1000000007
#define INV_MOD_2 500000004

inline void read(int &x) {
    register int c = getchar_unlocked();
    x = 0;
    int neg = 0;

    for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());

    if(c=='-') {
    	neg = 1;
    	c = getchar_unlocked();
    }

    for(; c>47 && c<58 ; c = getchar_unlocked()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }

    if(neg)
    	x = -x;
}

inline int Pow(int a, int b) {
    if (a == 1) {
        return a;
    }

    if (b==0) {
        return 1;
    }

    ll a_pow = a;
    int pos = 0;
    ll ret = 1;

    while (b) {
        if (b & (1<<pos)) {
            ret = ret * a_pow % MOD;
            b = b - (1<<pos);
        }
        a_pow = (a_pow * a_pow) % MOD;
        pos++;
    }

    return ret;
}

int dfs_cnt = 0;
int dfs_start[200005];
int dfs_end[200005];
int height[200005];

vector< vector<int> > tree;
vector< vector<int> > layer_tree;
int n_start[200005];
int n_end[200005];
int next_height[200005];

ll cache[200005];

ll gp_inv = 0;
ll gp_num = 0;
ll soFar = 1;
ll prn = 0;


ll ypow1[451];
ll ypow2[451];

inline void PowYSetup(ll y) {
  ypow1[0] = 1;
  for (int i=1; i<=450; i++) {
    ypow1[i] = ypow1[i-1] * y % MOD;
  }
  ypow2[0] = 1;
  for (int i=1; i<=450; i++) {
    ypow2[i] = ypow2[i-1] * ypow1[450] % MOD;
  }
}

inline ll PowY(ll p) {
  return (ypow2[p/450] * ypow1[p%450]) % MOD;
}

ll gpSum(ll r, ll n) {
  if (n==1) {
   return 1;
  }
  if (n%2) {
   return (1 + (r * gpSum(r, n-1))) % MOD;
  }
  return ((1+r) * gpSum(r * r % MOD, n/2)) % MOD;
}

void dfs(int u, int p) {
    dfs_start[u] = dfs_cnt++;
    height[u] = height[p] + 1;
    int h = height[u];

    n_start[u] = layer_tree[h+1].size();

    for (int i=0; i<tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == p) continue;
        dfs(v, u);
    }
    dfs_end[u] = dfs_cnt++;

    layer_tree[h].push_back(u);
    n_end[u] = layer_tree[h+1].size();
}

vector< vector<pii> > qhw;

void calcQhw(int u, int mxHeight) {

    if (!qhw[u].empty()) {
	return;
    }
	
    int lnode = n_start[u];
    int rnode = n_end[u];
    int cur = height[u]+1;

    
    while (cur <= mxHeight) {
        int qHeight = next_height[cur] - cur;
        int qWidth = rnode - lnode;
        cur = next_height[cur];
        lnode = n_start[layer_tree[cur-1][lnode]];
        rnode = n_end[layer_tree[cur-1][rnode-1]];

	qhw[u].push_back(pii(qHeight, qWidth));
    }
	
}

inline ll findW(int u, int y, int mxHeight) {

    calcQhw(u, mxHeight);

    ll ans = 0;

    int hSum = 1;

    gp_inv = Pow(y-1, MOD-2);
    gp_inv = (MOD - gp_inv) % MOD;
    soFar = y;

    PowYSetup(y);

    int cnt = 0;

    for (auto qhwPii : qhw[u]) {
        int qHeight = qhwPii.first;
        int qWidth = qhwPii.second;
        int start_dis = hSum;

	hSum += qHeight;

        ll v2 = PowY(qWidth * qHeight); // Old prn

        ll t1 = (y == 1)?qWidth:gp_inv;

        ll t3;
        if (y == 1) {
            t3 = (2*start_dis + (qHeight - 1));
            t3 = (t3 * qHeight) % MOD;
            t3 = (t3 * INV_MOD_2) % MOD;
        } else {
	    ll v1 = PowY(qWidth);
            ll a2 = (start_dis - ((start_dis + qHeight) * v2) % MOD) % MOD;
	    if (a2 < 0) {
               a2 = (a2 + MOD) % MOD;
            }
            t3 = (a2 + v1 * gpSum(v1, qHeight) % MOD) % MOD;
        }

        ans = ans + (t1 * t3 % MOD) * soFar % MOD;
        ans = ans % MOD;

        soFar *= v2;
        soFar %= MOD;
    }
    return ans;
}


inline void solve() {
    int n,q;
    read(n);
    read(q);

    tree.clear();
    qhw.clear();
    layer_tree.clear();
    for (int i=0; i<=n; i++) {
        tree.push_back(vector<int>());
        layer_tree.push_back(vector<int>());
	qhw.push_back(vector<pii>());
    }

    for (int i=1; i<n; i++) {
        int u,v;
	read(u);
	read(v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs_cnt = 0;
    dfs(1,0);

    int mx_height = 0;
    for (int i=1; i<=n; i++) {
        mx_height = max(mx_height, height[i]);
    }

    next_height[mx_height] = mx_height + 1;
    int cnt = 0;
    for (int i=mx_height-1; i > 0; i--) {
        if (layer_tree[i].size() == layer_tree[i+1].size()) {
            next_height[i] = next_height[i+1];
        } else {
            next_height[i] = i+1;
            cnt++;
        }
    }


    int ans = 0;
    while (q--) {
        int a,b;
	read(a);
	read(b);

        a = a ^ ans;
        b = b ^ ans;

        ans = findW(a, b, mx_height);


        printf("%d\n",ans);
    }

}

int main () {
   int t;
   fio;
   read(t);
    while (t--) {
        solve();
    }
}

