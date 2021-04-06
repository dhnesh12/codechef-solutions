#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define s second
#define f first
#define mod 1000000007
#define inf 1000000000000000000
#define MAX 100000LL

int main(){
      #ifndef ONLINE_JUDGE
            freopen("input.txt", "r", stdin);
      #endif
      ll t;
      cin>>t;
      ll p, q, r, a, b, c;
      while(t--){
            cin>>p>>q>>r>>a>>b>>c;
            ll input[3] = {p, q, r};
            ll output[3] = {a, b, c};
            ll add[3] = {a - p, b - q, c - r};
            ll mul[3];
            bool chkMul = true;
            for(ll i = 0; i < 3; i++){
                  if(input[i] == 0){
                        mul[i] = -mod;
                        chkMul = false;
                  }else if(abs(output[i]) % abs(input[i])){
                        mul[i] = -mod;
                        chkMul = false;
                  }else{
                        mul[i] = output[i] / input[i];
                  }
                  //cout<<add[i]<<" "<<mul[i]<<"\n";
            }

            ll ans = 3;
            ll chk = 0;
            for(ll i = 0; i < 3; i++){
                  if(add[i] == 0){
                        ++chk;
                  }
            }
            ans = min(ans, 3 - chk);
            
            if((add[0] == add[1]) && (add[1] == add[2])){
                  ans = min(ans, 1LL);
            }
            if(chkMul && ((mul[0] == mul[1]) && (mul[1] == mul[2]))){
                  ans = min(ans, 1LL);
            }

            ll k;
            for(ll i = 0; i < 3; i++){
                  for(ll j = 0; j < 3; j++){
                        if(i == j){
                              continue;
                        }
                        ll y = (output[i] * input[j]) - (output[j] * input[i]);
                        ll denominator = (output[j] - output[i]);
                        ll x;
                        if(denominator != 0 && ((y % denominator) == 0)){
                              y /= denominator;
                              x = output[i];
                              denominator = input[i] + y;
                              if(denominator != 0 && ((x % denominator) == 0)){
                                    x /= denominator;
                                    chk = 0;
                                    for(ll k = 0; k < 3; k++){
                                          if(((input[k] + y) * x) == output[k]){
                                                ++chk;
                                          }else if((input[k] + y) == output[k]){
                                                ++chk;
                                          }else if((input[k] * x) == output[k]){
                                                ++chk;
                                          }
                                    }
                                    if(chk == 3){
                                          ans = min(ans, 2LL);
                                    }      
                              }   
                        }

                        y = (output[j] - output[i]);
                        denominator = (input[j] - input[i]);
                        if(denominator != 0 && ((y % denominator) == 0)){
                              y /= denominator;
                              x = output[i] - (y * input[i]);
                              chk = 0;
                              for(ll k = 0; k < 3; k++){
                                    if(((input[k] * y) + x) == output[k]){
                                          ++chk;
                                    }else if((input[k] * y) == output[k]){
                                          ++chk;
                                    }else if((input[k] + x) == output[k]){
                                          ++chk;
                                    }
                              }
                              if(chk == 3){
                                    ans = min(ans, 2LL);
                              }
                        }

                        k = (3 - (i + j));

                        if(add[i] == add[j]){
                              if(add[k] != 0){
                                    ans = min(ans, 2LL);
                              }else{
                                    ans = min(ans, 1LL);
                              }
                        }
                        if(((input[k] + add[i]) + add[j]) == output[k]){
                              ans = min(ans, 2LL);
                        }

                        if(mul[j] == (-mod)){
                              continue;
                        }

                        if(((input[k] + add[i]) * mul[j]) == output[k]){
                              ans = min(ans, 2LL);
                        }
                        if(((input[k] * mul[j]) + add[i]) == output[k]){
                              ans = min(ans, 2LL);
                        }

                        if(mul[i] == (-mod)){
                              continue;
                        }

                        if(mul[i] == mul[j]){
                              if(add[k] != 0){
                                    ans = min(ans, 2LL);
                              }else{
                                    ans = min(ans, 1LL);
                              }
                        }
                        if(((input[k] * mul[i]) * mul[j]) == output[k]){
                              ans = min(ans, 2LL);
                        }
                  }
            }
            cout<<ans<<"\n";
      }
}