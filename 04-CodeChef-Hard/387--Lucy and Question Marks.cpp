#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll trie[1008][28],f[1009],fr[1009],to[1009][28];
ll dp[1009][1009];
ll nd,idd,n,k;
ll nwnod()
{
    nd++;
    for(int i=0;i<28;i++)trie[nd][i]=-1;
    for(int i=0;i<1009;i++)dp[i][nd]=-1;
    fr[nd]=0;
    return nd;
}
void init()
{
    idd=0;
    nd=-1;
    nwnod();

}
ll insert(string &s)
{
    ll u=0;
    for(int i=0;i<s.size();i++)
    {
        if(trie[u][s[i]-'a']==-1)trie[u][s[i]-'a']=nwnod();
        u=trie[u][s[i]-'a'];
    }
    fr[u]++;
    }
 void build()
 {
     queue<ll>q;
     for(int i=0;i<26;i++)
     {
         ll&u=trie[0][i];
         if(u!=-1)
         {
             f[u]=0;
             q.push(u);
         }
         else u=0;
         to[0][i]=u;
     }
    while(!q.empty())
    {
        ll r=q.front();
        fr[r]+=fr[f[r]];
        for(int i=0;i<26;i++)
        {to[r][i]=to[f[r]][i];
        if(trie[r][i]!=-1)to[r][i]=trie[r][i];}
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(trie[r][i]==-1)continue;
            ll g=f[r];
            while(trie[g][i]==-1)g=f[g];
            f[trie[r][i]]=trie[g][i];
            q.push(trie[r][i]);

        }
    }

 }
 string s;
ll go(ll x,ll nod)
{
    if(x==s.size())return dp[x][nod]=fr[nod];
    if(dp[x][nod]!=-1)return dp[x][nod];
    ll ans=0;
    if(s[x]!='?')return dp[x][nod]=fr[nod]+go(x+1,to[nod][s[x]-'a']);
    for(int i=0;i<26;i++)
        ans=max(ans,go(x+1,to[nod][i]));
      ans+=fr[nod];
     return dp[x][nod]=ans;

}
void fuck(ll x,ll nod)
{
    if(x==s.size())return;
    if(s[x]!='?'){cout<<s[x];fuck(x+1,to[nod][s[x]-'a']);return;}
    for(int i=0;i<26;i++)
    if(fr[nod]+dp[x+1][to[nod][i]]==dp[x][nod]){cout<<char('a'+i);fuck(x+1,to[nod][i]);return;}
}
int main()
{
ll t;
cin>>t;
while(t--)
{
   init();
   //memset(dp,-1,sizeof dp);
  cin>>n>>k;
  cin>>s;
  string w;
  while(k--)
  {
      cin>>w;
      insert(w);
  }
 build();
 cout<<go(0,0)<<endl;
 fuck(0,0);
 cout<<endl;

}

    return 0;
}
