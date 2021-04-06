
#include <iostream>
using namespace std;

long long  cnt(long long mid){long long count = 0, i; while (mid){
        for (i = 1; i <= mid; i *= 10);
        i /= 10; if (i == 1){count++; break;}
        long long rmdr = mid%i; int digi = mid/i; mid -= (rmdr/digi+1)*digi; count = count+rmdr/digi+1;
    }return count;}
int main(){int t; cin >> t;
    while(t--){long long int k,ans; cin >> k; long long l = 1, r = 1e14; long long int mid = (l+r)/2;
        while(l<=r){if (cnt(mid) > k-1){r = mid-1; mid = (l+r)/2;} else{ans = mid; l = mid+1; mid = (l+r)/2;}
        }cout << ans << endl;}}