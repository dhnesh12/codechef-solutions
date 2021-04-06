//comparator should return flase for equal values
#include<bits/stdc++.h>
using namespace std;
int gcd(int a , int b)
{
   if(b==0) return a;
   a%=b;
   return gcd(b,a);
}
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
//unordered_map<long long, int, custom_hash> safe_map;
vector<int> power(26,0);
int logg2(int a)
{
    for(int i=0;i<26;i++)
    {
        if(power[i]>a) return i-1;
        if(power[i]==a) return i;
    }
    return 25;
}
void run()
{
    char l='a';
    int a,b;cin>>a>>b;
    if(a>b)
    {
        cout<<-1;
        return;
    }
    int extra=b-a;
    string check(a,l);
    if(extra==0)
    {
        cout<<check;
        return;
    }
    for(int i=0;i<check.size();i++)
    {
        if(extra>0)
        {
            int req=logg2(extra+1);
            if(req<=25)
            {
                check[i]+=req;
                extra-=(power[req]-1);
            }
            else
            {
                check[i]+=25;
                extra-=(power[25]-1);
            }
        }
        else break;
    }
    sort(check.begin(),check.end());
    if(extra!=0) cout<<-1;
    else cout<<check;
    
}
int main()
{
    for(int i=0;i<26;i++)
    {
        if(i==0) power[i]=1;
        else power[i]=power[i-1]*2;
    }
    int a;cin>>a;
    while(a--)
    {
        run();
        cout<<endl;
    }
}