#include <bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef set<ll> si;
typedef map<ll,ll> mii;
typedef map<ii,ll> miii;
typedef map<char,int> mci;
typedef priority_queue <int> pq_g; //to store data in desecending order
typedef priority_queue <int, vector<int>, greater<int>> pq_s; 
#define pb(x) push_back(x);
#define MOD 1000000007
#define YES cout<<"YES"<<endl;
#define NO cout<<"NO"<<endl;
#define p(str) cout<<str;
#define pe(str) cout<<str<<"\n";
#define f(s,n,i) for(i=s;i<n;i++)
#define endl "\n"
#define vl(d)  (ll)str[d]-48
#define fast ios_base::sync_with_stdio(false),cin.tie(NULL)

const int LI = 1e2+5;
vector<vector<char> > arr(LI, vector<char> (LI, '-'));
vector<vector<bool> > vis(LI, vector<bool> (LI, false));

int gcd(ll a,ll b){return (b==0?a:gcd(b,a%b)) ;}

int main()
{ 
  fast;
  ll T=1;
  cin>>T;
   while(T--)
   {
    ll N,Q,K,i,j,k=0,x,y,z,ind,sum=0,flag=0,count=0,mx=0,r=0,a, 
	b,c,mn=INT_MAX,Motu=0,Tomu=0;
	cin>>N>>K;
	vi T,M; ll arr[N];
	f(0,N,i){
	    cin>>arr[i];
	    if(i%2==0){
	        Motu+=arr[i];
	        M.push_back(arr[i]);
	    }
	    else{
	        Tomu+=arr[i];
	        T.push_back(arr[i]);
	    }
	}
	sort(T.begin(),T.end());
	sort(M.begin(),M.end(),greater<int>());
	j=0; 
// 	f(0,T.size(),i)cout<<T[i]<<" "; cout<<endl;
// 	f(0,M.size(),i)cout<<M[i]<<" "; cout<<endl;
// 	cout<<Motu<<" "<<Tomu<<" "<<M[0]<<" "<<T[0]<<endl;
	f(0,min(K,N/2),i){
	    if(Tomu>Motu){ flag=1; break;}
	    else if(M[j]>T[j]){
	        Tomu=Tomu+M[j]-T[j];
	        Motu=Motu+T[j]-M[j];
	        j++;
	    }
	    else break;
	}
	if(Tomu>Motu)flag=1;
	if(flag)YES
	else NO
   } 
 return 0;
}
