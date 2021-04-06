//package codechef.medium.crypcur;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

    public static void main(String[] args) {
        stack = new Stack<>();
        id = new int[MAX_N];
        vis = new boolean[MAX_N];
        g1 = new Graph(MAX_N, MAX_N);
        rg = new Graph(MAX_N, MAX_N);
        g2 = new Graph(MAX_N, MAX_N);
        sz = new int[MAX_N];

        FastReader reader = new FastReader();
        StringBuilder buf = new StringBuilder();
        int tc = reader.nextInt();
        while (tc-- > 0) {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int[][] C = new int[m][];
            for (int i = 0; i < m; i++) {
                C[i] = new int[3];
                for (int j = 0; j < 3; j++) {
                    C[i][j] = reader.nextInt();
                }
            }
            int res = solve(n, m, C);
            if (res < 0) {
                buf.append("Impossible");
            } else {
                buf.append(res);
            }
            buf.append('\n');
        }
        System.out.print(buf.toString());
    }

    private static final int INF = 1 << 30;

    public static int solve(int n, int m, int[][] C) {
        if (!check(n, INF, C)) {
            return -1;
        }
        int left = 1;
        int right = INF;
        while (left < right) {
            int mid = (left + right) / 2;
            if (check(n, mid, C)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }

    private static boolean check(int n, int x, int[][] C) {
        g1.reset(n);
        for (int[] c : C) {
            if (c[2] > x) {
                continue;
            }
            g1.addEdge(c[0] - 1, c[1] - 1);
        }
        stack.clear();

        for (int i = 0; i < n; i++) {
            vis[i] = false;
            id[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(g1, i);
            }
        }

        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }
        Graph r = g1.getTranspose(n);
        int scc = 0;
        while (stack.size() > 0) {
            int u = stack.pop();
            if (!vis[u]) {
                dfs2(r, u, scc);
                scc++;
            }
        }

        g2.reset(scc);

        for (int u = 0; u < n; u++) {
            for (int i = g1.nodes[u]; i > 0; i = g1.next[i]) {
                int v = g1.to[i];
                if (id[u] != id[v]) {
                    g2.addEdge(id[u], id[v]);
                }
            }
        }

        for (int i = 0; i < scc; i++) {
            sz[i] = 0;
        }

        for (int i = 0; i < scc; i++) {
            if (dfs3(g2, i) == scc) {
                return true;
            }
        }
        return false;
    }

    private static final int MAX_N = 100010;

    private static int time;
    private static int scc;
    private static Stack<Integer> stack;
    private static int[] id;
    private static boolean[] vis;
    private static Graph g1;
    private static Graph g2;
    private static Graph rg;
    private static int[] sz;

    private static void dfs1(Graph g, int u) {
        vis[u] = true;
        for (int i = g.nodes[u]; i > 0; i = g.next[i]) {
            int v = g.to[i];
            if (!vis[v]) {
                dfs1(g, v);
            }
        }
        stack.push(u);
    }

    private static void dfs2(Graph g, int u, int ii) {
        id[u] = ii;
        vis[u] = true;
        for (int i = g.nodes[u]; i > 0; i = g.next[i]) {
            int v = g.to[i];
            if (!vis[v]) {
                dfs2(g, v, ii);
            }
        }
    }

    private static int dfs3(Graph g, int u) {
        if (sz[u] > 0) {
            return sz[u];
        }
        for (int i = g.nodes[u]; i > 0; i = g.next[i]) {
            int v = g.to[i];
            sz[u] = Math.max(sz[u], dfs3(g, v));
        }
        sz[u]++;
        return sz[u];
    }

    static class Graph {
        int[] nodes;
        int[] next;
        int[] to;
        int cur;

        public Graph(int nodes, int edges) {
            this.nodes = new int[nodes];
            this.next = new int[edges + 10];
            this.to = new int[edges + 10];
            this.cur = 0;
        }

        public void addEdge(int u, int v) {
            this.cur++;
            this.next[this.cur] = this.nodes[u];
            this.nodes[u] = this.cur;
            this.to[this.cur] = v;
        }

        public void reset(int n) {
            for (int i = 0; i < n; i++) {
                this.nodes[i] = 0;
            }
            this.cur = 0;
        }

        public Graph getTranspose(int n) {
            rg.reset(n);
            for (int u = 0; u < n; u++) {
                for (int i = this.nodes[u]; i > 0; i = this.next[i]) {
                    rg.addEdge(this.to[i], u);
                }
            }
            return rg;
        }
    }

}
