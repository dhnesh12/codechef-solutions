/*
  _    _ _      _ _      _ _      
 | |__| | | _ _| | | _ _| | | ___
 | '_ \_  _| ' \_  _| ' \_  _(_-< 
 |_.__/ |_||_||_||_||_||_||_|/__/

*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define pb push_back
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

/*
#define X real()
#define Y imag()
#define angle(a)                (atan2((a).imag(), (a).real()))
#define vec(a,b)                ((b)-(a))
#define same(p1,p2)             (dp(vec(p1,p2),vec(p1,p2)) < EPS)
#define dp(a,b)                 ( (conj(a)*(b)).real() )	// a*b cos(T), if zero -> prep
#define cp(a,b)                 ( (conj(a)*(b)).imag() )	// a*b sin(T), if zero -> parllel
#define length(a)               (hypot((a).imag(), (a).real()))
#define normalize(a)            (a)/length(a)
//#define polar(r,ang)            ((r)*exp(point(0,ang)))  ==> Already added in c++11
#define rotateO(p,ang)          ((p)*exp(point(0,ang)))
#define rotateA(p,ang,about)  (rotateO(vec(about,p),ang)+about)
#define reflectO(v,m)  (conj((v)/(m))*(m))
typedef complex<double> point;
const double PI  = acos(-1.0);
*/

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const double eps = 1e-9;
const int mod = 1e9 + 7;
const int oo = 1e9 + 7;
const ll lloo = 1e18 + 7;

const int N = 3e5 + 7;

//=======================

int n,a[N],k,b[N],d[N];

void solve()
{
	scanf("%d%d",&n,&k);
	for(int i = 0 ; i < n ; i++) scanf("%d",a+i);
	for(int i = 0 ; i < n ; i++) scanf("%d",d+i);
	for(int i = 0 ; i < k ; i++) scanf("%d",b+i);
	
	vector<pii> vec;
	ll nn = 0;
	for(int i = 0 ; i < n ; i++) {vec.pb({a[i],d[i]});nn += d[i];}
	sort(all(vec));
	
	int l = 0,r = n-1;
	
	for(int i = 0 ; i < k ; i++)
	{
		int x = nn-b[i];
		if ((i&1) == 0)
		{
			while(vec[l].S <= x)
			{
				x -= vec[l].S;
				nn -= vec[l].S;
				vec[l].S = 0;
				l++;
			}
			vec[l].S -= x;
			nn -= x;
		}
		else
		{
			while(vec[r].S <= x)
			{
				x -= vec[r].S;
				nn -= vec[r].S;
				vec[r].S = 0;
				r--;
			}
			vec[r].S -= x;
			nn -= x;
		}
		//cerr << l << ' ' << r << endl;
	}
	ll sum = 0;
	for(int i = l ; i <= r ; i++) sum += (ll)vec[i].F*vec[i].S;
	printf("%lld\n",sum);
}

int main()
{
    // freopen("in","r",stdin);
    // freopen("out","w",stdout);
    int t = 1;
    scanf("%d",&t);
    while (t--)
        solve();
    return 0;
}


// btw i use arch
