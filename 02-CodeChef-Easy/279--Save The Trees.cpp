#define    ll           long long
#define    dn           double
#define    mp           make_pair
#define    pb           push_back
#define    se           second
#define    fi           first
#define    mod          1000000007
#define    sob(v)       v.begin(),v.end()
#define    sobr(v)      v.rbegin(),v.rend()
#define    fr(i,a,b)    for(int i=a;i<=b;++i)
#define    frr(i,a,b)   for(int i=a;i>=b;--i)
#define    pi           acos(-1.00)
#define    inf          1e5
#define    EPS          1e-9
#define    check        cout<<"*"<<endl
#define    ffix(x)      cout<<fixed<<setprecision(x)
#define    fast         ios_base::sync_with_stdio(false);cill n.tie(NULL);cout.tie(NULL)

#include<bits/stdc++.h>
#include<string.h>
using namespace std;

typedef vector<int> vi;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef pair<int,vi> pp;
typedef vector<pii> vpii;
typedef pair<pair<int,int>,int> pain;

int dr[8]= {-1,0,+1,0,-1,-1,+1,+1};
int dc[8]= {0,+1,0,-1,-1,+1,-1,+1};

int kx[8]= {-1,+1,+1,-1,+2,+2,-2,-2};
int ky[8]= {+2,+2,-2,-2,-1,+1,+1,-1};

const int N=100005;


struct point
{
    ll x,y;
};
bool comp(point a,point b)
{
    return (a.x<b.x || (a.x==b.x && a.y<b.y));
}
bool cw(point a,point b,point c)
{
    return (a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))<0;
}
bool ccw(point a,point b,point c)
{
    return (a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))>0;
}

ll area_of_polygon(const vector<point>&pt)
{
    ll khetro=0,x1,x2,y1,y2;
    for(int i=0;i<(int)pt.size()-1;++i)
    {
        x1=pt[i].x;
        y1=pt[i].y;

        x2=pt[i+1].x;
        y2=pt[i+1].y;

        khetro+=(x1*y2-x2*y1);
    }
    return abs(khetro);
}
void convex_hull(vector<point>&pt)
{
    if(pt.size()<=1)return;

    sort(sob(pt),comp);
    vector<point>up,down;
    point p1=pt[0],p2=pt.back();
    up.pb(p1);
    down.pb(p1);
    for(int i=1;i<(int)pt.size();++i)
    {
        if(i==pt.size()-1 || cw(p1,pt[i],p2))
        {
            while(up.size()>=2 && !cw(up[up.size()-2],up[up.size()-1],pt[i]))up.pop_back();
            up.pb(pt[i]);
        }
        if(i==pt.size()-1 || ccw(p1,pt[i],p2))
        {
            while(down.size()>=2 && !ccw(down[down.size()-2],down[down.size()-1],pt[i]))down.pop_back();
            down.pb(pt[i]);
        }
    }
    pt.clear();
    for(int i=0;i<(int)up.size();++i)pt.pb(up[i]);
    for(int i=down.size()-2;i>=0;--i)pt.pb(down[i]);
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        vector<point>pt;
        point p;
        int n;
        cin>>n;
        ll a[n+1],mn,mx;
        fr(i,1,n)cin>>a[i];
        mn=mx=a[1];
        fr(i,2,n)
        {
            if(mn==mx)
            {
                p.x=mn;
                p.y=a[i];
                pt.pb(p);
            }
            else
            {
                pt.pb({mn,a[i]});
                pt.pb({mx,a[i]});
            }
            mn=min(a[i],mn);
            mx=max(a[i],mx);
        }
        convex_hull(pt);
       /// cout<<pt.size()<<endl;
       /// for(auto i:pt)cout<<i.x<<' '<<i.y<<endl;
        ll khetro=area_of_polygon(pt);
        if(n>2)cout<<khetro<<endl;
        else cout<<0<<endl;
    }
    return 0;
}
