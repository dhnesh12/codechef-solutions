#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define tii tuple<int,int,int>
#define fi first
#define se second
#define bp __builtin_popcount
#define nmax 200010
#define pb emplace_back

int getbit(ll x,int y)
{
    return (x>>y)&1;
}
ll getoff(ll x,int y)
{
    return x^((1ll)<<y);
}
const ll oo=1e9+7;
using namespace std;
int n,m,res,q,p[nmax];
ll base=311,power[nmax];
ll st[2][4*nmax],ht[nmax];
vector<int> lab[nmax];
void update(int j,int i,ll val)
{
    for (;i<=n;i+=i&(-i))
    {
        st[j][i]=st[j][i]+val;
        if (st[j][i]>=oo) st[j][i]-=oo;
    }
}
ll get(int j,int i)
{
    ll ans=0;
    for (;i>=1;i-=i&(-i))
    {
        ans=ans+st[j][i];
        if (ans>=oo) ans-=oo;
    }
    return ans;
}
ll gt(int j,int l,int r)
{
    return (get(j,r)-get(j,l-1)*power[r-l+1]+oo*oo)%oo;
}
void xuly(int x,int y)
{
    p[x]=y; lab[y].pb(x);

    ll cha1=(y-ht[x]+oo)*power[x]%oo; ll cha2=(y-ht[x]+oo)*power[n-x+1]%oo;
    ht[x]=y;
    update(0,x,cha1);
    update(1,x,cha2);
}
bool unite(int x,int y)
{
    x=p[x]; y=p[y];
    if (x==y) return 0;

    if (lab[x].size()>lab[y].size()) swap(x,y);
    for (int u:lab[x]) xuly(u,y);
    return 1;
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    power[0]=1;
    for (int i=1;i<=200000;++i) power[i]=power[i-1]*base%oo;

    cin>>n>>q; res=n;
    for (int i=1;i<=n;++i)
    {
        p[i]=i;
        xuly(i,i);
    }

    while (q--)
    {
        int x,y; cin>>x>>y;

        while (x<y)
        {
            if (gt(0,x,y)==gt(1,n-y+1,n-x+1)) break;
            int l=1; int r=(y-x)/2;
            while (l<r)
            {
                int mid=(l+r)>>1;
                int tam1=x+mid-1; int tam2=y-mid+1;

                if (gt(0,tam1,tam2)==gt(1,n-tam2+1,n-tam1+1)) l=mid+1;
                else r=mid;
            }

            if (unite(x+l-1,y-l+1)) res--;
            x+=l; y-=l;
        }
        cout<<res<<'\n';
    }
    return 0;
}
