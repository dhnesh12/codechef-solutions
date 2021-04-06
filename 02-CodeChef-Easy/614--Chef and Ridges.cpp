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
#define pin2(a, b) printf("%lld %lld ", a, b)
#define pll pair < ll, ll >
#define vl vector < ll > 
#define vll vector < pll > 
#define vvl vector < vl >
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define nl printf("\n");
void solve() {
    test(TT) {
        sd(n);

        pll d[26];
        

        d[1].F= 1;
        d[1].S = 2;
        d[2].F= 1;
        d[2].S = 4;

        f(i,3,25)
            {
                d[i].F = 2*d[i-2].F + d[i-1].F;
                d[i].S= pow(2,i);
            }


            pin2(d[n].F , d[n].S);

        // sdarr(a, n);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
    solve();
    return 0;
}