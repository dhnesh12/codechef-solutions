#include<bits/stdc++.h>

using namespace std;

#define FOR(i, x, y) for(int i = (x); i < (y); ++i)
#define REP(i, x, y) for(int i = (x); i <= (y); ++i)
#define PB push_back
#define MP make_pair
#define PH push
#define fst first
#define snd second
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 35;

int n, m, tot;
int a[1005], del[305], l[305];
unsigned int g[305], suf[305];
vector<int> all;

inline int len(int x){
	int ret = 0;
	for(int i = 0; i < n; ++i, x /= 3) if(x % 3)
		++ret;
	return ret;
}

inline bool belong(int x, int y){
	int ret = true;
	for(int i = 0; i < n; ++i, x /= 3, y /= 3)
		ret &= (!(x % 3) || (x % 3 == y % 3));
	return ret;
}

inline bool check(int x){
	int cnt = 0;
	FOR(i, 0, m){
		int res = belong(x, a[i]);
		if(res){
			++cnt;
			g[x] |= 1 << i;
		}
	}
	l[x] = len(x);
	return cnt == (1 << n - l[x]);
}

inline void print(int x){
	for(int i = 4; i >= 0; --i){
		if(!(x % 3))
			putchar('_');
		else if(x % 3 == 2)
			putchar('a' + i);
		else
			putchar('A' + i);
		x /= 3;
	}
	return;
}

inline void dfs(unsigned int msk, int dep, int cnt){
	if(msk == (1 << m) - 1){
		tot = min(tot, cnt);
		return;
	}
	if((msk | suf[dep]) != (1 << m) - 1)
		return; 
	if(dep == all.size())
		return;
	if(cnt >= tot)
		return;
	if((msk | g[all[dep]]) != msk){
		dfs(msk | g[all[dep]], dep + 1, cnt + l[all[dep]]);
	}
	dfs(msk, dep + 1, cnt);
	return;
}

inline void solve(){
	scanf("%d%d", &n, &m);
	FOR(i, 0, m){
		int x = 0;
		char buf[maxn];
		scanf("%s", buf);
		FOR(j, 0, n)
			(x *= 3) += (buf[j] >= 'a') + 1;
		a[i] = x;
	}
	sort(a, a + m);
	m = unique(a, a + m) - a;
	int mx = 1;
	FOR(i, 0, n)
		mx *= 3;
	vector<int> ans; ans.clear();
	FOR(msk, 0, mx){
		g[msk] = 0;
		if(check(msk)){
			ans.PB(msk);
		}
	}
	memset(del, 0, sizeof(del));
	FOR(j, 0, ans.size()) FOR(i, 0, ans.size()) if(i != j && !del[j] && belong(ans[i], ans[j])){
		del[j] = true;
		break;
	}
	all.clear();
	FOR(i, 0, ans.size()) if(!del[i])
		all.PB(ans[i]);
	suf[all.size()] = 0;
	for(int i = all.size() - 1; i >= 0; --i)
		suf[i] = suf[i + 1] | g[all[i]];
	tot = 0x3f3f3f3f;
	dfs(0, 0, 0);
	printf("%d\n", tot);
	return;
}

int main(){
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout); 
	int T;
	for(scanf("%d", &T); T--; solve());
	return 0;
}
