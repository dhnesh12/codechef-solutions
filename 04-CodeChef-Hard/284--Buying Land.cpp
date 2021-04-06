#include<bits/stdc++.h>
#define ld long double
#define ll long long
#define base complex<double>
using namespace std;
const ld pi=4.0*atan(1.0);
vector<ll>rev;
/*struct base
{
    ld x,y;
    base()
    {
        x=0;
        y=0;
    }
    base(ld a)
    {
        x=a;
        y=0;
    }
    base(ld a,ld b)
    {
        x=a;
        y=b;
    }
    base conj()
    {
        return base(x,-y);
    }
    base operator = (const base &b1){
        x=b1.x;
        y=b1.y;
        return *this;
    }
    base operator + (const base &b1){
        return base(x+b1.x,y+b1.y);
    }
    base operator - (const base &b1){
        return base(x-b1.x,y-b1.y);
    }
    base operator * (const base &b1){
        return base(x*b1.x - y*b1.y,x*b1.y + y*b1.x);
    }
    base operator * (ld num){
        return base(x*num,y*num);
    }
    base operator / (ld num){
        return base(x/num,y/num);
    }
};*/
void bitreversal(ll n, int bits)//n=2^bits
{
    rev.resize(n);
    for(ll i=0;i<n;i++)
    {
        ll res=0LL;
        for(int j=0;j<bits;j++)
        {
            if((i>>j)&1)
            res |= (1ll<<(bits-1-j));
        }
        rev[i]=res;
    }
}
void fft(ll n,vector<base>&a,bool inv)
{
    for(ll i=0;i<n;i++)
    {
        if(i<rev[i])
        swap(a[i],a[rev[i]]);
    }
    for(ll len=2;len<=n;len<<=1)
    {
        ll half=(len>>1);
        double ang=((2*M_PI)/len * (inv?-1:1));
        base w(cos(ang),sin(ang));
        for(ll i=0;i<n;i+=len)
        {
            base cur(1);
            for(ll j=0;j<half;j++)
            {
                base v=a[i+j];
                base u=a[i+j+half]*cur;
                a[i+j]=v+u;
                a[i+j+half]=v-u;
                cur = cur*w;
            }
        }
    }
    if(inv)
    {
        for(base &x:a)
        x /= n;
    }
}
void convolve(vector<ll>a,vector<ll>b,vector<ll>&res)
{
    ll n=1,bits=0;
    while(n<(a.size()+b.size()-1))
    {
        n=(n*2);
        bits++;
    }
    vector<base>A(n,0),B(n,0);
    res.resize(n);
    for(ll i=0;i<a.size();i++)
    A[i]=base((ld)a[i]);
    for(ll i=a.size();i<n;i++)
    A[i]=base((ld)0);
    for(ll i=0;i<b.size();i++)
    B[i]=base((ld)b[i]);
    for(ll i=b.size();i<n;i++)
    B[i]=base((ld)0);
    bitreversal(n,bits);
    fft(n,A,false);
    fft(n,B,false);
    for(ll i=0;i<n;i++)
    A[i]=(A[i]*B[i]);
    fft(n,A,true);
    for(ll i=0;i<n;i++)
    res[i]=roundl(A[i].real());
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll r,c;
    cin>>r>>c;
    vector<ll>grid(r*c,0),grid2(r*c,0),gridsum(r*c,0);
    for(ll i=0;i<r;i++)
    for(ll j=0;j<c;j++)
    {
        ll x;
        cin>>x;
        grid[i*c + j]=x;
        grid2[i*c + j]=(x*x);
    }
    ll h,w;
    cin>>h>>w;
    vector<ll>pattern(h*c + 1,0);
    ll sumx=0,sumx2=0;
    for(ll i=0;i<h;i++)
    {
        for(ll j=0;j<w;j++)
        {
            ll x;
            cin>>x;
            sumx += x;
            sumx2 += (x*x);
            pattern[(h-i)*c - j]=x;
        }
    }
    vector<ll>ans;
    convolve(grid,pattern,ans);
    ll a,b;
    cin>>a>>b;
    for(ll i=0;i<r;i++)
    for(ll j=0;j<c;j++)
    {
        gridsum[i*c + j]=grid[i*c + j];
        if(i>0)
        {
            gridsum[i*c + j] += gridsum[(i-1)*c + j];
            grid2[i*c + j] += grid2[(i-1)*c + j];
        }
        if(j>0)
        {
            gridsum[i*c + j] += gridsum[i*c + j - 1];
            grid2[i*c + j] += grid2[i*c + j - 1];
        }
        if(i>0 && j>0)
        {
            gridsum[i*c + j] -= gridsum[(i-1)*c + j - 1];
            grid2[i*c + j] -= grid2[(i-1)*c + j - 1];
        }
    }
    set<pair<ll,pair<ll,ll>>>s;
    for(ll i=0;i<=(r-h);i++)
    for(ll j=0;j<=(c-w);j++)
    {
        ll val=0,val2=0;
        val += gridsum[(i+h-1)*c + j+w-1];
        val2 += grid2[(i+h-1)*c + j+w-1];
        if(i>0)
        {
            val -= gridsum[(i-1)*c + j+w-1];
            val2 -= grid2[(i-1)*c + j+w-1];
        }
        if(j>0)
        {
            val -= gridsum[(i+h-1)*c + j-1];
            val2 -= grid2[(i+h-1)*c + j-1];
        }
        if(i>0 && j>0)
        {
            val += gridsum[(i-1)*c + j-1];
            val2 += grid2[(i-1)*c + j-1];
        }
        ll finalans= sumx2+val2;
        ll p=grid[(i+a-1)*c + j+b-1];
        finalans += (p*p*h*w + 2*p*sumx - 2*p*val -2*ans[h*c + i*c + j]);
        s.insert(make_pair(finalans,make_pair(i,j)));
    }
    ll k;
    cin>>k;
    auto it=s.begin();
    for(int i=0;i<k;i++,it++)
    {
        cout<<((*it).second.first+1)<<" "<<((*it).second.second+1)<<" "<<(*it).first<<"\n";
    }
    return 0;
}