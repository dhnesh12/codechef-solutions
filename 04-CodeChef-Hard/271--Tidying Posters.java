/**
 * Created by Aminul on 10/31/2018.
 */

import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class Main {
    public static void main(String[] args)throws Exception {
        FastReader in = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);
        int test = in.nextInt();
        for(int t = 1; t <= test; t++) {
            int n = in.nextInt();
            Kuhn kuhn = new Kuhn(n, n);
            Node node[] = new Node[n];
            for (int i = 0; i < n; i++) {
                node[i] = new Node(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
            }
            Arrays.sort(node);
            for (int i = 0; i < n; i++) {
                for(int j = 0; j < i; j++) {
                    if(intersect(node[i], node[j])) {
                        kuhn.addEdge(j, i);
                    }
                }
            }
            pw.println(n- kuhn.maxMatching());
        }

        pw.close();
    }

    static boolean intersect(Node r1, Node r2) {
        return max(r1.x1, r2.x1) <= min(r1.x2, r2.x2) &&
                max(r1.y1, r2.y1) <= min(r1.y2, r2.y2);
    }

    static class Node implements Comparable<Node>{
        long x1, x2, y1, y2;
        Node(int X1, int X2, int Y1, int Y2) {
            x1 = X1;
            x2 = X2;
            y1 = Y1;
            y2 = Y2;
        }

        @Override
        public int compareTo(Node other) {
             return Long.compare( (x2 - x1) , (other.x2 - other.x1));
        }

        @Override
        public String toString() {
            return x1+" "+x2+" "+y1+" "+y2;
        }
    }

    static class Kuhn {
        int left[], right[], vis[], cc = 1;
        List<Integer> g[];
        int n, m;
        Kuhn(int N, int M){
            n = N; m = M;
            left = new int[n + 1];
            right = new int[m + 1];
            vis = new int[n + m + 10];
            Arrays.fill(left, -1);
            Arrays.fill(right, -1);
            g = new List[n];
            for(int i = 0; i < n; i++) g[i] = new ArrayList<>();
        }

        void addEdge(int u, int v){
            g[u].add(v);
        }

        int maxMatching() { //0-based indexed
            boolean done;
            int res = 0;
            do {
                done = true;
                cc++;
                for (int i = 0; i < n; i++) {
                    if (left[i] == -1 && tryK(i)) {
                        done = false;
                    }
                }
            } while (!done);
            for (int i = 0; i < n; i++) {
                res += (left[i] != -1) ? 1 : 0;
            }
            return res;
        }

        boolean tryK(int v) {
            if (vis[v] == cc) return false;
            vis[v] = cc;
            for (int t : g[v]) {
                if (right[t] == -1) {
                    right[t] = v;
                    left[v] = t;
                    return true;
                }
            }
            for (int t : g[v]) {
                if (tryK(right[t])) {
                    right[t] = v;
                    left[v] = t;
                    return true;
                }
            }
            return false;
        }
    }

    static void debug(Object...obj) {
        System.err.println(Arrays.deepToString(obj));
    }

    static class FastReader {
        InputStream is;
        private byte[] inbuf = new byte[1024];
        private int lenbuf = 0, ptrbuf = 0;

        public FastReader(InputStream is) {
            this.is = is;
        }

        public int readByte() {
            if (lenbuf == -1) throw new InputMismatchException();
            if (ptrbuf >= lenbuf) {
                ptrbuf = 0;
                try {
                    lenbuf = is.read(inbuf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (lenbuf <= 0) return -1;
            }
            return inbuf[ptrbuf++];
        }

        public boolean isSpaceChar(int c) {
            return !(c >= 33 && c <= 126);
        }
        private boolean isEndOfLine(int c) {
            return c == '\n' || c == '\r' || c == -1;
        }

        public int skip() {
            int b;
            while ((b = readByte()) != -1 && isSpaceChar(b)) ;
            return b;
        }

        public String next() {
            int b = skip();
            StringBuilder sb = new StringBuilder();
            while (!(isSpaceChar(b))) {
                sb.appendCodePoint(b);
                b = readByte();
            }
            return sb.toString();
        }



        public String nextLine() {
            int c = skip();
            StringBuilder sb = new StringBuilder();
            while (!isEndOfLine(c)){
                sb.appendCodePoint(c);
                c = readByte();
            }
            return sb.toString();
        }

        public int nextInt() {
            int num = 0, b;
            boolean minus = false;
            while ((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-')) ;
            if (b == '-') {
                minus = true;
                b = readByte();
            }
            while (true) {
                if (b >= '0' && b <= '9') {
                    num = (num << 3) + (num << 1) + (b - '0');
                } else {
                    return minus ? -num : num;
                }
                b = readByte();
            }
        }

        public long nextLong() {
            long num = 0;
            int b;
            boolean minus = false;
            while ((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-')) ;
            if (b == '-') {
                minus = true;
                b = readByte();
            }

            while (true) {
                if (b >= '0' && b <= '9') {
                    num = (num << 3) + (num << 1) + (b - '0');
                } else {
                    return minus ? -num : num;
                }
                b = readByte();
            }
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public char[] next(int n) {
            char[] buf = new char[n];
            int b = skip(), p = 0;
            while (p < n && !(isSpaceChar(b))) {
                buf[p++] = (char) b;
                b = readByte();
            }
            return n == p ? buf : Arrays.copyOf(buf, p);
        }

        public char readChar() {
            return (char) skip();
        }
    }
}