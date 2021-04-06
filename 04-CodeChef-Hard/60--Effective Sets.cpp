
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;
#define pb push_back
#define ppb pop_back
#define pi 3.1415926535897932384626433832795028841971
#define mp make_pair
#define x first
#define y second
#define sqr(a) (a)*(a)
#define D(a,b) sqrt(((a).x-(b).x)*((a).x-(b).x)+((a).y-(b).y)*((a).y-(b).y))
#define pii pair<int,int>
#define pdd pair<double,double>
#define INF 1000000000
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,1,(n))
#define rept(i,n) FOR(i,0,(n)-1)
#define L(s) (int)((s).end()-(s).begin())
#define C(a) memset((a),0,sizeof(a))
#define VI vector <int>
#define ll long long
int a,b,c,d,i,j,n,m,k,kolt,MX,MY,cur;
int lim;
int num[1501][4];
int len[1501];
pii sm[1501][1501];
int cc[1501][1501],numb[1501][1501];
int cnt[1501];
vector<pii> cord;
vector<pii> bil;
map<pii,int> rast;
int mdst[30001];
int r;
void build(int v,int x1,int y1,int x2,int y2,vector <pair<pii,int> > &cur)
{
    int x=(x1+x2)/2;
    int y=(y1+y2)/2;
    vector <pair<pii,int> > cur4(0),cur1(0),cur2(0),cur3(0);
    cnt[v]=0;
    rept(i,L(cur))
    {
        if (cur[i].x.x>=x && cur[i].x.y>=y) cur1.pb(cur[i]); else
        if (cur[i].x.x<x && cur[i].x.y>=y) cur2.pb(cur[i]); else
        if (cur[i].x.x<x && cur[i].x.y<y) cur3.pb(cur[i]); else
        cur4.pb(cur[i]);
        cnt[v]+=cur[i].y;
    }
    if (cnt[v]<=lim || (x2==x1+1 && y2==y1+1))
    {
        len[v]=L(cur);
        rept(i,L(cur))
        {
            sm[v][i]=cur[i].x;
            cc[v][i]=cur[i].y;
        }
        cnt[v]=0;
        rept(i,L(cur)) cnt[v]+=cur[i].y;
        return;
    }
    rept(i,4)
    {
        if (i==0 && !L(cur1)) continue; else
        if (i==1 && !L(cur2)) continue; else
        if (i==2 && !L(cur3)) continue; else
        if (i==3 && !L(cur4)) continue;
        num[v][i]=k++;
    }
    if (L(cur1)) build(num[v][0],x,y,x2,y2,cur1);
    if (L(cur2)) build(num[v][1],x1,y,x,y2,cur2);
    if (L(cur3)) build(num[v][2],x1,y1,x,y,cur3);
    if (L(cur4)) build(num[v][3],x,y1,x2,y,cur4);
}
inline int ds(pii t1,pii t2)
{
    return (t1.x-t2.x)*(t1.x-t2.x)+(t1.y-t2.y)*(t1.y-t2.y);
}
inline int ds(pii t1,int x,int y)
{
    return (t1.x-x)*(t1.x-x)+(t1.y-y)*(t1.y-y);
}
int fnd(int v,int x1,int y1,int x2,int y2,pii t,int d)
{
    if (v==-1) return 0;
    int d1=ds(t,mp(x1,y1));
    int d2=ds(t,mp(x1,y2-1));
    int d3=ds(t,mp(x2-1,y1));
    int d4=ds(t,mp(x2-1,y2-1));
    int dd=max(d1,max(d2,max(d3,d4)));
    if (d>=dd) return cnt[v];
    dd=min(d1,min(d2,min(d3,d4)));
    if (d<dd)
    {
        if (!(t.x>=x1 && t.x<x2 && t.y>=y1 && t.y<y2))
        {
            if (t.x>=x1 && t.x<x2)
            {
                d1=ds(t,mp(t.x,y2-1));
                d2=ds(t,mp(t.x,y1));
                dd=min(d1,d2);
                if (d<dd) return 0;
            } else
            if (t.y>=y1 && t.y<y2)
            {
                d1=ds(t,mp(x2-1,t.y));
                d2=ds(t,mp(x1,t.y));
                dd=min(d1,d2);
                if (d<dd) return 0;
            } else
            return 0;
        }
    }
    if (cnt[v]<=lim || (x2==x1+1 && y2==y1+1))
    {
        int ans=0;
        rept(i,len[v])
        {
            int cd=ds(t,sm[v][i]);
            if (cd<=d) ans+=cc[v][i];
        }
        return ans;
    }
    int x=(x1+x2)/2;
    int y=(y1+y2)/2;
    return  fnd(num[v][0],x,y,x2,y2,t,d)+
            fnd(num[v][1],x1,y,x,y2,t,d)+
            fnd(num[v][2],x1,y1,x,y,t,d)+
            fnd(num[v][3],x,y1,x2,y,t,d);
}
int iter=0;
void findclosest(int v,int x1,int y1,int x2,int y2,pii t)
{
    if (v==-1) return;
    int d1=ds(t,x1,y1);
    int d2=ds(t,x1,y2-1);
    int d3=ds(t,x2-1,y1);
    int d4=ds(t,x2-1,y2-1);
    int dd=min(d1,min(d2,min(d3,d4)));
    if (r<dd)
    {
        if (!(t.x>=x1 && t.x<x2 && t.y>=y1 && t.y<y2))
        {
            if (t.x>=x1 && t.x<x2)
            {
                d1=ds(t,t.x,y2-1);
                d2=ds(t,t.x,y1);
                dd=min(d1,d2);
                if (r<dd) return;
            } else
            if (t.y>=y1 && t.y<y2)
            {
                d1=ds(t,x2-1,t.y);
                d2=ds(t,x1,t.y);
                dd=min(d1,d2);
                if (r<dd) return;
            } else
            return;
        }
    }
    if (cnt[v]<=lim || (x2<=x1+1 && y2<=y1+1))
    {
        rept(i,len[v])
        {
            int cd=ds(t,sm[v][i]);
            if (cd)
            {
                if (cd<r) r=cd;
                if (cd<mdst[numb[v][i]]) mdst[numb[v][i]]=cd;
            }
        }
        return;
    }
    int x=(x1+x2)/2;
    int y=(y1+y2)/2;
    int u[4];
    u[0]=0; u[1]=1; u[2]=2; u[3]=3;
    if (t.x>=x && t.y>=y); else
    if (t.x<x && t.y>=y) swap(u[0],u[1]); else
    if (t.x<x && t.y<y) swap(u[0],u[2]); else
    swap(u[0],u[3]);
    random_shuffle(u+1,u+4);
    rept(i,4)
    {
        int n=u[i];
        if (n==0) findclosest(num[v][0],x,y,x2,y2,t); else
        if (n==1) findclosest(num[v][1],x1,y,x,y2,t); else
        if (n==2) findclosest(num[v][2],x1,y1,x,y,t); else
                  findclosest(num[v][3],x,y1,x2,y,t);
    }
}
int main()
{
    /*srand(time(0));
    freopen("input.txt","w",stdout);
    printf("%d\n",5);
    rept(hod,5)
    {
        int n=30000;
        printf("%d\n",n);
        rept(i,n) printf("%d %d\n",rand()%10001,rand()%10001);
    }
    exit(0);*/
    srand(25091992);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    scanf("%d",&kolt);
    rept(hod,kolt)
    {
        cord.clear();
        scanf("%d",&n);
        if (n==1)
        {
            printf("0.00 0\n\n");
            continue;
        }
        bil.clear();
        rast.clear();
        C(len);
        memset(num,-1,sizeof(num));
        MX=-1; MY=-1;
        rept(i,n)
        {
            scanf("%d%d",&a,&b);
            cord.pb(mp(a,b));
            bil.pb(mp(a,b));
            MX=max(MX,a);
            MY=max(MY,b);
            mdst[i]=20000*20000;
        }
        SORT(bil);
        MX=max(MX,MY);
        MY=max(MX,MY);
        MX+=rand()%MX;
        MY+=rand()%MY;
        k=1;
        vector<pii> tmp=cord;
        SORT(tmp);
        tmp.resize(unique(all(tmp))-tmp.begin());
        vector<pair<pii,int> > tmo(0);
        rept(i,L(tmp))
        {
            tmo.pb(mp(tmp[i],upper_bound(all(bil),tmp[i])-lower_bound(all(bil),tmp[i])));
        }
        lim=sqrt((double)(L(tmp)));
        build(0,0,0,MX+1,MY+1,tmo);
        rept(i,k)
        {
            rept(j,len[i])
            {
                numb[i][j]=lower_bound(all(tmp),sm[i][j])-tmp.begin();
            }
        }
        rept(i,n)
        {
            a=lower_bound(all(tmo),mp(cord[i],-INF))->y;
            if (a>1)
            {
                printf("0.00 %d\n",a-1);
                continue;
            }
            //map<pii,int>::iterator it=rast.find(cord[i]);
            r=mdst[lower_bound(all(tmp),cord[i])-tmp.begin()];
            cur=i;
            //if (it!=rast.end()) r=it->y; else
            {
                rept(z,1)
                {
                    pii rr=tmp[rand()%(L(tmp))];
                    if (rr==cord[i]) continue;
                    r=min(r,ds(cord[i],rr));
                }
                findclosest(0,0,0,MX+1,MY+1,cord[i]);
                rast[cord[i]]=r;
            }
            printf("%.2lf %d\n",sqrt((double)r),fnd(0,0,0,MX+1,MY+1,cord[i],r*4)-1);
        }
        printf("\n");
        //cerr<<clock()<<endl;
    }
}