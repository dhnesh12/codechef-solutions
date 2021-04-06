#include <iostream>
#include <vector>
using namespace std;
int main() {int t, n, k; cin >> t; while (t--) {long int s, m, M; cin >> n >> s >> k >> m >> M; int x = -1;
        vector<long int> a(n);
        if (n%2 == 0){int med1 = n/2-1; int med2 = n/2;
            if (k <= med2){for (int i = 0; i < n; i++){if (i == med2 + 1 && a[i - 2] == a[i - 1]) {m++;}
                    a[i] = max(m, s - (M * (n - (i + 1)) - (max(med2 - i - 1, 0)))); s -= a[i]; 
                    if ((i >= med2 && a[i] > M) || s < 0 || (i < med2 && a[i] >= M)){cout << -1 <<endl;break;}
                    m = a[i]; if (i == n-1){for (int j = 0; j < n; j++) cout << a[j] << " ";}cout << endl;}}
            else{x = med2;}}
        else{int med = n/2;
            if (k > med && (n%k) < med){cout << -1 << endl;} else if (k <= med){x = med + 1;} else{x = med;}}
        if (x != -1){
            for (int i = 0; i < n; i++) {if (i == x){m++;}a[i]=max(m,s-(M*(n-(i+1))-(max(x-i-1,0))));s-=a[i];
                if ((i >= x && a[i] > M) || s < 0 || (i < x && a[i] >= M)){cout << -1 << endl;break;}m = a[i];
                if (i == n-1){for (int j = 0; j < n; j++) {cout << a[j] << " ";} cout << endl;}}}}}