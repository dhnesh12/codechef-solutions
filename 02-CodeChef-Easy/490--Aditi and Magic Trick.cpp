#include <bits/stdc++.h>
#define ll int
#define MOD 1e9+7
#define rep(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define sep(i,a,b) for(ll i=(ll)a;i>=(ll)b;i--)
#define pb push_back
#define db double
#define lb lower_bound
#define ub upper_bound
#define all(a) a.begin(),a.end()
#define sz(a) (ll)a.size()
#define Frs first
#define Snd second
#define quick ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

long long int fib[100];

void solve() {
	long long ll n;
	cin>>n;

    int i;
    for (i=0; i<100; ++i) {
        if (fib[i]>n)
            break;
    }

    cout<<i-2<<endl;

}

int main()
{quick;

    fib[0] =0;
    fib[1] =1;
    rep(i,2,100) {
        fib[i] = fib[i-1]+fib[i-2];
    }
	ll t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}