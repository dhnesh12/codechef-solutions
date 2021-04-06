#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp> 
using namespace boost::multiprecision;
using namespace std;
# define ll long long
# define nl "\n"
# define FAST ios_base::sync_with_stdio(0);cin.tie(0);
# define mod 1000000007
# define fi first
# define se second
# define pai pair<ll,ll>
#define pb push_back
# define bp __builtin_popcountl
# define g __gcd
# define mp make_pair
#define PI 3.1415926535897932384626433832795
const ll maxi=1e18;
ll ma=0;
ll mi=1e10;
template<typename A,typename B>
static inline void minimum(A &x,B y){
    if(y<x)
    x=y;
}
template<typename A,typename B>
static inline void maximum(A &x,B y){
    if(x<y)
    x=y;
}
ll Calpow(ll a,ll b){
    if(b==0)
    return 1;
    else if(b%2==0)
    return Calpow(a*a%mod,b/2);
    else if(b%2==1)
    return (a*Calpow(a*a%mod,(b-1)/2))%mod;
}
class CodeChef{
    public:
void test_case(){
    string s;
    cin>>s;
    ll k,c=0,i,j,res=0,m=0;
    cin>>k;
    for(i=0;i<s.size();i++){
        ll a[26]={},c=0,m=0;
        for(j=i;j<s.size();j++){
            if(a[s[j]-'a']==0){
            a[s[j]-'a']=1;
            c++;
            }
            else
            a[s[j]-'a']++;
            m=max(m,a[s[j]-'a']);
            res+=(m*c==j-i+1 && c>=k);
        }
    }
    cout<<res<<nl;
	return;
}
};
int main() {
	// your code goes here
	FAST
	int t;
	cin>>t;
	CodeChef ravi;
	while(t--)
	ravi.test_case();
	return 0;
}