#include <bits/stdc++.h>
using namespace std;

const int N = 256;

const bool DEBUG = false;

int n, q, k;
int querycnt;
int secret[N][N];
int ans[N][N];

int randint(int ub) {
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, ub-1);
    return dist(rng);
}

int count_diamonds() {
    int cnt = 0;
    for (int i=1; i<n; i++) {
        for (int j=1; j<n; j++) {
            cnt += (
                secret[i-1][j-1] == 0 &&
                secret[i][j-1] == 1 &&
                secret[i-1][j] == 1 &&
                secret[i][j] == 0);
        }
    }
    return cnt;
}

void print(int (&arr)[N][N]) {
    for (int i=0; i<n; i++) {
        cerr << "    ";
        for (int j=0; j<n; j++) {
            cerr << "/\\"[arr[i][j]] << " \n"[j+1==n];
        }
    }
}

void init() {
    querycnt = 0;
    if (DEBUG) {
        n = 5;
        q = 4*n*n;
        static int mask = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (0 || n>5) {
                    secret[i][j] = randint(2);
                }
                else {
                    int bit = 1 << (n*i+j);
                    secret[i][j] = !!(mask&bit);
                }
            }
        }
        mask++;
        k = count_diamonds();
        //print(secret);
    }
    else {
        cin >> n >> q >> k;
        assert(n < N);
        assert(q >= 4*n*n);
    }
}

int query(int row, int col) {
    assert(querycnt < q);
    querycnt++;
    if (DEBUG) {
        secret[row][col] ^= 1;
        return k = count_diamonds();
    }
    else {
        cout << "1 " << (row+1) << ' ' << (col+1) << '\n';
        cout.flush();
        int cnt = -1;
        cin >> cnt;
        if (cnt == -1) exit(0);
        return k = cnt;
    }
}

int query(int rowcol) {
    return query(rowcol/n, rowcol%n);
}

// query a known value and flip it in ans
int flip(int row, int col) {
    int cnt = query(row, col);
    ans[row][col] ^= 1;
    return cnt;
}

int maybe_flip(int row, int col, char value) {
    int v = value=='/'? 0 : 1;
    if (ans[row][col] != v) {
        flip(row, col);
    }
    return k;
}

void rip() {
    if (DEBUG) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (secret[i][j] != ans[i][j]) {
                    cerr << "ans: \n";
                    print(ans);
                    cerr << "actual: \n";
                    print(secret);
                }
                assert(secret[i][j] == ans[i][j]);
            }
        }
        static int maxq;
        if (querycnt > maxq) {
            maxq = querycnt;
            cout << "AC " << querycnt << '/' << q << '\n';
            cout.flush();
        }
    }
    else {
        cout << "2\n";
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                cout << ans[i][j] << " \n"[j+1==n];
            }
        }
        cout.flush();
        int z = -1;
        cin >> z;
        if (z == -1) exit(0);
    }
}

const vector<int> gray4b {
    0b0000, 0b0001, 0b0011, 0b0010, 0b0110, 0b0111, 0b0101, 0b0100,
    0b1100, 0b1101, 0b1111, 0b1110, 0b1010, 0b1011, 0b1001, 0b1000,
};

void solve_2x2() {
    vector<int> cnt(16);
    cnt[0] = k;
    for (int i=1; i<16; i++) {
        int d = gray4b[i] ^ gray4b[i-1];
        assert(__builtin_popcount(d) == 1);
        int pos = 3 - __builtin_ctz(d);
        cnt[gray4b[i]] = query(pos/2, pos%2);
    }
    for (int mask=0; mask<8; mask++) {
        int a = cnt[mask];
        int b = cnt[mask | 0b1000];
        if (abs(a-b) == 1) {
            ans[0][0] = a>b;
            ans[0][1] = mask&0b0100? 0 : 1;
            ans[1][0] = mask&0b0010? 0 : 1;
            ans[1][1] = mask&0b0001? 1 : 0;
            break;
        }
    }
}

void solve_1x2(int fixed, int x, int y1, int y2) {
    if (!ans[fixed/n][fixed%n]) {
        flip(fixed/n, fixed%n);
    }
    for (int i=0;; i++) {
        int a = k;
        int b = flip(x/n, x%n);
        if (a != b) {
            ans[y1/n][y1%n] = 1;
            ans[y2/n][y2%n] = 0;
            break;
        }
        assert(i < 3);
        query(i%2? y2 : y1);
    }
}

void solve_top(int col) {
    return solve_1x2(n+col-1, col-1, col, n+col);
}

void solve_left(int row) {
    return solve_1x2(n*(row-1)+1, n*(row-1), n*row, n*row+1);
}

void scheffeli() {
    init();
    solve_2x2();
    for (int col=2; col<n; col++) solve_top(col);
    for (int row=2; row<n; row++) solve_left(row);

    // . . . . . . . . . .
    // . \ \ \ \ \ \ \ \ /
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . \ ? ? ? ? ? ? ? ?
    // . / ? ? ? ? ? ? ? ?

    for (int row=2; row<n; row++) {
        for (int col=2; col<n; col++) {
            // Setup this:
            //
            // . / .
            // . x \
            // . \ ?
            //
            // If flipping x changes square count, ? is /.
            if (ans[row-2][col-1] == 1 && ans[row-1][col-2] == 1) {
                maybe_flip(row-2, col-1, '/');
            }
            maybe_flip(row+0, col-1, '\\');
            maybe_flip(row-1, col+0, '\\');
            int a = k;
            int b = flip(row-1, col-1);
            ans[row][col] = (a==b);
        }
    }
    rip();
}

int main() {
    cin.sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        scheffeli();
    }
}