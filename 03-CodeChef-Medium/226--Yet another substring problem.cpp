#include <bits/stdc++.h>
using namespace std;
string s,x,kq;
int n,i,j,q,mod=round(1e9)+7,v;
string dao(string s)
{
    string x=""; int i;
    for(i=s.length()-1;i>=0;i--) x+=s[i];
    return x;
}
string doi(int n)
{
    string s="";
    if(n==0) return "0";
    while(n>0)
    {
        s=char(n%10+48)+s;
        n/=10;
    }
    return s;
}
string Min(string a,string b)
{
    if(a=="") return b;
    if(b=="") return a;
    if(a.length()<b.length()) return a;
    if(b.length()<a.length()) return b;
    if(a<b) return a; return b;
}
string operator + (string a,string b)
{
    int i,nho=0; string x="";
    while(a.length()<b.length()) a="0"+a;
    while(b.length()<a.length()) b="0"+b;
    for(i=a.length()-1;i>=0;i--)
    {
        int sa=(int)a[i]-48,sb=(int)b[i]-48;
        x+=char((sa+sb+nho)%10+48);
        nho=(sa+sb+nho)/10;
    }
    if(nho>0) x+=char(nho+48);
    return dao(x);
}
string operator - (string a,string b)
{
    int i,nho=0; string x="";
    while(a.length()<b.length()) a="0"+a;
    while(b.length()<a.length()) b="0"+b;
    for(i=a.length()-1;i>=0;i--)
    {
        int sa=(int)a[i]-48,sb=(int)b[i]-48;
        if(sa-sb-nho>=0)
        {
            x+=char(sa-sb-nho+48);
            nho=0;
        }
        else { x+=char(sa-sb-nho+58); nho=1; }
    }
    x=dao(x);
    while(x[0]=='0' && x.length()>1) x.erase(0,1);
    return x;
}
string operator * (string a,int sb)
{
    int i,nho=0; string x="";
    for(i=a.length()-1;i>=0;i--)
    {
        int sa=a[i]-48;
        x+=char((sa*sb+nho)%10+48);
        nho=(sa*sb+nho)/10;
    }
    if(nho>0) x+=doi(nho);
    x=dao(x);
    while(x[0]=='0' && x.length()>1) x.erase(0,1);
    return x;
}
string tang(string s)
{
    int nho=1;
    for(int i=s.length()-1;i>=0;i--)
    {
        int sa=s[i]-'0';
        if(sa+nho<=9) { s[i]=char(sa+nho+'0'); return s; }
        else { s[i]='0'; nho=1; }
    }
    return "1"+s;
}
string giam(string s)
{
    int nho=1;
    for(int i=s.length()-1;i>=0;i--)
    {
        int sa=s[i]-'0';
        if(sa-nho>=0)
        {
            s[i]=char(sa-nho+'0');
            if(i==0 && s[i]=='0' && s.length()>1) s.erase(0,1);
            return s;
        }
        else { s[i]=char(sa+10-nho+'0'); nho=1; }
    }
}
bool kt(string s,string x,int l,int r)
{
    int i;
    string ss="",so=giam(x);
    vector <string> str;
    while(so!="0" && ss.length()<l-1) { ss+=so; str.push_back(so); so=giam(so); }
    if(ss.length()<l-1) return 0;
    ss="";
    if(str.size()>0)
        for(int i=str.size()-1;i>=0;i--) ss+=str[i];
    ss=" "+ss;
    for(i=l-1;i>=1;i--)
        if(s[i]!=ss[ss.length()-(l-i)]) return 0;
    ss="",so=tang(x);
    while(ss.length()<n-r) { ss+=so; so=tang(so); }
    ss=" "+ss;
    for(i=r+1;i<=n;i++)
        if(s[i]!=ss[i-r]) return 0;
    return 1;
}
int vt(string s)
{
    int kq=0;
    long long cs=1,sln=9,d=0,c=0; string sl="9";
    while(s!=sl && Min(s,sl)==sl) { kq=(kq+sln*cs)%mod; s=s-sl; cs++; sl+="0"; sln=sln*10%mod; }
    for(int i=0;i<s.length();i++) { c=d*10+s[i]-'0'; d=c%mod; }
    return (kq+d*cs)%mod;
}
int main()
{
    //freopen("ntu.inp","r",stdin);
    //freopen("ntu.out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>q;
    while(q--)
    {
        cin>>s; n=s.length();
        s=" "+s; kq="";
        for(i=1;i<=n;i++)
        {
            if(s[i]=='0') continue;
            x="";
            for(j=i;j<=n;j++)
            {
                x+=s[j];
                if(Min(kq,x)==kq) continue;
                if(kt(s,x,i,j)) { kq=x; v=j; }
            }
        }
        cout<<(vt(kq)-v+1+mod)%mod<<'\n';
    }
}
