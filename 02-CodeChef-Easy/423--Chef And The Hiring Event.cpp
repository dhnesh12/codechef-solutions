#include <bits/stdc++.h>
#define ll long long
#define MAX 1000000000
     
using namespace std;

ll arr[25] = {0, 2, 4, 6, 8, 20, 22, 24, 26, 28, 40, 42, 44, 46, 48, 60, 62, 64, 66, 68, 80, 82, 84, 86, 88};

ll fun(ll k){

  ll num, rem, mul, ans;

  if(k <= 25) return arr[k - 1];

  mul = k / 25;
  rem = k % 25;

  if(rem == 0){

    rem = 25;
    --mul;
  }
  num = fun(++mul);

  ans =  num * 100 + arr[rem - 1];

  return ans;

}


int main(){

  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

  int t;

  cin >> t;

  while(t--){

    ll k;

    cin >> k;

    if(k <= 25) cout << arr[k - 1] <<"\n";
    else {

      cout << fun(k) <<"\n";
    }

   }

   return 0;
}