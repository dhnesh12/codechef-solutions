#include<bits/stdc++.h>

using namespace std;

//#define int long long 
#define TESTCASES false
#define FASTIO true
const int inf = (int)1e18 + 1;
const int MOD =  998244353;
const int maxN = 1000009;
long long score;

int N,K;
int a[maxN];
long long ans[maxN];
int par[maxN];
int rnk[maxN];
int siz[maxN];
int Kpow[maxN];

long long exp(long long x,long long n)
{
    long long ret =1;
    while(n>0)
    {
        if(n&1)
        {
            ret=(ret*x)%MOD;
        }
        n>>=1;
        x=(x*x)%MOD;
    }
    return ret;
}

long long inv(long long x)
{
    return exp(x,MOD-2);
}
int Find(int u)
{
    if(par[u]==u)return u;
    return par[u]=Find(par[u]);
}

void Union(int u,int v)
{
    u=Find(u);
    v=Find(v);
    long long su =siz[u];
    long long sv= siz[v];

    if(rnk[u]<rnk[v])
    {
        par[u]=v;
        siz[v]+=siz[u];
    }
    else
    {
        par[v]=u;
        siz[u]+=siz[v];
    }
    if(rnk[u]==rnk[v])
    {
        rnk[u]++;
    }
    score+=exp(su+sv,K);
    score%=MOD;
    score+=(MOD-exp(su,K));
    score%=MOD;
    score+=(MOD-exp(sv,K));
    score%=MOD;
}

void solve()
{ 
    int i,j,k;
    cin >> N >> K;
   

    string s;
    cin >> s;
    s+='$';
    int n = N+1;

    vector<int> p(n,0),c(n,0),cnt(max(n,(int)256),0);
    for(i=0;i<n;i++)
    {
        cnt[s[i]]++;
    }
    for(i=1;i<cnt.size();i++)
    {
        cnt[i]+=cnt[i-1];
    }
    for(i=0;i<n;i++)
    {
        p[--cnt[s[i]]]=i;
    }
    c[p[0]]=0;
    int cc = 1;
    for(i=1;i<n;i++)
    {
        if(s[p[i]]!=s[p[i-1]])
        {
            cc++;
        }
        c[p[i]]=cc-1;
    }

    vector<int> cn(n,0),pn(n,0);

    int h;
    for(h=0;(1<<h)<n;h++)
    {
        for(i=0;i<n;i++)
        {
            pn[i]=p[i]-(1<<h);
            if(pn[i]<0)pn[i]+=n;
        }
        for(i=0;i<cnt.size();i++)
        {
            cnt[i]=0;
        }
        for(i=0;i<n;i++)
        {
            cnt[c[pn[i]]]++;
        }
        for(i=1;i<cnt.size();i++)
        {
        	cnt[i]+=cnt[i-1];
        }
        for(i=n-1;i>=0;i--)
        {
            p[--cnt[c[pn[i]]]]=pn[i];
        }
        cn[p[0]]=0;
        int cc = 1;
        for(i=1;i<n;i++)
        {
            pair<int,int> prev = {c[p[i-1]],c[(p[i-1]+(1<<h))%n]};
            pair<int,int> curr = {c[p[i]],c[(p[i]+(1<<h))%n]};
            if(prev!=curr)cc++;
            cn[p[i]]=cc-1;
        }

        c=cn;      
    }
    
    p.erase(p.begin());
    n--;
    
    int lcp[n-1];

    int Rank[n];
    for(i=0;i<n;i++)
    {
        Rank[p[i]]=i;
      //  cout << p[i] << " ";
    }

    
    k =0;
    for(i=0;i<n;i++)
    {
        if(Rank[i]==n-1)
        {
            k=0;
            continue;
        }
        int j = p[Rank[i]+1];
        while((i+k<n) && (j+k<n) && s[i+k]==s[j+k])
        {
            k++;
        }
        lcp[Rank[i]]=k;
        if(k)k--;
    }
    vector<int> lpos[n+1];
    for(i=0;i<n-1;i++)
    {
       // cout << lcp[i] << " ";
    }
    //cout << "\n";

    for(i=0;i<n-1;i++)
    {
        lpos[lcp[i]].push_back(i);
    }
    for(i=0;i<n;i++)
    {
        par[i]=i;
        rnk[i]=0;
        siz[i]=1;
    }
    score=0;
    for(i=n;i>=1;i--)
    {
        score++;
        score%=MOD;
        for(int p:lpos[i])
        {
            Union(p,p+1);
        }
        ans[i]=score;
    }

    for(i=1;i<=n;i++)
    {
        ans[i]*=inv(exp((n+1-i),K));
        ans[i]%=MOD;
    }

    for(i=1;i<=n;i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";
    

}

signed main()
{
    int i,j,k;
    int T = 1;
    if(FASTIO)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }
    if(TESTCASES)
    {
        cin >> T;
    }
    while(T--)
    {
        solve();
    }
}