
#include <bits/stdc++.h>
#define ll long long int
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define nl "\n"
#define ff first
#define ss second
#define pb push_back
#define po pop_back()
#define lb lower_bound
#define ub upper_bound
#define dbg(x) cout << (#x) << " = " << (x) << nl
#define fl(i,a,b,c) for(int i=a;i<b;i+=c)
#define rl(i,a,b,c) for(int i=a;i>b;i-=c)
#define sn(a,l) fl(i,0,l,1) cin>>a[i];
#define pr(a,l) fl(i,0,l,1) cout<<a[i]<<' ';
#define all(a) a.begin(),a.end()
#define test() int ts; cin>>ts; while(ts--)
const int INF = 1e9 + 1;
const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
const int K = 20;
using namespace std;

// CODE BEGINS HERE --- IMPLEMENTATION(TWO POINTERS)

void solve()
{
    int n;
    cin>>n;
    vector<ll> a(n);
    sn(a,n);
    ll x;
    cin>>x;
    int cur_box_A = 0, cur_box_B = n-1, tot_box_A = 0, tot_box_B = 0;
    ll tot_can_A = 0, tot_can_B = 0;
    while(cur_box_A < cur_box_B)
    {
        if(tot_can_A > tot_can_B)
        {
            tot_can_B += x * a[cur_box_B];
            cur_box_B -= 1;
            tot_box_B += 1;
        }
        else if(tot_can_A < tot_can_B)
        {
            tot_can_A += a[cur_box_A];
            cur_box_A += 1;
            tot_box_A += 1;
        }
        else
        {
            tot_can_A += a[cur_box_A];
            cur_box_A += 1;
            tot_box_A += 1;
            tot_can_B += x * a[cur_box_B];
            cur_box_B -= 1;
            tot_box_B += 1;
        }
    }
    if(cur_box_A == cur_box_B && tot_can_A < tot_can_B)
	    tot_box_A += 1;
	else if(cur_box_A == cur_box_B && tot_can_A > tot_can_B)
	    tot_box_B += 1;
	else
	{ 
	    if(tot_box_A >= tot_box_B)
	        tot_box_A += 1;
	    else
	        tot_box_B += 1;
	}
    cout << tot_box_A << ' ' << tot_box_B << nl;
    cout << nl;
}
 
int main()
{
    fastIO
    test()
    solve();
    return 0;
}


