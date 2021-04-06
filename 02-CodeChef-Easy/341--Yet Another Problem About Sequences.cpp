#include<bits/stdc++.h>

using namespace std;
using   ll = long long;
using   ld = long double;

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define int             long long int

#define pb              push_back
#define mp              make_pair
#define F               first
#define S               second
#define endl            "\n"

#define pii             pair<int , int>
#define vec             vector< int >

#define ALL(v)          v.begin(),v.end()
#define ALLR(v)         v.rbegin(),v.rend()
#define pi              3.14159265358979323
#define inf             LLONG_MAX
#define ones(x)         __builtin_popcount(x)
#define fill(a,b)       memset(a,b,sizeof(a))
#define mod             1000000007

int mod_pow(int a,int b,int m)
{
    int res = 1;
    while(b)
    {
        if(b&1)
        {
            res = (res*a) % m;
        }
        a = (a*a) % m;
        b >>= 1;
    }
    return res;
}

int mod_inverse(int a , int m)
{
    return mod_pow(a , m - 2 , m);
}

const int maxn = 1e6;
const int limit = 1e9;

vector< int > d;

int vis[maxn];

void go() {
	for(int i = 2; i < maxn; ++i) {
		if(!vis[i]) {
			d.pb(i);
			
			for(int j = i; j < maxn; j += i) {
				vis[j] = 1;
			}
		}
	}
}

void solve() {
	int n;
	
	cin >> n;
	
	int a[n];
	
	a[0] = d[0];
	
	for(int i = 1; i < n; ++i) {
		a[i] = d[i - 1]*d[i];
	}
	
	a[0] *= d[n - 1];
	
	for(int i = 0; i < n; ++i) {
		if(a[i] > limit) {
			cout << -1 << endl;
			return;
		}
	}
	
	for(int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

signed main() {
    fast;

    int t = 1;
    
    go();
	
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}