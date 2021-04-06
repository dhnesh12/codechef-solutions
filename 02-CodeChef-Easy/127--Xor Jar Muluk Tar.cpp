
#include <bits/stdc++.h>  
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
using namespace std;
typedef long long ll;
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 

ll n;
ll k;


vector<vector<ll>> multi(vector<vector<ll>> &a, vector<vector<ll>> &b){
    vector<vector<ll>> ans(n+1,vector<ll>(n+1));
    for(ll i = 1;i<=n;i++)
        for(ll j = 1;j<=n;j++)
            for(ll k =1 ;k<=n;k++)
                ans[i][j] += a[i][k]*b[k][j],ans[i][j]%=2;
    return ans;
}

vector<vector<ll>> log_mat_power(vector<vector<ll>> &trans, ll pow){
    // cout<<"K is "<<pow<<endl;
    if(pow == 1)
        return trans;
    auto tmp_ans = log_mat_power(trans, pow/2);
    tmp_ans = multi(tmp_ans,tmp_ans);
    if(pow%2 == 0)
        return tmp_ans;
    else return multi(tmp_ans, trans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        vector<ll> arr(n+1);
        vector<vector<ll>> trans(n+1,vector<ll>(n+1)), id(n+1,vector<ll>(n+1));
        for(ll i =1 ;i<=n;i++)
            cin>>arr[i];
        for(ll i =1;i<=n;i++){
            ll l,r;
            cin>>l>>r;
            for(ll j = l;j<=r;j++)
                trans[j][i] = 1;
        }
        auto final_trans = log_mat_power(trans, k - 1);
        // for(ll i = 1;i<=n;i++){
        //     for(ll j = 1;j<=n;j++)
        //         cout<<final_trans[i][j]<<" ";
        //     cout<<endl;
        // }
        vector<ll> ans(n+1);
        for(ll i = 1;i<=n;i++){
            for(ll j = 1;j<=n;j++)
                if(final_trans[j][i])
                    ans[i] ^= arr[j];
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}