#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int o1, o2;
        cin >> o1 >> o2;
        vector<int> a(o1 * o2);
        for(int i = 0; i < o1 * o2; i++) {
            cin >> a[i];
        }
        bool ok = false;
        vector<vector<int> > cnt(o1, vector<int> (2, 0));
        int cnt0 = 0, cnt1 = 0;
        for(int i = 0; i < o1; i++) {
            for(int j = (i * o2); j < (i + 1) * o2; j++) {
                cnt[i][a[j]]++;
            }
            if(cnt[i][0] < cnt[i][1]) {
                cnt1++;
            } else if(cnt[i][0] > cnt[i][1]) {
                cnt0++;
            }
        }
        if(cnt0 < cnt1) {
            ok = true;
        }
        for(int i = 1; i < o2; i++) {
            int idx = o2 + i - 1;
            for(int j = 1; j <= o1; j++) {
                cnt[j - 1][a[idx]]++;
                idx = (idx + o2) % (o1 * o2);
            }
            idx = i - 1;
            for(int j = 1; j <= o1; j++) {
                cnt[j - 1][a[idx]]--;
                idx = (idx + o2) % (o1 * o2);
            }
            cnt0 = 0, cnt1 = 0;
            for(int j = 0; j < o1; j++) {
                if(cnt[j][0] < cnt[j][1]) {
                    cnt1++;
                } else if(cnt[j][0] > cnt[j][1]) {
                    cnt0++;
                }
            }
            if(cnt0 < cnt1) {
                ok = true;
            }
        }
        cout << ok << endl;
    }
    return 0;
}