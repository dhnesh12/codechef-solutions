import java.io.*;
import java.util.*;
public class Main
{
    static final int[] primes = getPrimes((int) 1e6 + 1);
    private static int[] getPrimes(int max)
    {
        boolean[] notPrime = new boolean[max];
        for (int i = 2; i * i < max; i++)
        {
            if (!notPrime[i])
            {
                for (int j = i * i; j < max; j += i)
                {
                    notPrime[j] = true;
                }
            }
        }
        int cnt = 0;
        for (int i = 2; i < max; i++)
        {
            if (!notPrime[i])
            cnt++;
        }
        int[] res = new int[cnt];
        cnt = 0;
        for (int i = 2; i < max; i++)
        {
            if (!notPrime[i])
            res[cnt++] = i;
        }
        return res;
    }
    private static void solve() throws IOException
    {
        int tc = nextInt();
        while (tc-- > 0)
        {
            long p = nextLong();
            if (p < 5)
            {
                out.println(getStupid((int) p));
            }
            else
            {
                out.println(get(p));
            }
        }
    }
    static int get(long p)
    {
        long res = ((p - 1) % MOD) * ((p - 1) % MOD) % MOD;
        long n = p - 1;
        res += get2(n);
        return (int) (res % MOD);
    }
    final static int MOD = 1000000007;
    static long n;
    static Factor[] factors;
    static int[] pows;
    static long res;
    static HashMap<Long, Long> fatratmap = new HashMap<Long, Long>();
    static HashMap<Long, Long> fatratsums = new HashMap<Long, Long>();
    static void go(int i, long d)
    {
    if (i == factors.length)
    {
        work(d);
        return;
    }
    pows[i] = 0;
    go(i + 1, d);
    Factor f = factors[i];
    for (int j = 0; j < f.pow; j++)
    {
        pows[i]++;
        d *= f.p;
        go(i + 1, d);
    }
}
private static void work(long d)
{
    long phi = n / d;
    long fatratsum = 0;
    int nonzero = -1;
    for (int i = 0; i < factors.length; i++)
    {
    if (pows[i] > 0 && nonzero == -1)
    {
        nonzero = i;
        fatratsum += fatratsums.get(d / factors[i].p);
    }
    if (factors[i].pow > pows[i])
    phi -= phi / factors[i].p;
    }
    long cur = phi * d;
    if (nonzero != -1)
    {
        long p = factors[nonzero].p;
        long d1 = d;
        for (int i = 0; i < pows[nonzero]; i++)
        {
            d1 /= p;
        }
        long get = fatratsums.get(d1);
        if (pows[nonzero] == factors[nonzero].pow)
        {
            fatratsum += get / (p - 1) * p;
        }
        else
        {
            fatratsum += get;
        }
    }
    else
    {
        fatratsum += cur;
    }
    fatratmap.put(d, cur);
    fatratsums.put(d, fatratsum);
    fatratsum %= MOD;
    phi %= MOD;
    res += (fatratsum * fatratsum % MOD) * phi % MOD;
    res %= MOD;
}
static int get2(long n)
{
    Main.n = n;
    fatratmap.clear();
    fatratsums.clear();
    factors = factorize(n);
    pows = new int[factors.length];
    res = 0;
    go(0, 1);
    res %= MOD;
    return (int) res;
}
static class Factor
{
    @Override
    public String toString()
    {
        return "Factor [p=" + p + ", pow=" + pow + "]";
    }
    long p;
    int pow;
    public Factor(long p, int pow)
    {
        this.p = p;
        this.pow = pow;
    }
}
static Factor[] factorize(long n)
{
    ArrayList<Factor> res = new ArrayList<Factor>();
    for (int i : primes)
    {
        if ((long) i * i > n)
        break;
        if (n % i == 0)
        {
            int cnt = 1;
            n /= i;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            res.add(new Factor(i, cnt));
        }
    }
    if (n > 1)
    res.add(new Factor(n, 1));
    return (Factor[]) res.toArray(new Factor[res.size()]);
    }
    static int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    static int getStupid(int p)
    {
        int res = 0;
        for (int n = 1; n <= p * (p - 1); n++)
        {
            for (int m = 1; m <= p * (p - 1); m++)
            {
                if (modPow(m, n, p) == modPow(n, m, p))
                {
                    res++;
                }
            }
        }
        return res;
    }
    static int modPow(int a, int pow, int mod)
    {
        int res = 1;
        while (pow > 0)
        {
            if ((pow & 1) != 0)
            {
                res = (int) ((long) res * a % mod);
            }
            a = (int) ((long) a * a % mod);
            pow >>= 1;
        }
        return res;
    }
    public static void main(String[] args)
    {
        try
        {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            solve();
            out.close();
        }
        catch (Throwable e)
        {
            e.printStackTrace();
            System.exit(239);
        }
    }
    static BufferedReader br;
    static StringTokenizer st;
    static PrintWriter out;
    static boolean eof = false;
    static String nextToken() throws IOException
    {
        while (!st.hasMoreTokens())
        {
            String line = br.readLine();
            if (line == null)
            {
                eof = true;
                line = "0";
            }
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }
    static int nextInt() throws IOException
    {
        return Integer.parseInt(nextToken());
    }
    static long nextLong() throws IOException
    {
        return Long.parseLong(nextToken());
    }
    static double nextDouble() throws IOException
    {
        return Double.parseDouble(nextToken());
    }
}