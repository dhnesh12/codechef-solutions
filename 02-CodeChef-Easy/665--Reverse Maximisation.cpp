#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef unordered_map<int,int> umii;
typedef unordered_map<ll,ll> umll;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define bs(v,val) binary_search(v.begin(),v.end(),val)
#define mod 1000000007
#define mod2 998244353 
#define ff first
#define ss second
#define fi(n) for(int i=0;i<n;i++)
#define fj(n) for(int j=0;j<n;j++)
#define all(v) v.begin(),v.end()
#define pb push_back
#define m_p make_pair
#define endl '\n'

struct custom_hash {    // anti-hack for unordered_map. To declare: unordered_map<long long, int, custom_hash> safe_map;
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};
ll power(ll x, ll y, ll p)
{  
    ll res = 1;
    x = x % p;  
    if (x == 0) return 0;
    while (y > 0){  
        if (y & 1)  res = (res*x) % p;  
        y = y>>1;
        x = (x*x) % p;  
    }  
    return res;  
}
ll modInverse(ll n, ll p)
{
    return power(n, p-2, p); 
}
ll modAdd(ll a, ll b, ll p)
{
    return (a+b)%p;
}
ll modSub(ll a, ll b, ll p)
{
    return (a%mod - b%mod + mod)%p;
}
ll modMul(ll a, ll b, ll p)
{
    return (a*b)%p;
}

// ********** CODE STARTS HERE ****************//

void solve()
{
    string s;
    cin >> s;
    if(s.size() == 1)
        cout << s << '\n';
    else
    {
        if(s[0] == '1')
        {
            bool b = true;
            for(int i=1; i<s.size(); i++)
            {
                if(s[i] != '0')
                {
                    b = false;
                    break;
                }
            }
            if(b)
            {
                for(int i=0; i<s.size()-1; i++)
                    cout<<"9";
                cout << '\n';
                return;
            }
            int i;
            for(i=1; i<s.size(); i++)
                if(s[i]!='0')
                    break;
            int x = 0;
            for(int j=i+1;j<s.size();j++)
            {
                if(s[j]!='9')
                    x=1;
                s[j]='9';
            }
            if(x)
                s[i]--;
            cout << s << '\n';
        }
        else
        {
            int x = 0;
            for(int i=1;i<s.size();i++)
            {
                if(s[i]!='9')
                {
                    x=1;
                }
                s[i] = '9';
            }
            if(x)
                s[0]--;
            cout << s << '\n';
        }
        
    }
    
    
}

int main()
{
	fastio;
    int T;
    cin>>T;
    while(T--)
        solve();
	return 0;
}