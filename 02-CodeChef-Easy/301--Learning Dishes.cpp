#include <bits/stdc++.h>
#define MAX 1000005
#define ll long long
#define upperlimit 1000100
#define INF 1e18
#define eps 1e-8
#define endl '\n'
#define pcc pair<char,char>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define tr(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define MOD 1000000007LL
#define slld(t) scanf("%lld",&t)
#define sd(t) scanf("%d",&t)
#define pd(t) printf("%d\n",t)
#define plld(t) printf("%lld\n",t)
#define mp(a,b) make_pair(a,b)
#define FF first
#define SS second
#define pb(x) push_back(x)
#define vi vector<int>
#define vll vector<ll>
#define clr(a) memset(a,0,sizeof(a))
#define debug(a) printf("check%d\n",a)
#define csl ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
 
ll gcd(ll n1,ll n2){
    if(n2==0)
        return n1;
    if(n1%n2==0)return n2;
    return gcd(n2,n1%n2);
}
ll powmod(ll base,ll exponent)
{
    if(exponent<0) exponent+=MOD-1;
    ll ans=1;
    while(exponent){
        if(exponent&1)ans=(ans*base)%MOD;
        base=(base*base)%MOD;
        exponent/=2;
    }
    return ans;
}
int bc[1000002][21];
int arr[MAX];
int p[MAX];
std::vector<int> v[MAX];
void DFS(int n,int maxi)
{
    bc[n][0]=maxi;
    for(int i=1;i<=20;i++)
    {
        bc[n][i]=bc[bc[n][i-1]][i-1];
        // cout<<n<<" "<<i<<" "<<bc[n][i]<<endl;
    }
    if(arr[n]>arr[maxi])
        maxi=n;
    for(auto i:v[n])
    {
        DFS(i,maxi);
    }
}
int main()
{
     csl;
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            v[i].clear();
            cin>>arr[i];
        }
        for(int i=2;i<=n;i++)
        {
            cin>>p[i];
            v[p[i]].pb(i);
        }
        DFS(1,0);
        int q;
        cin>>q;
        int ans=0;
        while(q--)
        {
            int a,b;
            cin>>a>>b;
            int v=a^ans;
            int w=b^ans;
            ans=0;
            if(w>max(arr[bc[v][0]],arr[v]))
            {
                cout<<0<<endl;
                continue;
            }
            int vv=v;
            // cout<<v<<" "<<w<<endl;
            // cout<<bc[v][20]<<endl;
            for(int i=20;i>=0;i--)
            {
                if(bc[v][i]!=0)
                {
                    if(arr[bc[v][i]]>w)
                    {
                        // debug(i);
                        v=bc[v][i];
                        ans+=(1<<i);
                    }
                }
            }
            // debug(ans);
            // cout<<arr[vv]<<endl;
            // cout<<max(w,arr[bc[vv][0]])<<endl;
            if(arr[vv]>max(w,arr[bc[vv][0]]))
                ans++;
            cout<<ans<<endl;
        }
    }
}