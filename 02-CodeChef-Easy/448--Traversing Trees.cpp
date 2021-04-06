  #include<bits/stdc++.h>
            using namespace std;
            typedef long long int lli;
            #define fi(n) for(lli i=0;i<n;i++)
            #define fj(n) for(lli j=0;j<n;j++)
            #define pb push_back
            #define mp make_pair
            #define F first
            #define S second
            #define pii pair<lli,lli>
            #define MAX 200001
            #define INF (int)1e18
            #define vii vector<lli>
            lli mod=1000000007;
            vii g[MAX];
            int vis[MAX][2];
            lli pa[MAX],a[MAX];            
           /* bool comp(pii a,pii b)
            {
                if(a.F==b.F){return a.S<b.S;}
                return a.F<b.F;
            }*/
            /*lli modexp(lli x,lli y) 
            { 
                if (y == 0) 
                    return 1; 
                lli p = modexp(x, y/2) % mod; 
                p = (p * p) % mod; 
              
                return (y%2 == 0)? p : (x * p) % mod; 
            } */
            /*lli gcdext(lli a,lli b,lli *x,lli *y);
            lli modexpcop(lli a,lli m);
            lli modexpcop(lli a,lli m)   // a.x= 1 mod m  //a.x+b.y =gcd(a,b) extended
            {                            // for this b=m
                lli x,y;
                lli g=gcdext(a,m,&x,&y);
                if(g!=1)
                {
                    //inverse does not exists
                }
                else
                {
                    lli res=(x%m+m)%m;
                    return res;
                }
            }
            lli gcdext(lli a,lli b,lli *x,lli *y)
            {
                if(a==0)  //base case
                {
                    *x=0;*y=1;
                    return b;
                }
                lli x1,y1;
                lli g=gcdext(b%a,a,&x1,&y1);
                *x=y1-(b/a)*x1;
                *y=x1;
                return g;
            }*/
           /* vector<lli> v;
            bool a[MAX];
            bool b[MAX];
            void sieve()
            {
                for(lli i=0;i<MAX;i++)
                {
                    a[i]=true;
                    b[i]=false;
                }
                a[0]=false;a[1]=false;
                for(int i=4;i<MAX;i+=2)
                {
                    a[i]=false;
                }
                v.pb(2);
                for(lli i=3;i<MAX;i++)
                {
                    if(a[i]==true)
                    {
                        v.pb(i);
                        for(lli j=i*i;j<MAX;j+=i)
                        {
                            a[j]=false;
                        }
                    }
                }
            }*/
        
            /*lli f[100001];
            void fib()
            {
                f[0]=1;f[1]=1;f[2]=2;
                for(lli i=3;i<=100000;i++)
                {
                    f[i]=f[i-1]%mod+f[i-2]%mod;
                    f[i]=f[i]%mod;
                }
            }*/
            void parent(lli idx,lli p)
            {
                pa[idx]=p;
                for(auto x:g[idx])
                {
                    if(x!=p)
                    {
                        parent(x,idx);
                    }
                }
            }
            void dfs(lli idx,int lvl,lli p,lli so)
            {
                if(idx!=so && lvl==0)
                {
                    a[so]+=a[idx];
                    a[idx]=0;
                }
                if(!vis[idx][lvl])
                {
                    for(auto x:g[idx])
                    {
                        if(x!=p)
                        {
                            dfs(x,lvl^1,idx,so);
                        }
                    }
                }
                vis[idx][lvl]=1;
            }
            int main()
            {
                ios_base::sync_with_stdio(false);
                cin.tie(NULL);
                cout.tie(NULL);
                lli t;
                cin>>t;
                while(t--)
                {
                    lli n,q,u,v;
                    cin>>n>>q;
                    fi(n)
                    {
                        g[i].clear();
                        vis[i][0]=0;vis[i][1]=0;
                    }
                    //lli a[n];
                    fi(n)
                    {
                        cin>>a[i];
                    }
                    fi(n-1)
                    {
                        cin>>u>>v;
                        u--;v--;
                        g[u].pb(v);
                        g[v].pb(u);
                    }
                    parent(0,-1);
                    while(q--)
                    {
                        cin>>u;
                        u--;
                        if(vis[u][0]==0)
                        {
                            dfs(u,0,pa[u],u);
                            vis[u][0]=1;
                        }
                    }
                    fi(n)
                    {
                        cout<<a[i]<<" ";
                    }
                    cout<<"\n";
                }
                return 0;
            }    