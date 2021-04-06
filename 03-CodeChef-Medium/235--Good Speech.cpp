/*
MAY THE CODE BE WITH YOU

				-KANDI
*/
#include<bits/stdc++.h>
#define ll long long
#define LOCAL 0
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define vll vector<ll>
#define llin(a) ll a; cin>>a;
#define llin2(a,b) ll a,b; cin>>a>>b;
#define llin3(a,b,c) ll a,b,c; cin>>a>>b>>c;
#define debug(a) cout<<"<DEBUG> "<<a<<" <DEBUG>"<<endl;
#define debug2(a, b) cout<<"<DEBUG> "<<a<<" "<<b<<" <DEBUG>"<<endl;
#define debug3(a, b, c) cout<<"<DEBUG> "<<a<<" "<<b<<" "<<c<<" <DEBUG>"<<endl;
#define fulll(v) v.begin(),v.end()
#define vecin(n, v) for(ll i=0; i<n;i++) cin>>v[i];
#define vecout(n, v) for(ll i=0; i<n;i++) cout<<v[i]<<" "; cout<<endl;
#define rep(i, s, n) for(ll i=(ll)s;i<(ll)n;i++)
#define rrep(i, s, n) for(ll i=(ll)s;i>=(ll)n;i--)
#define pb push_back
#define mkp make_pair
#define ff first
#define ss second
#define endl "\n"
#define test cout<<"test line"<<endl;
#define swapper void swap(ll *a, ll *b){ll t=*a;*a=*b;*b=t;}
#define pll pair<ll,ll>
#define vpll vector<pll >
#define modexp ll power(ll x, ll y, ll p){ int res = 1; x = x % p; while(y>0){ if(y&1) res = (res*x) % p; y = y>>1; x = (x*x) % p; } return res; }
#define psieve void sieve(){ memset(prime, true, sizeof(prime)); for(ll p=2; p*p<=maxn; p++) if (prime[p]) for (ll i=p*2; i<=maxn; i+= p) prime[i] = false; }
#define mod 1000000007
#define INF 0x3f3f3f3f
#define MAX 100000

using namespace std;



struct node{
    ll maxin;
    node* child[26];
    node(){
        maxin=-1;
        rep(i,0,26)
            child[i]=NULL;
    }
};

node* root=NULL;


void insert(node* root, string s){
    node* ptr = root;
    for(char ch : s){
        ll next = ch-'a';
        if(!(ptr->child[next]))
            ptr->child[next] = new node();
        ptr = ptr->child[next];
    }
}

ll dfs(node* root, ll sum=0){
    ll mx = 0;
    rep(i,0,26){
        ll res=0;
        if(root->child[i])
            res = dfs(root->child[i], i+1);
        if(res>mx)
            mx=res, root->maxin=i;
    }
    return mx+sum;
}

void solve(node* root, vll &ans, ll sum=0){
    ll f=0;
    rep(i,0,26)
        if(root->child[i])
            if(i==root->maxin)
                solve(root->child[i], ans, sum + i+1), f=1;
            else
                solve(root->child[i], ans, i+1), f=1;
    if(!f)
        ans.pb(sum);
}

int main(){
	if(LOCAL){
		freopen("sin.txt", "r", stdin);
		freopen("sout.txt", "w", stdout);
	}
	else
		fast
    llin(t);
    while (t--){
        llin2(n, k);
        k = min(n,k);
        node* root = new node();
        rep(i,0,n){
            string s;
            cin>>s;
            insert(root, s);
        }
        vll ans;
        dfs(root);
        solve(root, ans);
        sort(fulll(ans));
        ll res = 0;
        rrep(i,ans.size()-1,max((ll)ans.size()-k, 0ll))
            res+=ans[i];
        cout<<res<<endl;
    }
if(LOCAL){
		fclose(stdout);
		fclose(stdin);
	}
	return 0;
}