/*
Author : 
    अंशुमान मिश्र
    compiler flag = g++ -std=c++17 <name>.cpp
    
We sort the queries based on magic number
We sort the edges based on their weights //priority queue of pairs

for each k
    We iterate over sorted edge priority queue
    now we need to add xor of only those edges which are in subtree of lca of 
    the two nodes or following property of xor
    we need to Xor and sum all edges with , arrival time > and departure time> for U and arrival time < and departure time > than V
    weights <=k

    // use segment tree to determine edges in subtree?
    
    */



#include <bits/stdc++.h>
using namespace std;


typedef long long					ll;
typedef unsigned long long  		ull;
typedef pair<int,int> 				pii;
typedef pair<ll,ll> 				pll;
typedef map<int,int> 				mii;
typedef map<ll,ll> 		    		mll;
typedef unordered_map<int,int> 		umii;
typedef unordered_map<ll,ll>   		umll;
#define Fast	 					ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define v    						vector
#define pq  	 					priority_queue
#define F    	 					first
#define S    	 					second
#define pb    	 					push_back
#define prec(a,x)    	 			cout<<fixed<<setprecision(x)<<a<<'\n';
#define all0(x) 					(x).begin(),(x).end()
#define all1(x) 					(x).begin()+1,(x).end()

ll nxtl(){ll x;cin>>x;return x;}
int nxt(){int x;cin>>x;return x;}

const int32_t MOD = 1e9 + 7;
const ll INF = 1e18;


template <typename T> void printmap(mii m){
   for (auto it=m.begin();it!=m.end();++it)
      cout<<it->F<<' '<<it->S<<'\n';
    cout<<'\n';
}
const int N = 1<<17;
template<typename T> void printvec(v<T> a){
    for (T i:a) cout<<i<<' ';cout<<'\n';
}

int T=0,n,a,b,c;
int ans[N],q1[N],q2[N]; // queries
int bit[N]; // binary index tree
v<int> V[N]; // tree
pii E[N]; // edge list
int W[N]; // weights of edges
int st[N],en[N]; //arrival and departure time

int add(int x,int p){
    while(x<=n){
        bit[x]^=p;
        x+=x&(-x); // add to all a[i] such that i > p
    }
}

int get(int x){
    int sum = 0;
    while (x)
    {
        sum^=bit[x];
        x-=x&(-x);
    }
    return sum;
}

void DFS(int i,int par){
    st[i] = ++T;
    for (auto e:V[i]){
        if (e!=par) DFS(e,i);
    }
    en[i] = T;
}

void Work(){
    T = 0;n = nxt();
    for (int i=0;i<=n;++i){
        bit[i]=0;
        V[i].clear();
    }    

    for (int i=1;i<n;i++){
        cin>>a>>b>>c;
        V[a].pb(b);
        V[b].pb(a);
        E[i]={a,b}; //push edge to edge list
        W[i]=c; //wt of corresp edge
    }
    //tree rooted at 1
    DFS(1,-1); //generates starting and ending time in st and end
    v<pii> sorted;

    for (int i=1;i<n;i++){
        if (st[E[i].F]<st[E[i].S])
            swap(E[i].F,E[i].S);
        sorted.pb({W[i],-E[i].F}); //edge is btw U and V , with weight wt ; we push {wt,min(U,V)}
    }

    int q = nxt();
    
    for (int i=1;i<=q;++i){
        cin>>a>>b>>c;
        q1[i]=a;q2[i]=b;
        sorted.pb({c,i});
    }
    sort(sorted.begin(),sorted.end());
    //for (int i=0;i<n;++i)
     //   cout<<st[i]<<' ';cout<<endl;
    for (auto Q:sorted){
        if (Q.S>=0){//query
            int idx = Q.S;
            //cout<<get(st[q1[idx]])<<" "<<get(st[q2[idx]])<<'\n';
            ans[idx] = get(st[q1[idx]])^get(st[q2[idx]]);
        }
        else{
            int node = -Q.S;
            add(st[node],Q.F); // add to all nodes with st > st[node]
            add(en[node]+1,Q.F); // add to all nodes with en > sen[node]
            // now when we query we will get xored with st[node]<=i<=en[node]
        }
    }
    for(int i=1;i<=q;++i)
        cout<<ans[i]<<'\n';
}

void solve(){
    int t=nxt();
    while(t--){
        Work();
    }
}

signed main()
{
    clock_t begin = clock(); Fast
    #ifdef NCR
        ncrinit();
    #endif
    #ifdef fft
        FFT::FFTinit()
    #endif
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif


    solve();

    #ifndef ONLINE_JUDGE
        clock_t end = clock();
        cout<<"\n\nExecuted in : "<<double(end-begin)/CLOCKS_PER_SEC*1000<<"ms\n";
    #endif
    return 0;
}