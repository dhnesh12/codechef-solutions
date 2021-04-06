#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(a) setprecision(a)<<fixed
#define ss second
#define fori(v) for(int i=0; i<v; i++)
#define forj(v) for(int j=0; j<v; j++)
#define fork(v) for(int k=0; k<v; k++)
#define forl(v) for(int l=0; l<v; l++)
#define fort(v) for(int t=0; t<v; t++)
#define forz(v) for(int z=0; z<v; z++)
#define forx(v) for(int x=0; x<v; x++)
#define ll long long
 #define MAX (int)(3*pow(10,5) + pow(10,4) )
 #define ch1 (int)(550)
 #define ch2 (int)(MAX/ch1 + 10)
// #define MAX (int)(10)
// #define ch1 (int)(3)
// #define ch2 (int)(MAX/ch1 + 10)
#define pb(a) push_back(a)
// #define cout out
// #define cin in
int inf = pow(10,9);
ll modulo = 1000007;
double eps = 1e-6;
ifstream in;
ofstream out;

// ch1 is the bucket size
// ch2 is number of buckets

int tin[MAX];
int tout[MAX];
vector<int> g[MAX];
int dep[MAX];

void dfs(int hd, int& tim){
	tin[hd] = tim;
	for(auto hr : g[hd]){
		++tim;
		dep[hr] = dep[hd] + 1;
		dfs(hr, tim);
	}
	tout[hd] = tim;
}

vector<vector<int> > forLs[MAX]; // 0 - starting r, 1 - ending r, 2 - query id, id being its place in sorted one
int sumChunk[ch2];
int chunkNumTin[MAX];		// maps node number i to chunk of that nodes euler tour thingy
int individualSum[MAX];
int n;
ll sumQuery[MAX];	// sum of ith sorted one, this sum will be subtracted from actual query answer


// from idxl to idxr inclusive
void addL(int idxl , int idxr){
	int bl1 = idxl/ch1;
	int bl2 = idxr/ch1;
	if(bl1 == bl2){
		for(int i = idxl; i<=idxr; i++){
			individualSum[i]++;
		}		
	}
	else{
		for(int i = bl1+1; i<bl2; i++){
			sumChunk[i]++;
		}
		int ls = (bl1+1)*ch1;
		for(int i = idxl; i<ls; i++){
			individualSum[i]++;
		}
		int fr = bl2*ch1;
		for(int i = fr; i<= idxr; i++){
			individualSum[i]++;
		}
	}
}

void dealWithL(){
	for(int i  =0; i<n; i++){
		chunkNumTin[i] = tin[i]/ch1;
	}
	for(int i = 0; i<n; i++){
		addL(tin[i], tout[i]);
//		cout<<"we are here "<<endl;
		for(auto& el : forLs[i]){
//			cout<<"sorry L "<<endl;
			register int id = el[2], rstart = el[0], rend = el[1];
			if(rstart > rend){
				while(rstart > rend){
					register int cur  = sumChunk[chunkNumTin[rstart]] + individualSum[tin[rstart]];
//					cout<<"answer l - 1 : "<<i<<" r  "<<rstart<<" "<<cur<<endl;
					sumQuery[id] -= cur;
					--rstart;
				}
			}
			if(rstart < rend){
				while(rstart < rend){
					++rstart;
					register int cur = sumChunk[chunkNumTin[rstart]] + individualSum[tin[rstart]];
//					cout<<"answer l - 1 : "<<i<<" r  "<<rstart<<" "<<cur<<endl;
					sumQuery[id] += cur;
				}
			}
		}
	}
}

int tinMinusOne[MAX];
int chunkNumTinMinusOne[MAX];
int chunkNumTOut[MAX];
vector<vector<int> > forRs[MAX]; // 0 - starting l, 1 - ending l, 2 - query id, id being its place in sorted one


void addR(int idx){	// we are adding right endpoints
	int bl = idx/ch1;
	for(int i = bl+1; i < ch2; i++){
		sumChunk[i]++;
//		cout<<"sumChunk[ "<<i<<" ] "<<sumChunk[i]<<endl;
	}	
	int ls = (bl+1)*ch1;
	for(int i = idx; i<ls; i++){
		individualSum[i]++;
//		cout<<"individualSum[ "<<i<<" ] "<<individualSum[i]<<endl;
	}
}



