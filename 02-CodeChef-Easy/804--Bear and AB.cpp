#include<bits/stdc++.h>
#define int long long
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
s.find_by_order(x) xth element in set
x.order_of_key(x) number of elements <x*/
#define ll long long
#define vi vector<int>
#define si set<int>
#define mii map<int,int>
#define pb push_back
#define pf push_front
#define PI acos(-1)
#define pii pair<int,int>
#define extract_word(s)  stringstream str(s); while(str>>word)
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define SET(s) cout<<fixed<<setprecision(s)
#define set0(a) memset(a,0,sizeof(a))
#define endl "\n"
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define lower_string(s) transform(all(s),s.begin(),::tolower)
#define upper_string(s) transform(all(s),s.begin(),::toupper)
#define len(s) (int)s.size()
#define F first
#define S second
template<typename T,typename U>
bool compare(T x,U y){return(abs(x-y)<=1e-9);}
const int MOD=1e9+7;
void solve()
{
ll n,k;
cin>>n>>k;
string s;
cin>>s;
ll A=count(all(s),'a');
ll B=count(all(s),'b');
ll ans=A*B*k*(k-1)/2;
ll cnt=0;
vi b(n);
for(int i=n-1;i>=0;i--)
if(s[i]=='b')
{
	b[i]=1;
}
vi m(n);
m[n-1]=b[n-1];
for(int i=n-2;i>=0;i--)
m[i]=m[i+1]+b[i];

for(int i=0;i<n;i++)
if(s[i]=='a')
cnt+=m[i];
cout<<ans+cnt*k;
}
signed main()
{
//code
fastio
int t=1;
cin>>t;
while(t--)
{
solve();
cout<<endl;
}
}
