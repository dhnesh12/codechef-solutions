
#include <bits/stdc++.h>
using namespace std;void solve(){int n, k;cin >> n >> k;vector<vector<int> > a(2, vector<int>(n));set<int> used;
	for(int i = 0; i < 2; i++){for(int& x : a[i]) cin >> x;for(int x : a[i]) used.insert(x);}vector<vector<int> > go(2, vector<int>(n));int cur = 1;
	for(int i = 0; i < 2; i++)for(int j = 0; j < n; j++){while(used.count(cur)) cur++;go[i][j] = cur;cur++;}vector<vector<int> > st[2],en[2];vector<int> where[2];
	for(int i = 0; i < 2; i++){for(int j = 0; j + k-1 < n; j++){where[i].push_back(j);st[i].push_back(vector<int>(a[i].begin() + j, a[i].begin() + j + k));
			map<int,int> seen;for(int r = j; r < j+k; r++){if(!seen.count(a[i][r])) seen[a[i][r]] = go[i][r];a[i][r] = seen[a[i][r]];}
			en[i].push_back(vector<int>(a[i].begin() + j, a[i].begin() + j + k));}}
	for(int i = 0; i < n; i++)for(int j = 0; j < n; j++)if((a[0][i] == a[0][j]) != (a[1][i] == a[1][j])){cout << "NO" << '\n';return;}
	cout << "YES" << '\n';for(int j = 0; j + k-1 < n; j++){where[0].push_back(j);st[0].push_back(vector<int>(a[0].begin() + j, a[0].begin() + j + k));map<int,int> seen;
		for(int r = j; r < j+k; r++){if(!seen.count(a[0][r])) seen[a[0][r]] = a[1][r];a[0][r] = seen[a[0][r]];}
		en[0].push_back(vector<int>(a[0].begin() + j, a[0].begin() + j + k));}reverse(where[1].begin(), where[1].end());reverse(st[1].begin(), st[1].end());
	en[0].insert(en[0].end(), st[1].begin(), st[1].end());where[0].insert(where[0].end(), where[1].begin(), where[1].end());
	cout << where[0].size() << '\n';for(int i = 0; i < where[0].size(); i++){cout << where[0][i] + 1;for(int r : en[0][i])cout << ' ' << r;cout << '\n';}}
int main(){ios_base::sync_with_stdio(false), cin.tie(nullptr);int T;cin >> T;while(T--) solve();}