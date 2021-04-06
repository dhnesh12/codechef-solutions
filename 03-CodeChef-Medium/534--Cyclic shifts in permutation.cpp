#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef long double ld;
typedef long long unsigned llu;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define fout(S,x)            cout<<fixed<<setprecision(x)<<(S)<<endl
typedef pair<int,int> PII;typedef vector<int> VI;typedef vector<PII> VPII;typedef set<PII> SPII;typedef vector<ll> VLL;
typedef pair<ll,ll> PLL;      typedef vector<PLL> VPLL;        typedef set<PLL> SPLL;       typedef map<ll,ll> MLL;
typedef map<string,int> MSI;  typedef map<int,VI> MVI;         typedef map<int,PII> MPII;   typedef vector<string> VS;
#define pb push_back
#define mp make_pair
#define sz(x) x.size()
#define present(c,x) ((c).find(x) != (c).end())
#define lp(i,a,b) for(int i=a;i<=b;i++)
#define rlp(i,a,b) for(int i=a;i>=b;i--)
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define T() ll t;cin>>t;while(t--)
#define db(x) cout<<x<<" "
#define db1(x) cout<<x<<endl
#define db2(x,y) cout<<x<<" "<<y<<endl
#define db3(x,y,z) cout<<x<<" "<<y<<" "<<z<<endl
#define db4(x,y,z,w) cout<<x<<" "<<y<<" "<<z<<" "<<w<<endl
#define tr1(x) cerr << #x << ": " << x << endl
#define tr2(x, y) cerr << #x << ": " << x << " | " << #y << ": " << y << endl
#define tr3(x, y, z) cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl
#define tr4(a, b, c, d) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl
#define tr5(a, b, c, d, e) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl
#define db_1 cout<<"okay1\n"
#define db_2 cout<<"okay2\n"
#define db_3 cout<<"okay3\n"
#define mem(a,b) memset(a,b,sizeof(a))
#define rtr(container, it) for(typeof(container.begin()) it = container.end()-1; it >= container.begin(); --it)
#define tr(container, it) for(typeof(container.begin()) it = container.begin(); it != container.end(); ++it)
#define all(s) s.begin(),s.end()
#define lbi(a, val) (lower_bound(all(a), val) - a.begin())
#define ubi(a, val) (upper_bound(all(a), val) - a.begin())
#define maxele(x)  *max_element(all(x))
#define minele(x)  *min_element(all(x))
#define ff first
#define ss second
#define S(z) z.size()
#define L(z) z.length()
#define nl cout<<endl
#define dbv(A,n) lp1(ti,0,n-1) cout<<ti<<" -- > "<<A[ti]<<"\n"
#define dbvp(Z) lp1(ti,0,S(Z)-1){cout<<ti<<" --> "<<Z[ti].ff<<" "<<Z[ti].ss<<"\n";}
#define dbm(W,n) lp1(ti,0,S(W)-1){cout<<ti<<" --> ";lp1(tj,0,sz(W[ti])-1) cout<<"("<<W[ti][tj]<<" , "<<W[ti][tj]<<")"<<"  ";cout<<"\n";}
#define dbmp(W,n) lp1(ti,0,S(W)-1){cout<<ti<<" --> ";lp1(tj,0,sz(W[ti])-1) cout<<"("<<W[ti][tj].ff<<" , "<<W[ti][tj].ss<<")"<<"  ";cout<<"\n";}
#define dbzmp(Z) tr(Z,zt) cout<<(zt->ff)<<" --> "<<(zt->ss)<<"\n"
#define dist(x1,y1,x2,y2)        ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define area(x1,y1,x2,y2,x3,y3)  (abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))/2.0))
#define ln(x)                    (ll(log2(LD(x))))
#define dig(x)                   (ll(log10(LD(x)))+1)
#define ceil(a,b)                (ll(ceil(LD(a)/LD(b))))
#define sin(x)                   (sin((x*PI)/180.0))
#define sq(x)                    ((x)*(x))
#define etm cerr << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n'
template<typename X> inline X sqr(const X& a) { return (a * a); }
template< class T > T _abs(T n) { return (n < 0 ? -n : n); }
template< class T > T _max(T a, T b) { return (!(a < b) ? a : b); }
template< class T > T _min(T a, T b) { return (a < b ? a : b); }
template< class T > T gcd(T a, T b) { return (b != 0 ? gcd<T>(b, a%b) : a); }
template< class T > T lcm(T a, T b) { return (a / gcd<T>(a, b) * b); }
template< class T > bool _in(T a, T b, T c) { return a<=b && b<=c; }
inline int fi(){int n=0;int ch=getchar();while(ch<'0'||ch>'9')ch=getchar();while(ch>='0'&&ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();return n;}
inline void fo(int a){char snum[20];int i=0;do{snum[i++]=a%10+48;a=a/10;}while(a!=0);i=i-1;while(i>=0)putchar(snum[i--]);putchar('\n');}
ll modpow(ll a,ll n,ll temp){ll res=1,y=a;while(n>0){if(n&1)res=(res*y)%temp;y=(y*y)%temp;n/=2;}return res%temp;}
const int er[8] = {-1,-1,0,1,1,1,0,-1};
const int ec[8] = {0,1,1,1,0,-1,-1,-1};
const int fr[4] = {-1,1,0,0};
const int fc[4] = {0,0,1,-1};
const int base=10,base_digits=10,mod=1000000007,INF=1000000000,maxn=1e5;
const ll INFLL =1000000000000000000LL;
const llu INFLLU=18446744073709551615ULL;
const ld EPS = (ld)1e-9;
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = mod) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = mod) {if ((a = (a - val)) < 0) a += p;}
#define fread(a) freopen("a","r",stdin)
#define fwrite(b) freopen("b","w",stdout)
#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))
#define min4(a,b,c,d) min(min(a,b),min(c,d))
#define max4(a,b,c,d) max(max(a,b),max(c,d))
int bs(vector<int>arr,int l,int r,int x){while(l<=r){int m=l+(r-l)/2;if(arr[m]==x)return m;if(arr[m]<x)l=m+1;else r=m-1;return -1;}}
#define common(a,b) SORT(a), SORT(b), a.erase(set_intersection(all(a),all(b),a.begin()),a.end())
#define uncommon(a,b) SORT(a), SORT(b), a.erase(set_symmetric_difference(all(a),all(b),a.begin()),a.end()
#define UN(v) sort(all(v));(v).earse(unique(all(v)),v.end())
int ft[maxn+10];
void add(int v,int d){
    for(;v<=maxn;v+=(v&-v))
        ft[v]+=d;
}
int sum(int r){
    int ans=0;
    for(;r>0;r-=(r&-r))
        ans+=ft[r];
    return ans;
}
int sum(int l,int r){
    return sum(r)-sum(l-1);
}
int index(vector<int>p,int mod){
    int n=p.size();
    memset(ft,0,sizeof(ft));
    for(int i=1;i<=n;++i){
        add(i,1);
    }
    int fact[maxn+10];
    fact[0]=1%mod;
    for(int i=1;i<=n;++i)
        fact[i]=(fact[i-1]*1ll*i)%mod;
    int ans=0;
    for(int i=0;i<n;++i){
        int id=sum(p[i]-1);
        ans=(ans+id*1ll*fact[n-i-1])%mod;
        add(p[i],-1);
    }
    return ans;
}
int parity(vector<int>p){
    int n=p.size();
    memset(ft,0,sizeof(ft));
    int ans=0;
    for(int i=n-1;i>=0;i--){
        int smaller=sum(p[i]-1);
        ans=(ans+smaller)%2;
        add(p[i],1);
    }
    return ans;
}
int main () {
    fastio;
    T(){
        int n,k;
        vector<int>p,q;
        cin>>n>>k;
        p.resize(n);
        q.resize(n);
        lp(i,0,n-1)
            cin>>p[i];
        lp(i,0,n-1)
            cin>>q[i];
        if(k==n){
            int start=-1;
            lp(i,0,n-1){
                if(q[i]==p[0]){
                    start=i;
                    break;
                }
            }
            bool good=true;
            for(int i=0;i<n;i++){
                if(p[i]!=q[(i+start)%n]){
                    good=false;
                    break;
                }
            }
            if(good)
                cout<<q[0]<<endl;
            else
                cout<<-1<<endl;
        }
        else if(k%2==0){
            int id=index(q,mod);
            cout<<(id+1)%mod<<endl;
        }
        else{
            if(parity(p)==parity(q)){
                int id=index(q,mod);
                if(index(q,2)==1)
                    id=(id+mod-1)%mod;
                id=id*500000004ll %mod;
                cout<<(id+1)%mod<<endl;
            }
            else{
                cout<<-1<<endl;
            }
        }
    }
    etm;
}

