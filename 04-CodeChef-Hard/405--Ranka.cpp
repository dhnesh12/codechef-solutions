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

const int N=15;
int ara[N][N];
vpi res;
int sz=10;
int ox=0,oy=0;
void print()
{
    for(int i=1;i<sz;i++)
    {
        for(int j=1;j<sz;j++)cout<<ara[i][j];
        cout<<endl;
    }
    cout<<endl;
}
void add(int i,int j)
{
    for(int k=sz-1;k>=1;k--){
        for(int l=sz-1;l>=1;l--){
            if(k==ox&&l==oy)continue;
            if(i==k&&j==l)continue;
            res.pb(MP(k,l));
//            ara[k][l]=res.size()%2;
//            print();
            res.pb(MP(0,0));
        }
    }
    res.pop_back();

}
int main()
{
    IOS;
    memset(ara,-1,sizeof ara);
    for(int i=1;i<sz;i++){
        for(int j=1;j<sz;j++){
            add(i,j);
            res.pb(MP(i,j));
//            memset(ara,-1,sizeof ara);
//            ara[i][j]=res.size()%2;
            res.pb(MP(0,0));
            ox=i,oy=j;
//            print();
        }
    }
    int n;cin>>n;
//    cout<<res.size()<<endl;
    for(int i=0;i<n;i++)cout<<res[i].ff<<" "<<res[i].ss<<endl;
}

