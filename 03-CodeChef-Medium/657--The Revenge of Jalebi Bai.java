

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
    }

    public static void main(String[] args) {
        FastReader fastReader = new FastReader();
        int tc = fastReader.nextInt();
        while (tc-- > 0) {
            int n = fastReader.nextInt();
            String[] S = new String[n];
            for (int i = 0; i < n; i++) {
                S[i] = fastReader.next();
            }
            String res = solve(S);
            System.out.println(res);
        }
    }

    private static final String solve(String[] S) {
        byte[] buf = new byte[17];
        for (int l = 1; l <= 16; l++) {
            for (int x = 0; x < 1 << l; x++) {
                decode(buf, l, x);
                if (check(buf, l, S)) {
                    return new String(buf, 0, l);
                }
            }
        }
        return "";
    }

    private static final void decode(byte[] buf, int l, int num) {
        while (num > 0) {
            int x = num & 1;
            if (x == 0) {
                buf[l - 1] = 'B';
            } else {
                buf[l - 1] = 'G';
            }
            l--;
            num >>= 1;
        }
        while (l > 0) {
            buf[l - 1] = 'B';
            l--;
        }
    }

    private static final boolean check(byte[] buf, int l, String[] S) {
        for (String s : S) {
            if (!check(buf, l, s)) {
                return false;
            }
        }
        return true;
    }

    private static final boolean check(byte[] buf, int l, String s) {
        int i = 0;
        int j = 0;
        while (i < l && j < s.length()) {
            if (buf[i] == s.charAt(j)) {
                j++;
            }
            i++;
        }

        return j == s.length();
    }
}
