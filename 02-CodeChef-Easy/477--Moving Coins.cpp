#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e9;

#define mod             1000000007
#define what_is(x)      cerr<<#x<<" is "<<x<<"\n";
#define read(x)         freopen("in.txt","r",stdin);
#define write(x)        freopen("out.txt","w",stdout);
#define Fast            ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

#define sz              10001

int arr[sz];

///greedy:pick the right most group of coins which can be moved

int solve(int n, int k){

    int cnt=0;
    int moves=0;
    for(int i=1000; i>=1; i--){
        if(arr[i]==1){
            cnt++;
        }
        else if(arr[i]==0 && cnt){
            moves+=((cnt/k)+(cnt%k!=0));
        }
    }
    return moves;
}



int main(){
    Fast;///using Fast I/O
    int a,b,c, i,j,k, t,n,m;
    cin>>t;
    while(t--){
        cin>>n>>k;
        memset(arr,0,sizeof(arr));
        for(i=1; i<=n; i++){
            cin>>a;
            arr[a]=1;
        }
        cout<<solve(n,k)<<endl;
    }

    return 0;
}
