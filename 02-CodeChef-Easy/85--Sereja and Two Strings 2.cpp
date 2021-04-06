#define ll long long
#include <iostream>
#include <string.h>
#define mod 1000000007
#define z(i) (i^(i-1))&i
using namespace std;
int nrt, n;
char a[100005];
ll frecv[30], p, fact[100005], invfact[100005], cnt, ans;
ll getp(){
    ll val=fact[n];
    for(int i=0; i<=25; i++)
        if(frecv[i]) val=(val*invfact[frecv[i]])%mod;
        return val;
}
ll putere(ll a, ll b){
    ll rez=1;
    while(b!=0){
        if(b%2) {rez*=a; rez%=mod;}
        b/=2;
        a*=a; a%=mod;
    }
    return rez;
}
void precalc(){
    int i;
    fact[0]=fact[1]=1;
    invfact[1]=1;
    for(i=2; i<=100000; i++)
        fact[i]=(fact[i-1]*i)%mod;
    invfact[100000]=putere(fact[100000], mod-2);
    for(i=100000-1; i>=1; i--)
        invfact[i]=(invfact[i+1]*(i+1))%mod;
}
ll getcnt(){
    int i,j,k,l;
    ll rez=1; ///0 swappuri
    for(i=0; i<=25; i++)  ///1 swap
        for(j=i+1; j<=25; j++){
            rez+=(frecv[i]*frecv[j])%mod;
            rez%=mod;
        }
    ///2swappuri
    for(i=0; i<=25; i++)
       for(j=i+1; j<=25; j++)
           for(k=j+1; k<=25; k++){
               rez+=((frecv[i]*frecv[j])%mod*frecv[k]*2LL)%mod;
               rez%=mod;
       }
     for(i=0; i<=25; i++)
       for(j=i+1; j<=25; j++)
           for(k=j+1; k<=25; k++)
               for(l=k+1; l<=25; l++){
               rez+=(((frecv[i]*frecv[j])%mod*frecv[k])*frecv[l]*3LL)%mod;
               rez%=mod;
       }
     for(i=0; i<=25; i++)
        if(frecv[i]>1)
         for(j=0; j<=25; j++)
             if(j!=i)
             for(k=j+1; k<=25; k++)
                if(k!=i){
         rez+=(((frecv[j]*frecv[k])%mod*frecv[i])%mod*(frecv[i]-1))%mod;
        rez%=mod;
     }
     for(i=0; i<=25; i++)
     if(frecv[i]>1)
     for(j=i+1; j<=25; j++)
        if(frecv[j]>1){
        rez+=(((frecv[i]*(frecv[i]-1))/2)%mod*((frecv[j]*(frecv[j]-1))/2)%mod)%mod;
        rez%=mod;
     }
     return rez;

}
int main(){

    int i;
    precalc();
    cin>>nrt;
    while(nrt--){
        cin>>a; n=strlen(a);
        for(i=0; i<=25; i++) frecv[i]=0;
        for(i=0; i<n; i++)
            frecv[a[i]-'a']++;
        p=getp();
        cnt=getcnt();
        ans=(p*p)%mod-(cnt*p)%mod;
        while(ans<0) ans+=mod;
        cout<<ans%mod<<"\n";
    }
    return 0;
}