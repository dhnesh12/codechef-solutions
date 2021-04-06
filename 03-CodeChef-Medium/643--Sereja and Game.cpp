//Editorial
#include <bits/stdc++.h>
using namespace std;
 
#define fastIO ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
#define endl '\n'
#define lli long long int
#define ld long double
#define p_b push_back
#define m_p make_pair
#define fs first
#define sc second
#define sz(x) ((lli)x.size())
#define all(x) x.begin(),x.end()
const lli mod = 1e9 + 7;
/*****************************************************/
lli t,n,m,a[1000005]={0};
map<pair<lli,lli>,bool> dp1;
map<pair<lli,lli>,double> dp2;
bool isWinning(lli g,lli taken)
{
    if(dp1.find({g,taken})!=dp1.end())
        return dp1[{g,taken}];
    bool win=false;
    lli i,tot=0;
    for(i=0;i<n;i++)
    {
        if(__gcd(g,a[i])==g)
            tot++;
    }
    if(taken<tot && !isWinning(g,taken+1))
            win=true;
    for(i=0;i<n;i++)
    {
        if(__gcd(g,a[i])==g)
            continue;
        if(__gcd(g,a[i])>1 && !isWinning(__gcd(g,a[i]),taken+1))
            win=true;
    }
    return dp1[{g,taken}]=win;
}
double prob(lli g,lli taken)
{
    if(dp2.find({g,taken})!=dp2.end())
        return dp2[{g,taken}];
    if(g==1)
        return dp2[{g,taken}]=1.00;
    if(taken==n)
        return dp2[{g,taken}]=0.00;
    lli i,tot=0;
    double r1=0;
    for(i=0;i<n;i++)
    {
        if(__gcd(g,a[i])==g)
            tot++;
    }
    if(taken<tot)
        r1+=((double)tot-taken)*1.00*(1.00-prob(g,taken+1))/(n-taken);
    for(i=0;i<n;i++)
    {
        if(__gcd(g,a[i])==g)
            continue;
        r1+=1.00*(1.00-prob(__gcd(g,a[i]),taken+1))/((double)n-taken);
    }
    if(r1<1e-8)
        r1=0;
    return dp2[{g,taken}]=r1;
}
int main()
{
    fastIO
    lli i,j,k,x,y;
    cin>>t;
    while(t--)
    {
        dp1.clear();
        dp2.clear();
        cin>>n;
        lli gg=0;
        for(i=1;i<=n;i++)
        {
            cin>>a[i-1];
            gg=__gcd(gg,a[i-1]);
        }
        if(gg>1)
        {
            cout<<n%2<<" "<<n%2<<".0000\n";
            continue;
        }
        if(isWinning(0,0))
            cout<<"1 ";
        else
            cout<<"0 ";
        cout<<fixed;
        cout<<setprecision(4);
        cout<<prob(0,0)<<endl;
    }
    // cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
    return 0;
}