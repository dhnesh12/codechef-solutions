#include"bits/stdc++.h"
#define ll long long
#define MX 100010
using namespace std;
ll tr[4*MX];
ll a[MX+2];
void build(ll pos, ll st, ll ed)
{
    if(st==ed)
    {
        tr[pos]=a[st];
        return;
    }
    ll mid = st+((ed-st)>>1);
    build(2*pos,st,mid);
    build(2*pos+1,mid+1,ed);
    tr[pos]=max(tr[2*pos],tr[2*pos+1]);
}
void update(ll pos,ll st, ll ed, ll x, ll val)
{
    if(st==ed )
    {
        tr[pos]=val;
        return;
    }
    ll mid = st+((ed-st)>>1);
    if(x<=mid)
        update(2*pos,st,mid,x,val);
    else
        update(2*pos+1,mid+1,ed,x,val);
    tr[pos]=max(tr[2*pos],tr[2*pos+1]);
}
ll query(ll pos, ll st, ll ed, ll l, ll r)
{
    if(st>r||ed<l)
        return 0;
    if(st>=l && ed<=r)
    {
        return tr[pos];
    }
    ll mid = st+((ed-st)>>1);
    return max(query(2*pos,st,mid,l,r),query(2*pos+1,mid+1,ed,l,r));
}
map<ll,ll>mp,num;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n,m;
        cin >> n >> m;
        ll sm = 0;
        mp.clear();
        num.clear();
        for(int i=1; i<=n; i++)
        {
            cin >> a[i];
            num[a[i]]=i;
            sm+=a[i];
        }
        build(1,1,n);
        set<ll>st;
        for(int i=1; i<=m; i++)
        {
            int l,r;
            cin >> l >> r;
            ll p = query(1,1,n,l,r);
            if(p==0)continue;
            mp[p]++;
            if(mp[p]==1)
            {
                st.insert(p);
            }
            else
            {
                st.erase(p);
                sm-=p;
                update(1,1,n,num[p],0);
                while(true)
                {
                    p = query(1,1,n,l,r);
                    if(p==0)break;
                    mp[p]++;
                    if(mp[p]==1)
                    {
                        st.insert(p);
                        break;
                    }
                    else
                    {
                        st.erase(p);
                        sm-=p;
                        update(1,1,n,num[p],0);
                    }
                }
            }
        }
        ll p = 0;
        for(auto u : st)
        {
            sm-=u;
            p = max(p,u);
        }
        sm+=p;
        cout << sm << "\n";
    }
    return 0;
}

