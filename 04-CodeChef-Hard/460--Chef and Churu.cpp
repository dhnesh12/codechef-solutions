#include <bits/stdc++.h>

namespace wxy{

#define int unsigned long long
#define x first
#define y second
const int N = 1e5 + 10;
typedef std::pair<int,int> PII;
int a[N],c[N],sum[N],b[N],times[400][N],n,q,S,cnt;
PII func[N];

inline int getL(int idx){return (idx - 1) * S + 1;}
inline int getR(int idx){return std::min(n,idx * S);}

inline int lowbit(int x){return x & -x;}
inline int ask(int x){
	int res = 0;
	for(;x;x-=lowbit(x)) res += c[x];
	return res;
}
inline void add(int x,int val){for(;x<=n;x+=lowbit(x))c[x] += val;}
inline int query(int l,int r){return ask(r)-ask(l-1);}
inline int change(int x,int y){
	int delta = y - a[x]; a[x] = y;
	add(x,delta);
	for(int i = 1; i <= cnt; i++)
		sum[i] = sum[i] + 1ll * times[i][x] * delta;
}
inline int getans(int l,int r){
	int res = 0;
	if(b[l] == b[r]){
		for (int i = l; i <= r; i++) res += query(func[i].x,func[i].y);
		return res;
	}
	for(int i = l; i <= getR(b[l]); i++) res += query(func[i].x,func[i].y);
	for(int i = getL(b[r]); i <= r; i++) res += query(func[i].x,func[i].y);
	for(int i = b[l] + 1; i < b[r]; i++) res += sum[i];
	return res;
}
inline void main(){
	std::cin >> n; S = (int)sqrt(n); 
	for(int i = 1; i <= n; i++) std::cin >> a[i];
	for(int i = 1; i <= n; i++) add(i,a[i]);
	for(int i = 1; i <= n; i++) std::cin >> func[i].x >> func[i].y;
	for(int i = 1; i <= n; i++){
		b[i] = (i - 1) / S + 1;
		sum[b[i]] += query(func[i].x,func[i].y);
		times[b[i]][func[i].x] += 1; times[b[i]][func[i].y+1] -= 1;
	} cnt = b[n];
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= n; j++)
			times[i][j] += times[i][j - 1];
	std::cin >> q;
	while(q--){
		int op,l,r; std::cin >> op >> l >> r;
		if(op == 1) change(l,r);
		else std::cout<< getans(l,r) << std::endl;
	}
}

}signed main(){wxy::main(); return 0;}