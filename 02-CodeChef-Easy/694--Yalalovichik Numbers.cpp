#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
 
int main(int argc, char** argv)
{
    int T;
    cin>>T;
    while(T--){
        string str;
        cin>>str;
        int n = str.size();
        long long p1 = 1 , p2 = 1;
        for(int j = 0 ; j < n ; j++) p1 *= 10 , p1 %= MOD;
        for(int j = 1 ; j < n ; j++) p2 *= 10 , p2 %= MOD;
        long long cur = 0 , ans = 0;
        for(auto ch : str){
            cur *= 10;
            cur += ch - '0';
            cur %= MOD;
        }
        ans = cur;
        for(int j = 0 ; j + 1 < n ; j++){
            cur -= (p2 * (str[j] - '0'))%MOD; cur += MOD; cur %= MOD;
            cur *= 10; cur += str[j] - '0'; cur %= MOD;
            ans *= p1; ans %= MOD; ans += cur; ans %= MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}