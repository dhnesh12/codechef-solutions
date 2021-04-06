#include<bits/stdc++.h>
#include<iostream>
#include<climits>
#include<string>
#include<cmath>
#include<stack>
#include<algorithm>
#include<cstdio>
#include<random>
#define rep(i,j,n) for(i=j;i<n;i++)
#define ll long long
#define ull unsigned long long
#define mod 1000000007
#define ff first
#define ss second
#define pb push_back
#define INF INT_MAX
#define Very_Fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define endl '\n'
using namespace std;

ll dist[100001];
vector<pair<ll, ll>>adj[100001];

void bfs(ll node)
{
    for (ll i = 0; i <= 100001; i++)
        dist[i] = INF;

    deque<int>q;
    q.push_back(node);
    dist[node] = 0;

    while (!q.empty())
    {
        int node = q.front();
        q.pop_front();

        for (auto child : adj[node])
        {
            if (child.second == 0)
            {
                if (dist[child.first] > dist[node])
                {
                    dist[child.first] = dist[node];
                    q.push_front(child.first);
                }
            }
            else
            {
                if (dist[child.first] > dist[node] + 1)
                {
                    dist[child.first] = dist[node] + 1;
                    q.push_back(child.first);
                }
            }
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Very_Fast

    ll i, j;
    ll cnt = 0, cnt2 = 0;
    ll temp = 0;
    ll n, m;
    cin >> n >> m;
    for (i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back({y, 0}); // normal edge of weight 0
        adj[y].push_back({x, 1}); // reverse edge of weight 1
    }

    // bfs lagao
    bfs(1);

    if (dist[n] == INF )
        cout << -1 << endl;
    else
        cout << dist[n] << endl;

    return 0;
}


