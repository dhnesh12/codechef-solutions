#include <bits/stdc++.h>                                           

//#define int long long	
//#pragma GCC optimize("Ofast")
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4")

#define file(s) freopen(s".in","r",stdin); freopen(s".out","w",stdout);                                          
#define forev(i, b, a) for(int i = (b); i >= (a); --i)	    
#define forn(i, a, b) for(int i = (a); i <= (b); ++i)
#define sz(s) (int)s.size()
#define all(x) x.bg, x.en                                                                    
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define rbg rbegin()
#define bg begin()
#define en end()
#define s second
#define f first                                               
	
   
using namespace std;                  
   
   
typedef pair < long long, long long > pll;    
typedef pair < int, int > pii;
typedef unsigned long long ull;         
typedef vector < pii > vpii;
typedef vector < int > vi;
typedef long double ldb; 
typedef long long ll;  
typedef double db;                            
						               
				
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1}, block = 33190;	
const pii base = mp(1171, 3307), Mod = mp(1e9 + 7, 1e9 + 9);  
const int inf = 1e9, N = 2e5 + 11, mod = 1e9 + 7;
const db eps = 1e-12, pi = 3.14159265359; 
const ll INF = 1e18;


int t, n, a[N];
vi g[20];
        	
bool ask1 (int x, int y, int d) {
	cout << 1 << ' ' << x << ' ' << y << ' ' << d << endl;
	string s;
	cin >> s;
	return s == "Yes";
}

bool ask2 (int x, int y) {
	cout << 2 << ' ' << x << ' ' << y << endl;
	string s;
	cin >> s;
	return s == "Yes";
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n;
		int mn = 1;
		forn (i, 2, n)
			if (!ask2(mn, i))						
				mn = i;

		a[mn] = 1;
		forn (i, 1, n)
			if (i != mn)
				forn (j, 1, n - 1)
					if (ask1(mn, i, j))
						a[i] = j + 1;

		cout << 3 << ' ';						
		forn (i, 1, n)
			cout << a[i] << ' ';
		cout << endl;							
	}
	return 0;
}