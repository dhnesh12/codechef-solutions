//{{{
#include <bits/stdc++.h>
using namespace std;
//types
typedef long long ll;
typedef pair<int,int> pii;
//input
void SR(int &x){scanf("%d",&x);}void SR(ll &x){scanf("%lld",&x);}
void SR(double &x){scanf("%lf",&x);}void SR(char *s){scanf("%s",s);}
void RI(){}
template<typename I,typename... T>void RI(I &x,T&... tail){SR(x);RI(tail...);}
//output
void SP(const int x){printf("%d",x);}void SP(const ll x){printf("%lld",x);}
void SP(const double x){printf("%.16lf",x);}void SP(const char *s){printf(s);}
void PS(){puts("");}
template<typename I,typename... T>void PS(I &x,T&... tail){putchar(' ');SP(x);PS(tail...);}
void PL(){puts("");}
template<typename I,typename... T>void PL(const I x,const T... tail){SP(x);PS(tail...);}
//macro
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x),end(x)
#define REP(i,n) for(int i=0;i<int(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=int(b);i++)
#define pb push_back
#define mkp make_pair
#define F first
#define S second
//debug
#ifdef darry140
template<typename I>
void _DOING(const char *s,I&& x){cerr<<s<<"="<<x<<endl;}//without ','
template<typename I,typename... T>
void _DOING(const char *s,I&& x,T&&... tail)//with ','
{
    int c=0;
    static const char bra[]="({[";
    static const char ket[]=")}]";
    while(*s!=',' || c!=0)//eg. mkp(a,b)
    {
        if(strchr(bra,*s)) c++;
        if(strchr(ket,*s)) c--;
        cerr<<*s++;
    }
    cerr<<"="<<x<<", ";
    _DOING(s+1,tail...);
}
#define debug(...) do{\
    fprintf(stderr,"%s:%d - ",__PRETTY_FUNCTION__,__LINE__);\
    _DOING(#__VA_ARGS__,__VA_ARGS__);\
}while(0);
template<typename It>
ostream& _OUTC(ostream &s,It b,It e)//container
{
    s<<"{";
    for(auto it=b;it!=e;it++) s<<(it==b?"":" ")<<*it;
    s<<"}";
    return s;
}
template<typename A,typename B>
ostream& operator <<(ostream&s, const pair<A,B> &p){return s<<"("<<p.F<<","<<p.S<<")";}
template<typename A,typename B>
ostream& operator <<(ostream&s, const map<A,B> &c){return _OUTC(s,ALL(c));}
template<typename T>
ostream& operator <<(ostream&s, const set<T> &c){return _OUTC(s,ALL(c));}
template<typename T>
ostream& operator <<(ostream&s, const vector<T> &c){return _OUTC(s,ALL(c));}
#else
#define debug(...)
#endif
//}}}
typedef long double ld;
struct Vir
{
    template<typename T>
    Vir(complex<T> c):
        re(c.real()),im(c.imag()){}
    Vir(ld a=0,ld b=0):
        re(a),im(b){}
    ld re,im;
    Vir operator +(const Vir &v) const
    {return Vir(re+v.re,im+v.im);}
    Vir operator -(const Vir &v) const
    {return Vir(re-v.re,im-v.im);}
    Vir operator *(const ld &x) const
    {return Vir(re*x,im*x);}
    Vir operator *(const Vir &v) const
    {return Vir(re*v.re-im*v.im,re*v.im+im*v.re);}
    Vir operator *=(const Vir &v)
    {return (*this)=(*this)*v;}
    double real() const {return re;}
    double imag() const {return im;}
    complex<ld> comp() const{return complex<ld>(re,im);}
};
Vir exp(const Vir &v){return Vir(exp(v.comp()));}
const int MOD=1e5+3;
template<size_t K>
struct FFT
{
    FFT()
    {
        REP(s,K)
        {
            memcpy(rev[s+1],rev[s],(1<<s)*sizeof(int));
            memcpy(rev[s+1]+(1<<s),rev[s],(1<<s)*sizeof(int));
            REP(i,2<<s) rev[s+1][i]<<=1;
            REP(i,1<<s) rev[s+1][i+(1<<s)]|=1;
        }
    }
    const Vir I=Vir(0,1);
    const ld pi=3.14159265358979323846264338;
    const int maxn=1<<K;
    int rev[K+1][1<<K];
    template<typename T>
    void brc(T *a,Vir *A,int on,int n)
    {
        int lg=__lg(n);
        REP(i,on) A[rev[lg][i]]=a[i];
        REP1(i,on,n-1) A[rev[lg][i]]=0;
    }
    template<typename T>
    void fft(int pw,T *a,Vir *A,int on,int n)
    {
        brc(a,A,on,n);
        int lg=__lg(n);
        REP1(s,1,lg)
        {
            int m=1<<s;
            Vir wm=exp(I*(pw*2*pi/m));
            for(int k=0;k<n;k+=m)
            {
                Vir w(1,0);
                REP(j,m/2)
                {
                    Vir u=A[k+j],t=w*A[k+j+m/2];
                    A[k+j]=u+t;
                    A[k+j+m/2]=u-t;
                    w*=wm;
                }
            }
        }
    }
    Vir F[1<<K],G[1<<K],H[1<<K],ans[1<<K];
    void mul(ll *p,ll *q,int n,ll *r)
    {
        REP(i,n) if(p[i]<0) p[i]+=MOD;
        REP(i,n) if(q[i]<0) q[i]+=MOD;
        int len=4<<__lg(n-1);
        fft(1,p,F,n,len);fft(1,q,G,n,len);
        REP(i,len) H[i]=F[i]*G[i];
        fft(-1,H,ans,len,len);
        REP(i,len) ans[i]=ans[i]*(1.0/len);
        REP(i,2*n) r[i]=ans[i].real()+0.5;
    }
};
const int maxn=65536+10;
int inv[MOD],fac[6*maxn],ifac[6*maxn];
int way[maxn];
int C(int x,int y)
{
    if(y<0||y>x) return 0;
    int u1=fac[x],u2=x/MOD;
    int v1=ifac[y],v2=y/MOD;
    int w1=ifac[x-y],w2=(x-y)/MOD;
    if(u2>v2+w2) return 0;
    return 1LL*u1*v1*w1%MOD;
}
void predo()
{
    inv[1]=fac[1]=ifac[1]=fac[0]=ifac[0]=1;
    REP1(i,2,MOD-1) inv[i]=1LL*inv[MOD%i]*(MOD-MOD/i)%MOD;
    REP1(i,2,6*maxn-1) fac[i]=1LL*max(1,i%MOD)*fac[i-1]%MOD;
    REP1(i,2,6*maxn-1) ifac[i]=1LL*inv[max(1,i%MOD)]*ifac[i-1]%MOD;
    
    way[1]=9;way[2]=243;
    int pw3[]={1,3,9,27,81};
    int pw2=(1<<6)%MOD;
    int sf=C(6,0)+C(6,1)+C(6,2);
    REP1(i,3,maxn-1)
    {
        way[i]=0;
        int cf=sf;
        REP(j,5)
        {
            way[i]=(way[i]+1LL*C(4,j)*pw3[j]*(pw2-cf))%MOD;
            cf=(cf-C(6*(i-2),i-j-1))%MOD;
        }
        pw2=(pw2<<6)%MOD;
        REP1(j,6*(i-2),6*(i-1)-1)
            sf=(2*sf-C(j,i-1))%MOD;
        sf=(sf+C(6*(i-1),i))%MOD;
    }
}
FFT<16> helper;
int n,k;
void read()
{
    RI(n,k);
}
ll tmp[25*maxn];int tsiz;
void doo(ll *a,int l,int r)
{
    memset(a,0,sizeof(ll)*(r-l+4));
    if(r-l<20)
    {
        a[0]=1;
        REP1(i,l,r) for(int j=i-l;j>=0;j--)
            a[j+1]=(a[j+1]+a[j]*way[i])%MOD;
        return;
    }
    int mid=(l+r)/2,osiz=tsiz;
    int ls=mid-l+1,rs=r-mid;
    ll *p=tmp+tsiz;tsiz+=ls+5;
    doo(p,l,mid);
    ll *q=tmp+tsiz;tsiz+=rs+5;
    doo(q,mid+1,r);
    p[ls+1]=p[ls+2]=q[rs+1]=q[rs+2]=0;
    helper.mul(p,q,ls+1,a);
    REP(i,r-l+2) a[i]%=MOD;
    tsiz=osiz;
}
void build()
{
    tsiz+=n+5;
    doo(tmp,1,n);
    tsiz=0;
}
void sol()
{
    ll ans=0;
    REP1(i,k,n) ans=(ans+tmp[i])%MOD;
    PL((ans+MOD)%MOD);
}
int main()
{
    predo();
    int t;RI(t);
    while(t--)
    {
        read();
        build();
        sol();
    }
    return 0;
}