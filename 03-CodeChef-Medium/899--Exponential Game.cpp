#include <bits/stdc++.h>  
using namespace std;
#define trace1(x)     cerr<<#x<<": "<<x<<endl
#define trace2(x,y)     cerr<<#x<<": "<<x<<" "<<#y<<" "<<y<<endl
#define int  long long   //double
typedef double ld;
//template<typename T> T pow(T a,T b, int m){T ans=1; while(b>0){ if(b%2==1) ans=(ans*a)%m; b/=2; a=(a*a)%m; } return ans%m; }
//#define Max(x,y,z) max(x,max(y,z))
//#define Min(x,y,z) min(x,min(y,z))
typedef vector<int> vi;
const int N=1e5+5,lg=1e6+5,mod=1e9+7;

int cache[N];

int grundy(int n){
    int &ans=cache[n];
    if (ans!=-1){
        return ans;
    }
    set<int> s;
    for (int i=1;pow(i,i)<=n;i++){
        s.insert(grundy(n-pow(i,i)));
    }
    for (int i=0;;i++){
        if (s.lower_bound(i)==s.upper_bound(i)){
            return ans=i;
        }
    }
}

void solve()
{
    int n,ans=0;
    cin>>n;
    for (int i=0,x;i<n;i++){
        cin>>x;
        ans^=grundy(x);
    }
    if (ans){
        cout<<"Little Chef\n";
    }
    else{
        cout<<"Head Chef\n";
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(cache,-1,sizeof(cache));
    int testCases=1;
    cin>>testCases;
    while (testCases--)
    {
        solve();
    }
}
/*freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);*/
