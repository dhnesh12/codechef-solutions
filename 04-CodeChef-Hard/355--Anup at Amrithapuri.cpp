#include<bits/stdc++.h>
typedef  long long int ll;
typedef  long double ld;
#define sync ios_base::sync_with_stdio(false); cin.tie(NULL) 
#define input(arr,n) for(ll i1=0;i1<n;i1++ )cin>>arr[i1]
#define mod 1000000007
#define F first
#define S second 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")
//recursions\
#pragma comment(linker, "/stack:200000000")
//loops\
#pragma GCC optimize("unroll-loops")
using namespace __gnu_pbds;
#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>//s.order_of_key(val) *s.find_by_order(ind)
using namespace std;

vector<string> split(const string& s, char c) {
    vector<string> v; stringstream ss(s); string x;
    while (getline(ss, x, c)) v.push_back(x); return move(v);
}
template<typename T, typename... Args>
inline string arrStr(T arr, int n) {
    stringstream s; s << "[";
    for(int i = 0; i < n - 1; i++) s << arr[i] << ",";
    s << arr[n - 1] << "]";
    return s.str();
}
#define EVARS(args...) {__evars_begin(__LINE__); __evars(split(#args, ',').begin(), args);}
inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template<typename T> inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template<typename T> inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template<typename T> inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }
template<typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cerr << "; ";
    __evars(++it, args...);
}
const int N = 1e5 + 1;
vector<ll> a(N);
struct Query
{
    ll l, r, i;
};
ll curr_ans = 0, blk;
vector<ll> freq(N);
#define MAXM 100001
ll pchk[MAXM];
vector<ll> prime[MAXM];
void sieve()
{
    pchk[0] = pchk[1] = 1;
    for(ll i = 2; i < MAXM; i++)
    {
        if(!pchk[i])
        {
            for(ll j = i; j < MAXM; j += i)
            {
                prime[j].push_back(i);
                pchk[j] = i;
            }
        }
    }
//  for(ll i = 2; i < MAXM; i++) if(!pchk[i]) prime.push_back(i);   
}
void add_element(ll idx)
{
    for(auto x: prime[a[idx]])
    {
        curr_ans += freq[x] + freq[x] + 1;
        if(curr_ans > mod)
            curr_ans -= mod;
        freq[x]++;
    }
}
void rem_element(ll idx)
{
    for(auto x: prime[a[idx]])
    {
        curr_ans -= freq[x] +  freq[x] - 1;
        if(curr_ans < 0)
            curr_ans += mod;
        freq[x]--;
    }
}
bool cmp (Query a, Query b)
{
    if(a.l / blk != b.l/ blk) 
         return a.l / blk < b.l / blk; 
    return (a.l / blk) & 1 ? a.r < b.r : b.r < a.r;
}
int main()
{
    sync;
    sieve();
    clock_t clk=clock();
    ll n, m;
    cin >> n >> m; 
    input(a, n);
    vector<ll> b(m);
    input(b, m);
    vector<Query> Q(m * m);
    ll position = 0;
    for(ll i = 0; i < m; i++)
    {
        for(ll j = 0 ; j < m; j++)
        {
            ll l = (b[i] + b[j]) % n, r =  (b[i] - b[j] + n) % n;
            if(l > r)
                swap(l, r);
           Q[position].l = l, Q[position].r = r, Q[position].i = i;
           position++;
        }
    }
    blk = m;
    ll curr_l = 0, curr_r = 0, q = Q.size();
    sort(Q.begin(), Q.end(), cmp);
    vector<ll> ans(m, 0);
    for(ll i = 0; i < q; i++)
    {
        while(curr_l > Q[i].l)
        {
            add_element(curr_l - 1);
            curr_l--;
        }
        while(curr_r <= Q[i].r)
        {
            add_element(curr_r);
            curr_r++;
        }
        while(curr_l < Q[i].l)
        {
            rem_element(curr_l);
            curr_l++;
        }
        while(curr_r > Q[i].r + 1)
        {
            rem_element(curr_r - 1);
            curr_r--;
        }
        if(!ans[Q[i].i] && curr_ans)
            ans[Q[i].i] = 1;
        ans[Q[i].i] = ans[Q[i].i] * curr_ans;
        if(ans[Q[i].i] > mod)
            ans[Q[i].i] %= mod;
       // EVARS(curr_l, curr_r, ans, curr_ans);
    }
    ll final_ans = 0;
    for(ll i = 0 ; i < m; i++)
        final_ans = (final_ans + ans[i]) % mod;
    cout << final_ans;
    //cerr << '\n'<<"Time (in s): " << double(clock() - clk) * 1.0 / CLOCKS_PER_SEC << '\n';    
}
