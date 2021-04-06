/*
Author : Vidish Joshi
*/

#include <bits/stdc++.h>
using namespace std;

//#include<boost/multiprecision/cpp_int.hpp>
//using namespace boost::multiprecision;

#define ll long long int
#define FIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define mod 1000000007
#define FOR1(i, m, n) for(i=m; i<n; i++)
#define FOR2(i, n, m) for(i=n-1; i>=m; i--)
#define re(v) ll v; cin>>v
#define mod 1000000007
#define mod2 998244353
#define mp make_pair
#define pb push_back
#define fill(a) memset(a, 0, sizeof(a))
#define start ll t; cin>>t; while(t--)
#define start1 ll t = 1; while(t--)
#define F first
#define S second
#define br "\n"

void solve(){
    int n, k; cin>>n>>k;
    if(k>n/2){
        cout<<"-1\n";
        return;
    }

    vector<int> v;
    for(int i=1; i<n+1; i++) v.pb(i);
    if(!k){
        for(int i=0; i<n; i++){
            cout<<v[i]<<" ";
        }
        cout<<br;
        return;
    }
    if(1){
        int i;
        int mid;
        for(i=0; i<n; i+=2*k){
            if(i + 2*k > n) break;
            rotate(v.begin() + i, v.begin() + i + k, v.begin() + i + 2*k);
            mid = i + k;
        }
        int j = max(n - 2*k, mid);
        rotate(v.begin() + j, v.begin() + j + k, v.end());
        // if(v[v.size()-1]==n){
        //     rotate(v.begin() + i, v.begin() + i + k, v.end());
        // }
    }
    for(int i=0; i<n; i++){
        cout<<v[i]<<" ";
    }
    cout<<br;
}

int main(){
    FIO;
    start{
        solve();
    }
    return 0;
}