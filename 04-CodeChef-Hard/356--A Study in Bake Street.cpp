#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ub              upper_bound
#define lb              lower_bound
#define isrt            insert
#define clr             clear
#define rsz             resize
#define ff              first
#define ss              second
#define int             long long int
#define pb              push_back
#define pf              push_front
#define mkp              make_pair
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define pqb             priority_queue<int>
#define pqs             priority_queue<int,vi,greater<int>>
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define INF             1e9
#define ps(x,y)         fixed<<setprecision(y)<<x
#define mk(arr,n,type)  type *arr=new type[n];
#define w(x)            int x; cin>>x; while(x--)
#define all(v)          v.begin(),v.end()
#define rall(v)         v.rbegin(),v.rend()
#define endl            "\n"
using cd = complex<double>;
const double PI = acos(-1);
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

int maxm(int a, int b)
{
    return (a >= b ? a : b);
}


int minm(int a, int b)
{
    return (a <= b ? a : b);
}

int power(int x, int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0)
        return 0;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

#define FMAX 1000010
vector<int> fact(FMAX, 1);
vector<int> fact_inv(FMAX, 1);
vector<int> spf(FMAX);

int nCrmodp(int n, int r, int p)
{
    if (r > n)
        return 0;
    int pro = (fact[n] * fact_inv[r]) % p;
    pro = (pro * fact_inv[n - r]) % p;
    return pro;
}
void precompute()
{
    int x = 1;
    for (int i = 1; i < FMAX; ++i)
    {
        x *= i;
        x %= mod;
        fact[i] = x;
        fact_inv[i] = power(x, mod - 2, mod);
    }
}

void spf_calc()
{
    for (int i = 1; i < FMAX; ++i)
        spf[i] = i;

    for (int i = 2; i * i < FMAX; ++i)
        if (spf[i] == i)
            for (int j = i * i; j < FMAX; j += i)
                if (spf[j] == j)
                    spf[j] = i;
}

int next_smaller(vector<int>v, int val)
{
    int l = 0, r = v.size() - 1, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (v[mid] <= val)
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ans;
}


void c_p_c()
{
    //precompute();
    //spf_calc();
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

#define MAXN 100010
vector<int>st[MAXN];
vector<pii>v(MAXN);

bool ccw(int x, int y, int z)
{
    pii a = v[x], b = v[y], c = v[z];
    return (a.ff * (b.ss - c.ss) + b.ff * (c.ss - a.ss) + c.ff * (a.ss - b.ss)) >= 0;
}

signed main()
{
    c_p_c();

    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            cin >> v[i].ff >> v[i].ss;
            st[i].clr();
        }
        int sz = -1;
        vector<int>ans(n, -1);
        st[++sz].pb(n - 1);

        for (int j = n - 2; j >= 0; --j)
        {
            if (v[j + 1].ss > v[j].ss)
                st[++sz].pb(j);
            else
            {
                int id = sz;
                while (id >= 0 && v[st[id][st[id].size() - 1]].ss < v[j].ss)
                    --id;
                ++id;
                for (int p = sz; p > id; --p)
                    st[p].clr();
                sz = id;

                while (st[id].size() >= 2 && ccw(j, st[id][st[id].size() - 1], st[id][st[id].size() - 2]))
                    st[id].pop_back();
                ans[j] = st[id][st[id].size() - 1] + 1;
                st[id].pb(j);
            }

        }

        for (auto it : ans)
            cout << it << " ";
        cout << endl;
    }
    return 0;
}