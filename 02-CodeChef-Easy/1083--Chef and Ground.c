#include <stdio.h>
//using namespace std;
typedef long long ll;
#define endl "\n"
#define pb push_back
ll m = 10000009;
#define time cerr<<"Time Taken:"<<(float)clock()/CLOCKS_PER_SEC<<"s"<<endl
//#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);

void solve();

int main()
{
    //fast
    ll t=1;
    scanf("%lld",&t);
    while(t--){
        solve();
    }
}

void solve()
{
    ll n,m,max=0,sum=0;
    scanf("%lld%lld",&n,&m);
    ll he[n];
    for(ll i=0;i<n;i++){
        scanf("%lld",&he[i]);
        if(he[i]>max)
        max=he[i];
    }
    for(ll i=0;i<n;i++){
           sum +=max-he[i];
    }
    if((m-sum)%n==0&&m-sum>=0)
    printf("Yes\n");
    else
    printf("No\n");
}

