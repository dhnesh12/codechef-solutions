/*************************************************
*                                                *
*      ****     ***        **  ******  **  **    *
*    **   **  **   **      **  **       ** *     *
*    **       **   **   *****  ****      **      *
*    **   **  **   **  **  **  **        **      *
*    **   **  **   **  **  **  ******   *  **    *
*      ****     ***     *****  ******  **   **   *
*                                                *
**************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long       ll;
typedef vector<ll>      vi;
typedef pair<ll,ll>     pii;
typedef map<ll,ll >     mii;
typedef set<ll>         si;
typedef complex<double> Point;
#define fast            ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define rep(i,a,r)      for(int i=a;i<r;i++)
#define rrep(i,a,r)     for(int i=r-1;i>=a;i--)
#define all(a)          a.begin(),a.end()
#define memset(dp)      memset(dp,0,sizeof(dp))
#define pb              push_back
#define F               first
#define S               second
#define sum(a)          accumulate(all(a),(ll)0)
#define lbnd            lower_bound
#define ubnd            upper_bound
#define bs              binary_search
#define er              equal_range
#define mkp             make_pair
#define strup(s)        transform(s.begin(),s.end(),s.begin(), ::toupper)
#define strlow(s)       transform(s.begin(),s.end(),s.begin(), ::tolower)
#define endl            '\n'
#define mod             1000000007
#define hell            998244353LL

#define print(a,n)    rep(i,0,n) cout<<a[i]<<endl;
#define enter(a,n)    rep(i,0,n) cin>>a[i];

//int prime[500001]={0};
//void PrimeNumbers()
//{
//    for(int i=2;i<500001;i++)
//        if(prime[i]==0)
//        for(int j=i;j<500001;j+=i)
//        if(prime[j]==0)
//        prime[j]=i;
//}

//ll pow(ll a,ll p,ll m )
//{
//    if(p==0)
//        return 1;
//    if(p%2)
//        return (a* ((pow((a*a)%m,p/2,m))%m))%m;
//    return ((pow((a*a)%m,p/2,m))%m);
//}

/*_____________________DID U MISS ME ?_______________________*/

ll l,r,n,k;
vi fib(100000,0);
map<ll,string> gn;
ll cnt;
void solve()
{
    cin>>l>>r>>n;
    auto a= lower_bound(fib.begin(),fib.begin()+k,l);
    auto b= lower_bound(fib.begin(),fib.begin()+k,r);
    if(r != *b ){
        b--;
    }
    if((b-a+1)<n) cout<<-1<<endl;
    else
    {
        auto x = a + n -1  ;
        cout<< (*x) <<" "<< gn[(*x)] << endl;
    }

}
void prod(ll x,string p){
    //cout<<x<<" "<< p <<endl;
    gn[x]=p;
    rep(i,2,cnt){
        if( x*fib[i] <= 100000000 )
        {
            if( gn.find(x*fib[i]) == gn.end() )
            {
                //cout<< x*fib[i] << endl;
                prod(x*fib[i],gn[x]+"#"+gn[fib[i]]);
            }
        }
        else
        return;
    }
}
int main()
{
    fast;
    //PrimeNumbers();
    int t=1;
    cin>>t;
    cnt = 2;
    gn.clear();
    gn[0]="#";
    gn[1]="..";
    fib[0]=1;fib[1]=1;
    rep(i,2,100000)  {
        fib[i] = fib[i-1] + fib[i-2] ;
        if(fib[i]> 100000000 ) {
            break;
        }
        cnt++;
        gn[fib[i]]=gn[fib[i-1]]+".";
    }
    gn[1]=".";
    rep(i,2,cnt)
        prod(fib[i],gn[fib[i]]);
    k=0;
    for( auto i=gn.begin();i!=gn.end();i++)
    {
        fib[k++] = (*i).first;
    }
//    rep(i,0,100)
//    cout<< fib[i] << " "<<gn[fib[i]]<<endl;
    while(t--)
    {
        solve();
    }
    return 0;
}
