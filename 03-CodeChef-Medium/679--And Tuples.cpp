#include <bits/stdc++.h>
/*

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

*/

#define pii pair<int,int>
#define fi first
#define pb push_back
#define si second
#define int   long long
#define mod  1000000009 //998244353
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define double long double
#define all(o) o.begin(),o.end()



/*
#define T pair<int, int>
#define ordered_set tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
*/


using namespace std;



int power(int x, int y)
{
    int res = 1LL;
    x = x % mod;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % mod;
        y = y>>1; // y = y/2
        x = (x*x) % mod;
    }
    return res%mod;
}
int inv(int  n)
{
    return power(n,mod-2)%mod;
}
int isprime(int n){
    if(n<2)return 0;
    int i;
    for(i=2;i*i<=n;i++)
        if(n%i==0)
            return 0;
    return 1;
}
void files(){  
    // For getting input from input.txt file 
    freopen("input.txt", "r", stdin);   
    // Printing the Output to output.txt file 
    freopen("output.txt", "w", stdout); 

}

int egcd(int a,int b,int &x ,int & y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    int x1,y1;
    int g=egcd(b,a%b,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g; 
}
const int N=2e6;
//https://codeforces.com/blog/entry/22747




int k,n;
map<int,int> mp;
int f(int n){
    if(n<0)
        return 0;
    if(n<=1)
        return 1;
    if(mp.find(n)!=mp.end())
        return mp[n];
    int ans=0;
    
    if(n&1){
        ans+=f((n-1)/2);
        ans%=mod;
        ans+=f((n-3)/2);
        ans%=mod;
    }
    else
    {
        ans+=f(n/2);
        ans%=mod;
        ans+=f((n-2)/2);
        ans%=mod;
    }
    
    if(k==4){
        if(n%2==0)
        {   ans+=f((n-4)/2);
            ans%=mod;
        }
    }
    return mp[n]=ans;


}
void solve(){

    cin>>k>>n;

    cout<<f(n)<<"\n";

    mp.clear();









} 


int32_t main(){ 
        fast

  
    int t=1;

     cin>>t;

    while(t-- ) 
    {
        solve();
    }
}