#include<bits/stdc++.h>
// #define int long long
using namespace std;
 

long long power(long long a, long long b,long long m) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a %m;
        a = a * a %m;
        b >>= 1;
    }
    return res;
}

vector<vector<pair<int,int> > >adj;
int ss,t;
int n;
int dis[100005];
set<int>s[100005];

int dik()
{
    for(int i=1;i<=n;i++)
    {
        dis[i]=1e8;
    }

    deque<pair<int,int> >qq;
    int mn=1e8;
    for(auto i:adj[ss])
    {
        dis[i.first]=0;
        s[i.first].insert(i.second);
        qq.push_back({0,i.first});
        if(i.first==t)
            mn=0;
    }

    while (!qq.empty())
    {
        pair<int,int>pp=qq.front();
        if(pp.second==t)
        {
            mn=min(mn,pp.first);
        }
        qq.pop_front();

        for(auto i:adj[pp.second])
        {
            if(s[pp.second].find(i.second)!=s[pp.second].end())
            {
                if(dis[i.first]>pp.first)
                {
                    s[i.first].clear();
                    dis[i.first]=pp.first;
                    s[i.first].insert(i.second);
                    qq.push_front({dis[i.first],i.first});
                }
                else if(dis[i.first]==pp.first)
                {
                    s[i.first].insert(i.second);
                }
            }
            else
            {
                if(dis[i.first]>1+pp.first)
                {
                    dis[i.first]=1+pp.first;
                    s[i.first].clear();
                    s[i.first].insert(i.second);
                    qq.push_back({dis[i.first],i.first});
                }
                else if(dis[i.first]==1+pp.first)
                {
                    s[i.first].insert(i.second);
                }
            }
        }
    }
    return mn;
}

signed main()
{
 
ios_base::sync_with_stdio(false);
cin.tie(NULL);  
cout.tie(0);   
 
#ifndef ONLINE_JUDGE
    if(fopen("INPUT.txt","r"))
    {
    freopen ("INPUT.txt" , "r" , stdin);
    freopen ("OUTPUT.txt" , "w" , stdout);
    }
#endif      

    int m;
    cin>>n>>m;
    adj.resize(n+1);
    int x,y,z;
    for(int i=0;i<m;i++)
    {
        cin>>x>>y>>z;   
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
    }              
    cin>>ss>>t;
    cout<<dik();

}
