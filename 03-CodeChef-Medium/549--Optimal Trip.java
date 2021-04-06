
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
        while (tc-- > 0) {
            int n = reader.nextInt();
            int D = reader.nextInt();
            int[] d = new int[n];
            int[] c = new int[n];
            for (int i = 0; i < n; i++) {
                d[i] = reader.nextInt();
                c[i] = reader.nextInt();
            }
            int[] res = solve(D, d, c);
            System.out.printf("%d %d\n", res[0], res[1]);
        }
    }


    private static final int N = 100010;

    private static int[] dp = new int[N];
    private static int[] que = new int[N];
    private static long[] P = new long[N];

    private static int[] solve(int D, int[] d, int[] c) {
        int n = d.length;
        c[n - 1] = 0;

        for (int i = 1; i <= n; i++) {
            P[i] = P[i - 1] + d[i - 1];
        }
        int L = find(N + 1, D, d, c);

        int left = 0;
        int right = N;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (find(mid, D, d, c) == L) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return new int[] {L, right};
    }

    private static int find(int L, int D, int[] d, int[] c) {
        int n = d.length;
        dp[n] = N;
        int front = 0;
        int end = 0;
        que[end++] = 0;

        for (int i = 1; i <= n; i++) {
            if (c[i - 1] > L) {
                continue;
            }
            while (front < end && P[que[front]] + D < P[i]) {
                front++;
            }
            if (front == end) {
                return N;
            }
            dp[i] = dp[que[front]] + 1;
            que[end++] = i;
        }
        return dp[n];
    }
}
