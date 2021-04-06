#include <bits/stdc++.h>

using namespace std;
#define mod 1000000007
using ll = long long;
int arr[4001];
vector<int> graph[4001];
int vis[4001];
ll fact[100001];
ll inv_fact[100001];
ll inv[100001];
ll mypower(ll a, ll b)
{
    ll ans = 1;
    b = b%(mod-1);
    while(b)
    {
        if(b%2)
            ans = ans*a % mod;
        b=b/2;
        a = a*a % mod;
    }
    return ans;
}
ll mul(ll a, ll b)
{
    ll ans = a*b;
    if(ans >= mod)
        ans = ans%mod;
    return ans;
}
ll add(ll a, ll b)
{
    ll ans = a + b;
    if(ans >= mod)
        ans-=mod;
    return ans;
}
ll sub(ll a, ll b)
{
    ll ans = a-b;
    if(ans < 0)
        ans+=mod;
    return ans;
}
void pre()
{
    fact[0] = 1;
    int i;
    for(i=1;i<100001;i++)
        fact[i] = mul(fact[i-1], i);
    inv_fact[100000] = mypower(fact[100000], mod - 2);
    inv[100000] = mul(inv_fact[100000], fact[(100000-1)]);
    for(i=(100000-1);i>=1;i--)
    {
        inv_fact[i] = mul(inv_fact[i+1], i+1);
        inv[i] = mul(inv_fact[i], fact[i-1]);
    }
    inv_fact[0] = 1;
}


void addMap(map <pair <int, int>, int> &M, const pair <int, int> &key, int val)
{
    auto it = M.find(key);
    if (it == M.end()) M.insert(make_pair(key, val));
    else it->second = add(it->second, val);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    pre();
    int n, m ,q;
    cin >> n >> m >> q;
    int i, j;
    for(i=1;i<=n;i++)
        cin >> arr[i];
    for(i=1;i<=m;i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    set<int, greater<int>> s;
    map<pair<int,int>, int> mp[n+1];
    // The general approach is the same as in the unofficial editorial....the answer for point is 1/(1-x*arr[n]), arr[n] = L[n]
    // Now the general formula is of the type c/(1-a*x)^b, mp[i] stores {a,b} mapped to c for point 'i'
    s.insert(n);
    mp[n][{arr[n], 1}] = 1;

    int sum = 0;
    while(s.size())
    {
        auto it = s.begin();        // Set is used in order to traverse vertices in decreasing order from 'n'
        int ver = *it;
        s.erase(it);
        for(auto j : graph[ver])
        {
            if(!vis[j] && j < ver)
            {
                s.insert(j);
                vis[j] = 1;
            }
            if(j < ver)
            {
                // The formulas derived here is from using this concept:we need to do partial fraction of s*F(ver)/(1-s*arr[j])
                // which is equal to F(ver)/(arr[j]*(1-s*arr[j]) - F(ver)/arr[j], so keeping F(ver) as a summation of partial fractions
                // I am finding the new partial fractions of F[j] in the decomposed form. F[n] = 1/(1-s*arr[n])
                for(auto k : mp[ver])
                {
                    int r = k.first.first;
                    int pw = k.first.second;
                    ll val = k.second;
                    ll x1 = mul(val, inv[arr[j]]);
                    ll x2 = sub(0, x1);
                    addMap(mp[j], {r, pw}, x2);
                   // mp[j][r][pw] = add(mp[j][r][pw], x2);
                    if(r == arr[j])
                    {
                        addMap(mp[j], {r, pw + 1}, x1);
                       // mp[j][r][pw+1] = add(mp[j][r][pw+1], x1);
                    }
                    else
                    {
                        x2 = mul(arr[j], inv[r]);
                        ll x4 = x2;
                        x2 = sub(1, x2);
                        ll x3 = mul(r, inv[arr[j]]);
                        x3 = sub(1, x3);
                        x2 = mypower(x2, mod-2);
                        x3 = mypower(mypower(x3, pw), mod-2);
                        ll c1 = 1, c2 = x2;
                        int f = 1;
                        for(int u = 0 ; u < pw ; u++)   // decomposition of 1/((1-a*x)*(1-b*x)^pw)
                        {
                            ll c3 = mul(mul(x1, c2), c1);
                            c1 = mul(c1, x4);
                            c2 = mul(c2, x2);
                            if(f == -1)
                                c3 = sub(0, c3);
                            f = -f;
                            addMap(mp[j], {r, pw - u}, c3);
                        }
                        addMap(mp[j], {arr[j], 1}, mul(x1, x3));
                    }

                }

            }

        }
    }
    //assert(false);
    vector<pair<int, pair<int,int>>> vp;
    for(auto j : mp[1])
        vp.push_back({j.first.first, {j.first.second, j.second}});

    // for(auto j : vp)
    //     cout << j.first << " " << j.second.first << " " << j.second.second << '\n';

   // ll b[q+1], maxa = 0;
    int k;
    for(i=1;i<=q;i++)
    {
        ll d;
        cin >> d;
        ll sum = 0;
        for(auto j : vp)
        {
            ll b = d%mod;
            ll ans = 1;
            for(k=1;k<=(j.second.first-1);k++)
                ans = mul(ans, b+k);
            ans = mul(ans, inv_fact[j.second.first-1]);
            ans = mul(ans, mypower(j.first, d));
            ans = mul(ans, j.second.second);
            sum = add(sum, ans);
        }
        cout << sum << '\n';
    }
    //cout << maxa << '\n';

}
