#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct segment
{
    ll value;
    ll lazy;
};
segment st[4000001];
void build(ll id,ll l,ll r,ll k)
{
    if (l==r)
    {
        st[id].value=k;
        return;
    }
    ll mid=(l+r)/2;
    build(id*2,l,mid,k);
    build(id*2+1,mid+1,r,k);
    st[id].value=st[id*2].value+st[id*2+1].value;
}
void update(ll id,ll l,ll r,ll u,ll v,ll k)
{
    if (st[id].lazy!=0)
    {
        ll t=st[id].lazy;
        st[id].value+=(r-l+1)*t;
        if (l!=r)
        {
            st[id*2].lazy+=t;
            st[id*2+1].lazy+=t;
        }
        st[id].lazy=0;
    }
    if ((l>v)||(r<u))
        return;
    if ((l>=u)&&(r<=v))
    {
        st[id].value+=(r-l+1)*k;
        if (l!=r)
        {
            st[id*2].lazy+=k;
            st[id*2+1].lazy+=k;
        }
        return;
    }
    ll mid=(l+r)/2;
    update(id*2,l,mid,u,v,k);
    update(id*2+1,mid+1,r,u,v,k);
    st[id].value=st[id*2].value+st[id*2+1].value;
}
ll get_result(ll id,ll l,ll r,ll pos)
{
    if ((pos<l)||(pos>r))
        return 0;
    if (st[id].lazy!=0)
    {
        ll t=st[id].lazy;
        st[id].value+=(r-l+1)*t;
        if (l!=r)
        {
            st[id*2].lazy+=t;
            st[id*2+1].lazy+=t;
        }
        st[id].lazy=0;
    }
    if (l==r)
        return st[id].value;
    ll mid=(l+r)/2;
    ll x=get_result(id*2,l,mid,pos);
    ll y=get_result(id*2+1,mid+1,r,pos);
    return x+y;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n,m,c;
    cin >> n >> m >> c;
    build(1,1,n,c);
    while (m--)
    {
        char q;
        cin >> q;
        if (q=='S')
        {
            ll u,v,k;
            cin >> u >> v >> k;
            update(1,1,n,u,v,k);
        }
        if (q=='Q')
        {
            ll p;
            cin >> p;
            cout << get_result(1,1,n,p) << '\n';
        }
    }
}
