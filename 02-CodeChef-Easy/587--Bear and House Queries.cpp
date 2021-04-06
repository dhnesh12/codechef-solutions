#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

string ask(int x, int y) {
    cout << "? " << x << " " << y << endl;
    string s;
    cin >> s;
    return s;
}

void test_case() {
    int sq = -1, th = -1, tp1 = -1, b = -1;

    // find end of square [x, 0]
    int l = 0, r = 1000; 
    while(l <= r) {
        int m = (l + r) / 2;
        if(ask(m, 0) == "YES") sq = m, l = m + 1;
        else r = m - 1;
    }

    // find height of whole house [0, y]
    l = 0, r = 1000;
    while(l <= r) {
        int m = (l + r) / 2;
        if(ask(0, m) == "YES") th = m, l = m + 1;
        else r = m - 1;
    }

    // find first part to hit on triangle [sq, m]
    l = 0, r = 1000;
    while(l <= r) {
        int m = (l + r) / 2;
        if(ask(sq, m) == "YES") tp1 = m, l = m + 1;
        else r = m - 1;
    }

    while(ask(sq + 1, tp1) == "NO") tp1--;

    l = 0, r = tp1;
    while(l <= r) {
        int m = (l + r) / 2;
        if(ask(sq + 1, m) == "YES") tp1 = m, r = m - 1;
        else l = m + 1;
    }

    // find base vertex for triangle [b, tp]
    l = 0, r = 1000;
    while(l <= r) {
        int m = (l + r) / 2;
        if(ask(m, tp1) == "YES") b = m, l = m + 1;
        else r = m - 1;
    }

    ll base = 2 * b;
    ll height = th - tp1;
    ll square_height = tp1;

    ll area = (square_height * square_height) + (base * height) / 2;
    cout << "! " << area << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while(tc--) {
        test_case();
    }
    return 0;
}