#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e5 + 4;

vector < int > adj[N];
int P[N] , C[N];
ll dp[N][2];

bool comp(pair < ll , ll > a , pair < ll , ll > b)
{
    return a.first - a.second < b.first - b.second;
}
void dfs(int u, int p = -1)
{
    vector < pair < ll , ll > > ret;
    for(auto x : adj[u]) if(x != p)
        dfs(x , u), ret.push_back({dp[x][0], dp[x][1]});

    sort(ret.begin() , ret.end() , comp);
    ll sum1 = 0 , sum2 = 0 , sum3 = 0;
    for(int i = 0 ; i < ret.size() ; i++)
    {
        if(i < C[u]) sum1 += ret[i].first;
        else sum1 += ret[i].second;

        if(i + 1 < C[u]) sum2 += ret[i].first;
        else sum2 += ret[i].second;

        sum3 += ret[i].second;
    }

    dp[u][0] = dp[u][1] = 1LL * P[u] + sum3;
    if(ret.size() >= C[u])  dp[u][0] = min(dp[u][0] , sum1);
    if(ret.size() >= C[u]-1)  dp[u][1] = min(dp[u][1] , sum2);
}

int main()
{
    ios::sync_with_stdio(false);    cin.tie(NULL);  cout.tie(NULL);
    int T;  cin >> T;
    while(T--)
    {
        int n;  cin >> n;
        for(int i = 1 ; i < n ; i++)
        {
            int u , v;  cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for(int i = 1 ; i <= n ; i++)   cin >> P[i];
        for(int i = 1 ; i <= n ; i++)   cin >> C[i];

        cout << (dfs(1) , dp[1][0]) << '\n';

        for(int i = 1 ; i <= n ; i++)   adj[i].clear();
    }
    return 0;
}
