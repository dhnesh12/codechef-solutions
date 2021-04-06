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
#define mod  1000000007 //998244353
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



int p[2000405];
int a[2000405];
void solve(){

    int n,d,i;
    cin>>n>>d;
    for(i=0;i<=2*n+40;i++)
        a[i]=0;

    for(i=0;i<n;i++)
    {   a[i]++;
        a[i+n]--;
    }

    for(i=1;i<2*n+4;i++)
    {
        if(a[i])
            a[i]+=a[i-1];
    }
    for(i=0;i<2*n+4;i++)
        a[i]*=d*d;

    for(i=0;;i++){
        if(a[i]==0)
            break;
        a[i+1]+=a[i]/10;
        a[i]%=10;
    }
    int j=i;

    int ans=0;
    for(j=j-1,i=0;j>=0;j--,i++){

        ans+=(a[j]*p[i])%mod;
        ans%=mod;
    }
    cout<<ans<<"\n";




} 

int32_t main(){ 
        fast

  
    int t=1,i;

    p[0]=1;
    for(i=1;i<=2e6;i++)
    {   p[i]=23*p[i-1];
        p[i]%=mod;
    }

      cin>>t;

    while(t-- ) 
    {
        solve();
    }
}