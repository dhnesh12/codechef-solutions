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
    void solve() {
        test(TT) {
            sd(n);
            sd2(m,s);


             sdarr(a, n);
             sort(a,a+n);
             bool o=0;
             ll c=0;
             f(i,0,n-1)
             {  if(m<=0)
                    break;
                if(a[i]<=s)
                {
                    c++;
                    m--;
                }
                else if(a[i]<=2*s)
                {   if(m!=1)	
                    {c++; 
                    m=m-2;}
                    
                }
                else
                {
                    break;
                }
             }

             pin(c);
        }
    }

    int main() {
    //    freopen("input.txt", "r", stdin);
      //  freopen("output.txt", "w", stdout);
        solve();
        return 0;
    }