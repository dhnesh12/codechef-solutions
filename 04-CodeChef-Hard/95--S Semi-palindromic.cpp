#include<bits/stdc++.h>
using namespace std;
#define ll long long int
ll i,j;
const ll N=1030,M=30,MOD1=1e9+7,OP=(MOD1+1)>>1,mm=1023;

ll f[30][1030],g[30][1030];
ll k1[30][1030],k2[30][1030];
ll f1[30][1030],g1[30][1030];
ll v1[30][1030],v2[30][1030];

ll check[1030];
ll w[1030];
ll n;
ll m,T;

ll ksm(ll o,ll t,ll ml)
{
    ll y=1;
    for(;t;t>>=1,o=o*o%ml)
        if(t&1)
            y=y*o%ml;
    return y;
}

ll modfun(ll p){

    if(p<MOD1)
        return p;
    else
        return (p-MOD1);
}

void dft(ll a)
{
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        register ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=f[a][i+half+j];
            f[a][i+half+j]=modfun(f[a][j+i]-keep+MOD1);
            f[a][i+j]=modfun(keep+f[a][i+j]);
        }
    }
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=g[a][i+half+j];
            g[a][i+half+j]=modfun(g[a][j+i]-keep+MOD1);
            g[a][i+j]=modfun(keep+g[a][i+j]);
        }
    }
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=f1[a][i+half+j];
            f1[a][i+half+j]=modfun(f1[a][j+i]-keep+MOD1);
            f1[a][i+j]=modfun(keep+f1[a][i+j]);
        }
    }
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=g1[a][i+half+j];
            g1[a][i+half+j]=modfun(g1[a][j+i]-keep+MOD1);
            g1[a][i+j]=modfun(keep+g1[a][i+j]);
        }
    }
}

void fwht(ll a)
{
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=v1[a][i+half+j];
            v1[a][i+half+j]=(v1[a][i+j]-keep+MOD1)*OP%MOD1;
            v1[a][i+j]=(keep+v1[a][i+j])*OP%MOD1;
        }
    }
    for(ll m=2;m<=mm+1;m<<=1){
        ll keep;
        ll half=m>>1;
        for(ll i=0;i<=mm;i+=m)
        for(j=0;j<half;j++){
            keep=v2[a][i+half+j];
            v2[a][i+half+j]=(v2[a][i+j]-keep+MOD1)*OP%MOD1;
            v2[a][i+j]=(keep+v2[a][i+j])*OP%MOD1;
        }
    }
}

void solve(ll o)
{
    w[0]=0;
    for(;o;o>>=1)w[++w[0]]=o;
    for(i=0;i<m;i++)
        for(ll l=0;l<=mm;l++)
            f[i][l]=g[i][l]=0;
    for(i=1;i<=9;i++)
        f[i%m][check[i]]=1;
    for(ll ko=w[0]-1;ko>=1;ko--){
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                k1[i][l]=f[i][l],f1[i][l]=0;
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                k2[i][l]=g[i][l],g1[i][l]=0;
        if(w[ko+1]&1)
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                swap(k1[i][l],k2[i][l]);
        ll yu=ksm(10,w[ko+1],m);
        for(i=0;i<m;i++)
        {
            ll e=i*yu%m; ll u=w[ko+1]&1;
            for(ll l=0;l<=mm;l++)
                f1[e][l]=modfun(f1[e][l]+f[i][l]),k1[e][l^u]=modfun(k1[e][l^u]+f[i][l]);
            for(ll l=0;l<=mm;l++)
                g1[e][l]=modfun(g1[e][l]+g[i][l]),k2[e][l^u]=modfun(k2[e][l^u]+g[i][l]);
        }
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                v1[i][l]=v2[i][l]=0;
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                if(l&1)swap(g[i][l^1],g[i][l]);
        for(i=0;i<m;i++)
            dft(i);
        for(i=0;i<m;i++)
            for(j=0;j<m;j++){
                ll k=(i+j)%m;
                for(ll l=0;l<=mm;l++)
                    v1[k][l]=(v1[k][l]+f1[i][l]*(f[j][l]+g[j][l]))%MOD1;
                for(ll l=0;l<=mm;l++)
                    v2[k][l]=(v2[k][l]+g1[i][l]*(f[j][l]+g[j][l]))%MOD1;
            }
        for(i=0;i<m;i++)fwht(i);
        for(i=0;i<m;i++)
            for(ll l=0;l<=mm;l++)
                f[i][l]=modfun(v1[i][l]+k1[i][l]),g[i][l]=modfun(v2[i][l]+k2[i][l]);
        if(w[ko]&1)
        {
            ll e=yu*yu%m;
            for(i=0;i<m;i++)
                for(ll l=0;l<=mm;l++)
                    v1[i][l]=g[i][l],v2[i][l]=f[i][l];
            for(j=1;j<=9;j++)
            for(i=0;i<m;i++){
                ll k=(i+j*e)%m;
                for(ll l=0;l<=mm;l++)
                    v1[k][l^check[j]]=(v1[k][l^check[j]]+f[i][l])%MOD1;
                for(ll l=0;l<=mm;l++)
                    v1[k][l^check[j]^1]=(v1[k][l^check[j]^1]+g[i][l])%MOD1;
            }
            for(j=1;j<=9;j++)
                v1[j*e%m][check[j]^(w[ko]&1)^1]++;
            for(i=0;i<m;i++)
                for(ll l=0;l<=mm;l++)
                    f[i][l]=v1[i][l],g[i][l]=v2[i][l];
        }
    }
}

int main()
{
    cin>>T;
    check[0]=1;
    for(i=1;i<=9;i++)
        check[i]=check[i-1]<<1;
    while(T--){
        cin>>m>>n;
        solve(n);
        ll ans=f[0][0]+f[0][1]+1;
        for(i=1;i<=9;i++)
            ans=(ans+f[0][check[i]])%MOD1;
        ans=ans+g[0][0]+g[0][1];
        for(i=1;i<=9;i++)
            ans=(ans+g[0][check[i]])%MOD1;
        ans=ans%MOD1;
        cout<<ans<<endl;
    }
}