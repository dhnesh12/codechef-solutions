#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef long long ll;

map <int, int> opa;
set <pair <int, int> > popa;
int answer[100005];

bool check(int n, int mn)
{
 	if (n == 0) return true;
 	if ((*opa.rbegin()).x <= mn) return false;
 	if ((*popa.rbegin()).x * 2 == n + 1 && (*popa.rbegin()).y == (*opa.rbegin()).x) return true;
 	if ((*popa.rbegin()).x * 2 == n && ((*popa.rbegin()).y == (*opa.begin()).x || (*popa.rbegin()).y > mn)) return true;
 	if (2 * (*popa.rbegin()).x < n) return true;
 	return false;
}

int main()
{
 	//freopen("input.txt", "r", stdin);
 	//freopen("output.txt", "w", stdout);
 	ios_base::sync_with_stdio(0); cin.tie(0);
 	int test;
 	cin >> test;
 	for (int rep = 1; rep <= test; rep++)
 	{
 	 	opa.clear(), popa.clear();
 	 	int n;
 	 	cin >> n;
 	 	for (int i = 1; i <= n; i++)
 	 	{
 	 	 	int x;
 	 	 	cin >> x;
 	 	 	opa[x]++;
 	 	}
 	 	for (auto it = opa.begin(); it != opa.end(); it++) popa.insert(mp(it->y, it->x));

 	 	if (!check(n, 0)) {cout << "NO\n"; continue;}

 	 	int last = 0;
 	 	for (int i = 1; i <= n; i += 2)
 	 	{
 	 	 	if (i == n)
 	 	 	{
 	 	 	 	answer[i] = (*opa.begin()).x;
 	 	 	}
 	 	 	else
 	 	 	{
 	 	 	 	int mn = (*opa.begin()).x;
 	 	 	 	auto its = opa.upper_bound(max(mn, last));
 	 	 	 	int nx = its->x;

 	 	 	 	popa.erase(mp(opa[mn], mn)), popa.erase(mp(opa[nx], nx));
 	 	 	 	opa[mn]--, opa[nx]--;
 	 	 	 	if (opa[mn] == 0) opa.erase(mn);
 	 	 	 	else popa.insert(mp(opa[mn], mn));
 	 	 	 	if (opa[nx] == 0) opa.erase(nx); 
 	 	 	 	else popa.insert(mp(opa[nx], nx));
 	 	 	 	
 	 	 	 	bool f = check(n - i - 1, mn);
 	 	 	 	if (f) {answer[i] = nx, answer[i + 1] = mn; last = mn; continue;}

                popa.erase(mp(opa[mn], mn)), popa.erase(mp(opa[nx], nx));
 	 	 	 	opa[mn]++, opa[nx]++;
 	 	 	 	popa.insert(mp(opa[mn], mn));
 	 	 	 	popa.insert(mp(opa[nx], nx));

 	 	 	 	int rp = (*popa.rbegin()).y;
 	 	 	 	if (rp > last) nx = rp;
 	 	 	 	else mn = rp;

 	 	 	 	popa.erase(mp(opa[mn], mn)), popa.erase(mp(opa[nx], nx));
 	 	 	 	opa[mn]--, opa[nx]--;
 	 	 	 	if (opa[mn] == 0) opa.erase(mn);
 	 	 	 	else popa.insert(mp(opa[mn], mn));
 	 	 	 	if (opa[nx] == 0) opa.erase(nx); 
 	 	 	 	else popa.insert(mp(opa[nx], nx));

 	 	 	   answer[i] = nx, answer[i + 1] = mn;
 	 	 	   last = mn;
 	 	 	}
 	 	}
        
 	    cout << "YES\n";
 	 	for (int i = 1; i <= n; i++)
 	 		cout << answer[i] << ' '; 
 	 	cout << '\n';
 	}
 	return 0;
}