import java.math.*;
import java.util.*;
import java.io.*;

class Solver {
    public static BigDecimal Invalid = new BigDecimal(-1);
    public static BigDecimal Precision = new BigDecimal(1e-30);
    public static BigDecimal Check = new BigDecimal(1e-20);
    private BigDecimal X;
    private BigDecimal Y;
    private BigDecimal XY;
    private BigDecimal diff;
    private BigDecimal ans;

    public Solver(long x, long y) {
        X = new BigDecimal(x);
        Y = new BigDecimal(y);
        XY = new BigDecimal(x * y);
        diff = new BigDecimal(-1);
    }

    BigDecimal get(BigDecimal sx, BigDecimal ex, BigDecimal sy, BigDecimal ey) {
        BigDecimal x1 = sy.divide(Y, 50, BigDecimal.ROUND_CEILING);
        BigDecimal y1 = ey.divide(Y, 50, BigDecimal.ROUND_CEILING);
        long t1 = sx.longValue();
        BigDecimal b1 = new BigDecimal(t1);
        x1 = x1.add(b1);
        y1 = y1.add(b1);
        if (sx.compareTo(x1) < 0)
            sx = x1;
        if (ex.compareTo(y1) > 0)
            ex = y1;
        if (sx.compareTo(ex) > 0)
            return Solver.Invalid;
        BigDecimal ab = ex.subtract(sx);
        if (ab.compareTo(Solver.Precision) < 0)
            return sx;
        return get(sy, ey, sx, ex);
    }

    BigDecimal swap(BigDecimal x) {
        BigDecimal minutes = x.multiply(X);
        long t = x.longValue();
        BigDecimal fraction = x.subtract(new BigDecimal(t));
        fraction = fraction.multiply(XY);
        t = fraction.longValue();
        long division = X.longValue();
        t /= division;
        BigDecimal ans = new BigDecimal(t);
        ans = ans.add(minutes.divide(XY, 50, BigDecimal.ROUND_CEILING));
        return ans;
    }

    BigDecimal getMinutes(BigDecimal x) {
        long t = x.longValue();
        BigDecimal fraction = x.subtract(new BigDecimal(t));
        fraction = fraction.multiply(XY);
        return fraction;
    }

    void doit(BigDecimal a) {
        if (a.compareTo(Solver.Invalid) == 0)
            return;
        BigDecimal x = swap(swap(a));
        x = x.subtract(a);
        if (x.abs().compareTo(Solver.Check) > 0)
            return;
        BigDecimal b = swap(a);
        if (a.compareTo(b) > 0) {
            BigDecimal c = a;
            a = b;
            b = c;
        }
        BigDecimal sub = b.subtract(a);
        if (sub.compareTo(diff) > 0) {
            diff = sub;
            ans = a;
        }
    }

    public void solve(long a, long b, long c, long d, long e, long f, long g, long h) {
        if (b != 0 || a == c) {
            BigDecimal sx = new BigDecimal(b);
            sx = sx.divide(XY, 50, BigDecimal.ROUND_CEILING);
            sx = sx.add(new BigDecimal(a));
            BigDecimal ex;
            if (a == c) {
                ex = new BigDecimal(d);
                ex = ex.divide(XY, 50, BigDecimal.ROUND_CEILING);
                ex = ex.add(new BigDecimal(c));
            } else {
                ex = new BigDecimal(a + 1);
            }
// Handle 2 cases
            if (h != 0 || e == g) {
                BigDecimal ey = new BigDecimal(h);
                ey = ey.divide(XY, 50, BigDecimal.ROUND_CEILING);
                ey = ey.add(new BigDecimal(g));
                BigDecimal sy;
                if (e == g) {
                    sy = new BigDecimal(f);
                    sy = sy.divide(XY, 50, BigDecimal.ROUND_CEILING);
                    sy = sy.add(new BigDecimal(e));
                } else {
                    sy = new BigDecimal(g);
                }
                BigDecimal bd = get(sx, ex, sy, ey);
                doit(bd);
            }
            if (g > e) {
                BigDecimal sy, ey;
                ey = new BigDecimal(g);
                if (g == e + 1) {
                    sy = new BigDecimal(f);
                    sy = sy.divide(XY, 50, BigDecimal.ROUND_CEILING);
                    sy = sy.add(new BigDecimal(g - 1));
                } else
                    sy = new BigDecimal(g - 1);
                BigDecimal bd = get(sx, ex, sy, ey);
                doit(bd);
            }
        }
        if (c > a) {
            BigDecimal sx, ex;
            if (b != 0) {
                sx = new BigDecimal(a + 1);
                if (c == a + 1) {
                    ex = new BigDecimal(d);
                    ex = ex.divide(XY, 50, BigDecimal.ROUND_CEILING);
                    ex = ex.add(sx);
                } else
                    ex = new BigDecimal(a + 2);
            } else {
                sx = new BigDecimal(a);
                ex = new BigDecimal(a + 1);
            }
// Handle 2 cases
            if (h != 0 || e == g) {
                BigDecimal ey = new BigDecimal(h);
                ey = ey.divide(XY, 50, BigDecimal.ROUND_CEILING);
                ey = ey.add(new BigDecimal(g));
                BigDecimal sy;
                if (e == g) {
                    sy = new BigDecimal(f);
                    sy = sy.divide(XY, 50, BigDecimal.ROUND_CEILING);
                    sy = sy.add(new BigDecimal(e));
                } else {
                    sy = new BigDecimal(g);
                }
                BigDecimal bd = get(sx, ex, sy, ey);
                doit(bd);
            }
            if (g > e) {
                BigDecimal sy, ey;
                ey = new BigDecimal(g);
                if (g == e + 1) {
                    sy = new BigDecimal(f);
                    sy = sy.divide(XY, 50, BigDecimal.ROUND_CEILING);
                    sy = sy.add(new BigDecimal(g - 1));
                } else
                    sy = new BigDecimal(g - 1);
                BigDecimal bd = get(sx, ex, sy, ey);
                doit(bd);
            }
        }
        if (diff.compareTo(Solver.Invalid) == 0)
            System.out.println("-1");
        else {
            BigDecimal min = getMinutes(ans);
            min = min.divide(new BigDecimal(1), 2, BigDecimal.ROUND_HALF_UP);
            System.out.println(ans.longValue() + ":" + min);
        }
    }
}

class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str = br.readLine();
        int t = Integer.parseInt(str);
        double xx = 2222222222222222.22F;
        long[] in = new long[8];
        while (t > 0) {
            str = br.readLine();
            String[] s = str.split(" ");
            int x = Integer.parseInt(s[0]);
            int y = Integer.parseInt(s[1]);
            str = br.readLine();
            s = str.split(" ");
            for (int i = 0; i < 8; i++)
                in[i] = Long.parseLong(s[i]);
            Solver solver = new Solver(x, y);
            solver.solve(in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7]);
            t--;
        }
    }
}