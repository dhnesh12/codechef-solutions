#include<bits/stdc++.h>
#define N 100050
using namespace std;
int read(){
	int cnt = 0, f = 1; char ch = 0;
	while(!isdigit(ch)){ ch = getchar(); if(ch == '-') f = -1;}
	while(isdigit(ch)) cnt = cnt * 10 + (ch-'0'), ch = getchar();
	return cnt * f;
}
typedef long long ll;
const int Mod = 1e9 + 7;
int add(int a, int b){ return a + b >= Mod ? a + b - Mod : a + b;}
int mul(int a, int b){ return 1ll * a * b % Mod;}
int power(int a, int b){
	if(b < 0) return 0;
	int ans = 1; for(;b;b>>=1){ if(b&1) ans = mul(ans, a); a = mul(a, a);}
	return ans;
}
const int inv2 = (Mod + 1) / 2, inv3 = (Mod + 1) / 3, inv6 = mul(inv2, inv3);
int c2(int n){ return mul(mul(n, n-1), inv2);}
int c3(int n){ return mul(mul(n, n-1), mul(n-2, inv6));}
int s[4][4] = {{1}, {0, 1}, {0, 1, 1}, {0, 1, 3, 1}};
int *S;
int n, m, k, ans, d[N];
vector<int> E[N], G[N];
int calc2(){
	int t1 = 0, t2 = c2(m);
	for(int i = 1; i <= n; i++) t1 = add(t1, c2(d[i]));
	t2 = add(t2, Mod - t1);
	return mul(S[2] + S[2], add(mul(t1, power(2, n - 3)), mul(t2, power(2, n - 4))));
}
bool cmp(int u, int v){ return d[u] > d[v] || (d[u] == d[v] && u > v);}
int vis[N], idx;
int ring(){
	int cnt = 0;
	for(int u = 1; u <= n; u++){
		for(int i = 0; i < E[u].size(); i++){
			int v = E[u][i]; if(cmp(u, v)) G[u].push_back(v);
		}
	}
	for(int u = 1; u <= n; u++){
		++idx;
		for(int i = 0; i < G[u].size(); i++) vis[G[u][i]] = idx;
		for(int i = 0; i < G[u].size(); i++){
			int v = G[u][i];
			for(int j = 0; j < G[v].size(); j++) if(vis[G[v][i]] == idx) ++cnt;
		}
	} return cnt;
}
int calc3(){
	int t1 = ring(), t2 = 0, t3 = 0, t4 = c3(m);
	for(int u = 1; u <= n; u++)
		for(int v = 0; v < G[u].size(); v++) add(t2, mul(d[u]-1, d[G[u][v]]-1));
	add(t2, Mod - mul(t1, 3));
	add(t3, Mod - add(t2, t2));
	for(int u = 1; u <= n; u++){
		t2 = add(t2, c3(d[u]));
		t3 = add(t3, mul(m - d[u], c2(d[u])));
	} 
	add(t3, Mod - mul(t1, 3));
	add(t4, Mod - add(add(t1, t2), t3));
	int t = mul(S[3], 6);
	return mul(t, add(add(mul(t1, power(2, n-3)), mul(t2, power(2, n-4))), add(mul(t3, power(2, n-5)), mul(t4, power(2, n-6)))));
}
void FSY(){
	for(int i = 1; i <= n; i++) G[i].clear(), E[i].clear(), d[i] = 0;
}
void Yolanda(){
	n = read(), m = read(), k = read(); S = s[k];
	for(int i = 1; i <= m; i++){
		int u = read(), v = read();
		E[u].push_back(v); E[v].push_back(u);
		++d[u]; ++d[v]; 
	}
	ans = mul(mul(m, S[1]), power(2, n - 2));
	if(k > 1 && m > 1) ans = add(ans, calc2());
	if(k > 2 && m > 2) ans = add(ans, calc3());
	cout << ans << '\n'; 
}
int main(){
//	freopen("1.in","r",stdin);
	int T = read();
	while(T--) Yolanda(), FSY(); return 0;
}