#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define MAX 10005
#define int long long
#define MOD 1000000007
#define inf 100000000000000000

int n;
vector<int> prime,a;
int isPrime(int n)
{
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}
void get_prime()
{
    for(int i=2;i<=MAX;i++)
    {
        if(isPrime(i))
            prime.push_back(i);
    }
}

int cal(int x)
{
    int cnt = a[0]%x ? x-(a[0]%x) : 0;
    int p =  a[0]%x ? a[0]+x-(a[0]%x) : a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]<p)
            cnt+=p-a[i];
        else{
            cnt+= a[i]%x ? x-(a[i]%x) : 0;
            p =  a[i]%x ? a[i]+x-(a[i]%x) : a[i];
        }
    }
    return cnt;
}
int32_t main()
{
    IOS;
    int t;cin>>t;
    get_prime(); 
    while(t--)
    {
        cin>>n;
        a.clear();
        a.resize(n,0);
        for(int i=0;i<n;i++)cin>>a[i];
        int ans=INT_MAX;
        for(int i=0;i<prime.size();i++)
            ans=min(ans,cal(prime[i]));
        cout<<ans<<endl;
    }
    return 0;
}


