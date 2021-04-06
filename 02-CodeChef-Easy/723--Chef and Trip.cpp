// Premature optimization is the root of all evil in programming - Knuth.

#include <bits/stdc++.h>

using namespace std;

typedef int ll;

#define mod (int) (1e9+7)

ll gcd(ll a, ll b){
	
	if(b==0){

	   return a;
	}
	
	return gcd(b, a%b);
	
}
 
 ll ncr(ll x, ll y){
 	ll ans=1;
 	
 	y=(y > x-y? x-y: y);
 	
 	for(ll i=0; i<y; i++){

 		ans=ans*(x-i);

 		ans=ans/(i+1);

 		ans=ans%mod;
 	}
 
 	return ans;
 }

ll power(ll x, ll y){

    ll ans=1;

    while(y){

        if(y&1){

            ans=ans*x;

            ans=ans%mod;

        }
        
        x=x*x;

        x=x%mod;

        y=y>>1;
    }
    
    return ans;
    
}

vector<ll> res;

ll dp[100005][8];

ll recur(vector<ll> &vec,ll index,ll n,ll k){
	
	if(index==n){
		
		bool flag=false;
		
		if(vec[index]==-1){
			flag=true;
			if(vec[index-1]==1){
				vec[index]=2;
			}
			else{
				vec[index]=1;
			}
		}
		
		if(vec[index]==vec[index-1]){
			if(flag)
			vec[index]=-1;
			return 0;
		}
		
		res=vec;
		
		if(flag){
			vec[index]=-1;
		}
		
		return 1;
		
	}
	
	if(vec[index]==vec[index-1]){
		return 0;
	}
	
	if(vec[index]==-1){
		
		ll val=0;
		
		for(int i=1; i<=k; i++){
			
			for(int i=1; i<=k; i++){
				if(dp[index][i]==1){
					return 1;
				}
			}
			
			if(i!=vec[index-1]){
				
				vec[index]=i;
				
				dp[index][i]=recur(vec,index+1,n,k);
				
				val=max(val,dp[index][i]);
				
			}
			
		}
		
		vec[index]=-1;
		
		return val;
		
	}
	else{
		
		return recur(vec,index+1,n,k);
		
	}
	
}


void solve(){
	
	ll n,k; cin>>n>>k;
	
	vector<ll> vec(n+1); vec[0]=0;
	
	for(int i=0; i<n; i++){
		cin>>vec[i+1];
	}
	
	if(n==1){
		if(vec[1]==-1){
			vec[1]=1;
		}
		cout<<"YES\n";
		cout<<vec[1]<<"\n";
		return;
	}
	
	memset(dp,-1,sizeof(dp));
	
	k=min(k,4); res.clear();
	
	ll val=recur(vec,1,n,k);
	
	if(val){
		cout<<"YES\n";
		for(int i=1; i<res.size(); i++){
			cout<<res[i]<<" ";
		}cout<<"\n";
		
		return;
	}
	
	cout<<"NO\n";
	return;
	
}




int main(){
    ios_base::sync_with_stdio(0);
    
    cin.tie(0);
    
    int t=1;cin>>t;
   
    // clock_t begin, end;
    
    // double time_spent;
    
    // begin = clock(); // Time taken till now.
    
    while(t--){
    
	  solve();
        
    }
    
   //end= clock(); // Total  Time taken till now.
   
   //time_spent= (end- begin) / CLOCKS_PER_SEC; 
   
   //cout<<time_spent<<"\n";
   
	return 0;
}

