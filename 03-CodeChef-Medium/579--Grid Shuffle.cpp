    #include<bits/stdc++.h>
    using namespace std;
    
    //                                 (POLICY BASED DS)
    // #include <ext/pb_ds/assoc_container.hpp>
    // #include <ext/pb_ds/tree_policy.hpp>
    // using namespace __gnu_pbds;
    // template<typename T>
    // using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
    // template<typename T>
    // using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
    //                      ( find_by_order( )  ,  order_of_key( ) )
    
    typedef long long ll;
    typedef long double ld;
    typedef unsigned long long ull;
    typedef vector<long long> vll;
    typedef pair<ll,ll> pll;
     
    const ll mod = 998244353;
    const ld PI = 3.1415926535897932384626;
    const ld eps = 1e-9;                            
     
    #define boost ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
    #define sidha(i,a,b) for(ll i=(ll)(a);i<(ll)(b);++i)
    #define ulta(i,a,b) for(ll i=(ll)(a);i>=(ll)(b);--i)
    #define stl(container,itr) \
        for(auto itr = container.begin(); itr != container.end(); itr++)
    #define sab(v) v.begin(), v.end()
    #define rall(v) v.rbegin(), v.rend()            
    #define test ll t;cin>>t;while(t--)
    #define sz size()
    #define pb push_back
    #define mp make_pair
    #define fi first
    #define se second
    #define LOG2(X) (63ll - __builtin_clzll(X))
    #define endl '\n'
    #define modinv(x) powermod(x, mod-2)
    #define mktree(x) ll a,b; sidha(i,0,x){cin>>a>>b; adj[a].pb(b); adj[b].pb(a);}
    #define ncr(n,r) ( (n) >= (r) ? ((((fact[n]*modinv(fact[r]))%mod)*modinv(fact[n-(r)]))%mod) : (ll)0)
    #define MAX 100005
     
    ll powermod(ll x, ll y) { 
        ll ans=1;
        x=x%mod;
        while(y>0) { 
            if (y&1) 
                ans=(ans*x)%mod; 
            y=y>>1;
            x=(x*x)%mod; 
        } 
        return ans; 
    }
    
    ll power(ll x, ll y) { 
        ll ans=1;
        while(y>0) { 
            if (y&1) 
                ans=(ans*x); 
            y=y>>1;
            x=(x*x); 
        } 
        return ans; 
    }
    
    ll gcd(ll x,ll y){
       if(y==0) return x;
       return   gcd(y,x%y);
    }
    
    ll ceil(ll x,ll y){
        return ( (x/y)+(x%y!=0) );
    }
    
    // vector<ll> adj[MAX];
    // ll visit[MAX];
    // void dfs(ll node){
    //     visit[node]=1;
    //     for(auto i : adj[node]){
    //         if(!visit[i]) dfs(i);
    //     }
    // }
    
    // ll spf[MAX];
    // void sieve(){
    //     sidha(i,1,MAX)  spf[i]=i;
    //     for(ll i=4;i<MAX;i+=2)  spf[i]=2;
    //     for(ll i=3;i*i<=MAX;i++){
    //         if(spf[i]==i){
    //             for(ll j=i*i;j<MAX;j+=i){
    //                 if(spf[j]==j)   spf[j]=i;
    //             }
    //         }
    //     }
    // }
    
    //                 use pow , ceil , max , min with precaution :)
    int main()
    {
        boost;
        clock_t begin,end;
        begin=clock();
        
        test{
            ll n,k,r,c,temp;
            cin>>n>>k>>r>>c;
            if(n==1){
                cout<<"1\n";
                continue;
            }
            ll dp[k+1][2][2];
            dp[0][0][0]=1;
            dp[0][0][1]=dp[0][1][0]=dp[0][1][1]=0;
            sidha(i,1,k+1){
                // for 0 0
                temp=((dp[i-1][0][0]*(n*2-2))%mod);
                temp=((temp*modinv(n*2))%mod);
                dp[i][0][0]=temp;
                temp=dp[i-1][0][0];
                temp=((temp*modinv(n*n))%mod);
                dp[i][0][0]=((dp[i][0][0]+temp)%mod);
                temp=((dp[i-1][0][1]+dp[i-1][1][0])%mod);
                temp=((temp*modinv(n*n*2))%mod);
                dp[i][0][0]=((dp[i][0][0]+temp)%mod);
                
                // for 0 1
                
                temp=((dp[i-1][0][0]*(n-1))%mod);
                temp=((temp*modinv(n*n*2))%mod);
                dp[i][0][1]=temp;
                
                temp=((dp[i-1][0][1]*(n*2-2))%mod);
                temp=((temp*modinv(n*2))%mod);
                dp[i][0][1]=((dp[i][0][1]+temp)%mod);
                
                temp=(dp[i-1][0][1]);
                temp=((temp*modinv(n*2))%mod);
                dp[i][0][1]=((dp[i][0][1]+temp)%mod);
                
                temp=(dp[i-1][1][1]);
                temp=((temp*modinv(n*n*2))%mod);
                dp[i][0][1]=((dp[i][0][1]+temp)%mod);
                
                // for 1 0 
                dp[i][1][0]=dp[i][0][1];
                // for 1 1
                // temp=((dp[i-1][1][1]*(n*2-2))%mod);
                // temp=((temp*modinv(n*2))%mod);
                // dp[i][1][1]=temp;
                // temp=((dp[i-1][1][1]*(n*2-2))%mod);
                // temp=((temp*modinv(n*n))%mod);
                // dp[i][1][1]=((dp[i][1][1]+temp)%mod);
                // temp=((dp[i-1][0][1]+dp[i-1][1][0])%mod);
                // temp=((temp*(n-1))%mod);
                // temp=((temp*modinv(n*n*2))%mod);
                // dp[i][1][1]=((dp[i][1][1]+temp)%mod);
                temp=((((dp[i][0][0]+dp[i][0][1])%mod)+dp[i][1][0])%mod);
                temp=((1-temp+mod)%mod);
                dp[i][1][1]=temp;
            }
            cout<<dp[k][0][0]<<endl;
        }
        
        end=clock();
        double tot_time=double(end-begin)/double(CLOCKS_PER_SEC);
        // cout<<"Time Taken: "<<fixed<<setprecision(3)<<tot_time;
        return 0;
    }
    