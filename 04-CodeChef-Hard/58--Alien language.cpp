  #include <cstdio>
  #include <cmath>
  #include <cstring>
  #define BUF 4096
  char ibuf[BUF], obuf[BUF];
  int ipt = BUF, opt = 0;
  long long readLL(){
  while (ipt < BUF && ibuf[ipt] < '0') ipt++;
  if (ipt == BUF) {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] < '0') ipt++;
    }
    long long n = 0;
    while (ipt < BUF && ibuf[ipt] >= '0') n = (n*10)+(ibuf[ipt++]-'0');
    if (ipt == BUF) {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] >= '0') n = (n*10)+(ibuf[ipt++]-'0');
    }
    return n;
    }
    void writeChar(char ch) {
    obuf[opt++] = ch;
    if (opt == BUF) { fwrite(obuf, 1, BUF, stdout); opt = 0; }
    }
    void writeLL(long long n) {
    long long mx = 1000000000;
    if (n > mx) mx = 1000000000000000000ll;
    while (mx > n) mx /= 10;
    while (mx > 1) {
    writeChar(n/mx%10+'0');
    mx /= 10;
    }
    writeChar(n%10+'0');
    }
    void write0LL(long long n) {
    long long mx = 100000000;
    while (mx > 1) {
    writeChar(n/mx%10+'0');
    mx /= 10;
    }
    writeChar(n%10+'0');
    }
    void flushWrite() {
    fwrite(obuf, 1, opt, stdout);
    }
    #define BIG 1000000000
    class int128 {
    public:
    int128(long long a) {
    a0 = a; a1 = 0; a2 = 0; a3 = 0;
    if (a0 >= BIG) {
    a1 = a0/BIG;
    a0 %= BIG;
    if (a1 >= BIG) {
    a2 = a1/BIG;
    a1 %= BIG;
    }
    }
    }
    int128 &operator*=(long long a) {
    a3 *= a;
    if ((a2 *= a) >= BIG) { a3 += a2/BIG; a2 %= BIG; }
    if ((a1 *= a) >= BIG) { a2 += a1/BIG; a1 %= BIG; }
    if ((a0 *= a) >= BIG) { a1 += a0/BIG; a0 %= BIG; }
    if (a2 > BIG) { a3 += a2/BIG; a2 %= BIG; }
    if (a1 > BIG) { a2 += a1/BIG; a1 %= BIG; }
    if (a0 > BIG) { a1 += a0/BIG; a0 %= BIG; }
    return *this;
    }
    int128 &operator+=(const int128 &b) {
    if ((a0 += b.a0) >= BIG) { a0 -= BIG; a1++; }
    if ((a1 += b.a1) >= BIG) { a1 -= BIG; a2++; }
    if ((a2 += b.a2) >= BIG) { a2 -= BIG; a3++; }
    a3 += b.a3;
    return *this;
    }
    void print() {
    bool flag = false;
    if (a3) { writeLL(a3); flag = true; }
    if (flag) { write0LL(a2); } else if (a2) { writeLL(a2); flag = true; }
    if (flag) { write0LL(a1); } else if (a1) { writeLL(a1); flag = true; }
    if (flag) { write0LL(a0); } else { writeLL(a0); }
    }
    private:
    long long a0, a1, a2, a3;
    };
    long long countc[41][2220];
    long long asumc[41][2220];
    long long nsumc[41][2220];
    void prep() {
    for (int i = 1; i < 41; i++) {
    countc[i][i] = 1;
    asumc[i][i] = 1;
    nsumc[i][i] = 1;
    long long ct = i;
    int mxj = i < 5 ? 2220 : i == 5 ? 660 : 300;
    for (int j = i+1; j < mxj; j++) {
    countc[i][j] = ct;
    asumc[i][j] = asumc[i][j-1]+ct*(j-(i-1));
    nsumc[i][j] = nsumc[i][j-1]+ct;
    ct = ct*j/(j-(i-1));
    }
    }
    }
    long long A, B;
    int bits[42];
    long long add[42];
    long long count[42];
    int ord[42];
    #ifdef LOCAL
    int dbg;
    #endif
    long long solve3(long long n, long long z, long long mx) {
    if (mx > 18200) mx = 18200;
    long long mn = 0;
    while (mn+1 < mx) {
    long long md = mn + (mx-mn)/2;
    long long ct = md*(md+1)/2*(md+2)/3 + md*(md+2*z+1)/2 + md;
    if (ct > n) mx = md;
    else mn = md;
    }
    return mn;
    }
    void doitClose(long long n, long long &a, long long &b) {
    if (n < 4) {
    switch (n) {
    case 1: a = 1; b = 0; break;
    case 2: a = 1; b = 1; break;
    case 3: a = 3; b = 2; break;
    }
    return;
    }
    int nb = 0;
    long long on = n-1;
    while (on) { nb++; on >>= 1; }
    int exb = (int)(nb*sqrt(A/double(B)))-1;
    on = n;
    int delta = B/A-1;
    if (exb < 40 && delta < 40) {
    n--;
    a = 0;
    b = 0;
    for (int i = 1; i <= exb; i++) {
    bits[i] = exb+(exb-i)*delta+1;
    add[i] = i*B + (bits[i]-i)*A + A;
    count[i] = countc[i][bits[i]];
    a += asumc[i][bits[i]-1];
    long long nr = nsumc[i][bits[i]-1];
    b += nr*i;
    n -= nr;
    }
    } else {
    n -= 1ll<<exb;
    a = (1ll<<(exb-1))*exb;
    b = a;
    for (int i = 1; i <= exb; i++) {
    bits[i] = exb+1;
    add[i] = i*B+(exb+1-i)*A+A;
    count[i] = i > 1 ? count[i-1]*(exb-(i-2))/(i-1) : 1;
    }
    if (delta && exb > 2) {
    /* treat 1 and 2 separately */
    {
    int dct = (exb-1)*delta;
    a += exb*dct + dct*(dct+1)/2;
    b += dct;
    n -= dct;
    bits[1] += dct;
    add[1] += A*dct;
    }
    {
    int dct = (exb-2)*delta, pex = exb-1;
    count[2] += dct;
    bits[2] += dct;
    add[2] += A*dct;
    a += dct*(dct+1)/2*(2*dct+1)/3 + dct*pex*(dct+pex+1);
    int adct = dct*(dct+2*pex+1)/2;
    b += adct*2;
    n -= adct;
    }
    for (int i = 3; i < exb; i++) {
    int tgt = exb+1+(exb-i)*delta;
    for (int j = exb+1; j < tgt; j++) {
    long long ct = count[i];
    count[i] = count[i]*bits[i]/(bits[i]-(i-1));
    a += ct*(bits[i]-i+1);
    b += ct*i;
    n -= ct;
    bits[i]++;
    }
    add[i] += A*(tgt-(exb+1));
    }
    }
    }
    for (int i = exb+1; i < 42; i++) {
    bits[i] = i;
    add[i] = i*B+A;
    count[i] = 1;
    }
    int op = 0, mxb = 1;
    ord[0] = 1;
    while (n) {
    if (add[mxb+1] < add[ord[op]]) {
    for (int j = mxb; j > op; j--) ord[j] = ord[j-1];
    ord[op] = ++mxb;
    }
    int mini = ord[op++];
    if (op == mxb) op = 0;
    long long ct = count[mini];//nCk(bits[mini]-1, mini-1);
    count[mini] = count[mini]*bits[mini]/(bits[mini]-(mini-1));
    if (ct > n) ct = n;
    a += ct*(bits[mini]-mini+1);
    b += ct*mini;
    n -= ct;
    bits[mini]++;
    add[mini] += A;
    }
    }
    void doit(long long n, long long &a, long long &b) {
    if (n < 4) {
    switch (n) {
    case 1: a = 1; b = 0; break;
    case 2: a = 1; b = 1; break;
    case 3: a = 3; b = 2; break;
    }
    return;
    }
    for (int i = 0; i < 42; i++) {
    bits[i] = i;
    add[i] = i*B+A;
    count[i] = 1;
    }
    bits[0] = 1;
    n--;
    long long use1 = B/A+1;
    if (use1 >= n) use1 = n;
    bits[1] = use1 + 1;
    add[1] = B/*the 1*/ + use1*A/*this many 0s*/ + A/*extra 0 on some word*/;
    a = use1*(use1+1)/2; b = use1;
    n -= use1;
    int mxb = 1;
    ord[0] = 1;
    if (!n) return;
    long long use12 = B/A;
    long long u12ct = use12*(use12+1)/2/*2s*/ + use12/*1s*/;
    if (u12ct > n) {
    use12 = ((long long)sqrt(9.0+8.0*n) - 3)/2;
    u12ct = use12*(use12+1)/2 + use12;
    }
    use1 += use12;
    bits[1] = use1 + 1;
    add[1] = B + use1*A + A;
    a = use1*(use1+1)/2; b = use1;
    count[2] += use12;
    bits[2] = use12 + 2;
    add[2] = 2*B + use12*A + A;
    a += use12*(use12+1)/2*(2*use12+1)/3;
    b += use12*(use12+1)/2*2;
    n -= u12ct;
    mxb = 2;
    ord[1] = 2;
    if (add[2] < add[1]) { int s = ord[0]; ord[0] = ord[1]; ord[1] = s; }
    if (!n) return;
    long long use123 = B/A;
    if (use123 > 18200) use123 = 18200;
    long long u123ct = use123*(use123+1)/2*(use123+2)/3/*3s*/ +
    use123*(use123+2*use12+1)/2+use123;
    if (u123ct > n) {
    use123 = solve3(n, use12, use123);
    u123ct = use123*(use123+1)/2*(use123+2)/3/*3s*/ +
    use123*(use123+2*use12+1)/2+use123;
    }
    use1 += use123;
    bits[1] = use1 + 1;
    add[1] = B + use1*A + A;
    a = use1*(use1+1)/2; b = use1;
    use12 += use123;
    count[2] = use12+1;
    bits[2] = use12 + 2;
    add[2] = 2*B + use12*A + A;
    a += use12*(use12+1)/2*(2*use12+1)/3;
    b += use12*(use12+1)/2*2;
    bits[3] = use123 + 3;
    add[3] = 3*B + use123*A + A;
    a += use123*(use123+1)/2*(use123+2)/3*(3*use123+1)/4;
    b += use123*(use123+1)/2*(use123+2)/3*3;
    count[3] = (use123+1)*(use123+2)/2;
    n -= u123ct;
    mxb = 3;
    ord[2] = 3;
    if (add[3] < add[ord[1]]) {
    int s = ord[1]; ord[1] = ord[2]; ord[2] = s;
    if (add[3] < add[ord[0]]) {
    int s = ord[0]; ord[0] = ord[1]; ord[1] = s;
    }
    }
    int op = 0;
    while (n) {
    if (add[mxb+1] < add[ord[op]]) {
    for (int j = mxb; j > op; j--) ord[j] = ord[j-1];
    ord[op] = ++mxb;
    }
    int mini = ord[op++];
    if (op == mxb) op = 0;
    long long ct = count[mini];//nCk(bits[mini]-1, mini-1);
    count[mini] = count[mini]*bits[mini]/(bits[mini]-(mini-1));
    if (ct > n) ct = n;
    a += ct*(bits[mini]-mini+1);
    b += ct*mini;
    n -= ct;
    bits[mini]++;
    add[mini] += A;
    }
    }
    int main(int argc, char **argv) {
    #ifdef LOCAL
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'd') dbg = 1;
    #endif
    prep();
    int t = readLL();
    for (int i = 0; i < t; i++) {
    A = readLL(); B = readLL();
    if (B < A) { long long s = A; A = B; B = s; }
    long long a, b, n = readLL();
    if (A*50 >= B) doitClose(n, a, b); else doit(n, a, b);
    int128 a128(a), b128(b);
    a128 *= A;
    b128 *= B;
    a128 += b128;
    a128.print();
    #ifdef LOCAL
    if (dbg) {
    writeChar(' ');
    writeChar('(');
    writeLL(a+b);
    writeChar(':');
    writeChar(' ');
    writeLL(a);
    writeChar(' ');
    writeLL(b);
    writeChar(')');
    }
    #endif
    writeChar('\n');
    }
    flushWrite();
    return 0;
    }  