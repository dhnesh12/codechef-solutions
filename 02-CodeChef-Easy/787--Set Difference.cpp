#include <iostream>
#include <algorithm>
#include <math.h>

#define MAXN 100001

using namespace std;

int mod = 1000000007;
long long powers[MAXN];


int main() {
    powers[0] = 1;
    for (long long c = 1; c < MAXN; c++) {
        powers[c] = (2*powers[c-1])%mod;
    }

    long long T;
    cin >> T;

    for (long long j = 0 ; j < T; j++) {
        long long N;
        cin >> N;
        long long arr[N];
        for (long long k = 0; k < N; k++) {
            cin >> arr[k];
        }
        sort(arr,arr+N);

        long long maxo = 0;
        long long mino = 0;

        for (long long i = 0; i < N; i++) {
            maxo = (maxo + (arr[i]*powers[i])%mod)%mod;
            mino = (mino + (arr[i]*powers[N-i-1])%mod)%mod;
        }

        long long res = (maxo - mino + mod)%mod;

        cout << res << endl; 
        
    }

    return 0;
}