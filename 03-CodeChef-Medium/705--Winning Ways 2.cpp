//我不会啊，这个题咋做啊。是不是要开一个数组啊。。。 
#include<bits/stdc++.h>
using namespace std;
#define int long long
//怎么做来着？忘记了
const int mod = 998244353; 
const int maxn = 100005;
int jc[maxn],ni[maxn],a[maxn];
int ksm(int a,int b){
	int ans = 1;
	while(b){
		if(b&1) ans *= a,ans %= mod;
		a *= a,a %= mod,b>>=1;
	}
	return ans;
}
bool huo[maxn];
struct stu{
	int l,r,id,da;
}sexy[maxn];
bool cmpp(stu a,stu b){
	return a.id < b.id; 
}
const int yz = 400,yuzhi = 400;//
int shu[maxn][322];
int b[maxn];
int ak[maxn],cntt;
int cnt[maxn];
int chu[401];
int xian[maxn];
void init()
{
	int qwq = 100000;
	jc[0] = 1;
	for(int i=1;i<=qwq;++i) jc[i] = jc[i-1] * i,jc[i] %= mod;
	ni[qwq] = ksm(jc[qwq],mod-2);
	for(int i=qwq-1;i>=0;--i) ni[i] = ni[i+1] * (i+1),ni[i] %= mod;
//	printf("%lld %lld\n",jc[5],ni[2]);
}
int C(int a,int b){
	if(a < b) return 0;
	if(b < 0 || a < 0) return 0;
	return jc[a] * ni[b] % mod * ni[a-b] % mod;
}
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
bool cmp(stu a,stu b){
	if(a.l/400 == b.l/400) return a.r < b.r;
	return a.l < b.l;
}
void jia(int x){
	x = a[x];
	if(huo[x]) return;
	
	chu[xian[x]] --;
	xian[x] ++;
	chu[xian[x]] ++;
}
void shan(int x){
	x = a[x];
	if(huo[x]) return;
	chu[xian[x]] --;
	xian[x] --;
	chu[xian[x]] ++;
}
signed main()
{
	init();
	int t = read(); 
	while(t!=0){
		--t;
		int n = read();
		int xtt,q;
	//	q = read();xtt = read();
		for(int i=1;i<=n;++i) a[i] = read(),b[i] = a[i];
		q = read();
		for(int i=1;i<=q;++i) sexy[i].l = read(),sexy[i].r = read(),sexy[i].id = i;
		sort(sexy + 1,sexy + q + 1,cmp);
		sort(b+1,b+n+1);
		int m = unique(b+1,b+n+1) - b - 1;
		for(int i=1;i<=n;++i) a[i] = lower_bound(b+1,b+m+1,a[i])-b,cnt[a[i]] ++;
		for(int i=1;i<=n;++i) if(cnt[i] >= yuzhi) huo[i] = 1,ak[++cntt] = i;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=cntt;++j) shu[i][j] = shu[i-1][j];
			if(huo[a[i]] == 1){
				for(int j=1;j<=cntt;++j) if(ak[j] == a[i]) {
				shu[i][j] ++; break;}
			}
		}
	//	printf("%lld\n",cntt);
	//	for(int i=1;i<=cntt;++i) printf("%lld ",ak[i]);
	//	printf("\n\n");
		int l = 1,r = 0;//
		for(int i=1;i<=q;++i){
			int xx = sexy[i].l;
			int yy = sexy[i].r;
			while(r < yy){++r;jia(r);}
			while(l > xx){--l;jia(l);}
			while(r > yy){shan(r);--r;}
			while(l < xx){shan(l);++l;}
			int ans = 0,yihuo = 0;
			for(int j=1;j<=399;++j)
				if(chu[j]%2==1) yihuo ^= j;
			for(int j=1;j<=cntt;++j){
				//if((shu[yy][j] - shu[xx-1][j])%2==1) yihuo ^= ak[j];
				yihuo ^= shu[yy][j] - shu[xx-1][j];
			}
		//	printf("%lld\n",C(6,3));
			for(int j=1;j<=399;++j){
			//	if(j<=3) printf("%lld ",chu[j]);
		//		if(chu[j]) printf("1");
				if((j^yihuo) < j)
				ans += C(j,j-(j^yihuo)) * chu[j] % mod;
				ans %= mod;
			}
		//	printf("\n");
			for(int j=1;j<=cntt;++j){
				int tc = shu[yy][j] - shu[xx-1][j];
				if(tc > (tc^yihuo))
				ans += C(tc,tc-(tc^yihuo)) % mod;
				ans %= mod;
			}
			if(yihuo != 0)
			sexy[i].da = ans;
			else sexy[i].da = 0;
		}
		sort(sexy + 1,sexy + q + 1,cmpp);
		for(int i=1;i<=q;++i) printf("%lld\n",sexy[i].da);
		//chongyixia();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=cntt;++j) shu[i][j] = 0;
			huo[i] = 0,cnt[i] = 0,xian[i] = 0,ak[i] = 0;
		}
		for(int i=1;i<=399;++i) chu[i] = 0;
		cntt = 0;
	}
}