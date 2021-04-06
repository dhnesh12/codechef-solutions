#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll Mod = 1e9 + 7;
const int Maxn = 100;
const int Maxval = 1e6;

int N;
ll A[Maxn + 5];
map<ll, int> cnt_div;
vector<ll> pri;
bool ispri[Maxval + 5];

void Init() {
	for(int i = 2; i <= Maxval; i++) {
		if(!ispri[i]) pri.push_back(i);
		for(int j = 0; j < (int)pri.size() && i * pri[j] <= Maxval; j++) {
			ispri[i * pri[j]] = true;
			if(i % pri[j] == 0) break;
		}
	}
}
ll GCD(ll x, ll y) {
	if(y == 0) return x;
	return GCD(y, x % y);
}

void Divide(ll x) {
	for(int i = 0; i < (int)pri.size(); i++) {
		if(pri[i] * pri[i] * pri[i] > x) break;
		if(x % pri[i]) continue;
		int cnt = 0;
		while(x % pri[i] == 0)
			x /= pri[i], cnt++;
		cnt_div[pri[i]] += cnt;
	}
	if(x == 1) return;
	ll tmp = sqrt(x);
	if(tmp * tmp == x) {
		cnt_div[tmp] += 2;
		return;
	}
	bool flag = false;
	for(int i = 1; i <= N; i++) {
		tmp = GCD(x, A[i]);
		if(tmp != 1 && tmp != x) {
			cnt_div[tmp]++, cnt_div[x / tmp]++;
			flag = true;
			break;
		}
	}
	if(flag) return;
	cnt_div[x]++;
}

int main() {
#ifdef LOACL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	Init();
	int _;
	scanf("%d", &_);
	while(_--) {
		cnt_div.clear();
		scanf("%d", &N);
		for(int i = 1; i <= N; i++)
			scanf("%lld", &A[i]);
		ll ans = 1;
		for(int i = 1; i <= N; i++) {
			ans = ans * (A[i] % Mod) % Mod;
			Divide(A[i]);
		}
		for(map<ll, int>::iterator it = cnt_div.begin(); it != cnt_div.end(); it++) {
			int cnt = it->second;
			while(cnt % 3 != 0) cnt++, ans = ans * (it->first % Mod) % Mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}