#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int N, Q, BITS, PREP_BITS, LOOP_BITS;
vector<int> A;
vector<vector<int>> xor_table;

void prepare() {
    BITS = 32 - __builtin_clz(N);
    LOOP_BITS = BITS / 2;
    PREP_BITS = BITS - LOOP_BITS;
    xor_table.assign(1 << PREP_BITS, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        xor_table[0][i] = A[i];

    for (int mask = 1; mask < 1 << PREP_BITS; mask++) {
        int zeros = __builtin_ctz(mask);
        int without = mask ^ (1 << zeros);
        int low = zeros + LOOP_BITS;

        for (int i = 0; i < N; i++) {
            xor_table[mask][i] = xor_table[without][i];

            if (i + (1 << low) < N)
                xor_table[mask][i] ^= xor_table[without][i + (1 << low)];
        }
    }
}

int main() {
    scanf("%d %d", &N, &Q);
    A.resize(N);

    for (int &a : A)
        scanf("%d", &a);

    prepare();

    for (int q = 0; q < Q; q++) {
        int k, x;
        scanf("%d %d", &k, &x);
        x--;

        int low_mask = k & ((1 << LOOP_BITS) - 1);
        int high_mask = (k >> LOOP_BITS) & ((1 << PREP_BITS) - 1);
        int sub = low_mask;
        int answer = 0;

        do {
            if (x + sub < N)
                answer ^= xor_table[high_mask][x + sub];

            sub = (sub - 1) & low_mask;
        } while (sub != low_mask);

        printf("%d\n", answer);
    }
}
