#include <bits/stdc++.h>
using namespace std;

// Hate My Life //

#define ff first
#define ss second
#define pb push_back
#define pf push_front
#define ppb pop_back()
#define ppf pop_front()
#define all(vec) vec.begin(), vec.end()
#define fol(i,a,b) for(int i=a;i<b;i++)
#define loop(i,a,b) for(int i=a;i>=b;i--)
#define forr(x,arr) for(auto& x:arr)
#define mod 998244353
#define INF 0x3f3f3f3f3f3f3f3f
#define EPS 1e-7
#define sz(x) ((lli)(x).size())

using   lli     =   long long;
using   lld     =   long double;
using   ulli    =   unsigned long long int;
using   pll     =   pair<lli, lli>;
using   ttt     =   pair<lli, pll>;
using   vttt    =   vector<ttt>;
using   vll     =   vector<pll>;
using   vl      =   vector<lli>;
using   vi      =   vector<int>;
using   vvi     =   vector<vector<int>>;
using   cd      =   complex<lld>;
const double PI = acos(-1);

#ifndef tejasp
#define trace(...) {}
#define cotra(...) {}
#define end_routine() {}
#define localsys 0
#define endl '\n'
#endif 

#define FMAX 100010
lli tre[FMAX];

void add(int x, lli val) {
    tre[x]+=val;
}

void add(int l, int r, lli val) { add(l,val); add(r+1,-val); }

void process (int prev, int nex, int off, int n, int val) {
    // trace(prev,nex,val)
    prev-=off; nex-=off;
    prev=((prev%n)+n)%n; 
    nex=((nex%n)+n)%n;
    if(prev>nex) {
        add(prev,n-1,val);
        add(0,nex,val);
    }
    else add(prev,nex,val);
}

int tejas_919(int kkkk)
{
    fol(i,0,FMAX) tre[i]=0;
    int n, m, k, q, u, v, temp=0, ans=1;
    cin>>n>>k;
    int posa[n+5]={}, posb[n+5]={};
    fol(i,0,n) {
        cin>>u;
        posa[u]=i;
    }
    fol(i,0,n) {
        cin>>u;
        posb[u]=i;
    }
    fol(i,1,n+1) {
        int off = posb[i]-posa[i];
        int prev=1, nex=1, val=0;
        trace(i,posa[i],posb[i])
        while(posa[i]+prev<n) {
            process(prev,min(nex,n-1-posa[i]),off,n,val);
            prev=nex+1;
            nex=2*nex+1;
            val++;
        }
        prev=1; nex=1; val=0;
        while(posa[i]-prev>=0){
            process(-min(nex,posa[i]),-prev,off,n,val);
            prev=nex+1;
            nex=2*nex+1;
            val++;
        }
    }

    ans = tre[0];
    fol(i,1,k) {
        tre[i] += tre[i-1];
        ans = (ans*tre[i])%mod;
    }

    cout<<ans<<endl;
    return 0;
}

signed main()
{
    #ifdef tejasp
            freopen("input.txt", "rt", stdin);
            freopen("output.txt", "wt", stdout);
    #endif
    if(!localsys) { ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); }
    cout << fixed << setprecision(10);
    int t=1;
    cin>>t;
    fol(i,0,t) { tejas_919(i+1); }
    end_routine();
    //if(localsys) system("pause");
}