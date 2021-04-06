///this wavelet tree code can do both adjacent-swap and index
///active/inactive toggle updates to achieve efficiency, make
///sure to use minimum amount of updatable(true) BitVectors
#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define popcnt(x) __builtin_popcount(x)

struct BitVector {
    typedef unsigned u32;
    vector<u32>blocks;
    int length, blockCount;

    bool updatable;
    BitVector(bool updatable) : updatable(updatable) { }

    vector< int >prefixSum; ///builds prefixSum if !updatable
    vector< int >fenwick;   ///builds fenwick if updatable
    void init(const vector< int > &base, int mid) {
        length = base.size();
        blockCount = (length+31)/32+1;
        blocks.assign(blockCount, 0);
        if (updatable) fenwick.assign(blockCount, 0);
        else prefixSum.assign(blockCount, 0);

        for (int i = 0; i < length; i++) {
            if (mid < base[i]) blocks[i>>5] |= 1 << (i&31);
        }
        if (updatable) {
            for (int i = 1; i < blockCount; i++) {
                fenwick[i] += popcnt(blocks[i-1]);
                if (i+(i&-i) < blockCount) fenwick[i+(i&-i)] += fenwick[i];
            }
        } else {
            for (int i = 1; i < blockCount; i++) {
                prefixSum[i] = prefixSum[i-1] + popcnt(blocks[i-1]);
            }
        }
    }

    bool access(int i) {
        return (blocks[i>>5]>>(i&31))&1;
    }
    int blockRank(int b) {
        if (!updatable) return prefixSum[b];
        int ans = 0;
        while (b > 0) {
            ans += fenwick[b];
            b -= b&-b;
        }
        return ans;
    }
    int rank(int i) {  ///set bits in [0..i)
        int b = i>>5, r = i&31;
        return blockRank(b) + popcnt( blocks[b] & ((1U<<r)-1) );
    }
    int flip(int i) {
        assert(updatable);
        int b = i>>5, r = i&31;
        blocks[b] ^= 1U<<r;
        int cur = (blocks[b]>>r)&1;
        b++;
        while (b < blockCount) {
            fenwick[b] += cur ? 1 : -1;
            b += b&-b;
        }
        return cur;
    }
};

struct Node {
    int cnt;
    Node *bam, *dan;
    Node(int c = 0, Node *b = NULL, Node *d = NULL) :  cnt(c), bam(b), dan(d) {}

    void build(int l, int r) {
        if (l==r) return;
        int mid = (l+r)/2;
        bam = new Node();
        dan = new Node();
        bam->build(l, mid);
        dan->build(mid+1, r);
    }

    Node* update(int l, int r, int idx, int v) {
        if (idx < l || r < idx) return this;
        if (l==r) {
            Node *ret = new Node(cnt);
            ret->cnt += v;
            return ret;
        }

        Node* ret = new Node();
        int mid = (l+r)/2;
        ret->bam = bam->update(l, mid, idx, v);
        ret->dan = dan->update(mid+1, r, idx, v);
        ret->cnt = ret->bam->cnt + ret->dan->cnt;
        return ret;
    }

    int query(int l, int r, int x, int y) {
        if (r < x || y < l) return 0;
        if (x <= l && r <= y) {
//            cout << "got " << cnt << " at [" << l << "," << r << "]" << endl;
            return cnt;
        }
        int mid = (l+r)/2;
        return bam->query(l, mid, x, y) + dan->query(mid+1, r, x, y);
    }
};

const int MAXN = 1e5+7;
int last[MAXN];

typedef Node* PSTree;

struct WaveletTree {
    int lo, hi;   ///minimum element and maximum element
    WaveletTree *lc, *rc;

    ///bv must be true if swaps are happening
    BitVector bv{false};         ///i-th bit 1 if it goes to right

    vector< PSTree >bamDistincts;

