#include <iostream>
#include <assert.h>

#define ll long long
#define mod 1000000007
using namespace std;

ll nck [2500][2500];
ll tpow [2500];
int main() {
    tpow[0] = 1;
    for(int i = 0; i < 2499; i++){
        tpow[i+1] = (tpow[i]*2)%mod;
    }
    for(int i = 0; i < 2500; i++){
        for(int j = 0; j < 2500; j++){
            nck[i][j] = 0;
        }
        nck[i][0] = 1;
    }
    for(int i = 1; i < 2500; i++){
        for(int j = 1; j < 2500; j++){
            nck[i][j] = (nck[i-1][j-1] + nck[i-1][j])%mod;
         //   cout << nck[i][j] << " ";
        }
        //nck[i][0] = 1;
    }
    /*for(int i = 0; i < 50; i++){
        for(int j = 0; j <= i; j++){
            cout << nck[i][j] << " ";
        }
        cout << endl;
    }*/
    int t;
    cin >> t;
    for(int o = 0; o < t; o++){
        
        
        int n;
        cin >> n;
        assert(n <= 2000);
        ll a[n];
        for(int i = 0; i < n; i++){
            cin >> a[i];
            
        }
        ll f[n];
        for(int i = 0; i < n; i++){
            f[i] = 0;
            for(int j = 0; j < n; j++){
                f[i] += (((a[j]*nck[j][i])%mod)*tpow[n-j-1])%mod;
                f[i] = f[i]%mod;
            }
            cout << f[i] << " ";
        }
        cout << endl;
    }
    
}
