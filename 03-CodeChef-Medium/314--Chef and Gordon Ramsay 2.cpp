#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

#define FOR(x,to) for(int x=0;x<(to);x++)
#define FORR(x,arr) for(auto& x:arr)
#define ITR(x,c) for(__typeof(c.begin()) x=c.begin();x!=c.end();x++)
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
#define all(x) x.begin(), x.end()
#define mp make_pair
#define pb push_back
#define fst first
#define sec second
#define SZ(x) ((int) (x).size())
#define SQR(x) ((x) * (x))
#define endl "\n"

typedef long long LL;
typedef long double LD;
typedef pair<int, int> II;
typedef vector<int> VI;
typedef vector<II> VII;
typedef vector<string> VS;
typedef vector<VI> VVI;

template<class T> T abs(T x) { return x > 0 ? x : -x; }

const int N = 200000;
VI E[N];
vector<LL> L[N], F[N];
bool A[N], V[N];

LL dfs(int u) {
	LL res = 0;
	V[u] = true;
	L[u].pb(A[u]);
	F[u].pb(0);
	FORR(v, E[u])
		if (!V[v]) {
			res += dfs(v);
			L[v].pb(0);
			F[v].pop_back();
			if (SZ(L[v]) > SZ(L[u])) {
				swap(L[v], L[u]);
				swap(F[v], F[u]);
			}
			if (SZ(F[u]) < SZ(L[v])) {
				vector<LL> t(SZ(L[v]) - SZ(F[u]), 0);
				F[u].insert(F[u].begin(), t.begin(), t.end());
			}
			FOR(i, SZ(L[v]))
				res += L[v][SZ(L[v]) - i - 1] * F[u][SZ(F[u]) - i - 1];
			FOR(i, SZ(F[v]))
				res += F[v][SZ(F[v]) - i - 1] * L[u][SZ(L[u]) - i - 1];
			FOR(i, SZ(L[v]))
				F[u][SZ(F[u]) - i - 1] += L[v][SZ(L[v]) - i - 1] * L[u][SZ(L[u]) - i - 1];
			FOR(i, SZ(F[v]))
				F[u][SZ(F[u]) - i - 1] += F[v][SZ(F[v]) - i - 1];
			FOR(i, SZ(L[v]))
				L[u][SZ(L[u]) - i - 1] += L[v][SZ(L[v]) - i - 1];
		}
	return res;
}

int main() {
	#ifndef ONLINE_JUDGE
    	freopen("x.in", "r", stdin);
    	freopen("x.out", "w", stdout);
	#endif
	int T, n, u, v;
	cin>>T;
	FOR(i, T) {
		cin>>n;
		FOR(j, n - 1) {
			cin>>u>>v;
			u--,v--;
			E[u].pb(v);
			E[v].pb(u);
		}
		FOR(j, n)
			cin>>A[j];
		cout<<dfs(0) * 6<<endl;
		FOR(j, n) {
			E[j].clear();
			L[j].clear();
			F[j].clear();
			V[j] = false;
		}
	}
	return 0;
}