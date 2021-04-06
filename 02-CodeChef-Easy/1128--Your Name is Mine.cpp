#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define f(i,a,b) for(int i= (int) a;i<=(int)b;i++)
#define s(a) scanf("%lld", &a);
#define sd(a) ll a; s(a);
#define s2(a, b) s(a);s(b);
#define sd2(a, b) sd(a); sd(b);
#define sdarr(arr, n) ll arr[n]; f(i, 0, n-1) {s(arr[i]);}
#define sarr(arr, n) f(i, 0, n-1) {s(arr[i]);}
#define test(TT) ll TT; s(TT); while(TT--)
#define pi(a) printf("%lld ", a)
#define pin(a) printf("%lld\n", a)
#define pin2(a, b) printf("%lld %lld\n", a, b)
#define pll pair < ll, ll >
#define vl vector < ll > 
#define vll vector < pll > 
#define vvl vector < vl >
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define nl printf("\n");
bool check(string a,string b)
{
    if(a.size()<b.size())
        return false;
    ll j=0;
    f(i,0,a.size()-1)
    {
        if(a[i]==b[j])
            {j++;}
        if(j==b.size())
            return true;
    }
    return false;
}
void solve() {
    test(TT) {
        string a,b;
        cin>>a;
        cin>>b;

        if (check(a,b) || check(b,a))
        {
            cout<<"YES";
        }
        else
            cout<<"NO";
        nl
        // sdarr(a, n);
    }
}

int main() {
   // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    solve();
    return 0;
}