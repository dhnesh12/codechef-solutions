#include<bits/stdc++.h>
using namespace std;

#define double long double
#define int long long
#define ALL(x) x.begin(),x.end()
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define pb(x) push_back(x)
#define eb emplace_back
#define SORT(ls) sort(ls.begin(), ls.end())
#define DESC(ls) sort(ls.rbegin(), ls.rend()) 
#define mp(x, y) make_pair(x, y)
#define INF 1000000000
#define MOD 998244353 
#define F(i, a, n) for(i=a;i<n;i++)
#define SI(x) cin>>x
#define DI(x, y) cin>>x>>y
#define TI(x, y, z) cin>>x>>y>>z
#define FI(w, x, y, z) cin>>w>>x>>y>>z
#define SO(x) cout<<x<<"\n"
#define DO(x, y) cout<<x<<" "<<y<<"\n"
#define TO(x, y, z) cout<<x<<" "<<y<<" "<<z<< "\n"
#define FO(w, x, y, z) cout<<w<<" "<<x<<" "<<y<<" "<<z<<"\n"
#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};


int numArrays(int a[], int n, int k)
{
	if(k == 0)
		return n*(n + 1)/2;
	int N = n + 5;
	FenwickTree bit(N);
	int ans = 0;
	int i, j;
	j = 0;
	int s = 0;
	F(i, 0, n)
	{	
		while(j < n && (s < k))
		{
			s += bit.sum(a[j] + 1, N - 1);
			bit.add(a[j], 1);
			++j;
		}
		if(j == n && s < k)
			break;
		ans += (n - j + 1);
		s -= bit.sum(0, a[i] - 1);
		bit.add(a[i], -1);
	}
	return ans;
}

void coordCompress(int a[], int n)
{
	map<int, int> mp;
	for(int i = 0; i < n; i++)
		mp[a[i]] = 1;
	int c = 1;
	for(auto &i: mp)
		i.second = c++;
	for(int i = 0; i < n; i++)
		a[i] = mp[a[i]];
}

int solve()
{ 
	int i, j;
	int n;
	SI(n);
	int a[n];
	F(i, 0, n)
		SI(a[i]);
	if(n == 1)
		return 0;
	coordCompress(a, n);
	int left = 0;
	int right = 2e10;
	int median = n*(n+1)/2;
	median = median - (median - 1)/2;
	while(left < right)
	{
		int mid = (left + right + 1) / 2;
		if(numArrays(a, n, mid) >= median)
			left = mid;
		else
			right = mid - 1;
	}
	return left;
}


int32_t main(void)
{
    FASTER;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int i, j;
    int t;
    SI(t);
    while(t--)
    	SO(solve());
	    
    
    #ifdef LOCAL
    	cout<<endl<<endl<<"Time: "<<(float)clock()/CLOCKS_PER_SEC<<" seconds"<<endl;
    #endif
    return 0;
}