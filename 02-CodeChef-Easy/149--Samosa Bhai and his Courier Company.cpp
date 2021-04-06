#include <bits/stdc++.h>
#include <sys/mman.h>
#include <sys/stat.h>
using namespace std;

struct RdMap {
    char* p, * last;
};
static RdMap rdmap_;

void map_stream(FILE* stream)
{
    struct stat sb;
    int fd = fileno(stream);
    
    fstat(fd, &sb);
    void* addr = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(addr != MAP_FAILED);
    
    rdmap_.p = static_cast<char*>(addr);
    rdmap_.last = rdmap_.p + sb.st_size;
}

inline int readchar()
{
    if (__builtin_expect(rdmap_.p != rdmap_.last, 1))
        return *rdmap_.p++;
    return EOF;
}

long int readlong()
{
    long int v = 0, m = 1;
    int c;
    
    while ( isspace(c = readchar()) )
        ;
    
    if (c == '-') {
        c = readchar();
        m = -1;
    }
    
    c -= '0';
    
    while ( static_cast<unsigned int>(c) < 10U ) {
        v = v * 10 + c;
        c  = readchar() - '0';
    }
    
    return v * m;
}

constexpr int MODi = pow(10, 9) + 7;
constexpr int NMAX = pow(10, 5);
constexpr int KMAX = 100;

#define FOR(i, first, last) \
    for ( i = (first); i < (last); i++ )
#define ROF(i, first, last) \
    for ( i = (last); (first) < i--; )

inline long int iwrap(long int x, long int y)
{
    if (x > 0)
        return x % y;
    if (x < 0)
        return (x + 1) % y + y - 1;
    return 0;
}

void rsort(int* a, int n)
{
    auto mask = [](unsigned int x, unsigned int i)
    { return (x >> i*8) % 256; };
    
    static int temp[NMAX];
    int* b = temp;
    int i, j;
    
    FOR(i, 0, 4) {
        int h[256]{};
        FOR(j, 0, n)
            h[mask(a[j], i)]++;
        FOR(j, 1, 256)
            h[j] += h[j-1];
        ROF(j, 0, n)
            b[--h[mask(a[j], i)]] = a[j];
        swap(a, b);
    }
}

static int binom[KMAX+1][KMAX+1];

__attribute__ ((constructor))
void build_binomial_table()
{
    int i, j;
    FOR(i, 0, KMAX+1) {
        binom[i][i] = binom[i][0] = 1;
    }
    FOR(i, 2, KMAX+1) {
        FOR(j, 1, i) {
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % MODi;
        }
    }
}

int solve(int n, int k, const int* A)
{
    static long int A_to_[KMAX+1], C[KMAX+1];
    long int res = 0;
    int i, a;
    
    fill(C, C + k+1, 0L);
    
    FOR(i, 0, n) {
        A_to_[0] = 1;
        FOR(a, 1, k+1) {
            A_to_[a] = A_to_[a-1] * -A[i] % MODi;
        }
        FOR(a, 0, k+1) {
            res = (res + C[a] * labs(A_to_[k-a])) % MODi;
            C[a] = (C[a] + A_to_[a] * binom[k][a]) % MODi;
        }
    }
    return iwrap(2*res, MODi);
}

int main(int argc, char* argv[])
{
    static_assert(sizeof(long int) == 8, "");
    static_assert(sizeof(int) == 4, "");
	
    map_stream(stdin);
    
    static int A[NMAX];
    int t = readlong();
    int i, j;
    
    FOR(i, 0, t) {
        int n = readlong();
        int k = readlong();
        
        FOR(j, 0, n) {
            A[j] = readlong();
        }
        
        rsort(A, n);
        printf("%d\n", solve(n, k, A));
    }
    return 0;
}