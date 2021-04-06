#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline int count_moves(vector<int> &v) {
    int ans = 0, empty = 0;
    for (int i = (int) v.size() - 2; i >= 0; i--) {
        empty += abs(v[i] - v[i + 1]) - 1;
        ans += empty;
    }
    return ans;
}

inline char solve(vector<int> w, vector<int> b) {
    char res;
    for (int mv = 0; ; mv ^= 1) {
        if (!mv) {
            if (w.back() + 1 == b.back()) {
                if (b.size() == 1 || b[b.size() - 2] != b.back() + 1 || w.size() == 1 || w[w.size() - 2] < w.back() - 2) {
                    w.back()++;
                    b.pop_back();
                    if (b.empty()) {
                        res = 'W';
                        break;
                    }
                    continue;
                }
                if (w.size() >= 2 && w[w.size() - 2] == w.back() - 2) {
                    w[w.size() - 2]++;
                    continue;
                }
            }
            if (w.back() + 2 < b.back()) {
                w.back()++;
            } else {
                res = count_moves(w) > count_moves(b) ? 'W' : 'B';
                break;
            }
        } else {
            if (b.back() - 1 == w.back()) {
                if (w.size() == 1 || w[w.size() - 2] != w.back() - 1 || b.size() == 1 || b[b.size() - 2] > b.back() + 2) {
                    b.back()--;
                    w.pop_back();
                    if (w.empty()) {
                        res = 'B';
                        break;
                    }
                    continue;
                }
                if (b.size() >= 2 && b[b.size() - 2] == b.back() + 2) {
                    b[b.size() - 2]--;
                    continue;
                }
            }
            if (b.back() - 2 > w.back()) {
                b.back()--;
            } else {
                res = count_moves(b) > count_moves(w) ? 'B' : 'W';
                break;
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        string s;
        cin >> s;
        vector<int> w, b;
        for (int i = 0; i < (int) s.size(); i++) {
            if (s[i] == 'W') {
                w.push_back(i);
            } else if (s[i] == 'B') {
                b.push_back(i);
            }
        }
        reverse(b.begin(), b.end());
        char res = solve(w, b);
        if (w.size() >= 2 && w.back() + 1 == b.back()) {
            w.pop_back();
            if (solve(w, b) == 'W') {
                res = 'W';
            }
        }
        cout << res << '\n';
    }
    return 0;
}