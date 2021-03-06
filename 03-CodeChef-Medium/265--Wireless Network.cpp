///sutirtha_rej
#include <bits/stdc++.h>
using namespace std;

#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

 
#define WR printf
#define RE scanf
#define PB push_back
#define SE second
#define FI first
#define MP make_pair
 
#define FOR(i,Be,En) for(int (i)=(Be);(i)<=(En);++(i))
#define DFOR(i,Be,En) for(int (i)=(Be);(i)>=(En);--(i))
#define SZ(a) (int)((a).size())
#define FA(i,v) FOR(i,0,SZ(v)-1)
#define RFA(i,v) DFOR(i,SZ(v)-1,0)
#define CLR(a) memset(a,0,sizeof(a))
 
#define LL  long long
#define VI  vector<int>
#define PAR pair<int ,int> 
 
using namespace std;
void __never(int a){printf("\nOPS %d", a);}
void __die(int a){printf("%d",(a*a)/(a+a));}
#define ass(s) {if (!(s)) {__never(__LINE__);cout.flush();cerr.flush();__die(0);}}
 
 
 
const int INF = 1e9;
int n, q;
PAR rou[32];
 
 
PAR r[32][32];
int cc[32];
 
int graf[32][32];
int id[32][32];
 
int deg[32];
 
 
bool used[32];
int d[32];
int par[32];
int dist(PAR a, PAR b) {
	return (a.FI - b.FI)*(a.FI - b.FI) + (a.SE - b.SE)*(a.SE - b.SE);
}
void Calc(int v) {
	FOR(i,1,n) if (i != v) {
		int res = INF;
		int rid = -1;
		FOR(j,1,cc[v]) {
			int d = dist(r[v][j], rou[i]);
			if (d < res) {
				res = d;
				rid = j;
			}
		}
		graf[v][i] = res;
		id[v][i] = rid;
	}
}
void init()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
}
void sol(){	
	CLR(r);
	CLR(cc);
	cin >> n >> q;
	int x, y;
	PAR xy;
	FOR(i,1,n) {
		cin >> rou[i].FI >> rou[i].SE >> deg[i];
	}
	FOR(i,1,n) Calc(i);
	int curm = 0.;
	FOR(Q,1,q) {
		cin >> x >> y;
		xy = MP(x,y);
		FOR(i,1,n) graf[0][i] = dist(xy, rou[i]);
		//dei
		FOR(i,0,n) {
			used[i] = false;
			d[i] = INF;
		}
		d[0] = 0;
		
		while (true) {
			int ind = -1;
			FOR(i,0,n) if (!used[i] && (ind == -1 || d[ind] > d[i])) ind = i;
			if (ind == -1) break;
			used[ind] = true;
			FOR(i,0,n) if (!used[i]){
				int nd = max(d[ind], graf[ind][i]);
				if (d[i] > nd) {
					d[i] = nd;
					par[i] = ind;
				}
			}
		}
		// !dei
		int ind = -1;
		FOR(i,1,n) if (cc[i] < deg[i]) {
			if (ind == -1 || d[ind] > d[i]) ind = i;
		}
		ass(ind > 0);
		VI path;
		int cur = ind;
		int it = 0;
		while (cur) {
			path.PB(cur);
			cur = par[cur];
			ass(++it < 1000);
		}
		path.PB(0);
		ass(SZ(path) > 1);
		reverse(path.begin(), path.end());
		DFOR(i,SZ(path)-2,1) {
			int a = path[i];
			int b = path[i+1];
			r[b][++cc[b]] = r[a][id[a][b]];
			swap(r[a][id[a][b]], r[a][cc[a]]);
			cc[a]--;
		}
		r[path[1]][++cc[path[1]]] = xy;
		
		FA(i,path) if (i) Calc(path[i]);
		curm = max(curm, d[ind]);
		WR("%.3lf\n",sqrt(1.*curm));
	}
	WR("\n");
	
}
int main()
{
	//init();
	fast_io
	int T;
	cin >> T;
	FOR(t,1,T){
		sol();
	}
	return 0;
}  