#define y1 askjdkasldjlkasd
#include <bits/stdc++.h>
#undef y1

using namespace std;

#define pb push_back
#define mp make_pair
#define fi(a, b) for(int i=a; i<=b; i++)
#define fj(a, b) for(int j=a; j<=b; j++)
#define fo(a, b) for(int o=a; o<=b; o++)
#define fdi(a, b) for(int i=a; i>=b; i--)
#define fdj(a, b) for(int j=a; j>=b; j--)
#define fdo(a, b) for(int o=a; o>=b; o--)
#define sz(x) (int)x.size()

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef vector<ll> vll;
typedef __int128_t i128;
typedef __float128 f128;

string tostring(i128 x) {
	string s;
	if (x == 0) return "0";
	bool pos = true;
	if (x < 0) {
		pos = false;
		x = -x;
	}
	while (x) {
		s.pb((char) (x % 10 + '0'));
		x /= 10;
	}
	if (!pos) s.pb('-');
	reverse(s.begin(), s.end());
	return s;
}

void print(i128 x) {
	printf("%s", tostring(x).c_str());
}

#ifdef LOCAL
#define err(...) fprintf(stderr, __VA_ARGS__)
#else
#define err(...) while (0)
#endif

double START_TIME;

void exit() {
#ifdef LOCAL	
	cerr << "TIME: " << setprecision(5) << fixed << (clock() - START_TIME) / CLOCKS_PER_SEC << endl;
#endif	
	exit(0);
}

