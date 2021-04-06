#include <bits/stdc++.h>

#define rr(i, b)    for (int i = 0; i < int(b); i++)
#define vi(n, a) vector <int> a(n); rr(i, n) cin >> a[i]
#define pvec(a) rr(i, a.size()) cout << a[i] << " "; cout << endl
#define bug(x) cout << #x << " " << x << endl
#define ll long long
#define vii vector <int>

using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;

    vi(n, a);

    int wal = (x + 1) / 2;
    int jes = x / 2;

    int rem = n - x;

    int even = 0, odd = 0;

    for(int x : a) {
        if(x % 2 == 0) even++;
        else odd++; 
    }

    if(jes >= odd) {
        cout << "Jesse" << endl;
    }
    else if(jes >= even) {
        if(rem % 2 == 0) cout << "Jesse" << endl;
        else cout << "Walter" << endl;
    }
    else {
        if(x % 2) cout << "Walter" << endl;
        else cout << "Jesse" << endl;
    }

}
 
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}