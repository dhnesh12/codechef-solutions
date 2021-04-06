#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <vector>

#define MAX 100000
#define MOD 1000000007

using namespace std;

typedef long long int64;

void fast_scanf(int &number);
int  num_valid_pairings(int *array, int n);

int lookup_factorial[MAX + 1];

int main(void)
{
    // Pre-compute factorial table.
    lookup_factorial[0] = lookup_factorial[1] = lookup_factorial[2] = 1;
    for (int i = 3; i <= MAX; i += 2)
        lookup_factorial[i + 1] = lookup_factorial[i]
            = (int64)lookup_factorial[i - 1] * i % MOD;

    int test_cases;
    fast_scanf(test_cases);

    while (test_cases--) {
        int n;
        fast_scanf(n);

        int *array = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            fast_scanf(array[i]);

        printf("%i\n", num_valid_pairings(array, n));
    }

    return 0;
}

void fast_scanf(int &number)
{
    register int ch = getchar_unlocked();
    number          = 0;

    while (ch > 47 && ch < 58) {
        number = number * 10 + ch - 48;
        ch     = getchar_unlocked();
    }
}

int num_valid_pairings(int *array, int n)
{
    // Sort the array in descending order.
    sort(array, array + n, greater<int>());

    // Create a frequencies table.
    vector<int> frequencies;
    frequencies.reserve(n);

    int count = 1;
    for (int i = 1; i < n; i++) {
        if (array[i] == array[i - 1])
            count++;
        else {
            frequencies.push_back(count);
            count = 1;
        }
    }
    frequencies.push_back(count);

    int answer = 1;
    for (int i = 0; i < frequencies.size(); i++) {
        if (frequencies[i] & 1)
            answer = (int64)answer * frequencies[i + 1]-- % MOD;
        answer = (int64)answer * lookup_factorial[frequencies[i]] % MOD;
    }

    return answer;
}