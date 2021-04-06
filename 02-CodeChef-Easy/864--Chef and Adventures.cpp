#include <iostream>
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
        int n, m, x, y;
        cin >> n >> m >> x >> y;

        // work out if ShareChat is needed for knowledge
        const int knowledgeRemainder = (n - 1) % x;

        // work out if ShareChat is needed for power
        const int powerRemainder = (m - 1) % y;

        bool possible = false;
        if (knowledgeRemainder == 0 && powerRemainder == 0) {
            // don't need ShareChat
            possible = true;
        }
        else if (knowledgeRemainder == 1 && powerRemainder == 1) {
            // can use ShareChat
            possible = true;
        }
        else if (knowledgeRemainder == 1 && powerRemainder == 0 && y == 1 && m > 1) {
            // can increase powerRemainder one less time, then use ShareChat
            possible = true;
        }
        else if (powerRemainder == 1 && knowledgeRemainder == 0 && x == 1 && n > 1) {
            // can increase knowledgeRemainder one less time, then use ShareChat
            possible = true;
        }

        cout << (possible ? "Chefirnemo" : "Pofik") << '\n';
    }

    return 0;
}