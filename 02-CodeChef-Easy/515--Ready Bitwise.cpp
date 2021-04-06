#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
struct wow
{
    long long zer,unu,a,A;
};
int poz,n;
char s[100005];
wow eval();
wow termen();
wow eval()
{
    wow rez=termen(),acum,cop;
    while (poz<n&&(s[poz]=='&'||s[poz]=='|'||s[poz]=='^'))
    {
        if (s[poz]=='&')
        {
            poz++;
            acum=termen();
            cop.zer=((rez.zer*acum.A)%MOD+(rez.A*acum.zer)%MOD+(rez.zer*acum.zer)%MOD+(rez.zer*acum.a)%MOD+(rez.a*acum.zer)%MOD+(rez.unu*acum.zer)%MOD+(rez.zer*acum.unu)%MOD+(rez.a*acum.a)%MOD+(rez.A*acum.a)%MOD)%MOD;
            cop.unu=(acum.unu*rez.unu)%MOD;
            cop.a=(((rez.a*acum.unu)%MOD+(rez.unu*acum.a)%MOD)%MOD+(rez.a*acum.a)%MOD)%MOD;
            cop.A=((rez.A*acum.unu)%MOD+(rez.unu*acum.A)%MOD+(rez.A*acum.A)%MOD)%MOD;
            rez=cop;
        }
        else
        if (s[poz]=='|')
        {
            poz++;
            acum=termen();
            cop.zer=(rez.zer*acum.zer)%MOD;
            cop.unu=((rez.unu*acum.unu)%MOD+(rez.unu*acum.a)%MOD+(rez.a*acum.unu)%MOD+(rez.zer*acum.unu)%MOD+(rez.unu*acum.zer)%MOD+(rez.a*acum.A)%MOD+(rez.A*acum.a)%MOD+(rez.A*acum.unu)%MOD+(rez.unu*acum.A)%MOD)%MOD;
            cop.a=((rez.a*acum.a)%MOD+(rez.a*acum.zer)%MOD+(rez.zer*acum.a)%MOD)%MOD;
            cop.A=((rez.zer*acum.A)%MOD+(rez.A*acum.zer)%MOD+(rez.A*acum.A)%MOD)%MOD;
            rez=cop;
        }
        else
        if (s[poz]=='^')
        {
            poz++;
            acum=termen();
            cop.zer=(((rez.unu*acum.unu)%MOD+(rez.a*acum.a)%MOD)%MOD+(rez.A*acum.A)%MOD+(rez.zer*acum.zer)%MOD)%MOD;
            cop.unu=((rez.unu*acum.zer)%MOD+(rez.zer*acum.unu)%MOD+(rez.a*acum.A)%MOD+(rez.A*acum.a)%MOD)%MOD;
            cop.a=((rez.zer*acum.a)%MOD+(rez.a*acum.zer)%MOD+(rez.unu*acum.A)%MOD+(rez.A*acum.unu)%MOD)%MOD;
            cop.A=((rez.zer*acum.A)%MOD+(rez.A*acum.zer)%MOD+(rez.unu*acum.a)%MOD+(rez.a*acum.unu)%MOD)%MOD;
            rez=cop;
        }
    }
    return rez;
}
wow termen()
{
    wow rez={748683265,748683265,748683265,748683265};
    if (s[poz]=='(')
    {
        poz++;
        rez=eval();
        poz++;
        return rez;
    }
    while (poz<n&&s[poz]=='#')
    {
        poz++;
    }
    return rez;
}
int t;
wow sfarsit;
int main()
{
    #ifdef HOME
    ifstream cin("date.in");
    ofstream cout("date.out");
    #endif // HOME
    cin>>t;
    for (;t--;)
    {
        cin>>s;
        n=strlen(s);
        poz=0;
        sfarsit=eval();
        cout<<sfarsit.zer<<" "<<sfarsit.unu<<" "<<sfarsit.a<<" "<<sfarsit.A<<'\n';
    }
    return 0;
}
