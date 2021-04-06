#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll ;
typedef double db;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector< pair<int,int> > vii;
const double pi = 2*acos(0) ;
const int mod = 1000000007;
const int N = 100003;

#define pf		  	 printf
#define sf			 scanf
#define pb(a)        push_back(a)
#define ff 			 first
#define ss			 second
#define for0(i,n)    for(int i=0;i<(int)n;i++)
#define for1(i,n)    for(int i=1;i<=n;i++)
#define forab(i,a,b) for(int i=a;i<=b;i++)
#define gcd(a,b)     __gcd(a,b)
#define all(v) 		 v.begin(),v.end()
#define rall(v) 	 v.rbegin(),v.rend()
#define WakandaForever     ios_base::sync_with_stdio(0); cin.tie(0);

void solve(){
	ll n,k,m;
	cin>>n>>k>>m;
	vi a(n),b(n),d(n);
	
	for0(i,n) cin>>a[i];
	for0(i,n) cin>>b[i];
	for0(i,n) d[i] = a[i]-b[i];
	
	sort(all(d),greater<int>());
	
	ll len = k+m;
	vi bt(len);
	for0(i,k+m) cin>>bt[i];
	sort(all(bt),greater<int>());
	
	int j=0;
	for0(i,n){
		if(j<len){
			while(1){
				if(d[i]>=bt[j]){
					d[i] -= bt[j];
					j++;
					break;
				}
				else j++;
			}
		}
	}
	ll cnt = 0;
	for0(i,n) cnt += d[i];
	
	cout<<cnt<<endl;
	

}
int main()
{
    WakandaForever
    int q=1;
    cin>>q;
    while(q--){
		solve();
	}
	
    return 0;
}
