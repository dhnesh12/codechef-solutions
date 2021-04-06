#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip> 
//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val
 
using namespace std;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define fd(i,a,b) for(i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define vi vector< int >
#define vl vector< ll >
#define ss second
#define ff first
#define ll long long
#define pii pair< int,int >
#define pll pair< ll,ll >
#define sz(a) a.size()
#define inf (1000*1000*1000+5)
#define all(a) a.begin(),a.end()
#define tri pair<int,pii>
#define vii vector<pii>
#define vll vector<pll>
#define viii vector<tri>
#define mod (163577857)
#define pqueue priority_queue< int >
#define pdqueue priority_queue< int,vi ,greater< int > >
#define MAXN 100000
ll mat[40][210][210],res[210],res1[210],a[210],coef[210];
ll k;
 
ll computematr(ll val){
	ll i,j,p;
	rep(i,k+1){
		rep(j,k+1){
			rep(p,k+1){
				mat[val][i][j]+=mat[val-1][i][p]*mat[val-1][p][j];
				mat[val][i][j]%=mod;
			}
		}
	}
	return 0;
}
//std::ios::sync_with_stdio(false);   
ll getallmatrices(){
	ll i,j,p;
	rep(i,40){
		rep(j,110){
			rep(p,110){
				mat[i][j][p]=0;
			}
		}
	}
 
	mat[0][0][0]=1;
	//cout<<mat[0][1][0]<<endl;
	f(i,1,k+1){
		//cout<<mat[0][1][0]<<endl;
		mat[0][0][i]=coef[i];
		mat[0][1][i]=coef[i];
	}
 
	f(j,2,k+1){
		mat[0][j][j-1]=1;
	}
 
	f(i,1,40){
		computematr(i);
	}
 
}
ll matrixmult(ll res[110],ll val){
	ll i,j;
	rep(i,k+1){
		res1[i]=0;
		rep(j,k+1){
			res1[i]+=mat[val][i][j]*res[j];
			res1[i]%=mod;
		}
	}
	rep(i,k+1){
		res[i]=res1[i];
	}
	return 0;
}
ll pre[210],pos[MAXN];
ll getsum(ll val){
	if(val<=k){
		return pre[val];
	}
	val-=k;
	res[0]=pre[k];
	int i;
	f(i,1,k+1){
		res[i]=a[k-i+1];
	}
	i=0;
 
	while(val>0){
		if(val%2){
			matrixmult(res,i);
		}
		i++;
		val/=2;
 
	}
	return res[0];
 
}
ll extend_gcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll x1,y1;
	ll ans =extend_gcd(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
 
	return ans;
}
int main(){
    std::ios::sync_with_stdio(false);
    ll t;
    //cin>>t;
    t=1;
    while(t--){
    	ll n,h,x;
    	cin>>n>>h>>x>>k;
    	ll i,j,p;
    	rep(i,n){
    		cin>>pos[i];
    	}
    	pre[0]=0;
    	f(i,1,k+1){
    		cin>>a[i];
    		pre[i]=pre[i-1]+a[i];
    		pre[i]%=mod;
    	}
    	f(i,1,k+1){
    		cin>>coef[i];
    	}
    	getallmatrices();
    	
    	ll ans,total=0;
    	ll valued=getsum(h);
    	rep(i,n){
    		ans=getsum(pos[i]);
    		if(pos[i]>x){
    			ans-=getsum(pos[i]-x);
    		}
    		else if(pos[i]<x){
    			ans+=valued-getsum(h+pos[i]-x);
 
    		}
    		//cout<<ans<<endl;
    		total+=ans;
    		total%=mod;
 
    	}
    	total+=mod;
    	total%=mod;
    	//cout<<getsum(102)<<endl;
    	//cout<<total<<endl;
    	if(valued!=0){
    		ll aa,bb;
    		extend_gcd(mod,valued,aa,bb);
    		bb%=mod;
    		bb+=mod;
    		bb%=mod;
    		total*=bb;
    		total%=mod;
    		cout<<total<<endl;
    	}
    	else{
    		cout<<"Booo"<<endl;
    		//cout<<total<<endl;
    		//cout<<valued<<endl;
    	}
 
    	
 
    }
    return 0;  
    
}
 
 