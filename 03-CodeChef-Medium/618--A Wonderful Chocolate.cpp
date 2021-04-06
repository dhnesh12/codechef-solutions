#include<bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define mp make_pair
#define FF first
#define SS second
#define all(v) v.begin(),v.end()
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> pp;
typedef pair<ll,pp> ppp;
typedef vector<ll> vll;

const double PI = acos(-1);
const int N = 2e5+5;
const ll INF = 1e9;
const ll mod  = 1e9+7;


void mul(vector<vector<ll> > &a,vector<vector<ll> > b, ll n){
    
    ll c[n][n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            c[i][j] = 0;
            for(int k=0;k<n;k++){
                c[i][j] += a[i][k]*b[k][j];
                c[i][j] %=mod;
            }
        }

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j] = c[i][j];

    
}

ll sol(ll a,ll b){


    ll n = (1LL<<a);
    ll m1,m2;
    // cout<<n<<endl;
    vector< vector<ll> > mat(n,vector<ll>(n)),result(n,vector<ll>(n,0));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m1 = i&j;
            m2 = i|j;
            mat[i][j] = 1;
            for(int k=0;k<(a-1);k++){
                if( (m1&(1<<k)) && (m1&(1<<(k+1))) ){
                    mat[i][j] = 0;
                    break;
                }
            }    
            for(int k=0;k<(a-1);k++){
                if( (m2&(1<<k))==0 && (m2&(1<<(k+1)))==0 ){
                    mat[i][j] = 0;
                    break;
                }
            }    
        }
    }

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
    //         cout<<mat[i][j]<<" ";
    //     cout<<endl;
    // }
    
    for(int i=0;i<n;i++)
        result[i][i] = 1;

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
    //         cout<<result[i][j]<<" ";
    //     cout<<endl;
    // }
    
    b = b-1;
    while(b>0){
        if(b&1)
            mul(result,mat,n);
        mul(mat,mat,n);
        b/=2;
    }   

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
    //         cout<<result[i][j]<<" ";
    //     cout<<endl;
    // }

    ll ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            ans = (ans+result[i][j])%mod;
    }
    return ans;
}


void solve(){
    ll a,b;
    cin>>a>>b;
    if(a>b)
        swap(a,b);
    
    ll ans = sol(a,b);
    cout<<ans<<endl;
    
}


int main() 
{
    FAST
    int t;
    t=1;
    
    // cin>>t;
    while(t--)
        solve(); 
    return 0;       
}


