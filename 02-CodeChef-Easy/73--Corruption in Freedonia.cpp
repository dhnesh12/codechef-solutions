#include <bits/stdc++.h>
using namespace std;
#define int long long
int n; vector<int>v[1000005];
pair<int,int> dfs(int pos){int ans = 0, deg = v[pos].size(); if (deg == 0){return {1,0};}
    if (deg == 1){return dfs(v[pos][0]);} int f = 0;
    for (auto i:v[pos]){pair<int,int> p = dfs(i); f |= p.second; ans += p.first;}if (f){return {ans,1};}
    else{return {ans-1,1};}}
int32_t main(){ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cin >> n;
    for (int i = 0; i < n-1; i++){int a, b;cin >> a >> b;v[a].push_back(b);}cout << dfs(1).first;}