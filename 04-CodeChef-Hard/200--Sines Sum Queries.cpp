#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define mx 300000
#define dx mx*5
struct ext{
   double sn,cs;
};
ext tree[dx];
ll lazy[dx];
double calcos(double d)
{
   if(d==0)return 0;
   double x=(d+1)/2;
   double y=d/2;
   return (cos(x)*sin(y))/sin(0.5);
}
double calsin(double d)
{
  // if(d==0)return 0;
      if(d==0)return 0;
   double x=(d+1)/2;
   double y=d/2;
   return (sin(x)*sin(y))/sin(0.5);
}

vector<int>vc;
void update(int node,int st,int en)
{
    double x=lazy[node];
    double sn=sin(x);
    double cs=cos(x);
    ext ret;
     int d=1;
    ret.sn=(tree[node].sn*cs+tree[node].cs*sn)*d;
    ret.cs=(tree[node].cs*cs-tree[node].sn*sn)*d;
    //lazy[node]=0;
    if(st!=en)
    {
        lazy[node*2]+=lazy[node];
        lazy[node*2+1]+=lazy[node];
    }
    lazy[node]=0;
    tree[node]=ret;
}

void build(int node,int st,int en)
{   lazy[node]=0;

    if(vc[st]==0){
        tree[node].sn=calsin(vc[en+1]-1);
        tree[node].cs=calcos(vc[en+1]-1)+1;
    }
    else{
    tree[node].sn=calsin(vc[en+1]-1)-calsin(vc[st]-1);
    tree[node].cs=calcos(vc[en+1]-1)-calcos(vc[st]-1);
    }
    if(st==en)return ;
    int mid=(st+en)>>1;
    build(node*2,st,mid);
    build(node*2+1,mid+1,en);
}
void update(int node,int st,int en,int l,int r,int x)
{
    if(lazy[node]){
       update(node,st,en);
    //   return ;
    }
    if(st>r or en<l)return ;
    if(st>=l and en<=r)
    {
        lazy[node]+=x;
        update(node,st,en);
        return ;
    }
    int mid=(st+en)>>1;
    update(node*2,st,mid,l,r,x);
    update(node*2+1,mid+1,en,l,r,x);
    tree[node].sn=tree[node*2].sn+tree[node*2+1].sn;
     tree[node].cs=tree[node*2].cs+tree[node*2+1].cs;
}
double query(int node,int st,int en,int l,int r)
{
   if(st>r or en<l)return 0;
   if(lazy[node])update(node,st,en);
   if(st>=l and en<=r)return tree[node].sn;
   int mid=(st+en)>>1;
   double ret=0;
   ret+=query(node*2,st,mid,l,r);
   ret+=query(node*2+1,mid+1,en,l,r);
   return ret;
}
struct dim{
 int l,r,d;

};
dim Q[mx];
int main()
{
    int i,j,k,l,m,n,q;
    int ts;
   // cout<<sin(0)<<endl;

      //  vector<int>vc;
      vc.clear();
        scanf("%d%d",&n,&q);
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].d);
            Q[i].r++;
            vc.pb(Q[i].l);
            vc.pb(Q[i].r);
        }
        vc.pb(0);
        vc.pb(n);
        sort(vc.begin(),vc.end());
        vc.resize(unique(vc.begin(),vc.end()) - vc.begin());
        int sz=vc.size();
        build(1,0,sz-2);
        for(int i=1;i<=q;i++)
        {
            int c=lower_bound(vc.begin(),vc.end(),Q[i].l)-vc.begin();
            int d=lower_bound(vc.begin(),vc.end(),Q[i].r)-vc.begin();
            d--;
            int x=Q[i].d;
            if(x)update(1,0,sz-2,c,d,x);
            else{
               double ans=query(1,0,sz-2,c,d);
              // assert(ans>=0);
               printf("%.7lf\n",ans);
            }
        }

}
