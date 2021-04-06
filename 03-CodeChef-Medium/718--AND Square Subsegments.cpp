#include <bits/stdc++.h>
using namespace std;
#define int long long
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r){return l+rng()%(r-l+1);}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0);
#define fori(x,a,b) for (int x=a;x<=b;x++)
#define ford(x,a,b) for (int x=a;x>=b;x--)
#define forv(a,b) for(auto&a:b)
#define fi first
#define se second
#define pb push_back
#define ii pair<int,int>
#define mt make_tuple
#define mp make_pair
#define all(a) a.begin(),a.end()
#define reset(f, x) memset(f, x, sizeof(f))
#define getbit(x,i) ((x>>(i-1))&1)
#define batbit(x,i) (x|(1ll<<(i-1)))
#define tatbit(x,i) (x&~(1<<(i-1)))
#define gg exit(0);
const int maxn = 1e5 + 10;
int a[maxn],n,t,q,l,r;
int f[maxn][25],ans[5*maxn];
vector<ii> ke[maxn];
void rmq(int n)
{
    fori(i,1,n) f[i][0] = a[i];
    fori(k,1,log2(k))
    {
        for (int i=1;i+(1<<k)-1<=n;i++)
        f[i][k] = f[i][k-1]&f[i+(1<<(k-1))][k-1];
    }
}

int va(int l,int r)
{
    int k = (int)log2(r-l+1);
    return (f[l][k]&f[r-(1<<k)+1][k]);
}

int lazy[4*maxn],s[4*maxn];
void trans(int x,int l,int r)
{
    if (lazy[x]!=0)
    {
         int p = lazy[x];
        int mid = (l+r)/2;
        s[2*x]+=(mid-l+1)*p;
        s[2*x+1]+=(r-mid)*p;
        lazy[2*x]+=p;
        lazy[2*x+1]+=p;

        lazy[x] = 0;
    }

}
void up(int x,int l,int r,int u,int v,int val)
{
   if (l > v || r < u) return;
   if (l>=u && r<=v)
   {
       s[x]+=(r-l+1)*val;
       lazy[x]+=val;
       return;
   }
   trans(x,l,r);
   int mid = (l+r)/2;
   up(2*x,l,mid,u,v,val);
   up(2*x+1,mid+1,r,u,v,val);
   s[x] = s[2*x] + s[2*x+1];
}


int get(int x,int l,int r,int u,int v)
{
    if (l > v || r < u) return 0;
    if (l>=u && r<=v) return s[x];
    trans(x,l,r);
    int mid = (l+r)/2;
    return get(2*x,l,mid,u,v) + get(2*x+1,mid+1,r,u,v);
}
int cp(int x)
{
    int m = sqrt(x);
    return (m*m==x);
}
main()
{
    fasty;
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        fori(i,1,n) cin>>a[i];
        fori(i,0,n+1) ke[i].clear();
        reset(ans,0);
        reset(s,0);reset(lazy,0);
        fori(i,1,q)
        {
            cin>>l>>r;
            ke[l].pb({r,i});
        }

        rmq(n);
        ford(i,n,1)
        {
            int pos = i,tmp = a[i];
            while(pos<=n)
            {
                int l = pos,r = n,kq = pos;
                while(l<=r)
                {
                    int mid = (l+r)/2;
                    if (va(i,mid)==tmp)
                    {
                        kq = mid;
                        l = mid+1;
                    }
                    else r = mid-1;
                }
                if (cp(tmp)) up(1,1,n,pos,kq,1);
                if (kq < n)
                {
                    pos = kq+1;
                    tmp = tmp&a[kq+1];
                }
                else break;
            }
            forv(v,ke[i]) ans[v.se]+=get(1,1,n,i,v.fi);

        }

        fori(i,1,q)
        cout<<ans[i]<<"\n";
        cout<<"\n";
    }
}


