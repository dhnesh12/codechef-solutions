#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define ff            first
#define ss            second
#define pb            push_back
#define mp            make_pair
#define pii           pair<int,int>
#define vi            vector<int>
#define mii           map<int,int>
#define pqb           priority_queue<int>
#define pqs           priority_queue<int,vi,greater<int>>
#define setbits(x)    __builtin_popcountll(x)
#define zrobits(x)    __builtin_ctzll(x)
#define mod           1000000007
#define inf           1e18
#define ps(x,y)       fixed<<setprecision(y)<<x
#define mk(arr,n,type) type *arr=new type[n];
#define w           int x12;cin>>x12;while(x12--)
#define F10            ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;
#define Max           1000005
int n;
void solution()
{
    int ans=0;
    vector<vi> arr(Max);
    vi arr1(Max,0);
    for (int i = 0; i <Max ; ++i) {

        arr[i].resize(21);
    }
    for (int i = 0; i < n; ++i) {
        int a;
        cin>>a;
        arr[a][0]++;

    }
    for (int j = 0; j <Max ; ++j) {
        int i;
        for (i = 1; i <=20 ; ++i) {
            if(j & (1<<(i-1)))
            {
                arr[j][i]=arr[j^(1<<(i-1))][i-1]+arr[j][i-1];

            } else{
                arr[j][i]=arr[j][i-1];
            }
        }
        if(arr[j][0])
            ans+=(arr[j][0]*(arr[j][20]-arr[j][0])+(arr[j][0]*(arr[j][0]-1))/2);
        //cout<<j<<" "<<ans<<"\n";
    }
    cout<<ans<<"\n";
}
void s()
{
    int ans=0,arr[1001];

    for (int k = 0; k <n ; ++k) {
        cin>>arr[k];
    }
    for (int i = 0; i <n ; ++i) {
        for (int j = i+1; j < n; ++j) {
            if(max(arr[i],arr[j])>=(arr[i]|arr[j])){
                ans+=1;
            }
        }
    }
    cout<<ans<<"\n";
}
int32_t main()
{

    w
    {

        cin>>n;
        if(n<1000)
            s();
        else
            solution();
    };
}