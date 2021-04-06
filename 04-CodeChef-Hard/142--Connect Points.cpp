#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <list>
#include <unordered_set>
#include <stack>
using namespace std;
const int maxn=99999,MAXE=900000;
typedef long long LL;
unordered_set<int> G[maxn];
unordered_set<int> redu;
unordered_set<LL> faces;
bool reduced[maxn];
typedef unordered_set<int>::iterator IT;
typedef unordered_set<LL>::iterator II;
struct item{ int a,b; int o(int x){return a==x?b:a;}};
LL f(int a,int b,int c)
{
    if(b<a)swap(a,b); if(c<a)swap(a,c); if(c<b)swap(b,c);
    return (a*100000LL+b)*100000LL+c;
}
 
bool reduce(int x)
{
    int sn=G[x].size()==5?-2:0;
    if(G[x].size()<=3)return 1;
    if(G[x].size()!=4/*&&G[x].size()!=5*/)return 0;
    for(IT it=G[x].begin();it!=G[x].end();++it)sn+=G[*it].size()<18;
    return sn>=2;
}
void update(int x)
{
    if(reduce(x))redu.insert(x);
    else redu.erase(x);
}
int elim(int n)
{
    int N=n;redu.clear(); stack<int> S;
    for(int i=1;i<=n;++i) update(i);
    while(n>4)
    {
        if(redu.empty())return 0; --n;
        int x=*redu.begin(); redu.erase(redu.begin()); reduced[x]=1;
        int p[5],pc=0;
        for(IT it=G[x].begin();it!=G[x].end();++it)
        {
            p[pc++]=*it; G[*it].erase(x);
        }
        G[x].clear();
        int w=0;
        for(int i=0;i<pc;++i)
        {
            int ns=0; for(int j=0;j<pc;++j)ns+=G[p[i]].count(p[j]);
            if(ns==2){w=p[i];break;}
        }
        if(pc<3)return 0;
        if(pc==3)
        { S.push(p[0]); S.push(p[1]); S.push(p[2]); }
        else if(pc==4)
        {
            if(!w)return 0;
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[1]);
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[2]);
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[3]);
            if(p[0]==w || G[w].count(p[0])) return 0;
            G[w].insert(p[0]); G[p[0]].insert(w);
 
            S.push(w);S.push(p[0]);
            if(p[1]!=w)S.push(p[1]);
            if(p[2]!=w)S.push(p[2]);
            if(p[3]!=w)S.push(p[3]);
        }else if(pc==5)
        {
            if(!w)return 0;
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[1]);
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[2]);
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[3]);
            if(p[0]==w || G[w].count(p[0])) swap(p[0],p[4]);
            if(p[0]==w || G[w].count(p[0])) return 0;
            if(p[1]==w || G[w].count(p[1])) swap(p[1],p[2]);
            if(p[1]==w || G[w].count(p[1])) swap(p[1],p[3]);
            if(p[1]==w || G[w].count(p[1])) swap(p[1],p[4]);
            if(p[1]==w || G[w].count(p[1])) return 0;
            G[w].insert(p[0]); G[p[0]].insert(w);
            G[w].insert(p[1]); G[p[1]].insert(w);
 
            S.push(w);S.push(p[0]);S.push(p[1]);
            if(p[2]!=w)S.push(p[2]);
            if(p[3]!=w)S.push(p[3]);
            if(p[4]!=w)S.push(p[4]);
        }
        S.push(x); S.push(pc);
        for(int i=0;i<pc;++i)update(p[i]);
    }
    int ect=0,lc[10];
    for(int x=1;x<=N;++x){
        if(reduced[x])continue;
        if(G[x].size()!=3)return 0;
        lc[ect++]=x;
    } if(ect!=4)return 0;
    faces.clear();
    faces.insert(f(lc[0],lc[1],lc[2]));
    faces.insert(f(lc[0],lc[1],lc[3]));
    faces.insert(f(lc[0],lc[2],lc[3]));
    faces.insert(f(lc[1],lc[2],lc[3]));
    while(!S.empty())
    {
        int pc=S.top();S.pop();
        if(pc==3)
        {
            int x=S.top();S.pop();
            int p1=S.top();S.pop();
            int p2=S.top();S.pop();
            int p3=S.top();S.pop();
            II ff=faces.find(f(p1,p2,p3));
            if(ff==faces.end())return 0;
            faces.erase(ff);
            faces.insert(f(x,p1,p2));
            faces.insert(f(x,p1,p3));
            faces.insert(f(x,p2,p3));
        }else if(pc==4)
        {
            int x=S.top();S.pop();
            int p1=S.top();S.pop();
            int p2=S.top();S.pop();
            int p0=S.top();S.pop();
            int w=S.top();S.pop();
            II f1=faces.find(f(w,p0,p1));
            II f2=faces.find(f(w,p0,p2));
            if(f1==faces.end() || f2==faces.end())return 0;
            faces.erase(f1); faces.erase(f2);
            faces.insert(f(w,x,p1));
            faces.insert(f(w,x,p2));
            faces.insert(f(p0,x,p1));
            faces.insert(f(p0,x,p2));
        }else if(pc==5)
        {
            int x=S.top();S.pop();
            int p3=S.top();S.pop();
            int p2=S.top();S.pop();
            int p1=S.top();S.pop();
            int p0=S.top();S.pop();
            int w=S.top();S.pop();
            II f1=faces.find(f(w,p0,p3));
            II f2=faces.find(f(w,p1,p2));
            II f3=faces.find(f(w,p0,p1));
            if(f1==faces.end() || f2==faces.end() || f3==faces.end())
            {
                swap(p2,p3);
                f1=faces.find(f(w,p0,p3));
                f2=faces.find(f(w,p1,p2));
                f3=faces.find(f(w,p0,p1));
            }
            if(f1==faces.end() || f2==faces.end() || f3==faces.end())return 0;
            faces.insert(f(w,p3,x));
            faces.insert(f(p0,p3,x));
            faces.insert(f(p0,p1,x));
            faces.insert(f(p1,p2,x));
            faces.insert(f(w,p2,x));
        }
    }
    return 1;
}
void dit()
{
    int n,m; scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)G[i].clear(),reduced[i]=0;;
    for(int i=0;i<m;++i){
        int a,b;scanf("%d%d",&a,&b);
        G[a].insert(b);
        G[b].insert(a);
    }
    if(n==1){printf("1\n");return; }
    if(n==2){printf("%d\n",(m==1)?1:0);return; }
    if(n==3){printf("%d\n",(m==3)?1:0);return; }
    if(n==4){printf("%d\n",(m==6)?1:0);return; }
    if(n==5){printf("%d\n",(m>8&&m<10)?1:0);return;}
    if(m!=3*n-6){printf("0\n");return;}
    printf("%d\n",elim(n));
}
int main() 
{ int T;scanf("%d",&T);while(T--)dit();return 0; }