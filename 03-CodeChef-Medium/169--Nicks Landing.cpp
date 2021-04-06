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
typedef pair<pi,int> ppi;
const int mod=1e9+7;
ll power(ll a,ll p){ll r=1,y=a;while(p){if(p&1)r=(1LL*r*y)%mod;p>>=1;y=(1LL*y*y)%mod;}return r;}

const int N=210000;
const int bsize=450;
pair<pi,int>ara[N];
pair<pi,int>qr[N];
ll ans[N];
int nxt[N],prv[N],pos[N],val[N];
int n,m;
ll sum=0;
bool comp(ppi p,ppi q)
{
    int x=p.ff.ff/bsize;
    int y=q.ff.ff/bsize;
    if(x==y)return p.ff.ss>q.ff.ss;
    return (x<y);
}
void add(int x)
{
//    error(x,pos[x],x);
    x=pos[x];
    nxt[prv[x]]=x;
    prv[nxt[x]]=x;
}
ll del(int x)
{
//    error(x,pos[x]);
    x=pos[x];
    int s2=prv[x];
    int s1=prv[prv[x]];
    int s3=x;
    int s4=nxt[x];
    int s5=nxt[nxt[x]];
    ll f1=val[s1],f2=val[s2],f3=val[s3],f4=val[s4],f5=val[s5];
    ll dif=0,d=0;
    if(f1)dif+=abs(f3-f1);
    if(f2&&f4)dif+=abs(f4-f2);
    if(f5)dif+=abs(f5-f3);

    if(f1&&f4)d+=abs(f4-f1);
    if(f2&&f5)d+=abs(f5-f2);
    prv[nxt[x]]=prv[x];
    nxt[prv[x]]=nxt[x];
//    error(x,nxt[x],prv[x],dif,d);
    return dif-d;
}
void start()
{
    for(int i=1;i<=n;i++){
        prv[i]=i-1;
        nxt[i]=i+1;
        pos[ara[i].ss]=i;
        val[i]=ara[i].ff.ss;
    }
    prv[n+1]=n;
    nxt[0]=1;
}

void solve()
{
    start();
    for(int i=3;i<=n;i++)sum+=abs(1ll*val[i]-val[i-2]);
    int cur_l=1;
    int cur_r=n;
    ll blk_ans=sum;
    int blk=0;
    ll dif=0;
//    error(sum);
    for(int i=1;i<=m;i++)
    {
        int l=qr[i].ff.ff;
        int r=qr[i].ff.ss;
        int cur_blk=l/bsize;
//        error(l,r,cur_blk,cur_l,cur_r);
        if(cur_blk>blk){            ///initiate this block to [l_block,n]
            int p=cur_blk*bsize;
            ll temp=0;
            while(cur_r<n)add(++cur_r);
            while(cur_l<p)temp+=del(cur_l++);
            blk_ans-=temp;
            blk=cur_blk;
            dif=0;
//            error(blk_ans,blk);
        }
        ll temp=0;
        int pv=cur_l;
        while(cur_r>r)dif+=del(cur_r--);
        while(cur_l<l)temp+=del(cur_l++);
        ans[qr[i].ss]=blk_ans-dif-temp;
//        error(dif,temp);
        while(cur_l>pv)add(--cur_l);            ///restore l to l_block
    }
}
int main()
{
    IOS;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>ara[i].ff.ff>>ara[i].ff.ss;
        ara[i].ss=i;
    }
    sort(ara+1,ara+n+1);
    cin>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>qr[i].ff.ff>>qr[i].ff.ss;
        qr[i].ss=i;
    }
    sort(qr+1,qr+m+1,comp);
//    for(int i=1;i<=m;i++)cout<<ara[i]<<endl;
    solve();
    for(int i=1;i<=m;i++)cout<<ans[i]<<endl;
}

/*
8
2 1
8 6
4 6
1 4
3 10
7 5
6 4
5 8

10
4 5
1 3
1 6
3 6
2 5
4 4
7 7
1 8
4 7
2 6

*/
