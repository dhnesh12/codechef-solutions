import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.IOException;
import java.util.ArrayList;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Aman Kumar Singh
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TreeSequences solver = new TreeSequences();
        solver.solve(1, in, out);
        out.close();
    }

    static class TreeSequences {
        long mod = 1000000007;
        int MAXN = 100005;
        int MAX_S = 1000005;
        int lgN = 21;
        PrintWriter out;
        InputReader in;
        long[] fact = new long[MAX_S];
        long[] inv_fact = new long[MAX_S];
        ArrayList<Integer>[] tree = new ArrayList[MAXN];
        int[] depth = new int[MAXN];
        int[] heavy = new int[MAXN];
        int[] head = new int[MAXN];
        int[] pos = new int[MAXN];
        int[] parent = new int[MAXN];
        int[] chain_pos = new int[MAXN];
        int[] chain_ind = new int[MAXN];
        int[] chain_size = new int[MAXN];
        int[] chain_head = new int[MAXN];
        int[] tin = new int[MAXN];
        int[] tout = new int[MAXN];
        int[][] anc = new int[lgN][MAXN];
        int timer = 0;
        int cur_pos = 0;
        int chain_no = 0;
        int[] arr = new int[MAXN];
        int n;
        ArrayList<Integer> hld_traversal = new ArrayList<>();
        long[][] segtree;

        void pre() {
            fact[0] = 1;
            inv_fact[0] = 1;
            int i = 0;
            for (i = 1; i < MAX_S; i++) {
                fact[i] = fact[i - 1] * i;
                fact[i] %= mod;
                inv_fact[i] = power(fact[i], mod - 2);
            }
        }

        long nCr(int n, int r) {
            if (n < r)
                return 0;
            if (n < 0 || r < 0)
                return 0;
            long ans = fact[n];
            ans *= inv_fact[n - r];
            ans %= mod;
            ans *= inv_fact[r];
            ans %= mod;
            return ans;
        }

        int dfs(int v, int p) {
            int size = 1;
            int max_c_size = 0;
            anc[0][v] = p;
            tin[v] = timer++;
            for (int i = 1; i < lgN; i++)
                anc[i][v] = anc[i - 1][anc[i - 1][v]];
            for (int c : tree[v]) {
                if (c != parent[v]) {
                    parent[c] = v;
                    depth[c] = depth[v] + 1;
                    int c_size = dfs(c, v);
                    size += c_size;
                    if (c_size > max_c_size) {
                        max_c_size = c_size;
                        heavy[v] = c;
                    }
                }
            }
            tout[v] = timer++;
            return size;
        }

        void decompose(int v, int h) {
            if (chain_head[chain_no] == -1)
                chain_head[chain_no] = v;
            head[v] = h;
            chain_ind[v] = chain_no;
            chain_pos[v] = chain_size[chain_no];
            chain_size[chain_no]++;
            pos[v] = cur_pos++;
            hld_traversal.add(v);
            if (heavy[v] != -1)
                decompose(heavy[v], h);
            for (int c : tree[v]) {
                if (c != parent[v] && c != heavy[v]) {
                    chain_no++;
                    decompose(c, c);
                }
            }
        }

        long segtree_sum_query(int l, int r) {
            long sum = 0;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1)
                    sum += segtree[0][l++];
                if ((r & 1) == 1)
                    sum += segtree[0][--r];
            }
            return sum;
        }

        long query_prod_segtree(int type, int l, int r) {
            long prod = 1;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) {
                    prod *= segtree[type][l++];
                    prod %= mod;
                }
                if ((r & 1) == 1) {
                    prod *= segtree[type][--r];
                    prod %= mod;
                }
            }
            return prod;
        }

        void build() {
            int i = 0;
            for (i = 0; i < n; i++)
                segtree[0][n + i] = arr[hld_traversal.get(i)];
            for (i = n - 1; i > 0; i--)
                segtree[0][i] = segtree[0][i << 1] + segtree[0][i << 1 | 1];
            for (i = 0; i < n; i++) {
                int curr = hld_traversal.get(i);
                if (arr[curr] == -1) {
                    segtree[1][n + i] = 1;
                    segtree[2][n + i] = 1;
                    segtree[3][n + i] = 1;
                    segtree[4][n + i] = 1;
                    continue;
                }
                int rem = chain_size[chain_ind[curr]] - chain_pos[curr];
                if (rem == 1 || segtree_sum_query(pos[curr] + 1, pos[curr] + rem) == -(rem - 1)) {
                    segtree[1][n + i] = 1;
                    segtree[2][n + i] = 1;
                    segtree[3][n + i] = 1;
                    segtree[4][n + i] = 1;
                    continue;
                }
                int lo = i + 1, hi = i + rem - 1;
                int ans = -1;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    int curr_val = mid - i;
                    if (segtree_sum_query(i + 1, mid + 1) != -curr_val) {
                        hi = mid - 1;
                        ans = mid;
                    } else
                        lo = mid + 1;
                }
                int len = ans - i - 1;
                segtree[1][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] - 1), len);
                segtree[2][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] - 1), len);
                segtree[3][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] + len), len);
                segtree[4][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] + len), len);
            }
            for (i = n - 1; i > 0; i--) {
                segtree[1][i] = (segtree[1][i << 1] * segtree[1][i << 1 | 1]) % mod;
                segtree[2][i] = (segtree[2][i << 1] * segtree[2][i << 1 | 1]) % mod;
                segtree[3][i] = (segtree[3][i << 1] * segtree[3][i << 1 | 1]) % mod;
                segtree[4][i] = (segtree[4][i << 1] * segtree[4][i << 1 | 1]) % mod;
            }
        }

        void segtree_update(int ind) {
            ind += n;
            for (; ind > 1; ind >>= 1) {
                segtree[1][ind >> 1] = (segtree[1][ind] * segtree[1][ind ^ 1]) % mod;
                segtree[2][ind >> 1] = (segtree[2][ind] * segtree[2][ind ^ 1]) % mod;
                segtree[3][ind >> 1] = (segtree[3][ind] * segtree[3][ind ^ 1]) % mod;
                segtree[4][ind >> 1] = (segtree[4][ind] * segtree[4][ind ^ 1]) % mod;
                segtree[0][ind >> 1] = (segtree[0][ind] + segtree[0][ind ^ 1]) % mod;
            }
        }

        void update(int node, int val) {
            arr[node] = val;
            segtree[0][n + pos[node]] = arr[node];
            if (arr[node] == -1) {
                segtree[1][n + pos[node]] = 1;
                segtree[2][n + pos[node]] = 1;
                segtree[3][n + pos[node]] = 1;
                segtree[4][n + pos[node]] = 1;
            } else {
                int curr = node;
                int i = pos[curr];
                int rem = chain_size[chain_ind[curr]] - chain_pos[curr];
                if (rem == 1 || segtree_sum_query(pos[curr] + 1, pos[curr] + rem) == -(rem - 1)) {
                    segtree[1][n + i] = 1;
                    segtree[2][n + i] = 1;
                    segtree[3][n + i] = 1;
                    segtree[4][n + i] = 1;
                } else {
                    i = pos[node];
                    int lo = i + 1, hi = i + rem - 1;
                    int ans = -1;
                    while (lo <= hi) {
                        int mid = (lo + hi) >> 1;
                        int curr_val = mid - i;
                        if (segtree_sum_query(i + 1, mid + 1) != -curr_val) {
                            hi = mid - 1;
                            ans = mid;
                        } else
                            lo = mid + 1;
                    }
                    int len = ans - i - 1;
                    segtree[1][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] - 1), len);
                    segtree[2][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] - 1), len);
                    segtree[3][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] + len), len);
                    segtree[4][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] + len), len);
                }
            }
            segtree_update(pos[node]);
            int rem = pos[node] - pos[head[node]];
            if (!(rem == 0 || segtree_sum_query(pos[head[node]], pos[node]) == -rem)) {
                int lo = pos[head[node]], hi = pos[node] - 1;
                int ans = -1;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    int len = pos[node] - mid;
                    if (segtree_sum_query(mid, pos[node]) != -len) {
                        lo = mid + 1;
                        ans = mid;
                    } else
                        hi = mid - 1;
                }
                node = hld_traversal.get(ans);
                int curr = node;
                rem = chain_size[chain_ind[curr]] - chain_pos[curr];
                int i = pos[node];
                if (rem == 1 || segtree_sum_query(pos[curr] + 1, pos[curr] + rem) == -(rem - 1)) {
                    segtree[1][n + i] = 1;
                    segtree[2][n + i] = 1;
                    segtree[3][n + i] = 1;
                    segtree[4][n + i] = 1;
                } else {
                    lo = i + 1;
                    hi = i + rem - 1;
                    ans = -1;
                    while (lo <= hi) {
                        int mid = (lo + hi) >> 1;
                        int curr_val = mid - i;
                        if (segtree_sum_query(i + 1, mid + 1) != -curr_val) {
                            hi = mid - 1;
                            ans = mid;
                        } else
                            lo = mid + 1;
                    }
                    int len = ans - i - 1;
                    segtree[1][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] - 1), len);
                    segtree[2][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] - 1), len);
                    segtree[3][n + i] = nCr((int) (arr[hld_traversal.get(ans)] - arr[hld_traversal.get(i)] + len), len);
                    segtree[4][n + i] = nCr((int) (-arr[hld_traversal.get(ans)] + arr[hld_traversal.get(i)] + len), len);
                }
                segtree_update(pos[node]);
            }
        }

        boolean is_ancestor(int u, int v) {
            return tin[u] <= tin[v] && tout[u] >= tout[v];
        }

        int lca_of(int u, int v) {
            if (is_ancestor(u, v))
                return u;
            if (is_ancestor(v, u))
                return v;
            int i = 0;
            for (i = lgN - 1; i >= 0; i--) {
                if (!is_ancestor(anc[i][u], v))
                    u = anc[i][u];
            }
            return anc[0][u];
        }

        int k_th(int u, int k) {
            int j = 0;
            while (k > 0) {
                if ((k & 1) == 1)
                    u = anc[j][u];
                k = k >> 1;
                j++;
            }
            return u;
        }

        int[] query1(int x, int y, int last, int type, int last_node, int cnt) {
            int[] hola = new int[5];
            hola[0] = last_node;
            hola[1] = last_node;
            int node = x;
            int rem = pos[x] - pos[y] + 1;
            long ways = 1;
            if (!(segtree_sum_query(pos[y], pos[node] + 1) == -rem)) {
                int lo = pos[y], hi = pos[node];
                int ans = -1;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    int len = pos[node] - mid + 1;
                    if (segtree_sum_query(mid, pos[node] + 1) != -len) {
                        lo = mid + 1;
                        ans = mid;
                    } else
                        hi = mid - 1;
                }
                node = hld_traversal.get(ans);
                hola[0] = node;
                node = y;
                lo = pos[y];
                hi = pos[x];
                ans = -1;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    int len = mid - pos[y] + 1;
                    if (segtree_sum_query(pos[node], mid + 1) != -len) {
                        hi = mid - 1;
                        ans = mid;
                    } else
                        lo = mid + 1;
                }
                node = hld_traversal.get(ans);
                hola[1] = node;
                ways *= query_prod_segtree(type, pos[hola[1]], pos[hola[0]]);
                ways %= mod;
                //pn(ways +" "+type);
                //pn(hola[0] +" "+hola[1]+" "+type+" "+segtree[3][n + pos[hola[1]]]);
                if (type == 1) {
                    int dis = depth[last_node] - depth[hola[0]] - 1;
                    if (cnt == 0)
                        dis++;
                    ways *= nCr(-(int) arr[hola[0]] + last, dis);
                    last = arr[hola[1]] - 1;
                    ways %= mod;
                } else if (type == 2) {
                    int dis = depth[last_node] - depth[hola[0]] - 1;
                    if (cnt == 0)
                        dis++;
                    ways *= nCr(-last + (int) arr[hola[0]], dis);
                    last = arr[hola[1]] + 1;
                    ways %= mod;
                } else if (type == 3) {
                    int dis = depth[last_node] - depth[hola[0]] - 1;
                    if (cnt == 0)
                        dis++;
                    ways *= nCr(-(int) arr[hola[0]] + last + dis, dis);
                    last = arr[hola[1]];
                    ways %= mod;
                } else {
                    int dis = depth[last_node] - depth[hola[0]] - 1;
                    if (cnt == 0)
                        dis++;
                    ways *= nCr((int) arr[hola[0]] - last + dis, dis);
                    ways %= mod;
                    last = arr[hola[1]];
                }
                cnt++;
            }
            hola[2] = last;
            hola[3] = (int) ways;
            hola[4] = cnt;
            return hola;
        }

        int[] query(int a, int b, int last, int last_node, int type) {
            long ways = 1;
            int x = b;
            int cnt = 0;
            for (; head[a] != head[b]; b = parent[head[b]]) {
                int[] curr = query1(b, head[b], last, type, last_node, cnt);
                ways *= (long) curr[3];
                ways %= mod;
                last = curr[2];
                last_node = curr[1];
                cnt = curr[4];
                //pn(Arrays.toString(curr)+" "+1);
            }
            int[] curr = query1(b, a, last, type, last_node, cnt);
            ways *= curr[3];
            ways %= mod;
            //pn(Arrays.toString(curr)+" 2");
            return new int[]{(int) ways, curr[1], curr[2]};
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            this.out = out;
            this.in = in;
            n = ni();
            int q = ni();
            pre();
            segtree = new long[5][2 * n];
            Arrays.fill(heavy, -1);
            Arrays.fill(chain_head, -1);
            int i = 0;
            for (i = 0; i < n; i++) {
                arr[i] = ni();
                tree[i] = new ArrayList<>();
            }
            for (i = 0; i < n - 1; i++) {
                int u = ni() - 1;
                int v = ni() - 1;
                tree[u].add(v);
                tree[v].add(u);
            }
            dfs(0, 0);
            decompose(0, 0);
            build();
            int u = 0, v = 0, lca = 0, a = 0, b = 0;
            while (q-- > 0) {
                switch (n()) {
                    case "UPDATE":
                        int node = ni() - 1;
                        int val = ni();
                        update(node, val);
                        break;
                    case "INCREASING":
                        u = ni() - 1;
                        v = ni() - 1;
                        lca = lca_of(u, v);
                        a = ni();
                        b = ni();
                        if (u != lca && v != lca) {
                            int dis = depth[v] - depth[lca];
                            int find_other = k_th(v, dis - 1);
                            int[] hola1 = query(lca, u, a, u, 2);
                            int[] hola2 = query(find_other, v, b, v, 1);
                            dis = depth[hola1[1]] + depth[hola2[1]] - 2 * depth[lca] - 1;
                            if (arr[hola1[1]] == -1)
                                dis++;
                            if (arr[hola2[1]] == -1)
                                dis++;
                            long ways = (long) hola1[0] * (long) hola2[0];
                            ways %= mod;
                            ways *= nCr((hola2[2] - hola1[2] + 1), dis);
                            ways %= mod;
                            pn(ways);
                        } else {
                            if (lca == u) {
                                int[] hola1 = query(lca, v, b, v, 1);
                                int dis = depth[hola1[1]] - depth[u];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((hola1[2] - a + 1), dis);
                                ways %= mod;
                                pn(ways);
                            } else {
                                int[] hola1 = query(lca, u, a, u, 2);
                                int dis = depth[hola1[1]] - depth[v];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((-hola1[2] + b + 1), dis);
                                ways %= mod;
                                pn(ways);
                            }
                        }
                        break;
                    case "DECREASING":
                        u = ni() - 1;
                        v = ni() - 1;
                        lca = lca_of(u, v);
                        a = ni();
                        b = ni();
                        if (u != lca && v != lca) {
                            int dis = depth[v] - depth[lca];
                            int find_other = k_th(v, dis - 1);
                            int[] hola1 = query(lca, u, b, u, 1);
                            int[] hola2 = query(find_other, v, a, v, 2);
                            dis = depth[hola1[1]] + depth[hola2[1]] - 2 * depth[lca] - 1;
                            if (arr[hola1[1]] == -1)
                                dis++;
                            if (arr[hola2[1]] == -1)
                                dis++;
                            long ways = (long) hola1[0] * (long) hola2[0];
                            ways %= mod;
                            ways *= nCr((hola1[2] - hola2[2] + 1), dis);
                            ways %= mod;
                            pn(ways);
                        } else {
                            if (lca == u) {
                                int[] hola1 = query(lca, v, a, v, 2);
                                int dis = depth[hola1[1]] - depth[u];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((-hola1[2] + b + 1), dis);
                                ways %= mod;
                                pn(ways);
                            } else {
                                int[] hola1 = query(lca, u, b, u, 1);
                                int dis = depth[hola1[1]] - depth[v];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((hola1[2] - a + 1), dis);
                                ways %= mod;
                                pn(ways);
                            }
                        }
                        break;
                    case "NON-DECREASING":
                        u = ni() - 1;
                        v = ni() - 1;
                        lca = lca_of(u, v);
                        a = ni();
                        b = ni();
                        if (u != lca && v != lca) {
                            int dis = depth[v] - depth[lca];
                            int find_other = k_th(v, dis - 1);
                            int[] hola1 = query(lca, u, a, u, 4);
                            int[] hola2 = query(find_other, v, b, v, 3);

                            dis = depth[hola1[1]] + depth[hola2[1]] - 2 * depth[lca] - 1;
                            if (arr[hola1[1]] == -1)
                                dis++;
                            if (arr[hola2[1]] == -1)
                                dis++;
                            long ways = (long) hola1[0] * (long) hola2[0];
                            ways %= mod;
                            ways *= nCr((hola2[2] - hola1[2] + dis), dis);
                            ways %= mod;
                            pn(ways);
                        } else {
                            if (lca == u) {
                                int[] hola1 = query(lca, v, b, v, 3);
                                int dis = depth[hola1[1]] - depth[u];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((hola1[2] - a + dis), dis);
                                ways %= mod;
                                pn(ways);
                            } else {
                                int[] hola1 = query(lca, u, a, u, 4);
                                int dis = depth[hola1[1]] - depth[v];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((-hola1[2] + b + dis), dis);
                                ways %= mod;
                                pn(ways);
                            }
                        }
                        break;
                    case "NON-INCREASING":
                        u = ni() - 1;
                        v = ni() - 1;
                        lca = lca_of(u, v);
                        a = ni();
                        b = ni();
                        if (u != lca && v != lca) {
                            int dis = depth[v] - depth[lca];
                            int find_other = k_th(v, dis - 1);
                            int[] hola1 = query(lca, u, b, u, 3);
                            int[] hola2 = query(find_other, v, a, v, 4);
                            //pn(Arrays.toString(hola1));
                            //pn(Arrays.toString(hola2));
                            dis = depth[hola1[1]] + depth[hola2[1]] - 2 * depth[lca] - 1;
                            if (arr[hola1[1]] == -1)
                                dis++;
                            if (arr[hola2[1]] == -1)
                                dis++;
                            long ways = (long) hola1[0] * (long) hola2[0];
                            ways %= mod;
                            ways *= nCr((hola1[2] - hola2[2] + dis), dis);
                            ways %= mod;
                            pn(ways);
                        } else {
                            if (lca == u) {
                                int[] hola1 = query(lca, v, a, v, 4);
                                int dis = depth[hola1[1]] - depth[u];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((-hola1[2] + b + dis), dis);
                                ways %= mod;
                                pn(ways);
                            } else {
                                int[] hola1 = query(lca, u, b, u, 3);
                                int dis = depth[hola1[1]] - depth[v];
                                if (arr[hola1[1]] == -1)
                                    dis++;
                                long ways = hola1[0];
                                ways *= nCr((hola1[2] - a + dis), dis);
                                ways %= mod;
                                pn(ways);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        String n() {
            return in.next();
        }

        int ni() {
            return in.nextInt();
        }

        void pn(long zx) {
            out.println(zx);
        }

        long power(long x, long y) {
            if (y == 0) {
                return 1;
            }
            long p = power(x, y / 2) % mod;
            p = (p * p) % mod;
            return (y % 2 == 0) ? p : (x * p) % mod;
        }

    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1) {
                throw new UnknownError();
            }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new UnknownError();
                }
                if (numChars <= 0) {
                    return -1;
                }
            }
            return buf[curChar++];
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            int c = read();
            while (isSpaceChar(c)) {
                c = read();
            }
            StringBuffer res = new StringBuffer();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));

            return res.toString();
        }

        private boolean isSpaceChar(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

    }
}

