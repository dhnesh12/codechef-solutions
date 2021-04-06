#include <bits/stdc++.h>
     
    #include <ext/pb_ds/assoc_container.hpp> // Common file 
    #include <ext/pb_ds/tree_policy.hpp> 
      
    typedef __gnu_pbds::tree<long long, __gnu_pbds::null_type, std::less<long long>, __gnu_pbds::rb_tree_tag, 
                 __gnu_pbds::tree_order_statistics_node_update> 
        new_tree; 
     
    namespace Input {
        const int BUFFER_SIZE = int(1.1e5);
     
        char _buf[BUFFER_SIZE + 10];
        int _buf_pos, _buf_len;
     
        char seekChar() {
            if(_buf_pos >= _buf_len) {
                _buf_len = fread(_buf, 1, BUFFER_SIZE, stdin);
                _buf_pos = 0;
            }
            assert(_buf_pos < _buf_len);
            return _buf[_buf_pos];
        }
     
        bool seekEof() {
            if(_buf_pos >= _buf_len) {
                _buf_len = fread(_buf, 1, BUFFER_SIZE, stdin);
                _buf_pos = 0;
            }
            return _buf_pos >= _buf_len;
        }
     
        char readChar() {
            char ret = seekChar();
            _buf_pos++;
            return ret;
        }
     
        long long readLong(long long lb, long long rb) {
            char c = readChar();
            long long mul = 1;
            if(c == '-') {
                c = readChar();
                mul = -1;
            }
            assert(isdigit(c));
     
            long long ret = c - '0';
            char first_digit = c;
            int len = 0;
            while(!seekEof() && isdigit(seekChar()) && ++len <= 19) {
                ret = ret * 10 + readChar() - '0';
            }
            ret *= mul;
     
            if(len >= 2) assert(first_digit != '0');
            assert(len <= 18);
            assert(lb <= ret && ret <= rb);
            return ret;
        }
     
        int readInt(int lb, int rb) {
            return readLong(lb, rb);
        }
     
        void readEoln() {
            char c = readChar();
            assert(c == '\n');
            //assert(c == '\n' || (c == '\r' && readChar() == '\n'));
        }
     
        void readSpace() {
            char c = readChar();
            assert(c == ' ');
        }
    }
    using namespace Input;
     
    const int MAX_N = 200000;
    const int MAX_SUM_N = 200000;
    const int MAX_Q = 200000;
    const int MAX_SUM_Q = 200000;
     
    class DisjointSet {
        std::vector<int> par;
    public:
        DisjointSet(int n): par(n+1) {
            for(int i = 1; i <= n; i++) par[i] = i;
        }
     
        int get(int x) {
            return par[x] == x ? x : (par[x] = get(par[x]));
        }
     
        bool merge(int x, int y) {
            x = get(x);
            y = get(y);
            par[x] = y;
            return x != y;
        }
    };
     
    namespace PersistentSegmentTree {
        struct node {
            int sum, left, right, ts;
        };
     
        node tree[int(1.2e7)]; int NUM_NODES;
        int TIME;
     
        node& get_node(int x) {
            node& ret = tree[x];
            if(ret.ts < TIME) {
                ret = {0, 0, 0, TIME};
            }
            return ret;
        }
     
        node& new_node() {
            return get_node(++NUM_NODES);
        }
     
        int insert(int ni, int nl, int nr, int x) {
            node &nd = get_node(ni);
            int ret = ++NUM_NODES;
            node &new_node = get_node(ret);
     
            new_node = nd;
            if(nl == nr) {
                new_node.sum += 1;
                return ret;
            }
     
            int nm = (nl + nr) >> 1;
            if(x <= nm) {
                new_node.left = insert(nd.left, nl, nm, x);
            }else {
                new_node.right = insert(nd.right, nm+1, nr, x);
            }
     
            new_node.sum = tree[new_node.left].sum + tree[new_node.right].sum;
            return ret;
        }
     
        int get_sum (int ni, int nl, int nr, int x, int y) {
            if(ni == 0 || x > y) return 0;
     
            node &nd = get_node(ni);
            if(nl == x && nr == y) {
                return nd.sum;
            }
            
            int nm = (nl + nr) >> 1;
            int ret = 0;
            if(x <= nm) {
                ret += get_sum(nd.left, nl, nm, x, std::min(y, nm));
            }
            if(nm < y) {
                ret += get_sum(nd.right, nm+1, nr, std::max(x, nm+1), y);
            }
            return ret;
        }
     
        int get_kth(int nl, int nr, std::vector<int> nodes, std::vector<int> coefs, long long &k) {
            const int NUM_CONSIDERING_NODES = nodes.size();
            while(nl < nr) {
                int nm = (nl + nr) >> 1;
     
                int leftsum = 0;
                for (int i = 0; i < NUM_CONSIDERING_NODES; i++) {
                    if (!nodes[i]) continue;
                    auto &nd = get_node(nodes[i]);
                    if (!nd.left) continue;
                    auto &ndl = get_node(nd.left);
                    leftsum += ndl.sum * coefs[i];
                }
     
                if (k < leftsum) {
                    for (int i = 0; i < NUM_CONSIDERING_NODES; i++) {
                        if (!nodes[i]) continue;
                        nodes[i] = get_node(nodes[i]).left;
                    }
                    nr = nm;
                } else {
                    k -= leftsum;
                    for (int i = 0; i < NUM_CONSIDERING_NODES; i++) {
                        if (!nodes[i]) continue;
                        nodes[i] = get_node(nodes[i]).right;
                    }
                    nl = nm+1;
                }
            }
            return nl;
        }
     
        void clear() {
            TIME++;
            NUM_NODES = 0;
        }
    }
     
     
    int sumN = 0, sumQ = 0;
     
    std::vector<int> gph[MAX_N+5];
    int depth[MAX_N+5];
    int subtreeSize[MAX_N+5];
    long long candidatePrefixSum[MAX_N+5];
     
    std::vector<int> ord;
    std::vector<int> nodes_with_depth[MAX_N+5], roots_with_depth[MAX_N+5];
     
    int L[MAX_N+5], R[MAX_N+5];
     
    int dfs (int u, int p) {
        depth[u] = depth[p] + 1;
        ord.push_back(u);
        nodes_with_depth[depth[u]].push_back(u);
        L[u] = ord.size();
        for (int v : gph[u]) if(v != p) subtreeSize[u] += dfs(v, u);
        R[u] = ord.size();
        return ++subtreeSize[u];
    }
     
    int roots[MAX_N+5];
     
    void run() {
        int N = readInt(1, MAX_N);
        readEoln();
        sumN += N;
        assert(sumN <= MAX_SUM_N);
     
        DisjointSet ds(N);
        for (int e = 0; e < N-1; e++) {
            int u = readInt(1, N);
            readSpace();
            int v = readInt(1, N);
            readEoln();
            
            bool merged = ds.merge(u, v);
            assert(merged);
     
            gph[u].push_back(v);
            gph[v].push_back(u);
        }
        
        ord.reserve(N);
        dfs(1, 0);
        for (int i = 1; i <= N; i++) {
            candidatePrefixSum[i] = candidatePrefixSum[i-1] + (N - subtreeSize[i]);
        }
     
        PersistentSegmentTree::clear();
        for (int i = 1; i <= N; i++) {
            roots[i] = PersistentSegmentTree::insert(roots[i-1], 0, N, depth[ord[i-1]]);
        }
        for (int d = 0; d <= N; d++) if(!nodes_with_depth[d].empty()) {
            PersistentSegmentTree::new_node();
            roots_with_depth[d].push_back(PersistentSegmentTree::NUM_NODES);
            for (int u : nodes_with_depth[d]) {
                int new_root = PersistentSegmentTree::insert(roots_with_depth[d].back(), 1, N, u);
                roots_with_depth[d].push_back(new_root);
            }
        }
     
        int Q = readInt(1, MAX_Q);
        readEoln();
        sumQ += Q;
        assert(sumQ <= MAX_SUM_Q);
        
        new_tree usedPositions;
     
        const int MOD = 1'000'000'007;
        long long decryptionKey = 0;
        for (long long pow2 = 1, pow3 = 1, qid = 0; qid < Q; qid++) {
            (pow2 *= 2) %= MOD;
            (pow3 *= 3) %= MOD;
     
            long long encryptedChoice = readLong(0, (1ll << 36));
            readEoln();
     
            long long decryptedChoice = (encryptedChoice ^ decryptionKey) - 1;
            
            long long target = -1;
            {
                long long low = decryptedChoice;
                long long high = std::min(decryptedChoice + qid, candidatePrefixSum[N]);
                while (low <= high) {
                    long long mid = (low + high) / 2;
                    long long currentPosition = mid - usedPositions.order_of_key(mid+1);
                    if (currentPosition < decryptedChoice) {
                        low = mid+1;
                    } else {
                        target = mid;
                        high = mid-1;
                    }
                }
     
                if (target < 0) {
                    printf("qid = %d, dc = %lld %lld\n", qid, decryptedChoice, candidatePrefixSum[N]);
                }
     
                assert(target >= 0);
                usedPositions.insert(target);
            }
            
            // find target-th position from list
     
            // candidatePrefixSum[u-1] <= target < candidatePrefixSum[u]
            int u = std::upper_bound(candidatePrefixSum, candidatePrefixSum + N + 1, target) - candidatePrefixSum;
            target -= candidatePrefixSum[u-1];
     
            int d = PersistentSegmentTree::get_kth(
                0, N, 
                {roots[N], roots[R[u]], roots[L[u]-1]},
                {+1, -1, +1},
                target
            );
     
            int pl = std::distance(
                nodes_with_depth[d].begin(),
                std::lower_bound(
                    nodes_with_depth[d].begin(), nodes_with_depth[d].end(), u,
                    [&](const int &a, const int &b) { return L[a] < L[b]; }
                )
            );
     
            int pr = std::distance(
                nodes_with_depth[d].begin(),
                std::upper_bound(
                    nodes_with_depth[d].begin(), nodes_with_depth[d].end(), ord[R[u]-1],
                    [&](const int &a, const int &b) { return L[a] < L[b]; }
                )
            );
            int v = PersistentSegmentTree::get_kth(
                1, N,
                {roots_with_depth[d].back(), roots_with_depth[d][pr], roots_with_depth[d][pl]},
                {+1, -1, +1},
                target
            );
     
            assert(target == 0);
            assert(v > 0);
            assert(depth[v] == d);
     
            (decryptionKey += pow2 * u + pow3 * v) %= MOD;
        }
        printf("%lld\n", decryptionKey);
        // initialize global vars
        ord.clear();
        for (int u = 0; u <= N; u++) {
            gph[u].clear();
            depth[u] = 0;
            subtreeSize[u] = 0;
            L[u] = R[u] = 0;
            candidatePrefixSum[u] = 0;
            nodes_with_depth[u].clear();
            roots_with_depth[u].clear();
        }
    }
     
    int main() {
    #ifdef IN_MY_COMPUTER
        freopen("example.in", "r", stdin);
    #endif
     
        int T = readInt(1, 1000);
        readEoln();
        while(T--) {
            run();
        }
        assert(feof(stdin));
        return 0;
    } 