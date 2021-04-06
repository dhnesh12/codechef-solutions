#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int p_root=3;
const int maxR=1e6;

int fact[maxR+1], invfact[maxR+1];
int powM(int a,int p){
    int ans=1;
    while(p){
        if(p&1)
            ans=1LL*ans*a%mod;
        a=1LL*a*a%mod;
        p>>=1;
    }
    return ans;
}
void preComp(){
    fact[0]=1;
    for(int i=1;i<=maxR;i++)
        fact[i]=1LL*fact[i-1]*i%mod;
    invfact[maxR]=powM(fact[maxR],mod-2);
    for(int i=maxR-1;i>=0;i--)
        invfact[i]=1LL*invfact[i+1]*(i+1)%mod;
}
const int sz=1<<((int)ceil(log2(maxR)));

int rev[sz], r[sz+1], inv_sz;
void initialize(int sz){
    int bits=32-__builtin_clz(sz)-1;
    int r1=powM(p_root,(mod-1)/sz);
    inv_sz=powM(sz,mod-2);
    r[0]=r[sz]=1;
    for(int i=1;i<sz;i++)
        r[i]=1LL*r1*r[i-1]%mod;
    for(int i=1;i<sz;i++)
        rev[i]=(rev[i>>1]>>1) | ((1&i)<<(bits-1));
}
void ntt(int coeff[],int sz,int dir=0){
    for(int i=1;i<sz-1;i++)
        if(i<rev[i]) swap(coeff[i],coeff[rev[i]]);
   
    for(int len=2;len<=sz;len<<=1){
        for(int i=0;i<sz;i+=len){
            for(int j=0;j<(len>>1);j++){
                int &temp1=coeff[i+j];
                int &temp2=coeff[i+j+(len>>1)];
                int temp3=1LL*r[dir ? sz-sz/len*j : sz/len*j]*temp2%mod;
                temp2=temp1-temp3<0 ? temp1-temp3+mod : temp1-temp3;
                temp1=temp1+temp3>=mod ? temp1+temp3-mod : temp1+temp3;
            }
        }
    }
    
    if(dir)
        for(int i=0;i<sz;i++)
            coeff[i]=1LL*inv_sz*coeff[i]%mod;
}
int a[sz],b[sz],c[sz];
void mulPoly(int n){
    if(n==1)
        return void(a[1]=1);
    if(n&1){
        mulPoly(n-1);
        for(int i=n;i>0;i--)
            a[i]=(a[i-1]-1LL*(n-1)*a[i]%mod+mod)%mod;
        a[0]=(mod-1LL*(n-1)*a[0]%mod)%mod;
        return;
    }
    n>>=1;
    mulPoly(n);
    int sz1=1<<((int)ceil(log2(n+n+1)));
    for(int i=0;i<=n;i++)
        b[i]=1LL*fact[n-i]*a[n-i]%mod;
    for(int i=0,j=1;i<=n;i++,j=1LL*((mod-n%mod)%mod)*j%mod)
        c[i]=1LL*j*invfact[i]%mod;
    for(int i=n+1;i<sz1;i++) 
        b[i]=c[i]=0;
    
    initialize(sz1);
    ntt(b,sz1);
    ntt(c,sz1);
    for(int i=0;i<sz1;i++)
        b[i]=1LL*b[i]*c[i]%mod;
    ntt(b,sz1,1);
    reverse(b,b+n+1);
    for(int i=0;i<=n;i++)
        b[i]=1LL*invfact[i]*b[i]%mod;
    for(int i=n+1;i<sz1;i++)
        a[i]=b[i]=0;
    ntt(a,sz1);
    ntt(b,sz1);
    for(int i=0;i<sz1;i++)
        a[i]=1LL*a[i]*b[i]%mod;
    ntt(a,sz1,1);
}
void solve(){
    int N,p,r;
    cin >> N >> p >> r;
    mulPoly(r);
    for(int i=0;i<=r;i++)
        a[i]=1LL*invfact[r]*a[i]%mod;
    int ans=0,temp;
    for(int i=0,j=1;i<=r;i++,j=1LL*p*j%mod){
        if(j==1)
            temp=(N+1)%mod;
        else
            temp=1LL*(powM(j,N+1)-1+mod)*powM(j-1,mod-2)%mod;
        ans+=1LL*a[i]*temp%mod;
        ans%=mod;
    }   
    cout << ans << endl;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	preComp();
	while(T--)
		solve();
	return 0;
}
