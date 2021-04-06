#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define ll long long int
using namespace std;
void fast()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
ll r,c,w,tot;
map<pair<ll,ll>,bool> edgsh,edgsv;
map<ll,ll> nodes;
ll root[400010],rep[400010];
ll z=1;
ll frst(ll x1,ll y1,ll x2,ll y2)
{
    if(x1==x2)
    {
        if(x1==1) return tot+1;
        return (x1-2)*(c-1)+min(y1,y2);
    }
    else
    {
        if(y1==1) return tot+4;
        return (min(x1,x2)-1)*(c-1)+(y1-1);
    }
}
ll scnd(ll x1,ll y1,ll x2,ll y2)
{
    if(x1==x2)
    {
        if(x1==r) return tot+3;
        return (x1-1)*(c-1)+min(y1,y2);
    }
    else
    {
        if(y1==c) return tot+2;
        return (min(x1,x2)-1)*(c-1)+y1;
    }
}
ll anc(ll x)
{
    return root[x]==x?x:(root[x]=anc(root[x]));
}
bool check(ll u,ll v,bool dir)
{
    if(nodes.find(v)==nodes.end()) return 0;
    if((dir && edgsv.find({u,v})!=edgsv.end()) || 
        (!dir && edgsh.find({u,v})!=edgsh.end())) return 0;
    u=nodes[u];
    v=nodes[v];
    if((u=anc(u))==(v=anc(v))) return 1;
    return 0;
}
bool chkForOne()
{
    bool flag=0;
    for(ll i=1;i<z;i++)
    {
        ll vertex=rep[i];
        ll rgt=vertex%(c-1)==0?tot+2:(vertex+1);
        ll lft=(vertex-1)%(c-1)==0?tot+4:(vertex-1);
        ll upw=(vertex-(c-1))<0?tot+1:(vertex-(c-1));
        ll dwn=(vertex+(c-1))>((r-1)*(c-1))?tot+3:(vertex+(c-1));
        // cout<<lft<<" "<<rgt<<" "<<upw<<" "<<dwn<<endl;
        flag=flag || check(vertex,rgt,0) || check(vertex,lft,0) || 
                check(vertex,upw,1) || check(vertex,dwn,1);
        if(flag) break;
    }
    return flag;
}
int main()
{
    fast();
    int t; cin>>t;
    while(t--)
    {
        edgsh.clear();
        edgsv.clear();
        nodes.clear();
        z=1;
        cin>>r>>c>>w;
        tot=(r-1)*(c-1);
        // int root[2*w+5],rep[2*w+5]={0};
        // memset(rep,0,sizeof(rep));
        // memset(root,0,sizeof(root));
        bool cycle=0;
        nodes[0]=0;
        rep[0]=0;
        for(int i=1;i<=4;i++) 
        {
            nodes[tot+i]=2*w+i;
            rep[2*w+i]=tot+i;
            root[2*w+i]=0;
        }
        for(ll i=0;i<=2*w;i++) root[i]=i;
        for(ll i=0;i<w;i++)
        {
            ll x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
            if(cycle) continue;
            ll fst,scd;
            ll u,v;
            fst=frst(x1,y1,x2,y2);
            scd=scnd(x1,y1,x2,y2);
            // cout<<fst<<" "<<scd<<endl;
            if(nodes.find(fst)==nodes.end())
            { rep[z]=fst; nodes[fst]=z++; }
            u=nodes[fst];
            if(nodes.find(scd)==nodes.end())
            { rep[z]=scd; nodes[scd]=z++;}
            v=nodes[scd];
            if((x1==x2 && edgsv.find({fst,scd})==edgsv.end()) ||
               (y1==y2 && edgsh.find({fst,scd})==edgsh.end()))
            {
                if((u=anc(u))==(v=anc(v))) cycle=1;
                else
                { root[u]=v; }
                if(x1==x2) { edgsv[{fst,scd}]=1; edgsv[{scd,fst}]=1;}
                else { edgsh[{fst,scd}]=1; edgsh[{scd,fst}]=1;}
            }
        }
        // cout<<z<<endl;
        if(r==1 && c==1) cout<<"Chefland is doomed"<<endl;
        else if(r==1 || c==1)
        {
            if(w>0) cout<<0<<endl;
            else cout<<1<<endl;
        }
        else
        {
            if(cycle) cout<<0<<endl;
            else
            {
                if(w>0 && chkForOne()) cout<<1<<endl;
                else cout<<2<<endl;
            }
        }
    }
    return 0;
}
/*9
4 4 3
1 1 1 2
1 4 2 4
1 1 2 1
2 2 2
1 1 1 2
1 2 2 2
4 4 2
1 1 1 2
1 1 2 1
4 4 1
1 1 1 2
4 4 1
1 1 2 1
4 1 1
2 1 3 1
4 4 2
1 2 1 3
2 1 3 1
4 4 3
1 2 1 3
2 1 3 1
2 2 3 2
4 4 4
1 2 1 3
2 1 3 1
2 2 2 3
2 2 3 2*/


/*1
7 7 12
1 3 1 4
2 3 2 4
2 4 3 4 
2 5 3 5
3 4 3 5
4 4 4 5
5 2 5 3
4 3 5 3
4 4 5 4 
4 5 5 5
5 5 5 6
5 6 6 6*/

/*1
5 2 1
3 1 4 1*/