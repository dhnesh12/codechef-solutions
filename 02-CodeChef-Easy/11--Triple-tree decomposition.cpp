#include <bits/stdc++.h>
using namespace std;
int n, t,np = 0;
vector <vector<int >> adj, an;
int dfs (int u,int p){int r = 0;
    for (auto v:adj[u]){if (v == p){continue;} if (dfs(v,u)){an[v].push_back(u);} else{an[u].push_back(v),r++;}}
    if (r%3 == 0){return 0;} if (r%3 == 1){np = 1;} return 1;}
int main(){ios::sync_with_stdio(0); cin.tie(0); cin >> t;
    while (t--){cin >> n; np = 0; adj.clear(); adj.resize(n+1); an.clear(); an.resize(n+1);
        for (int i = 0; i < n-1; i++){int a, b; cin >> a >> b; adj[a].push_back(b); adj[b].push_back(a);}
        if (dfs(1,-1)){cout << "NO" << endl;} else if (np){cout << "NO" << endl;}
        else{cout << "YES" << endl;
            for (int i = 1; i <= n; i++){
                if (an[i].empty()){continue;}int cnt = 0;
                for (auto v:an[i]){
                    if (cnt%3 == 0){if (cnt){cout << endl;}cout << i;}
                    cout << ' ' << v; cnt++;}cout << endl;}}}}