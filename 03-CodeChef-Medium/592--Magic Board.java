
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
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
        FastReader reader = new FastReader();
        int tc = reader.nextInt();
        StringBuilder buf = new StringBuilder();
        while (tc-- > 0) {
            int n = reader.nextInt();
            int m = reader.nextInt();
            String[] grid = new String[n];
            for (int i = 0; i < n; i++) {
                grid[i] = reader.next();
            }
            int res = solve(n, m, grid);
            buf.append(res);
            buf.append('\n');
        }
        System.out.print(buf.toString());
    }

    public static int solve(int n, int m, String[] grid) {
        Arrays.fill(vis, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i].charAt(j) > '0') {
                    dfs(grid, n, m, i, j, grid[i].charAt(j) - '0');
                }
            }
        }
        for (int i = 1; i < MAX; i++) {
            if (!vis[i]) {
                return i;
            }
        }
        return MAX;
    }

    private static final int MAX = 1000001;
    private static final int[] dd = {-1, 0, 1, 0, -1};

    private static final boolean[] vis = new boolean[MAX];

    private static void dfs(String[] grid, int n, int m, int i, int j, int num) {
        if (num >= MAX) {
            return;
        }
        vis[num] = true;

        for (int k = 0; k < 4; k++) {
            int ii = i + dd[k];
            int jj = j + dd[k + 1];
            if (ii >= 0 && ii < n && jj >= 0 && jj < m) {
                int next = num * 10 + grid[ii].charAt(jj) - '0';
                dfs(grid, n, m, ii, jj, next);
            }
        }
    }

}
