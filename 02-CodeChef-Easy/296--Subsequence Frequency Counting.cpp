#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define x first
#define y second    
#define mp make_pair
#define sz(a) ((int)(a.size()))
using namespace std;
const int mod = 1000 * 1000 * 1000 + 7;
const int INF = 1000 * 1000 * 1000;
const int MAX = 500005;
int cnt[MAX];
int cnt2[MAX];
int answer[MAX];
int fact[MAX];
int inv[MAX];
int prefC[MAX];
vector<int> byCnt[MAX];
int add(int a, int b)
{
    return a + b >= mod ? a + b - mod : a + b;
}
int sub(int a, int b)
{
    return a - b < 0 ? a - b + mod : a - b;
}
int mult(int a, int b)
{
    return a * (ll)b % mod;
}
int c(int n , int k)
{
    return mult(fact[n] , mult(inv[n - k] , inv[k]));
}
int modPow(int a, int step)
{
    int ans = 1;
    while(step)
    {
        if(step & 1)
            ans = mult(ans , a);
        a = mult(a , a);
        step >>= 1;
    }
    return ans;
}
int main() {
    
    ios_base::sync_with_stdio(0);
    fact[0] = inv[0] = 1;
    for(int i = 1; i < MAX; i++)
    {
        fact[i] = mult(fact[i - 1] , i);
        inv[i] = modPow(fact[i] , mod - 2);
    }
    
    int T;
    cin >> T;
    assert(1 <= T && T <= 100);
    int total = 0;
    for(int i = 1; i <= T; i++)
    {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            prefC[i] = 1;
        assert(1 <= n && n <= 500000);
        total += n;
        assert(total <= 500000);
        vector<int> a(n);
        for(auto &x : a)
        {
            cin >> x;
            assert(1 <= x && x <= n);
            cnt[x]++;
            byCnt[cnt[x]].pb(x);
        }
        for(int i = 1; i <= n; i++)
        {
            sort(byCnt[i].begin() , byCnt[i].end());
            reverse(byCnt[i].begin() , byCnt[i].end());
        }
        ll all = 1;
        for(int i = 1; i <= n; i++)
            for(auto x : byCnt[i])
            {
                ll except = mult(all , modPow(prefC[x] , mod - 2) );
                cnt2[x]++;
                answer[x] = add(answer[x] , mult(except , c(cnt[x] , cnt2[x])));
                
                all = mult(all, modPow(prefC[x] , mod - 2));
                prefC[x] = add(prefC[x] , c(cnt[x] , cnt2[x]));
                all = mult(all, prefC[x]);
            
            }
        
        for(int i = 1; i <= n; i++)
            cout << answer[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; i++)
        {
            answer[i] = cnt[i] = cnt2[i] = 0;
            byCnt[i].clear();
        }
    }
}