void dealWithR(){
	for(int i = 0; i<ch2; i++){
		sumChunk[i] = 0;
	}
	for(int i = 0; i<MAX; i++){
		individualSum[i] = 0;
		tinMinusOne[i]  = tin[i] - 1;
		chunkNumTinMinusOne[i] = tinMinusOne[i]/ch1;
		chunkNumTOut[i] = tout[i] / ch1;
	}
	
	fori(n){
		addR(tin[i]);
		for(auto& el : forRs[i]){
			register int id = el[2], lstart = el[0], lend = el[1];
			while(lstart > lend){
				--lstart;
				register int cur = sumChunk[chunkNumTOut[lstart]] + individualSum[tout[lstart]] 
						- sumChunk[chunkNumTinMinusOne[lstart]] -  individualSum[tinMinusOne[lstart]] ;
//				cout<<"for how many people from 1 till "<<i+1<<" "<<lstart+1<<" is parent of theirs: "<<cur<<endl;
				sumQuery[id] -=cur ;
			}
			while(lstart < lend){
				register int cur = sumChunk[chunkNumTOut[lstart]] + individualSum[tout[lstart]] 
						- sumChunk[chunkNumTinMinusOne[lstart]] -  individualSum[tinMinusOne[lstart]];
//				cout<<"for how many people from 1 till "<<i+1<<" "<<lstart+1<<" is parent of theirs: "<<cur<<endl;
				sumQuery[id] += cur;
				++lstart;
			}
		}
	}	
}

ll queAns[MAX];

int fen[MAX];
ll uptoIfromL[MAX];


ll toSubtract[MAX];

void upd(int idx, int vl){
	while(idx < MAX){
		fen[idx]+=vl;
		idx+=idx&-idx;
	}
}

int que(int idx){
	int s = 0;
	while(idx){
		s+=fen[idx];
		idx-=idx&-idx;
	}
	return s;
}

void pre(){
	ll s= 0;
	for(int i = 0; i<n; i++){
		s+=que(tin[i]);
		uptoIfromL[i] = s;
		upd(tin[i], 1);
		upd(tout[i]+1, -1);
	}
	
	memset(fen, 0, sizeof(fen));
	
	s = 0;
	for(int i = 0; i<n; i++){
		upd(tin[i], 1);
		s+=que(tout[i]) - que(tin[i]-1);
		toSubtract[i] = s;
	}
	memset(fen, 0, sizeof(fen));
	
}


#define moChunk 550
// #define moChunk 3
bool mo(vector<int>& a, vector<int>& b){
	if(a[0] / moChunk != b[0] / moChunk){
		return a[0] / moChunk < b[0] / moChunk;
	}
	if( ( a[0] / moChunk ) & 1){
		return a[1] < b[1];
	}
	return a[1] > b[1];
}

pair<int,int> queriesInGivenOrder[MAX];



vector<pair<int,int> > additional;
int szIncluded[MAX];
bitset<MAX> childs[40];
bitset<MAX> pars[40];
vector<int> gf[MAX];
int giren[MAX];
bitset<32> includedSpecEdges[MAX];
bitset<32> canBeIncludedSpecEdges[MAX];


int m;
int q;

bool forExtra(pair<int,int>& a, pair<int,int>& b){
	if(dep[a.ss] == dep[b.ss]){
		return dep[a.ff] > dep[b.ff];
	}
	return dep[a.ss] < dep[b.ss];
}

void lastPart(){
	sort(additional.begin(), additional.end(), forExtra);
	
	fori(n){
		canBeIncludedSpecEdges[i].set();
	}
	
	fori(m){
		int to1 = additional[i].ss;
		int from1 = additional[i].ff;
		includedSpecEdges[from1][i] = 1;
		
		forj(i){
			int to2 = additional[j].ss;
			if(tin[to2] <= tin[to1] && tout[to2] >= tin[to1]){	
				int from2 = additional[j].ff;
				canBeIncludedSpecEdges[from2][i] = 0;
			}
		}
	}
	
	fori(m){
		int to = additional[i].ss;
		forj(n){
			if(tin[to] <= tin[j] && tout[to] >= tin[j]){
				childs[i][j] = 1;
			}
			if(tin[j] <= tin[to] && tout[j] >= tin[to] && j!=to){
				canBeIncludedSpecEdges[j][i] = 0;
			}
		}
	}
	
	vector<int> bfs;
	fori(n){
		if(!giren[i]){
			bfs.pb(i);
		}
	}
	
	fori((int)bfs.size()){
		auto hd = bfs[i];
		includedSpecEdges[hd] &= canBeIncludedSpecEdges[hd];
		for(auto& hr : gf[hd]){
			--giren[hr];
			includedSpecEdges[hr] |= includedSpecEdges[hd];
			canBeIncludedSpecEdges[hr] &= canBeIncludedSpecEdges[hd];
			if(!giren[hr]){
				bfs.pb(hr);
			}
		}
	}
	
	fori(n){
		forj(m){
			if(includedSpecEdges[i][j]){
				pars[j][i] = 1;
			}
		}
	}
	
}

