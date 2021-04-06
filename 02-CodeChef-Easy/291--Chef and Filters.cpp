#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 5;
const int MOD = 1000000000 + 7;

int tn, need, bn, zeroes, current_mask, n, basis[MAXN];

int read_mask () {
    string s;
    cin >> s;
    int ret = 0;
    for(int i = 0; i < s.length(); i++)
        if (s[i] == '+' || s[i] == 'w')
            ret += (1 << i);
    return ret;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin >> tn;
    while (tn--) {
        need = read_mask();
        cin >> n;
        bn = zeroes = 0;
        for(int i = 0; i < n; i++) {
            current_mask = read_mask();
            for(int j = 0; j < bn; j++)
                if ((current_mask ^ basis[j]) < current_mask)
                    current_mask ^= basis[j];
            if (current_mask == 0)
                ++zeroes;
            else
                basis[bn++] = current_mask;
        }
        int ans = 0;
        for(int i = 0; i < (1 << bn); i++) {
            int q = 0;
            for(int j = 0; j < bn; j++)
                if (i & (1 << j))
                    q = q ^ basis[j];
            if (q == need)
                ++ans;
        }
        for(int i = 0; i < zeroes; i++)
            ans = (ans * 2LL) % MOD;
        cout << ans << endl;
    }
    return 0;
}