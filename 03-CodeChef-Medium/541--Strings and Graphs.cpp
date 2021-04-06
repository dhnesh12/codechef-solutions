/*
   Salim Shebli
   Russian,Syrian
   Faculty Of Information Technology
   Game Developer
 */
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>

using namespace std;

ll n,m;
vector<ll>g[100100];
ll dis[100100];
ll cur[100100];
ll sol[100100];
ll ds[100100];
ll pos[100100];
int main() {
    ios::sync_with_stdio(false);

    ll t;
    cin>>t;
    while(t--) {
        cin>>n>>m;
       // can=true;
    //    ord.clear();
        for(int i=0;i<=n+1;i++)
        {
            g[i].clear();
        //    cl[i]=0;
            dis[i]=1e9;
            cur[i]=0;
            sol[i]=0;
            ds[i]=0;
            pos[i]=-1;
        }
        for(int i=0;i<m;i++)
        {
            ll a,b;
            cin>>a>>b;
            g[a].pb(b);
            ds[b]++;
        }
          bool ccc=true;
        for(int i=0;i<=n;i++)
        {
            sort(g[i].begin(),g[i].end());
            set<ll>toUse;
            for(int j=1;j<=g[i].size();j++)
                toUse.insert(j);
            for(int j=0;j<g[i].size();j++)
            {
                ll to=g[i][j];
                if(sol[to]!=0)
                {

                    toUse.erase(sol[to]);
                }
            }
            ll vv=0;
           // ll mx=g[i].size()+1;
            for(int j=0;j<g[i].size();j++)
            {
                ll to=g[i][j];
                if(sol[to]==0)
                {
                    if(i!=0)
                    {
                        vv++;
                        sol[to]=sol[i];
                      //  toUse.erase(sol[to]);
                    }
                    else{
                        sol[to]=*toUse.begin();
         //               cout<<to<< "   "<<sol[to]<<endl;
                        toUse.erase(toUse.begin());

                    }
                }
            }
            if(vv>1)
                ccc=false;
      //  cout<<i<<" "<<sol[i]<<endl;
        if(!ccc)
            break;
//            if(ccc==false)
  //              break;
        }
        if(!ccc)
        {
            cout<<-1<<endl;
            continue;
        }
        set<ll>pv;
        ll mxx=-1;
        for(int i=n;i>=0;i--)
        {

            if((sol[i]==0&&i!=0)||g[i].size()>g[0].size())
            {
                ccc=false;
                break;
            }
          //  ds[i]=pv.size();
            set<ll>xx;
            for(int j=0;j<g[i].size();j++)
            {
                ll to=g[i][j];
                if(to<=i)
                    ccc=false;
                xx.insert(to);
            }
            if(xx.size()!=g[i].size())
            {
                ccc=false;
                break;
            }
           // if(xx.size()>g[0].size)
            if(xx.size()!=pv.size())
            {
                ccc=false;
                break;
            }
            auto it1=xx.begin();
            auto it2=pv.begin();
            for(int j=0;j<xx.size();j++)
            {

                if(*it1!=*it2)
                {
                    ccc=false;
                    break;
                }
                it1++;
                it2++;
            }
            if(pos[sol[i]]==-1)
                pv.insert(i);
            else{
                pv.erase(pos[sol[i]]);
                pv.insert(i);
            }
            pos[sol[i]]=i;
            if(!ccc)
                break;
        }
        if(!ccc)
        {
            cout<<-1<<endl;
            continue;
        }

        for(int i=1;i<=n;i++)
        {
            if(i!=n)
            {
                cout<<sol[i]<<" ";
            }
            else cout<<sol[i]<<endl;
        }
    }
    return 0;
}
