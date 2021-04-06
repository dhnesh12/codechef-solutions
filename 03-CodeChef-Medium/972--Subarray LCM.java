/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class Main {
    private static final int N = (int) 1e6 + 6;
    private static int[] p = new int[N];

    public static void main(String args[]) {
        FastReader sc = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        pre();
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc, out);
        }
        out.close();
    }

    private static void pre() {
        for (int i = 2; i < N; i++) {
            if (p[i] == 0) {
                p[i] = i;
                for (int j = 2 * i; j < N; j += i) {
                    p[j] = i;
                }
            }
        }
    }

    private static void solve(FastReader sc, PrintWriter out) {
        int n = sc.nextInt();
        int[] a = new int[N];
        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
        }
//        int[] dp = new int[N];
        int[] last = new int[N];
//        Arrays.fill(dp, 0);
        Arrays.fill(last, 0);
        int dp = 1;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x = a[i], fac = 0;
            while (x > 1) {
                int j = p[x];
                fac = Math.max(fac, last[j]);
                last[j] = i;
                while (x % j == 0) {
                    x /= j;
                }
            }
            if (i > 1) {
                dp = Math.min(dp + 1, i - fac);
            }
            ans = Math.max(ans, dp);
        }
        out.println(ans > 1 ? ans : "-1");
    }


    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        FastReader() {
            br = new BufferedReader(new
                    InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements())
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
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
}
