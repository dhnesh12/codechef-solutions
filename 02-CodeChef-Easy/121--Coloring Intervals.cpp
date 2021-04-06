#include <bits/stdc++.h>
using namespace std;

#define all(n)      for(int i=0; i<int(n); i++)
#define pb          push_back
#define F           first
#define S           second
#define FIO         ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define deb(...)    << "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

using ll = long long;

void test_case() {
    int n;
    cin >> n;
    vector<array<int, 3>> in(n);
    all(n) cin >> in[i][0] >> in[i][1], in[i][2] = i;

    sort(in.begin(), in.end());
    int yellow=0, blue=0;
    bool col[n];
    for(int i=0; i<n; i++) {
        int end = max(yellow, blue);
        int idx = in[i][2];
        // cerr deb(yellow) deb(blue) << endl;
        if(in[i][1] <= yellow) {
            // completely inside
            col[idx] = 0;
            blue = max(blue, in[i][1]);
        }
        else if(in[i][1] <= blue) {
            col[idx] = 1;
            yellow = max(yellow, in[i][1]);
        }
        else if(in[i][0] > end){
            // no overlap
            yellow = in[i][1];
            col[idx] = 1;
        }
        else if(yellow > blue) {
            col[idx] = 0;
            blue = max(blue, in[i][1]);
        }
        else {
            col[idx] = 1;
            yellow = max(yellow, in[i][1]);
        }
    }

    all(n) cout << col[i];
    cout << '\n';
}

int main() {
    FIO;

    int t=1;
    cin >> t;
    while(t--) test_case();
}

