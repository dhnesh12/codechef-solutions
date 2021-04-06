
import java.io.*;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    //SOLUTION BEGIN
    int B = 18;

    void solve(int TC) throws Exception {
        int n = ni();
        g = new int[n][];
        int[][] edge = new int[n - 1][];
        int[] cnt = new int[n];
        for (int i = 0; i < n - 1; i++) {
            edge[i] = new int[] {ni() - 1, ni() - 1};
            cnt[edge[i][0]]++;
            cnt[edge[i][1]]++;
        }
        for (int i = 0; i < n; i++)
            g[i] = new int[cnt[i]];
        for (int i = 0; i < n - 1; i++) {
            g[edge[i][0]][--cnt[edge[i][0]]] = edge[i][1];
            g[edge[i][1]][--cnt[edge[i][1]]] = edge[i][0];
        }
        sub = new int[n];
        de = new int[n];
        par = new int[B][n];
        for (int b = 0; b < B; b++)
            for (int i = 0; i < n; i++)
                par[b][i] = -1;
        dfs1(g, par, sub, de, 0, -1);
        for (int b = 1; b < B; b++)
            for (int i = 0; i < n; i++)
                if (par[b - 1][i] != -1)
                    par[b][i] = par[b - 1][par[b - 1][i]];
        chainHead = new int[n];
        chainInd = new int[n];
        treePos = new int[n];
        chainPos = new int[n];
        hc = new int[n];
        Arrays.fill(chainHead, -1);
        Arrays.fill(hc, -1);
        hld(0);
        m = 1;
        while (m < n)
            m <<= 1;
        t = new int[m << 1];
        lazy = new boolean[m << 1];
        for (int q = ni(); q > 0; q--) {
            int a = ni() - 1, b = ni() - 1;
            int lca = lca(a, b);
            updateUp(a, lca);
            updateUp(b, lca);
            pni(query(1, 0, m - 1, 0, m - 1));
        }
    }

    void update(int l, int r, int ll, int rr, int i) {
        if (lazy[i]) {
            t[i] = rr - ll + 1 - t[i];
            if (ll != rr) {
                lazy[i << 1] = !lazy[i << 1];
                lazy[i << 1 | 1] = !lazy[i << 1 | 1];
            }
            lazy[i] = false;
        }
        if (ll > rr || ll > r || rr < l)
            return;
        if (ll >= l && rr <= r) {
            t[i] = rr - ll + 1 - t[i];
            if (ll != rr) {
                lazy[i << 1] = !lazy[i << 1];
                lazy[i << 1 | 1] = !lazy[i << 1 | 1];
            }
            return;
        }
        int mid = (ll + rr) >> 1;
        update(l, r, ll, mid, i << 1);
        update(l, r, mid + 1, rr, i << 1 | 1);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }

    int query(int i, int start, int end, int l, int r) {
        if (lazy[i]) {
            t[i] = end - start + 1 - t[i];
            if (start != end) {
                lazy[i << 1] = !lazy[i << 1];
                lazy[i << 1 | 1] = !lazy[i << 1 | 1];
            }
            lazy[i] = false;
        }
        if (start > end || start > r || l > end)
            return 0;
        if (start >= l && end <= r)
            return t[i];
        int mid = (start + end) >> 1;
        return query(i << 1, start, mid, l, r) + query(i << 1 | 1, mid + 1, end, l, r);
    }

    int[][] g;
    int[] sub, de, par[];
    int[] t;
    boolean[] lazy;
    int m = 1;
    int chainNo = 0, pos = 0, chainHead[], chainInd[], treePos[], chainPos[], hc[];

    void hld(int u) {
        if (chainHead[chainNo] == -1)
            chainHead[chainNo] = u;
        chainInd[u] = chainNo;
        treePos[u] = pos++;
        int ch = -1;
        for (int v : g[u]) {
            if (v == par[0][u])
                continue;
            if (ch == -1 || sub[ch] < sub[v])
                ch = v;
        }
        if (ch >= 0) {
            hc[u] = ch;
            hld(ch);
        }
        for (int v : g[u]) {
            if (v == par[0][u] || v == ch)
                continue;
            chainNo++;
            hld(v);
        }
    }

    void updateUp(int a, int lca) {
        while (chainInd[a] != chainInd[lca]) {
            update(treePos[chainHead[chainInd[a]]], treePos[a], 0, m - 1, 1);
            a = par[0][chainHead[chainInd[a]]];
        }
        if (a != lca)
            update(treePos[hc[lca]], treePos[a], 0, m - 1, 1);
    }

    int lca(int u, int v) {
        if (de[u] > de[v]) {
            int tmp = v;
            v = u;
            u = tmp;
        }
        int d = de[v] - de[u];
        for (int b = B - 1; b >= 0; b--)
            if (((d >> b) & 1) == 1)
                v = par[b][v];
        if (u == v)
            return u;
        for (int b = B - 1; b >= 0; b--)
            if (par[b][u] != par[b][v]) {
                u = par[b][u];
                v = par[b][v];
            }
        return par[0][u];
    }

    void dfs1(int[][] g, int[][] par, int[] sub, int[] de, int u, int p) {
        sub[u] = 1;
        for (int v : g[u]) {
            if (v == p)
                continue;
            de[v] = de[u] + 1;
            par[0][v] = u;
            dfs1(g, par, sub, de, v, u);
            sub[u] += sub[v];
        }
    }

    //SOLUTION END
    long mod = (long) 1e9 + 7, IINF = (long) 5e18;
    final int INF = (int) 2e9;
    DecimalFormat df = new DecimalFormat("0.000000000");
    double PI = 3.1415926535897932384626433832792884197169399375105820974944, eps = 1e-8;
    static boolean multipleTC = false, memory = false;
    FastReader in;
    PrintWriter out;

    void run() throws Exception {
        in = new FastReader();
        out = new PrintWriter(System.out);
        int T = (multipleTC) ? ni() : 1;
        //Solution Credits: Taranpreet Singh
        for (int i = 1; i <= T; i++)
            solve(i);
        out.flush();
        out.close();
    }

    public static void main(String[] args) throws Exception {
        if (memory)
            new Thread(null, new Runnable() {
                public void run() {
                    try {
                        new Main().run();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }, "1", 1 << 28).start();
        else
            new Main().run();
    }

    long gcd(long a, long b) {
        return (b == 0) ? a : gcd(b, a % b);
    }

    int gcd(int a, int b) {
        return (b == 0) ? a : gcd(b, a % b);
    }

    int bit(long n) {
        return (n == 0) ? 0 : (1 + bit(n & (n - 1)));
    }

    void p(Object o) {
        out.print(o);
    }

    void pn(Object o) {
        out.println(o);
    }

    void pni(Object o) {
        out.println(o);
        out.flush();
    }

    String n() {
        return in.next();
    }

    String nln() {
        return in.nextLine();
    }

    int ni() {
        return Integer.parseInt(in.next());
    }

    long nl() {
        return Long.parseLong(in.next());
    }

    double nd() {
        return Double.parseDouble(in.next());
    }


    class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }


        public FastReader(String s) throws Exception {
            br = new BufferedReader(new FileReader(s));
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
}