    int sz;
    ///assumes all element are non-negative and
    ///every element between min and max are present
    WaveletTree(const vector< int > &v) : sz(v.size()) {
        assert(!v.empty());
        lo = *min_element(all(v));
        hi = *max_element(all(v));
        if (lo == hi) return;

        int mid = (lo+hi)/2;
        vector< int >bam, dan;

        bamDistincts.reserve(sz+1);
        bamDistincts.push_back(new Node());
        bamDistincts.back()->build(0, sz-1);
        for (int j = lo; j <= hi; j++) last[j] = -1;

//        cout << "building " << lo << "," << mid << "," << hi << endl;
        for (int i = 0; i < sz; i++) {
            int x = v[i];
            PSTree tr = bamDistincts.back();
            if (x <= mid) {
                bam.push_back(x);
//                cout << "+1 at " << i << endl;
                tr = tr->update(0, sz-1, i, 1);
                if (last[x] != -1) {
                    tr = tr->update(0, sz-1, last[x], -1);
//                    cout << "-1 at " << last[x] << endl;
                }
                last[x] = i;
            } else {
                dan.push_back(x);
            }
            bamDistincts.push_back(tr);
        }

        bv.init(v, mid);

        lc = new WaveletTree(bam);
        rc = new WaveletTree(dan);
    }

    ///find the current value in i-th index
    int access(int i) {
        if (lo == hi) return lo;
        int ii = bv.rank(i);
        if (bv.access(i)) return rc->access(ii);
        else return lc->access(i-ii);
    }

//    ///find k-th smallest in [i, j); 1 <= k <= active in [i, j)
//    int quantile(int i, int j, int k) {
//        if (lo == hi) return lo;
//        int ii = bv.rank(i);
//        int jj = bv.rank(j);
//        int inleft = (j-i)-(jj-ii); ///if the elements are always active
//        if (k <= inleft) return lc->quantile(i-ii, j-jj, k);
//        return rc->quantile(ii, jj, k-inleft);
//    }
    ///find k-th smallest in distinct [i, j)
    int distinctQuantile(int i, int j, int k) {
//        cout << "in " << lo << " " << hi << " with " << k << endl;
//        cout << "ij " << i << " " << j << endl;
        if (i >= j) return -1;
        if (lo == hi) return k == 1 ? lo : -1;
        int ii = bv.rank(i);
        int jj = bv.rank(j);
        int inleft = bamDistincts[j]->query(0, sz-1, i, sz-1);
//        cout << "bam " << inleft << endl;
//        int inleft = (j-i)-(jj-ii); ///if the elements are always active
        if (k <= inleft) return lc->distinctQuantile(i-ii, j-jj, k);
        return rc->distinctQuantile(ii, jj, k-inleft);
    }

    ///find no of values in [i, j) which are active and < x
    int countLessThan(int i, int j, int x) {
        if (i >= j || x <= lo) return 0;
        if (hi < x) return j-i; ///if the elements are always active

        int ii = bv.rank(i), jj = bv.rank(j);
        return lc->countLessThan(i-ii, j-jj, x) + rc->countLessThan(ii, jj, x);
    }

    ~WaveletTree() {
        if (lo == hi) return;
        delete lc;
        delete rc;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector< int >v(n);
    for (int &x : v) {
        cin >> x;
    }

    vector< int >distinct(v);
    sort(all(distinct));
    distinct.erase(unique(all(distinct)), distinct.end());

    auto place = [&](const vector< int >&v, int x) {
        return lower_bound(all(v), x) - v.begin();
    };
    for (int i = 0; i < n; i++) {
        v[i] = place(distinct, v[i]);
//        cout << v[i] << " ";
    }
//    cout << endl;

    WaveletTree wt(v);

    int ans = 0;
    while (q--) {
        int a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;
        int l, r;
        l = (a*1LL*max(ans, 0)+1LL*b)%n+1;
        r = (c*1LL*max(ans, 0)+1LL*d)%n+1;
        if (l > r) swap(l, r);
//        cout << "l = " << l << " r = " << r << endl;

        ans = wt.distinctQuantile(l-1, r, k);
        if (ans != -1) ans = distinct[ans];

        cout << ans << "\n";
    }

    return 0;
}

