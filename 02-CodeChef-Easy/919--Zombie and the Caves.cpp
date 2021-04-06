#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define f(i,a,b) for(int i= (int) a;i<=(int)b;i++)
#define s(a) scanf("%lld", &a);
#define sd(a) ll a; s(a);
#define s2(a, b) s(a);s(b);
#define sd2(a, b) sd(a); sd(b);
#define sdarr(arr, n) ll arr[n]; f(i, 1, n-1) {s(arr[i]);}
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
void solve() {
    test(TT) {
        sd(n);
        n=n+1;

         sdarr(a, n);
         a[0]=0;
         sdarr(b,n);
         b[0]=0;
         ll p[n+1];
         memset(p,0,sizeof(p));
         ll x,y;
         f(i,1,n-1)
            {   x= max(0ll, i-a[i]);
                y= min(n, i+a[i]);
                y=y+1;
                p[x]+=1;
                p[y]-=1;
            }
          f(i,1,n-1)
            {
                p[i]+=p[i-1];
                a[i]=p[i];
            }  

           sort(a,a+n);
           sort(b,b+n);
          
           bool f=1;

           f(i,1,n-1) 
           {
            if(a[i]!=b[i])
            {
                f=0;
                break;
            }
           } 

           if(f)
            cout<<"YES";
        else
            cout<<"NO";
        nl

    }
}

int main() {
  //  freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
    solve();
    return 0;
}