template<typename A, typename B>
ostream& operator<<(ostream& os, pair<A, B> p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v) {
	fi(0, sz(v) - 1) {
		os << v[i] << " ";
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, set<T> t) {
	for (auto z : t) {
		os << z << " ";
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, deque<T> t) {
	for (auto z : t) {
		os << z << " ";
	}
	return os;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& os, map<T1, T2> t) {
	cerr << endl;
	for (auto z : t) {
		os << "\t" << z.first << " -> " << z.second << endl;
	}
	return os;
}

#ifdef LOCAL
#define dbg(x) {cerr << __LINE__ << "\t" << #x << ": " << x << endl;}
#define dbg0(x, n) {cerr << __LINE__ << "\t" << #x << ": "; for (int ABC = 0; ABC < n; ABC++) cerr << x[ABC] << ' '; cerr << endl;}
#else
#define dbg(x) while(0){}
#define dbg0(x, n) while(0){}
#endif

#ifdef LOCAL
#define ass(x) if (!(x)) { cerr << __LINE__ << "\tassertion failed: " << #x << endl, abort(); }
#else
#define ass(x) assert(x)
#endif

///////////////////////////////////////////////////

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

int getrandint(int l, int r) {
	ll res = generator();
	return (int) (res % (r - l + 1) + l);
}

const int MAX = 1e3 + 41;

int n, b;
int c[MAX];
int d[MAX];
int w[MAX];
int q[MAX];
int pos[MAX];
deque<int> a[MAX];
vpii ans;
ll cost;
ll sumop;
ll curcost;
int basestack;

deque<int> aa[MAX];
int pos2[MAX];
vpii answer;
ll bestanswer;
int BESTBASE;
int bestbasestack;
int DEG;

ld lglg[20][MAX];

int BASE;

void init() {
	fi(0, MAX - 1) {
		lglg[0][i] = 1;
		fj(1, 19) {
			lglg[j][i] = lglg[j - 1][i] * log(i);
		}
	}
}

void copyall() {
	fi(1, n) a[i] = aa[i];
	curcost = 0;	
	memcpy(pos, pos2, sizeof(pos2));
	ans.clear();
}

void print() {
	fi(1, n) {
		if (i != BESTBASE || !bestbasestack) {
			printf("Q");
		} else {
			printf("S");
		}
	}
	printf("\n");
	printf("%d\n", sz(answer));
	for (auto z : answer) {
		printf("%d %d\n", z.first, z.second);
	}	
#ifdef LOCAL
	cost += bestanswer;
	sumop += sz(answer);
	err("cost =  %lld opr = %.4lf logop = %.3lf log = %.3lf\n", cost, (double) sz(answer) / b, (double) log(sumop), (double) log(cost));
	/*assert(sz(a[BESTBASE]) == b);
	fi(1, sz(a[BESTBASE]) - 1) {
		assert(a[BESTBASE][i] == a[BESTBASE][i - 1] + 1);
	}*/
#endif	
}

void move(int c1, int c2) {
	int x;
	if (c1 == BASE && basestack) {
		x = a[c1].back();
		a[c1].pop_back();
	} else {
		x = a[c1].front();
		a[c1].pop_front();
	}	
	a[c2].push_back(x);
	pos[x] = c2;
	ans.pb(mp(c1, c2));	
	curcost += (c[c1] + d[c2]) * w[x];
}


int getcheapestplacefor(int x) {	
	int res = -1;
	ld cost = 0;
	fi(1, n) {
		if (i == pos[x] || i == BASE) continue;
		ld pcost = (c[i] + d[i]) * (w[x] + sqrt(sz(a[i])));
		fdj(sz(a[i]) - 1, 0) {
			if (a[i][j] < x) {
				pcost += w[x] *	lglg[DEG][(x - a[i][j])];
				break;
			}
			pcost += w[a[i][j]] * c[i];
		}
		if (res == -1 || pcost < cost) {
			res = i;
			cost = pcost;
		}
	}	
	return res;
}

bool check(int BASE) {
	if (sz(a[BASE]) == 0) return true;
	fi(0, sz(a[BASE]) - 1) {
		if (a[BASE][i] != i + 1) return false;
	}
	return true;
}

void emptybase() {
	while (sz(a[BASE]) > 0 && !check(BASE)) {
		if (!basestack) {
			int to = getcheapestplacefor(a[BASE].front());		
			move(BASE, to);
		} else {
			int to = getcheapestplacefor(a[BASE].back());		
			move(BASE, to);
		}
	}
}

void solve () {	
	answer.clear();
	bestanswer = -1;
	for (DEG = 3; DEG <= 5; DEG++) {
		for (BASE = 1; BASE <= n; BASE++) {
			for (basestack = 0; basestack <= 1; basestack++) {		
				copyall();
				emptybase();
				fi(1, b) {
				if (pos[i] == BASE) continue;
					while (a[pos[i]].front() != i) {
						//int to = getmostempty(pos[i]);
						int to = getcheapestplacefor(a[pos[i]].front());
						move(pos[i], to);
					}
					move(pos[i], BASE);
				}
				if (bestanswer == -1 || bestanswer > curcost) {
					bestanswer = curcost;
					answer = ans;
					BESTBASE = BASE;
					bestbasestack = basestack;
				}		
			}
		}
	}
	print();
}

int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	START_TIME = (double)clock();
#endif	

	init();	
#ifdef LOCAL
	fi(0, 7) {
		string filename;
		filename.pb( (char) (i + '0') );
		filename += ".in";
		FILE *file = fopen(filename.c_str(), "r");

		fscanf(file, "%d %d", &n, &b);
		fi(1, n) fscanf(file, "%d", &c[i]);
		fi(1, n) fscanf(file, "%d", &d[i]);
		fi(1, b) fscanf(file, "%d", &w[i]);
		fi(1, n) {
			fscanf(file, "%d", &q[i]);
			fj(1, q[i]) {
				int x;
				fscanf(file, "%d", &x);
				pos2[x] = i;
				aa[i].pb(x);
			}
		}
		solve();
		fclose(file);
		fi(1, n) aa[i].clear();
		ans.clear();
	}
#else
	scanf("%d %d", &n, &b);
	fi(1, n) scanf("%d", &c[i]);
	fi(1, n) scanf("%d", &d[i]);
	fi(1, b) scanf("%d", &w[i]);
	fi(1, n) {
		scanf("%d", &q[i]);
		fj(1, q[i]) {
			int x;
			scanf("%d", &x);
			pos2[x] = i;
			aa[i].pb(x);
		}
	}
	solve();
#endif	

	exit();
	return 0;
}



