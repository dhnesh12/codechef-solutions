using namespace std;
#include <bits/stdc++.h>
#include <iostream>


#define 		mod 				998244353
#define 		FastRead 			ios_base::sync_with_stdio(false);cin.tie(0),cout.tie(0)
#define 		ll 					long long int
#define 		ld					long double
#define 		vi					vector<ll>
#define			pi 					pair<ll,ll>
#define			vpi					vector<pi>
#define 		mp					make_pair
#define			pb                  push_back
#define 		F                   first
#define         S 					second
#define 		f(i,a,b)			for(ll i=a;i<b;i++)
#define 		rep(i,n) 			f(i,0,n)
#define 		fd(i,a,b)			for(ll i=a;i>=b;i--)
#define			get_mod(a)			(mod+(a%mod))%mod			


// ll m_neg(ll a){
//  return(mod + (a%mod)) % mod;
// }
long long int binary_expo(long long int base,long long int pw){
    long long int res = 1;
    while(pw){
        if(pw%2){
            res*=base;
            res%=mod;
            pw-=1;
        }
        else{
            base*=base;
            base%=mod;
            pw/=2;
        }
    }
    return res;
}

long long int mod_inv(long long int k){ return binary_expo(k,mod-2);}

int t;

int main() {
    FastRead;
    cin>>t;

    while(t--){
    	ll n;
    	cin>>n;
    	vi v(n);
    	vi freq(100005,0ll);

    	rep(i,n){
    		cin>>v[i];
    		if(v[i]<=100001)freq[v[i]]++;
    	}

    	ll ans = binary_expo(2,n-freq[1])%mod;
    	// cout<<ans<<endl;
    	vi presum(100005,0ll);

    	rep(i,100002){
    		presum[i] = freq[i];
    		if(i>0)presum[i]+=presum[i-1];
    	}
    	ll mul = 1;
    	f(i,1,100001){
    		if(freq[i]==0)break;
    		
    		mul= ((mul%mod) * ((binary_expo(2,freq[i])-1)%mod))%mod;

    		ll tmp = (mul*binary_expo(2,n-presum[i+1]))%mod;
    		tmp = ((i+1)*tmp)%mod;
    		ans+=tmp;
    		ans = ans%mod;

    	}
    	cout<<ans<<"\n";
    }
	return 0;
}



/*
DONT GET STUCK AT ONE APPROACH! 
Dont get stuck at one problem read all problems till at least D.
Try to see pattern by writing it down.
*/



