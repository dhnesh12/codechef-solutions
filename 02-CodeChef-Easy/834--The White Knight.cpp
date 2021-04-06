#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t-- > 0) {
        int n;
        cin >> n;

        vector<string> board(n);
        int kr = -1;
        int kc = -1;
        for (int i = 0; i < n; i++) {
            cin >> board[i];

            const size_t kpos = board[i].find('K');
            if (kpos < board[i].length()) {
                assert(kr == -1 && kc == -1);
                kr = i;
                kc = int(kpos);

                board[i][kpos] = '.';
            }
        }

        vector<vector<int>> captures(n, vector<int>(n, -1));
        captures[kr][kc] = 0;

        for (; kc + 1 < n; kc++) {
            for (int r = 0; r < n; r++) {
                if (captures[r][kc] >= 0) {
                    // here's a place a knight can get to

                    // try the four possible moves
                    for (int move = 1; move <= 4; move++) {
                        const int cdelta = 1 + move % 2;
                        const int rdelta = move <= 2 ? 3 - cdelta : cdelta - 3;

                        if (kc + cdelta < n && 0 <= r + rdelta && r + rdelta < n) {
                            const int captures2 = captures[r][kc] + (board[r + rdelta][kc + cdelta] == 'P');
                            captures[r + rdelta][kc + cdelta] = max(captures[r + rdelta][kc + cdelta], captures2);
                        }
                    }
                }
            }
        }

        // result is the maximum number of captures on the last two columns
        int result = 0;
        for (kc = n - 2; kc < n; kc++) {
            for (int r = 0; r < n; r++) {
                result = max(result, captures[r][kc]);
            }
        }

        cout << result << '\n';
    }

    return 0;
}
