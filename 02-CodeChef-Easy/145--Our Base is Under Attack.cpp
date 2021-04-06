#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll MAX = 10001;
ll MAX3 = 1000000000001ll;
ll scan()
{
    ll x= 0;
    char c = getchar_unlocked();
    while(c<'0' || c>'9')
        c=getchar_unlocked();
    while(c>='0' && c<='9'){
        x = (x<<1) + (x<<3) + (c&15);
        c=getchar_unlocked();
    }
    return x;
}
void print(ll x)
{
    char s[65];
    int i=0;
    do{
        s[i++] = x%10+'0';
        x/=10;
    }while(x);
    --i;
    while(i>=0)
        putchar_unlocked(s[i--]);
        putchar_unlocked('\n');
}
vector<ll> base;
void computePow()
{
    for(int i=2;i<MAX;i++){
        ll st = 1ll*i*i*i;
        while(st<MAX3){
            base.push_back(st);
            st *= i;
        }
    }
    sort(base.begin(),base.end());
}
int main()
{
    computePow();
    ll n,t,ans;
    t = scan();
    while(t--){
        ans=0;
        n = scan();
        if(n==1){
            printf("INFINITY\n");
        }else{
            ans += (n+1)/2;
            ans += ((int)sqrt(n))-((int)sqrt(n/2));
            ans += upper_bound(base.begin(),base.end(),n)-
                            upper_bound(base.begin(),base.end(),n/2);
            print(ans);
        }
    }
    return 0;
} 