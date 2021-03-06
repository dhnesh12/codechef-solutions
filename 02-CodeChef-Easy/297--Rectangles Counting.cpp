#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

#define fi first
#define se second

typedef pair<int, int> PII;

int n;
vector<PII> p, seg;

int main() {
    ios::sync_with_stdio(false);

    do {
        cin >> n;
        if (!n) break;

        p.clear();

        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;

            p.push_back(PII(x, y));
        }

        sort(p.begin(), p.end());

        seg.clear();

        for (int i = 1; i < n; i++) {
            if (p[i].fi == p[i - 1].fi) {
                seg.push_back(PII(p[i].se, p[i].se - p[i - 1].se));
            }
        }

        sort(seg.begin(), seg.end());

        long long res = 0;

        if (seg.size()) {
            PII last = seg[0];
            long long cnt = 1;
            for (int i = 1; i < seg.size(); i++) {
                if (seg[i] == seg[i - 1]) cnt++;
                else {
                    res += cnt * (cnt - 1) / 2;
                    cnt = 1;
                }
            }
            res += cnt * (cnt - 1) / 2;
        }

        cout << res << endl;
    } while (1);

    return 0;
}








