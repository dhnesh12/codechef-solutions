#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int x = 2;
int main()
{
  /* code */
  vector<ll> v2;
  ll n = 4000005;
   vector<ll> prime(n+1, 1);
        prime[0] = 0;
        prime[1] = 0;

        for (ll i = 2; i*i <= n ; ++i)
         {
            /* code */
                if(prime[i] == 1) {
                  v2.push_back(i);
                    for (int j = i*i; j <= n ; j+=i )
                    {
                        /* code */
                        prime[j] = 0;
                    }
                }
         } 



  int t;
  cin >> t;

  while(t--) {

   ll n;
   cin >> n;
   vector<ll> v(n), v1;

   for (ll i = 0; i < n; ++i)
   {
     /* code */
     cin >> v[i];
   }
   
   unordered_map<ll,ll> mp;

   for(ll i = 0; i < n; ++i) {

      if(mp.find(v[i]) == mp.end()) {

        while(prime[x] == 0) {
          x++;
        }
          mp[v[i]] = x;
          x++;
        
      }
    }

   for (ll i = 0; i < n; ++i)
   {
     /* code */
     cout << mp[v[i]] << ' ';
   }
   cout << endl;
  }

  return 0;
}
