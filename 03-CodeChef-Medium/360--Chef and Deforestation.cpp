#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define pi 3.141592653589793238
#define int long long
#define ll long long
#define ld long double
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


long long power(long long a, long long b,long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a %mod;
        a = a * a %mod;
        b >>= 1;
    }
    return res;
}


int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b); 
     
}
    
int seg[1000005];
int lz[1000005];
int cnt[1000005];
pair<int,int>p[250005];
int nxt[250005];
ld kaam[250005];

void build(int ver,int tl,int tr)
{
    if(tl>tr)
        return;
    else if(tl==tr)
    {
        seg[ver]=p[tl].second;
        cnt[ver]=1;
        lz[ver]=0;
    }
    else
    {
        int tm=(tl+tr)/2;
        build(2*ver,tl,tm);
        build(2*ver+1,tm+1,tr);
        seg[ver]=seg[2*ver]+seg[2*ver+1];
        cnt[ver]=cnt[2*ver]+cnt[2*ver+1];
        lz[ver]=0;
    }
}

void push(int ver)
{
    lz[2*ver]+=lz[ver];
    lz[2*ver+1]+=lz[ver];
    seg[2*ver]+=lz[ver]*(cnt[2*ver]);
    seg[2*ver+1]+=lz[ver]*cnt[2*ver+1];
    lz[ver]=0;
}

void off(int ver,int tl,int tr,int pos)
{
    if(tl>tr)
        return;
    else if(tl==tr)
    {
        seg[ver]=0;
        cnt[ver]=0;
        lz[ver]=0;
    }
    else
    {
        int tm=(tl+tr)/2;
        if(lz[ver])
            push(ver);
        if(tm>=pos)
            off(2*ver,tl,tm,pos);
        else
            off(2*ver+1,tm+1,tr,pos);
        seg[ver]=seg[2*ver]+seg[2*ver+1];
        cnt[ver]=cnt[2*ver]+cnt[2*ver+1];        
    }    
}

void upd(int ver,int tl,int tr,int l,int r,int val)
{
    if(tl>tr||l>r||tr<l||r<tl)
        return;
    else if(tl==l&&tr==r)
    {
        seg[ver]+=cnt[ver]*val;
        lz[ver]+=val;
    }
    else
    {
        int tm=(tl+tr)/2;
        if(lz[ver])
            push(ver);
        upd(2*ver,tl,tm,l,min(tm,r),val);
        upd(2*ver+1,tm+1,tr,max(tm+1,l),r,val);
        seg[ver]=seg[2*ver]+seg[2*ver+1];
        cnt[ver]=cnt[2*ver]+cnt[2*ver+1];                
    }
}

int get(int ver,int tl,int tr,int l,int r)
{
    if(tl>tr||l>r||tr<l||r<tl)
        return 0;
    else if(tl==l&&tr==r)
    {
        return seg[ver];
    }
    else
    {
        int tm=(tl+tr)/2;
        if(lz[ver])
            push(ver);
        int z=get(2*ver,tl,tm,l,min(tm,r));
        z+=get(2*ver+1,tm+1,tr,max(tm+1,l),r);
        seg[ver]=seg[2*ver]+seg[2*ver+1];
        cnt[ver]=cnt[2*ver]+cnt[2*ver+1];     
        return z;           
    }
}

ld find(int x,int y)
{
    ld sq=(p[x].first-p[y].first)*(p[x].first-p[y].first)+(p[x].second+p[x].first-p[y].second-p[y].first)*(p[x].second+p[x].first-p[y].second-p[y].first);
    sq=sqrt(sq);
    return sq;
}

ld dp[250005];

signed main()
{

ios_base::sync_with_stdio(false); 
cin.tie(NULL);  
cout.tie(0);   

#ifndef ONLINE_JUDGE
    if(fopen("INPUT.txt","r"))
    {
        freopen("INPUT.txt","r",stdin);
        freopen("OUTPUT.txt","w",stdout);
    }
#endif          


    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        map<int,vector<int> >mm;
        vector<pair<int,int> >lol;
        for(int i=1;i<=n;i++)
            dp[i]=-1e17;
        for(int i=1;i<=n;i++)
            nxt[i]=0;
        for(int i=1;i<=n;i++)
        {
            cin>>p[i].first>>p[i].second;
            p[i].second-=p[i].first;
        }
        sort(p+1,p+n+1);
        build(1,1,n);

        for(int i=1;i<=n;i++)
        {
            lol.push_back({p[i].second,i});
            mm[p[i].second].push_back(i);            
        }

        for(auto i:mm)
        {
            int sz=i.second.size();
            for(int j=0;j<sz-1;j++)
            {
                nxt[i.second[j]]=i.second[j+1];
            }
        }

        sort(lol.begin(),lol.end());
        int prev=0;
        for(auto i:lol)
        {   
            off(1,1,n,i.second);
            upd(1,1,n,1,n,-(p[i.second].second-prev));
            prev=p[i.second].second;
            if(nxt[i.second])
                kaam[i.second]=-get(1,1,n,i.second+1,nxt[i.second]-1)+find(i.second,nxt[i.second]);
        }

        ld mx=-1e17;
        for(int i=1;i<=n;i++)
        {
            if(nxt[i])
            {
                dp[nxt[i]]=max({dp[nxt[i]],dp[i]+kaam[i],kaam[i]});
            }
            mx=max(mx,dp[i]);
        }
        if(mx<-1e16)
        {
            cout<<-1<<'\n';
            continue;
        }
        cout<<fixed<<setprecision(9);
        cout<<mx<<'\n';
    }

}    
    