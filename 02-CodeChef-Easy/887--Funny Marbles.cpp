#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct BITree {
    // 1-based indexing internally, 0-based internally

    vector<long long> bits; 

    BITree(int n) : bits(n + 1) {}

    void add(int k, long long x) {
        k++;
        while (k < int(bits.size())) {
            bits[k] += x;
            k += k & -k;
        }
    }

    long long sum(int k) const {
        k++;

        long long s = 0;
        while (k >= 1) {
            s += bits[k];
            k -= k & -k;
        }
        return s;
    }

    long long sum(int l, int r) const {
        long long s = sum(r);
        if (l > 0) {
            s -= sum(l - 1);
        }

        return s;
    }
};

int
main()
{
    int n, q;
    cin >> n >> q;

    BITree bitree(n);

    // populate the initial data
    for (int i = 0; i < n; i++) {
        long long v;
        cin >> v;
        bitree.add(i, v);
    }

    // deal with the queries
    while (q-- > 0) {
        string s;
        int i, j;

        cin >> s >> i >> j;

        if (s == "S") {
            const long long sum = bitree.sum(i, j);
            cout << sum << '\n';
        }
        else if (s == "G") {
            bitree.add(i, j);
        }
        else {
            assert(s == "T");
            bitree.add(i, -j);
        }
    }

    return 0;
}