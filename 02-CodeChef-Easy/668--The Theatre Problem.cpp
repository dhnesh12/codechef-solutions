#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long int
#define rep(i, a, b) for (int i = a; i < b; i++)
#define revrep(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define vii vector<pii>
#define min3(a, b, c) min(a, min(b, c))
#define max3(a, b, c) max(a, max(b, c))

int ceilInt(int a, int b) {
    if(!b) return 0;
    if(a%b) return a/b + 1;
    return a/b;
}

int INF = 1e18;
int MOD = 998244353;

int solve()
{
    int n; cin>>n;
    int mt[4][4] = {};
    rep(i, 0, n) {
        char c; int b;
        cin>>c>>b;
        b = b/3-1;
        mt[c-'A'][b]++;
    }
    set<int> st = {0, 1, 2, 3};
    int ans = -INF;
    rep(i, 0, 4) {
        st.erase(i);
        rep(j, 0, 4) {
            if(st.find(j) == st.end()) continue;
            st.erase(j);
            rep(k, 0, 4) {
                if(st.find(k) == st.end()) continue;
                st.erase(k);
                {
                    int l = *st.begin();
                    multiset<int> temp = {mt[0][i], mt[1][j], mt[2][k], mt[3][l]};
                    int cost = 25, sum = 0;
                    for(int cst: temp) {
                        sum += cost*cst;
                        cost += 25;
                        if(cst == 0) sum -= 100;
                    }
                    ans = max(ans, sum);
                }
                st.insert(k);
            }
            st.insert(j);
        }
        st.insert(i);
    }
    cout<<ans<<endl;
    return ans;
}

signed main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    int sum = 0;
    rep(i, 0, t)
    {   
        sum += solve();
    }
    cout<<sum<<endl;
    return 0;
}