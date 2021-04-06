#include <iostream>
#include <vector>
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
        int n, m;
        cin >> n >> m;

        vector<int> sointChakraSum(101); // for each level
        while (n-- > 0) {
            int c, l;
            cin >> c >> l;
            sointChakraSum[l] += c;
        }

        vector<int> sofloatChakraSum(101); // for each level
        while (m-- > 0) {
            int c, l;
            cin >> c >> l;
            sofloatChakraSum[l] += c;
        }

        // aggregate the chakra deficit for any levels where there is one
        int aggregateDeficit = 0;
        for (size_t l = 0; l < sointChakraSum.size(); l++) {
            const int deficit = sofloatChakraSum[l] - sointChakraSum[l];
            if (deficit > 0)
                aggregateDeficit += deficit;
        }

        cout << aggregateDeficit << '\n';
    }
}