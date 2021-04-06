    /*input
    1
    34
    6311861109697810998905373107116111
    10 4 25
    */
    #include<bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    typedef vector<int> vi;
    typedef vector<ll> vll;
    typedef vector<vi> vii;
    typedef pair<int,int> pii;
    typedef list<int>li;
    typedef list<li>lii;
    typedef set<int>si;
    typedef set<ll> sl;
    typedef set<si>sii;
    typedef map<int,int> mi;
    typedef map<ll, ll> mll;
    #define be_fast std::ios::sync_with_stdio(false);std::cin.tie(NULL); std::cout.tie(NULL);
    #define print cout <<
    #define bitlezero(n) __builtin_clz(n)    //trailing zeroes
    #define bitone(n) __builtin_popcount(n)        //1-count
    #define bittrzero(n) __builtin_ctz(n)            //trailing zeroes
    #define ict ll t;cin>>t;while(t--)
    #define lp(n)  for(ll i=0;i<n;i++)
    #define lpe(n) for(ll i=1;i<=n;i++)
    #define loop(a,b,c)   for (int (a)=(b); (a)<(c); ++(a))
    #define loopn(a,b,c)  for (int (a)=(b); (a)<=(c); ++(a))
    #define loopd(a,b,c)  for (int (a)=(b); (a)>=(c); --(a))
    #define MOD 1000000007
    #define INF 0x3f3f3f3f
    #define limit 100000+5
    #define pb push_back
    #define mp make_pair
    #define X first
    #define Y second
    #define takeline(str) getline(cin, str)
    #define all(c) c.begin(), c.end()    //iterator range
    #define rall(c) c.rbegin(),c.rend()    //reverse all iterator
    #define tr(c,i) for(typeof((c).begin() i = (c).begin(); i != (c).end(); i++))
    #define present(c,x) ((c).find(x) != (c).end())
    #define cpresent(c,x) (find(all(c),x) != (c).end())
    ll check(ll gd,string s,ll in,ll n,ll x,ll y,ll m)
    {   
        // cout<<"\n"<<gd<<" "<<in;
        ll pd,c=0;
        for(ll i = in;i<n;)
        {   c++;
            // cout<<"A";
            ll il;
            ll g=1;
            char b[11];
            ll kd = -1;
            b[10]='\0';
            for(ll j = i,k=0;j<n&&k<m;j++,k++)
            { 
                if(k!=9 ) {b[k] = s[j];
              b[k+1] = '\0';}
              ll no = atoi(b);
              if(k==9)
              {
                no*=10;
                no+=(s[j]-'0');
              }
              // cout<<no<<" "<<k<<"k ";
              pd = __gcd(gd,no);
              if(pd>kd)
              {
                il=j+1; 
                kd = pd;
              }
            }
            gd = kd;
            // cout<<" " <<gd<<" ";
            if(gd==1)
            { 
                return 1;
            }
            i = il; 
        }
        // cout<<c<<" ";
         if(c>=x)
         { 
            return gd;
         } 
         // cout<<gd<<"G "; 
         if(gd!=0) return 1;
         else return 0;
    }
    int main()
    {
        be_fast;
        ict{
            ll n; cin>>n;
            string s; cin>>s;
            ll m,x,y;
     
            cin>>m>>x>>y;
            ll g = 0,i1,i2;
            for(ll i=m;i>=1;i--)
            {   if(n<=i) {g=0;continue;}
                char a[i+1];
                a[i] = '\0'; 
                for(ll j=0;j<i&&j<9;j++) a[j]=s[j];
                ll no = atoi(a);
            if(i==10)
            {
                no*=10;
                no+=(s[9]-'0');
            }
            // cout<<g<<" gd";
            // cout<<no<<" "<<i<<"i ";
                // char b[i+1];
                // for(ll j=i,k=0;k<m&&j<n;j++,k++)
                // {
                //     b[k] = s[j];
                //     b[k+1] = '\0';
                //     ll no2 = atoi(b);
                //     // cout<<no2<<" ";
                //     ll p = n-1-j;
                //     ll q;
                //     if(p==0) q=1;
                //     else q=2;
                //     ll gd = __gcd(no,no2);
                    // cout<<gd<<" ";
                    ll gd = check(no,s,i,n,x,y,m);
                    // cout<<g<<"A";
                    // cout<<gd<<" ";
                    g = max(gd,g);
                    
                // }    
            }
            cout<<g<<endl;
        }
        
        return 0;
    } 