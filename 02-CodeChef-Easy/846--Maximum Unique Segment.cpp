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

        vector<int> c;
        for (int i = 0; i < n; i++) {
            int j;
            cin >> j;
            c.push_back(j);
        }

        vector<int> w;
        for (int i = 0; i < n; i++) {
            int j;
            cin >> j;
            w.push_back(j);
        }

        // use l and r indices for the range, both inclusive
        int l = 0;
        int r = 0;
        vector<int> cCounts(n);
        cCounts[c[0]]++;
        long long maxWeight = w[0];
        long long weight = w[0];
        int nonuniqueCount = 0;
        for (;;) {
            // at the start of the loop, the range should be valid, with the weight already banked
#ifdef DEBUG
            {
                long long weight2 = 0;
                assert(l <= r && l >= 0 && r < int(c.size()));
                vector<int> cCounts2(n);
                for (int l2 = l; l2 <= r; l2++) {
                    cCounts2[c[l2]]++;
                }
                assert(cCounts == cCounts2);
                int nonuniqueCount2 = 0;
                for (size_t i = 0; i < cCounts2.size(); i++) {
                    if (cCounts2[i] > 1)
                        nonuniqueCount2++;
                }
                assert(nonuniqueCount == nonuniqueCount2);
            }
#endif

            // try advancing r
            r++;
            if (r >= int(c.size()))
                break;

            if (cCounts[c[r]] == 1)
                nonuniqueCount++;
            cCounts[c[r]]++;
            weight += w[r];

            while (nonuniqueCount > 0) {
                // advance l until the range is valid again
                assert(l <= r);

                weight -= w[l];
                cCounts[c[l]]--;
                if (cCounts[c[l]] == 1)
                    nonuniqueCount--;

                l++;
            }

            // another valid range
            maxWeight = max(maxWeight, weight);
        }

        cout << maxWeight << '\n';
    }

    return 0;
}
