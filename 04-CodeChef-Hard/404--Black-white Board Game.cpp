#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
cs int N = 1e5 + 50;
int T, n;
int rt[N], lc[N], rc[N];
int r[N], d[N], id[N], pt[N];
void upt(int x){
	if(!lc[x] && !rc[x]) d[x] = 0;
	else d[x] = d[rc[x]] + 1; 
}
int mrg(int x, int y){
	if(!x || !y) return x | y; 
	if(r[x] > r[y]) swap(x, y); 
	rc[x] = mrg(rc[x], y);
	if(d[rc[x]] > d[lc[x]]) 
	swap(lc[x], rc[x]); 
	return upt(x), x;
}
void Main(){
	scanf("%d", &n);
	for(int i = 1, l; i <= n; i++){
		scanf("%d%d", &l, &r[i]);
		rt[l] = mrg(rt[l], i), id[i] = pt[i] = i;
	} 
	int ans = 1; 
	for(int i = 1, x; i <= n; i++){
		x = rt[i]; if(!x) { ans = 0; break; }
		if(id[i] != x) {
			ans = -ans; int z = id[i];
			swap(id[i], id[pt[x]]);
			swap(pt[x], pt[z]);
		}
		rt[i] = mrg(lc[x], rc[x]);
		rt[r[x] + 1] = mrg(rt[r[x] + 1], rt[i]);
	} 
	if(!ans) puts("Draw");
	if(ans > 0) puts("Alex");
	if(ans < 0) puts("Fedor");
	for(int i = 0; i <= n + 1; i++)
	rt[i] = lc[i] = rc[i] = d[i] = 0;
}
int main(){
	#ifdef FSYo
	freopen("1.in", "r", stdin);
	#endif
	cin >> T;
	while(T--) Main();
	return 0; 
}