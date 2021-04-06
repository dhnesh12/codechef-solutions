#include<bits/stdc++.h>
typedef long long ll;
#define fr(i, a, b) for(ll i = a; i <= b; i++)
#define rf(i, a, b) for(int i = a; i >= b; i--)
#define REP(i,n) for(int i=0;i<(n);++i)
#define SIZE(c) ((int)((c).size()))
#define FOREACH(i,x) for (__typeof((x).begin()) i=(x).begin(); i!=(x).end(); ++i) 
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mx 100002
#define CLR(x) memset(x,0,sizeof(x))
#define SET(x) memset(x,-1,sizeof(x))
#define pii pair<int,int>
#define pb push_back
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define fi first
#define se second
using namespace std;
const double EPS = 1E-11;
const double eps=1e-11;
int n=4;
vector < vector<double> > as (4, vector<double> (4));
double determinant(vector<vector<double>> &aa)
{
    fr(i,0,3)
        fr(j,0,3)
            as[i][j]=aa[i][j];
    double det = 1;
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j)
            if (abs (as[j][i]) > abs (as[k][i]))
                k = j;
        if (abs (as[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap (as[i], as[k]);
        if (i != k)
            det = -det;
        det *= as[i][i];
        for (int j=i+1; j<n; ++j)
            as[i][j] /= as[i][i];
        for (int j=0; j<n; ++j)
            if (j != i && abs (as[j][i]) > EPS)
                for (int k=i+1; k<n; ++k)
                    as[j][k] -= as[i][k] * as[j][i];
    }
    return det;
}
double t[4];
double v[4];

double a,b,c,d;
vector<double> wow;
double f(double x)
{
    double ans=0;
    ans+=a*x*x*x;
    ans+=b*x*x;
    ans+=c*x;
    ans+=d;
    return ans;
}
void search(double l,double r)
{
    if(f(l)>0 and f(r)<0)
    {
        while(r-l>eps)
        {
            double mid=(l+r)/2;
            if(f(mid)>0)l=mid;
            else r=mid;
        }
        wow.pb(l);
        return;
    }
    else if(f(l)<0 and f(r)>0)
    {
        while(r-l>eps)
        {
            double mid=(l+r)/2;
            if(f(mid)<0)l=mid;
            else r=mid;
        }
        wow.pb(l);
        return;
    }
}
double integ(double l,double r)
{
    double xx=a*r*r*r*r/4+b*r*r*r/3+c*r*r/2+d*r;
    r=l;
    double yy=a*r*r*r*r/4+b*r*r*r/3+c*r*r/2+d*r;
    xx=yy-xx;
    if(xx<0)xx*=-1;
    return xx;
}
bool vv(double x,double g)
{
    if(x<0 or x>g)return 0;
    return 1;
}
signed main()
{
    IO;
    int tt;
    cin>>tt;
    while(tt--)
    {
        double g;

        cin>>g;
        fr(i,0,3)cin>>t[i]>>v[i];
        vector < vector<double> > x (4, vector<double> (4));        
        fr(i,0,3)
        {
            x[i][0]=t[i]*t[i]*t[i];
            x[i][1]=t[i]*t[i];
            x[i][2]=t[i];
            x[i][3]=1;
        }
        vector < vector<double> > y (4, vector<double> (4));                
        fr(i,0,3)
            fr(j,0,3)
                y[i][j]=x[i][j];
        fr(i,0,3)
            y[i][0]=v[i];
        a=determinant(y)/determinant(x);
        fr(i,0,3)
            fr(j,0,3)
                y[i][j]=x[i][j];
        fr(i,0,3)
            y[i][1]=v[i];
        b=determinant(y)/determinant(x);
        fr(i,0,3)
            fr(j,0,3)
                y[i][j]=x[i][j];
        fr(i,0,3)
            y[i][2]=v[i];
        c=determinant(y)/determinant(x);
        fr(i,0,3)
            fr(j,0,3)
                y[i][j]=x[i][j];
        fr(i,0,3)
            y[i][3]=v[i];
        d=determinant(y)/determinant(x);
        double xd=b*b-3*a*c;
        int zeros=0;
        if(xd==0)zeros=1;
        else if(xd>0)zeros=2;
        wow.clear();
        wow.pb(0);
        if(zeros!=0)
        {
            xd=sqrt(xd);
            double alp=(-b-xd)/(3*a);
            double bet=(-b+xd)/(3*a);
            if(alp>bet)swap(alp,bet);
            if(!vv(alp,g) and !vv(bet,g))search(0,g);
            if(!vv(alp,g) and vv(bet,g))search(0,bet),search(bet,g);
            if(vv(alp,g) and !vv(bet,g))search(0,alp),search(alp,g);
            if(vv(alp,g) and vv(bet,g))search(0,alp),search(alp,bet),search(bet,g);
        }
        else search(0,g);
        //cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
        wow.pb(g);
        sort(all(wow));
        double ans=0;
        fr(i,0,SIZE(wow)-2)
        {
            ans+=integ(wow[i],wow[i+1]);
        }
        cout<<fixed<<setprecision(11)<<ans<<endl;
    }
}