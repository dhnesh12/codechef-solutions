#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
// using namespace __gnu_pbds;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define pb push_back
#define mp(a,b) make_pair(a,b)
#define _f0(i,n) for(i = 0; i < ( n ); i ++)
#define _f1(i,n) for(i = 1; i <= ( n ); i ++)
#define _f(i,m,n) for(auto i = ( m ); i <= ( n ); i ++)
#define _in(v) for(auto& _var:v)    cin>>_var;
#define _out(v) for(auto _var:v)    cout<<_var<<" ";
#define _rout(x) for(auto _it=x.rbegin(); _it!=x.rend(); _it++) cout<<(*_it)<<" ";
#define _all(x) x.begin(), x.end()
#define _rall(x) x.rbegin(), x.rend()
#define _loop(x) for(auto& _var:x)
#define _ms(x,n) memset(x,n,sizeof(x))
#define run ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define nl cout<<"\n";
#define loopt int _tc; cin>>_tc; while(_tc--)
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<int>;
using vl = vector<ll>;
using ii = pair<int,int>;
using lili = pair<long long int,long long int>;
using vii = vector<ii >;
using vll = vector<lili>;
using viv = vector<vi >;

const ll INF = 1000000005;
const ll mod = ((int)1e9+7);
const ll mod1 = 998244353;

/////////////////////////////////\\\\\\\\

ll _fac(ll n, ll MOD = LLONG_MAX)   {return (n==1||n==0)?1:(n*((_fac(n-1))%MOD))%MOD;}

ll _pow(ll a, ll b, ll MOD = LLONG_MAX)
{
    if(b==0||a==1)  return 1;
    if(a==0)    return 0;
    if(b&1) {ll temp = _pow(a,b/2,MOD)%MOD; return (((temp*temp)%MOD)*a)%MOD;}
    else    {ll temp = _pow(a,b/2,MOD)%MOD; return (temp*temp)%MOD;}
}

ll _powm(ll a, ll b, ll MOD)
{
    ll res = 1; a = a%MOD;
    if(a==0)    return 0;
    while(b>0)
    {
        if(b&1) res = (res*a)%MOD;
        b = b>>1;
        a = (a*a)%MOD;
    }
    return res;
}

ll _gcd(ll a, ll b) {if(b==0)    return a;   return _gcd(b,a%b);}

ll _lcm(ll a, ll b) {return (a*b)/_gcd(a,b);}

ll _nPr(ll n, ll r) {return _fac(n)/_fac(r);}

ll _nCr(ll n, ll r)
{
    if(r>n-r)   r = n-r;
    if(r==0)    return 1;
    ll n1 = 1;
    ll n2 = 1;
    _f(i,1,r)    n1*=i;
    _f(i,n-r+1,n)  n2*=i;
    return n2/n1;
}

ll _invMod(ll a, ll m)  {return _pow(a, m-2, m);}

ll _cat(int n)  {return _nCr(2*n,n)/(n+1);}

ll _msb(ll n)
{
    n |= n>>1;
    n |= n>>2;
    n |= n>>4;
    n |= n>>8;
    n |= n>>16;
    n |= n>>32;
    n++;
    return (n>>1);
}

int _nod(ll n)  {int c = 0;  while(n>0)  {c++; n/=10;}   return c;}

int _nob(ll n)  {int c = 0;  while(n>0)  {c++; n&=(n-1);}   return c;}

bool _isPrime(ll n, int k = 5)
{
    if(n<=1||n==4)  return false;
    if(n<=3)    return true;
    while(k>0)
    {
        ll a = 2 + rand()%(n-4);
        if(_gcd(n,a)!=1)    return false;
        if(_pow(a,n-1,n)!=1)    return false;
        k--;
    }
    return true;
}

/////////////////////////////////\\\\\\\\

class _rand_ {public: _rand_() {func();}   void func() {srand((unsigned)time(0));}};  _rand_ _rno_;

class _udf
{
    private: vi _p, _rank;
    public: _udf(int n)
    {
        _rank.assign(n+1,0);
        _p.assign(n+1,0);
        _f(i,1,n) _p[i] = i;
    }
    int findSet(int i)  {return (_p[i]==i)?i:(_p[i] = findSet(_p[i]));}
    bool isSameSet(int i, int j)   {return findSet(i)==findSet(j);}
    void unionSet(int i, int j)
    {
        if(!isSameSet(i,j))
        {
            int x = findSet(i), y = findSet(j);
            if(_rank[x]>_rank[y]) _p[y] = x;
            else    {_p[x] = y; if(_rank[x]==_rank[y]) _rank[y]++;}
        }
    }
};

clock_t _tstart, _tend;

class ___
{
    public:
        ___(){b();}
        ~___(){e();}
    void b()
    {
        _tstart = clock();
        #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        #endif
    }
    void e()
    {
        _tend = clock();
        #ifndef ONLINE_JUDGE
            nl;nl; cout<<"Time Take: "<<(double)(_tend-_tstart)/(double)(CLOCKS_PER_SEC)<<"s"; nl; nl; nl;
        #endif
    }
};  ___ __;
/////////////////////////////////\\\\\\\\\\\\\\\\

int main()
{
	loopt
	{
		ll a, b, c;
		cin>>a>>b>>c;
		ll p = b-a;
		ll q = c-b;
		ll temp = abs(p-q);
		ll ans = (temp+1)/2;
		cout<<ans;
		nl;
	}
}