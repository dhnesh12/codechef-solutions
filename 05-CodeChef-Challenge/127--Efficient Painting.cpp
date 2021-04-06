//                        Bismillahir Rahmanir Rahim
//ALGO:
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define all(v) v.begin(), v.end()
#define FILL(a, x) memset(a, x, sizeof(a))
#define ll long long
#define Fast ios_base::sync_with_stdio(false);cin.tie(NULL);
#define INF INT_MAX
#define mx 1000010
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_multiset tree<pair<int, int>, null_type,less<pair<int, int> >, rb_tree_tag,tree_order_statistics_node_update>
*/
const double Pi=acos(-1);
using namespace std;
int debug=01;

int main() {
    int n;
    cin>>n;
    string g[n];
    for(int i=0; i<n; i++) cin>>g[i];
    vector<pair<int, int>>v;
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) if(g[i][j]=='B') v.pb({i, j});
    cout<<v.size()<<"\n";
    for(auto x:v)cout<<x.F<<" "<<x.S<<" "<<x.F<<" "<<x.S<<" B\n";
}
