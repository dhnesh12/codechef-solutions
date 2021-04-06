#include <bits/stdc++.h>
 
#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")
 
using namespace std;
#define ll long long
#define ull unsigned long long
#define rep(i,n,N) for(int i=n;i<=N;++i)
#define asd(i,n,N) for(int i=n;i< N;++i)
#define rap(i,n,N) for(int i=n;i>=N;--i)
#define mp make_pair
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define fi first
#define se second
#define ff fi.fi
#define fs fi.se
#define sf se.fi
#define ss se.se
#define lc (id<<1)
#define rc ((id<<1)|1)
#define db(x) cout << ">>>> " << #x << " -> " << x << endl
#define mems(x,y) memset(x,y,sizeof x)
#define all(x) x.begin(),x.end()
#define rng() ((rand()<<16)|rand())
#define pii pair<int,int> 
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define piii pair<int,pii>
#define piiii pair<pii,pii>
#define psi pair<string,int>
#define endl '\n'
const int MAX = 1e5+5;
const ll MAX2 = 11;
const ll MOD = 1000000007;
const ll MOD2 = 1000005329;
const ll INF = 2e18;
const int dr[]={1,0,-1,0,1,1,-1,-1,0};
const int dc[]={0,1,0,-1,1,-1,1,-1,0};
const double pi = acos(-1);
const double EPS = 1e-9;
const int block = 555;

int n,sa[18][MAX<<1],bt,cnt[MAX],mn[MAX],pos[MAX],z[MAX],tb[MAX],y[MAX],stp,jmp;
pii x[MAX];
int snw[MAX],snx[MAX];
string s;
priority_queue<piii, vector<piii>, greater<piii>> pq;

int ret,nx;
inline int getlcp(int x,int y){
	if(x>y)x^=y^=x^=y;
	ret = 0, nx = jmp>>1;
	rap(i,stp-1,0){
		if(y+nx<=n && sa[i][x]==sa[i][y]){
			ret+= nx;
			x+= nx, y+= nx;
		}
		nx>>= 1;
	}
	return ret;
}

int main(){
// cout<<fixed<<setprecision(3);
// freopen("trip.in", "r", stdin);
// freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>s;
    for(char c:s)sa[0][n++] = c;
    	
	stp = 0, jmp = 1, bt = 128;
	while(jmp<n){
		mems(cnt,0);
		asd(i,0,n)++cnt[sa[stp][i+jmp]];
		rep(i,1,bt)cnt[i]+= cnt[i-1];
		asd(i,0,n)snx[cnt[sa[stp][i+jmp]]--] = i;
		
		mems(cnt,0);
		asd(i,0,n)++cnt[sa[stp][i]];
		rep(i,1,bt)cnt[i]+= cnt[i-1];
		rap(i,n,1)snw[cnt[sa[stp][snx[i]]]--] = snx[i];
		
		++stp;
		sa[stp][snw[1]] = 1;
		rep(i,2,n)sa[stp][snw[i]] = sa[stp][snw[i-1]] + !(sa[stp-1][snw[i]] == sa[stp-1][snw[i-1]]
		&& sa[stp-1][snw[i]+jmp] == sa[stp-1][snw[i-1]+jmp]);
		jmp<<= 1, bt = sa[stp][snw[n]];
	}
	
	asd(i,0,n)z[sa[stp][i]] = i;
//	rep(i,1,n){
//		cout<<i<<" = ";
//		asd(j,z[i],n)cout<<s[j]; cout<<endl;
//	}
	rep(i,2,n)tb[i] = getlcp(z[i-1],z[i]);
	
	rep(i,1,n)mn[i] = n;
	int mx,le,ri;
	rep(i,1,n){
		mx = max(tb[i],tb[i+1]);
		if(z[i]+mx<n){
			le = z[i]+1, ri = z[i]+mx+1;
			x[le] = {mx+1,ri};
			y[ri] = max(y[ri],le-1);
		}
	}
	
	rep(i,1,n){
		while(!pq.empty() && pq.top().ss<i)pq.pop();
		if(x[i].fi){
			le = x[i].se - x[i].fi;
			pq.push({x[i].fi,{sa[stp][le],x[i].se}});
		}
		
		if(!pq.empty())mn[i] = pq.top().fi, pos[i] = pq.top().ss - pq.top().fi;
	}
	
	int sta = -1;
	rep(i,1,n){
		if(y[i])sta = max(sta,y[i]);
		if(sta!=-1){
			if(mn[i]>i-sta || (mn[i]==i-sta && sa[stp][pos[i]]>sa[stp][sta])){
				mn[i] = i-sta, pos[i] = sta;
			}
		}
		cout<<pos[i]+1<<" "<<mn[i]<<endl;
	}
    return 0;
}