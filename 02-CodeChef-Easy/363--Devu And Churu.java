
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;
import java.awt.Point;
import java.math.BigInteger;

 class Newbie {

    static InputReader sc = new InputReader(System.in);
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        solver s = new solver();
        int t = 1;
        while (t > 0) {
            //out.println("case : "+t);
            s.sol();
            t--;
        }
        out.close();
    }
           /* static class descend implements Comparator<pair1> {
                public int compare(pair1 o1, pair1 o2) {
                    if (o1.pop != o2.pop)
                        return (int) (o1.pop - o2.pop);
                    else
                        return o1.in - o2.in;
                }
            }*/

    static class InputReader {
        public BufferedReader br;
        public StringTokenizer token;

        public InputReader(InputStream stream) {
            br = new BufferedReader(new InputStreamReader(stream), 32768);
            token = null;
        }

        public String sn() {
            while (token == null || !token.hasMoreTokens()) {
                try {
                    token = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return token.nextToken();
        }

        public int ni() {
            return Integer.parseInt(sn());
        }

        public String snl() throws IOException {
            return br.readLine();
        }

        public long nlo() {
            return Long.parseLong(sn());
        }

        public double nd() {
            return Double.parseDouble(sn());
        }

        public int[] na(int n) {
            int a[] = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = sc.ni();
            return a;
        }

        public long[] nal(int n) {
            long a[] = new long[n];
            for (int i = 0; i < n; i++)
                a[i] = sc.nlo();
            return a;
        }
    }

    static class extra {

        static boolean v[] = new boolean[100001];
        static List<Integer> l = new ArrayList<>();
        static int t;

        static void shuffle(int a[]) {
            for (int i = 0; i < a.length; i++) {
                int t = (int) Math.random() * a.length;
                int x = a[t];
                a[t] = a[i];
                a[i] = x;
            }
        }

        static void shufflel(long a[]) {
            for (int i = 0; i < a.length; i++) {
                int t = (int) Math.random() * a.length;
                long x = a[t];
                a[t] = a[i];
                a[i] = x;
            }
        }

        static int gcd(int a, int b) {
            if (b == 0)
                return a;
            else
                return gcd(b, a % b);
        }

        static boolean valid(int i, int j, int r, int c) {
            if (i >= 0 && i < r && j >= 0 && j < c) {
                // System.out.println(i+" /// "+j);
                return true;
            } else {
                //  System.out.println(i+" //f "+j);
                return false;
            }
        }

        static void seive() {
            for (int i = 2; i < 101; i++) {
                if (!v[i]) {
                    t++;
                    l.add(i);
                    for (int j = 2 * i; j < 101; j += i)
                        v[j] = true;
                }
            }
        }

        static long fastexpo(long x, long y) {
            long res = 1;
            while (y > 0) {
                if ((y & 1) == 1) {
                    res *= x;
                }
                y = y >> 1;
                x = x * x;
            }
            return res;
        }

        static long lfastexpo(long x, long y, long p) {
            long res = 1;
            x = x % p;
            while (y > 0) {
                if ((y & 1) == 1) {
                    res = (res * x) % p;
                }
                y = y >> 1;
                x = (x * x) % p;
            }
            return res;
        }
    }

    static int inf = 5000013;

    static class solver {
        DecimalFormat df = new DecimalFormat("0.00000000");
        extra e = new extra();
        long mod = (long) (1000000007);

        private int find(int n) {
            if (n < ar[0])
                return -1;

            if (n >= ar[ar.length - 1])
                return ar.length - 1;

            int start = 0, end = ar.length - 1, mid = (start + end) >>> 1;
            while (start != mid) {
                if (ar[mid] == n)
                    return mid;

                if (ar[mid] > n)
                    end = mid;
                else
                    start = mid;

                mid = (start + end) >>> 1;
            }
            return start;
        }

        long ar[];

        void sol() throws IOException {
            int n = sc.ni();
            int m = sc.ni();
            long a[] = sc.nal(n);
            TreeMap<Long, Long> map = new TreeMap<>();
            long max = -1;
            for (int i = 0; i < n; i++) {
                max = Math.max(max, a[i]);
                int r = i + 1;
                int l = i - 1;
                while (l >= 0 && a[l] < a[i]) {
                    l--;
                }
                while (r < n && a[r] <= a[i]) {
                    r++;
                }
                l += 1;
                r -= 1;
                long d = r - l + 1;
                long total = (d * (d + 1)) / 2;
//                System.out.println(i+" "+d+" "+r+" "+l+" "+total);
                long d1 = i - l;
                long d2 = r - i;
                total = total - ((d1 * (d1 + 1)) / 2) - ((d2 * (d2 + 1)) / 2);
                map.put(a[i], map.getOrDefault(a[i], 0l) + total);
            }
//            System.out.println(map);
            ar = new long[map.size()];
            int p = 0;
            for (long h : map.keySet())
                ar[p++] = h;
            StringBuilder ans = new StringBuilder();
            long sums[] = new long[p];
            sums[0] = map.get(ar[0]);
            for (int i = 1; i < p; i++)
                sums[i] = sums[i - 1] + map.get(ar[i]);
            char xor = ('D' ^ 'C');
            for (int i = 0; i < m; ++i) {
                String qtype = sc.sn();
                int num = sc.ni();
                String player = sc.sn();
                int index = 0;
                long count = 0;
                if (qtype.charAt(0) == '=') {
                    index = find(num);
                    if (index != -1 && ar[index] == num) {
                        count = sums[index];
                        if (index > 0)
                            count -= sums[index - 1];
                    }
                } else if (qtype.charAt(0) == '<') {
                    index = find(num - 1);
                    if (index != -1)
                        count = sums[index];
                } else {
                    index = find(num);
                    if (index != -1)
                        count = sums[ar.length - 1] - sums[index];
                    else
                        count = sums[ar.length - 1];
                }
                if ((count & 1) == 1)
                    ans.append(player.charAt(0));
                else
                    ans.append((char) (xor ^ player.charAt(0)));
            }
//            while (m-- > 0) {
//                String s[] = sc.snl().split(" ");
//                long t = Long.parseLong(s[1]);
//                if (s[0].equals(">")) {
//                    Long k = set.higher(t);
//                    if (k == null) {
//                        if (s[2].equals("D"))
//                            ans.append("C");
//                        else
//                            ans.append("D");
//                    } else {
//                        long val = pre.get(max);
//                        val -= pre.getOrDefault(t, 0l);
//                        if (val % 2 == 0) {
//                            if (s[2].equals("D"))
//                                ans.append("C");
//                            else
//                                ans.append("D");
//                        } else
//                            ans.append(s[2]);
//                    }
//                } else if (s[0].equals("<")) {
//                    Long k = set.lower(t);
//                    if (k == null) {
//                        if (s[2].equals("D"))
//                            ans.append("C");
//                        else
//                            ans.append("D");
//                    } else {
//                        long val = pre.get(k);
//                        if (val % 2 == 0) {
//                            if (s[2].equals("D"))
//                                ans.append("C");
//                            else
//                                ans.append("D");
//                        } else
//                            ans.append(s[2]);
//                    }
//                } else {
//                    long val = map.getOrDefault(t, Long.MAX_VALUE);
//                    if (val == Long.MAX_VALUE) {
//                        if (s[2].equals("D"))
//                            ans.append("C");
//                        else
//                            ans.append("D");
//                    } else {
//                        if (val % 2 == 0) {
//                            if (s[2].equals("D"))
//                                ans.append("C");
//                            else
//                                ans.append("D");
//                        } else
//                            ans.append(s[2]);
//                    }
//                }
//            }
            System.out.println(ans);
        }
    }
}

