

#include<bits/stdc++.h>
using namespace std;

#define inf 1001000009
#define infmx 1e18
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define MP make_pair
#define IOS ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define all(x) x.begin(),x.end()
///debug
#define wh(x)   cerr<<#x<<" is "<<x<<endl;
#define error(args...){string _s=#args;replace(_s.begin(),_s.end(),',',' ');stringstream _ss(_s);istream_iterator<string> _it(_ss);err(_it,args);}
void err(istream_iterator<string>it){cout<<endl;}
template<class H,class... T>void err(istream_iterator<string>it,H a,T... t){cerr<<*it<<" = "<<a<<" | ";err(++it,t...);}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class T>auto&operator<<(ostream& os,vector<T>_v){bool a=1;for(auto x:_v){os<<(a?"":" ")<<x;a=0;}return os;}
///
typedef pair<int,int>pi;
typedef pair<long long,long long>pll;
typedef pair<pi,int>ppi;
typedef pair<int,pi>pip;
typedef vector<int>vi;
typedef vector<pi>vpi;
const int mod=1e9+7;
ll power(ll a,ll p){ll r=1,y=a;while(p){if(p&1)r=(1LL*r*y)%mod;p>>=1;y=(1LL*y*y)%mod;}return r;}

const int N=2100;
int ara[N];
int A[N],B[N],f1[N],f2[N];
int n;
bool used[N];
int dp[N][N];
vi v;
int sz=2001;
void build()
{
    for(int i=2;i<=sz;i++){
        for(int m=2;m<=sz;m++){
            if(i-m>=0)
                dp[i][m]=m-1+dp[i-m][m];
            if(i-m-1>=0)
                dp[i][m]=max(dp[i][m],m+dp[i-m-1][m]);
//                error(i,m,dp[i][m]);
        }
    }
}
int func(int p)
{
    int cur=A[p];
    int cyc=B[p],cnt=1;
    used[cur]=1;
//    error(cur,f1[cur]);
    while(cur!=cyc){
        cur=f2[cur];
        cnt++;
//        error(cur,f1[cur],cnt);
        used[cur]=1;
    }
    return cnt;
}
int res[N];
int check_top()
{
//    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)res[i][j]=0;
    for(int i=0;i<=n;i++)res[i]=0;
    v.clear();
    for(int i=1;i<=n;i++){
        if(used[A[i]]==0)
            v.pb(func(i));
    }
//    cerr<<v<<endl;

    for(auto x:v){
        for(int m=x;m>=2;m--){
            res[m]+=dp[x][m];
//            error(x,m,dp[x][m],res[m]);
        }
    }

    int ans=0;
    for(int i=2;i<=n;i++)
        ans=max(ans,res[i]);
    return ans;
}
int main()
{
    IOS;
    build();
    int t;cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)cin>>A[i];
        for(int i=1;i<=n;i++)cin>>B[i];
        for(int i=0;i<=n+6;i++)used[i]=0;
        int ex=0;
        for(int i=1;i<=n;i++){
            if(A[i]==B[i]){
                used[A[i]]=1;
                ex++;
            }
            else{
                f1[A[i]]=B[i];
                f2[B[i]]=A[i];
            }
        }
        int f=check_top();
        int ans=ex;
        ans=max(ans,f);
        cout<<ans<<endl;
        v.clear();
    }
}
/*
15
5
1 2 3 4 5
1 2 3 4 5
10
1 2 3 4 5  6 7 8 9 10
5 1 10 3 2 7 8 9 6 4

5
1 2 3 4 5
2 1 3 5 4

*/
