#include<bits/stdc++.h>
using namespace std;
bool mark[100005];
vector<int> query(int type, int node){cout << type << " " << node+1 << endl;int size; cin >> size;
    mark[node] = true;vector<int> res(size);for(auto &x : res){cin>>x; x--;}return res;}
int main(){ios::sync_with_stdio(false); cin.tie(0);int n , k, start = -1; cin >> n >> k; vector<int> deg(n);
    for (int i = 0; i < n; i++){cin >> deg[i];if(deg[i] >= k){start = i;}}
    if (start != -1){vector<int> good = query(2, start);
        for(auto x : good){vector<int> bad = query(1, x);for(auto y : bad) mark[y] = true;}}
    for (int i=0; i<n;i++){if(mark[i])continue;vector<int> bad=query(1,i);for(auto x : bad) mark[x] = true;}
    cout << 3 << endl;return 0;}