ll totSum[MAX];
int childCount[MAX];
int parCount[MAX];

void lastCalc(){
	fori(m){
		int parseen = 0;
		int childseen = 0;
		ll tot = 0;
		forj(n){
			if(childs[i][j]){
				++childseen;
				tot+=parseen;
			}
			if(pars[i][j]){
				++parseen;
			}
			totSum[j] = tot;
			childCount[j] = childseen;
			parCount[j] = parseen;
		}
		forx(q){
			int li = queriesInGivenOrder[x].ff, ri = queriesInGivenOrder[x].ss;
			ll curAns = totSum[ri];
			if(li){
				curAns -= totSum[li-1];
				curAns -= (ll)(childCount[ri] - childCount[li-1]) * (ll)parCount[li-1];
			}
			queAns[x] += curAns;
		}
	}
}



void deal(){
	cin>>n>>m;
	fori(n-1){
		int fi;
		cin>>fi;
		--fi;
		g[fi].pb(i+1);
		gf[i+1].pb(fi);
		giren[fi]++;
	}
	
	fori(m){
		int ai, bi;
		cin>>ai>>bi;
		--ai, --bi;
		additional.pb(mp(ai, bi));
		gf[bi].pb(ai);
		giren[ai]++;
	}
	
	int tim = 1;
	dfs(0, tim);
	pre();
	
//	fori(n){
//		cout<<tin[i]<<" "<<tout[i]<<endl;		
//	}
	
	
	cin>>q;
	
	vector<vector<int> > all;
	forx(q){
		int li, ri;
		cin>>li>>ri;
		--li, --ri;
		all.pb(vector<int>({li, ri, x}));
		queriesInGivenOrder[x] = mp(li,ri);
	}
	
	
	sort(all.begin(), all.end(), mo);
	
	int l = 0, r = -1;
	forx(q){
		int newl = all[x][0], newr = all[x][1];
//		cout<<" query is "<<newl+1<<" "<<newr+1<<endl;
		if(r < newr){
			if(l){
				forLs[l-1].pb(vector<int>({r, newr, x}));
			}
			r = newr;
		}
		if(l > newl ){
			sumQuery[x] += toSubtract[l-1];
			sumQuery[x] += uptoIfromL[l-1];
			
			if(newl){
				sumQuery[x] -= toSubtract[newl-1];
				sumQuery[x] -= uptoIfromL[newl-1];
			}
			
			
			
			forRs[r].pb(vector<int>({l, newl, x}));
			l = newl;
		}
		if(r > newr){
			if(l){
				forLs[l-1].pb(vector<int>({r, newr, x}));
			}
			r = newr;
		}
		if(l < newl){
			sumQuery[x] -= toSubtract[newl-1]; // this is right dont change this !!
			sumQuery[x] -= uptoIfromL[newl-1]; // this is right dont change this !!
			if(l){
				sumQuery[x] += toSubtract[l-1];  // this is right dont change this !!	
				sumQuery[x] += uptoIfromL[l-1];  // this is right dont change this !!	
			}
			
			
			forRs[r].pb(vector<int>({l, newl, x}));
			l = newl;
		}
//		cout<<"all effects before the handling at query "<<newl+1<<" "<<newr+1<<" is "<<sumQuery[x]<<endl;
	}
	
	dealWithL();
	
	dealWithR();
	
	ll curS = 0;
	forx(q){
		curS += sumQuery[x];
//		cout<<"so sum query at query "<<all[x][0]+1<<" "<<all[x][1]+1<<" is "<<curS<<endl;
		queAns[all[x][2]] -= curS;
	}
	
//	fori(n){
//		cout<<"upt "<<uptoIfromL[i]<<endl;
//	}

	lastPart();
	lastCalc();
	
	forx(q){
		int li = queriesInGivenOrder[x].ff, ri = queriesInGivenOrder[x].ss;
		queAns[x] += uptoIfromL[ri];
		if(li){
			queAns[x] -= uptoIfromL[li-1];
		}
	}
	
	forx(q){	
		cout<<queAns[x]<<'\n';
	}
	
}
 
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
//	test();
	deal();
}
 
 
 
/* 
6 8 
1 2
2 3
3 4
4 1
2 5
3 5
1 6
4 6
*/