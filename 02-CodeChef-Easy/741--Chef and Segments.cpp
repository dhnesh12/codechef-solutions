#include<bits/stdc++.h>
using namespace std;
#define fast() ios_base::sync_with_stdio(0);cin.tie(NULL); cout.tie(NULL);
#define file() freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define test_cases() cin>>_;
#define debug(x) cout<<#x<<" = "<<x<<'\n';
#define display(a) for(int i=0;i<a.size();i++) cout<<a[i]<<' '; cout<<'\n';
#define all(a) a.begin(),a.end()
int _;
long long bin_expo(long long base,long long power,long long mod)
{
    long long res = 1;
    while(power)
    {
        if(power%2==1)
        {
            res = (res*base)%mod;
        }
        base = (base*base)%mod;
        power/=2;
    }
    return res;
}
int main()
{
    _=1;
    // file();
    // fast();
    // test_cases();
    while(_--)
    {
        int n;
        cin>>n;
        vector<long long> a(n);
        for(int i=0;i<n;i++)
        cin>>a[i];
        vector<vector<int> > powers(n,vector<int>(25,0));
        vector<int> prime = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
        for(int i=0;i<n;i++)
        {
            long long temp = a[i];
            for(int j=0;j<25;j++)
            {
                while(temp%prime[j]==0)
                {
                    temp/=prime[j];
                    powers[i][j]++;
                }
            }
        }
        vector<vector<int> > pre_pow(n,vector<int>(25,0));
        for(int i=0;i<25;i++)
        {
            pre_pow[0][i]=powers[0][i];
        }
        for(int i=1;i<n;i++)
        {
            for(int j=0;j<25;j++)
            {
                pre_pow[i][j]+=pre_pow[i-1][j]+powers[i][j];
            }
        }
        int q;
        cin>>q;
        while(q--)
        {
            int l,r,m;
            cin>>l>>r>>m;
            l--;
            r--;
            if(l==0)
            {
                long long temp = 1;
                for(int i=0;i<25;i++)
                {
                    temp = (temp*bin_expo(prime[i],pre_pow[r][i],m))%m;
                }
                cout<<temp<<'\n';
            }
            else
            {
                long long temp = 1;
                for(int i=0;i<25;i++)
                {
                    temp = (temp*bin_expo(prime[i],pre_pow[r][i]-pre_pow[l-1][i],m))%m;
                }
                cout<<temp<<'\n';
            }
        }
    }
    return 0;
}