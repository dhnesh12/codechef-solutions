#include<bits/stdc++.h>
using namespace std;
#define ll long long int
struct node{
    ll init,mul,add;
};
void build(vector<ll> &st,int si,int lx,int rx,vector<ll> &arr,int mod)
{
    if (lx==rx)
    {
        st[si]=arr[lx];
        return;
    }
    int mid=lx+(rx-lx)/2;
    build(st,2*si+1,lx,mid,arr,mod);
    build(st,2*si+2,mid+1,rx,arr,mod);
    st[si]=(st[2*si+1]+st[2*si+2])%mod;
}
void propagation(vector<ll> &st,int si,int lx,int rx,vector<node> &lazy,int mod)
{
    if (lazy[si].init!=0LL)
    {
        st[si]=(lazy[si].init*(rx-lx+1))%mod;
        if (lx!=rx)
        {
            lazy[2*si+1].init = lazy[si].init;
            lazy[2*si+2].init = lazy[si].init;
            lazy[2*si+1].mul = 1LL;
            lazy[2*si+2].mul = 1LL;
            lazy[2*si+1].add = 0LL;
            lazy[2*si+2].add = 0LL;
        }
        lazy[si].init = 0LL;
    }
    if (lazy[si].mul!=1LL)
    {
        st[si] = (st[si]*lazy[si].mul)%mod;
        if (lx!=rx)
        {
            lazy[2*si+1].mul = (lazy[2*si+1].mul*lazy[si].mul)%mod;
            lazy[2*si+2].mul = (lazy[2*si+2].mul*lazy[si].mul)%mod;
            lazy[2*si+1].add = (lazy[2*si+1].add*lazy[si].mul)%mod;
            lazy[2*si+2].add = (lazy[2*si+2].add*lazy[si].mul)%mod;
        }
        lazy[si].mul=1LL;
    }
    if (lazy[si].add!=0LL)
    {
        st[si] = (st[si]+lazy[si].add*(rx-lx+1))%mod;
        if (lx!=rx)
        {
            lazy[2*si+1].add = (lazy[2*si+1].add+lazy[si].add)%mod;
            lazy[2*si+2].add = (lazy[2*si+2].add+lazy[si].add)%mod;
        }
        lazy[si].add = 0LL;
    }
}
void update(vector<ll> &st,int si,int lx,int rx,int l,int r,int v,vector<node> &lazy,int choices,int mod)
{
    //lazy propagation here
    propagation(st,si,lx,rx,lazy,mod);
    if (choices==1)//add
    {
        if (l>r)
        return;
        else if (lx==l && rx==r)
        {
            st[si] = (st[si]+1LL*v*(rx-lx+1))%mod;
            if (lx!=rx)
            {
                lazy[2*si+1].add = (lazy[2*si+1].add+1LL*v)%mod;
                lazy[2*si+2].add = (lazy[2*si+2].add+1LL*v)%mod;
            }
            return;
        }
        else
        {
            int mid=lx+(rx-lx)/2;
            update(st,2*si+1,lx,mid,l,min(mid,r),v,lazy,choices,mod);
            update(st,2*si+2,mid+1,rx,max(mid+1,l),r,v,lazy,choices,mod);
            st[si]=(st[2*si+1]+st[2*si+2])%mod;
            return;
        }
    }
    else if (choices==2)//mul
    {
        if (l>r)
        return;
        else if (lx==l && rx==r)
        {
            st[si]=(st[si]*v)%mod;
            if (lx!=rx)
            {
                lazy[2*si+1].mul = (lazy[2*si+1].mul*v)%mod;
                lazy[2*si+2].mul = (lazy[2*si+2].mul*v)%mod;
                lazy[2*si+1].add = (lazy[2*si+1].add*v)%mod;
                lazy[2*si+2].add = (lazy[2*si+2].add*v)%mod;
            }
            return;
        }
        else
        {
            int mid=lx+(rx-lx)/2;
            update(st,2*si+1,lx,mid,l,min(mid,r),v,lazy,choices,mod);
            update(st,2*si+2,mid+1,rx,max(mid+1,l),r,v,lazy,choices,mod);
            st[si]=(st[2*si+1]+st[2*si+2])%mod;
            return;
        }
    }
    else//init
    {
        if (l>r)
        return;
        else if (lx==l && rx==r)
        {
            st[si] = (1LL*v*(rx-lx+1))%mod;
            if (lx!=rx)
            {
                lazy[2*si+1].init = 1LL*v;
                lazy[2*si+2].init = 1LL*v;
                lazy[2*si+1].mul = 1LL;
                lazy[2*si+2].mul = 1LL;
                lazy[2*si+1].add = 0LL;
                lazy[2*si+2].add = 0LL;
            }
            return;
        }
        else
        {
            int mid=lx+(rx-lx)/2;
            update(st,2*si+1,lx,mid,l,min(mid,r),v,lazy,choices,mod);
            update(st,2*si+2,mid+1,rx,max(mid+1,l),r,v,lazy,choices,mod);
            st[si]=(st[2*si+1]+st[2*si+2])%mod;
            return;
        }
    }
}
ll get(vector<ll> &st,int si,int lx,int rx,int l,int r,vector<node> &lazy,int mod)
{
    propagation(st,si,lx,rx,lazy,mod);
    if (l>r)
    return 0LL;
    else if (lx==l && rx==r)
    return st[si];
    else
    {
        int mid=lx+(rx-lx)/2;
        ll val1=get(st,2*si+1,lx,mid,l,min(mid,r),lazy,mod);
        ll val2=get(st,2*si+2,mid+1,rx,max(mid+1,l),r,lazy,mod);
        st[si]=(st[2*si+1]+st[2*si+2])%mod;
        return (val1+val2)%mod;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m,mod=1e9+7;
    cin>>n>>m;
    vector<ll> arr(n);
    for (int i=0;i<n;i++)
    cin>>arr[i];
    vector<ll> st(4*n,0LL);
    vector<node> lazy(4*n,{0LL,1LL,0LL});
    build(st,0,0,n-1,arr,mod);
    while (m--)
    {
        int x,y,z,w;
        cin>>x;
        if (x==1 || x==2 || x==3)
        {
            cin>>y>>z>>w;
            update(st,0,0,n-1,y-1,z-1,w,lazy,x,mod);
        }
        else
        {
            cin>>y>>z;
            ll ans=get(st,0,0,n-1,y-1,z-1,lazy,mod);
            cout<<ans<<"\n";
        }
    }
}