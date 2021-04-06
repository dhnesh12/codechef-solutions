#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,fma,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
//ordered_set  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 

#define ook order_of_key
#define fbo find_by_order
  
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define um unordered_map<ll, ll>
#define us unordered_set<ll>
#define SORT(v) sort(v.begin(),v.end())
#define fori(i,a,b) for(ll i=a;i<b;i++)
#define ford(i,a,b) for(ll i=a;i>=b;i--)
#define tc ll t;cin>>t;while(t--)
#define in_range(x, y, r, c) (x < r && y < c && x >= 0 && y >= 0)

#define MOD 1000000007
#define INF LLONG_MAX
#define PI 3.1415926535897932385

typedef pair<ll, ll> ii;
typedef pair<ii, ll> iii;
typedef vector<ii> vii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vvi;

bool sortcol( const vector<ll>& v1, 
               const vector<ll>& v2 ) { 
 return v1[1] < v2[1]; 
} 

struct comparator{
    bool operator()( const ll &lhs,const ll &rhs)const{
        return lhs<rhs;
    }
};


/*
vi parent;
vi renk;
void initialise(){
    fori(i,1,n+1){parent[i]=i;}
    fori(i,1,n+1){renk[i]=1LL;}
}

ll find_set(ll p){
    if(parent[p]==p) return p;
    
    return parent[p]=find_set(parent[p]);
}

void set_union(ll x,ll y){
    ll a=find_set(x);
    ll b=find_set(y);
    if(a!=b){
        if(renk[a]<renk[b])
            swap(a,b);
        
        parent[b]=a;
        renk[a]+=renk[b];
    }
}
*/






int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	tc{
	    ll n,k;cin>>n>>k;
	    vi v(n);
	    ll arr[n];
	    fori(i,0,n){cin>>arr[i];v[i]=arr[i];}
	    
	    SORT(v);
	    ll q=v.size()-1;
	    vi ans;
	    
	    fori(i,0,n){
	        ll idx;
	        fori(j,0,n){
	            if(arr[j]==v[q]){idx=j;break;}    
	        }
	        
	        while(1){
	            if(idx==q)break;
	            
	            ans.pb(idx+1);
	            
	            if(idx+k<n)
	                sort(arr+idx,arr+idx+k);
	            else
	                sort(arr+idx,arr+n);
	            
	            if(idx+k>=n)break;
	            
	            idx=idx+k-1;
	            
	        }
	        
	        q--;
	    }
	    
	    
	    cout<<ans.size()<<"\n";
	    fori(i,0,ans.size()){cout<<ans[i]<<" ";}
	    if(ans.size()!=0)cout<<"\n";
	    
	    
	}
	
	
	return 0;
}
