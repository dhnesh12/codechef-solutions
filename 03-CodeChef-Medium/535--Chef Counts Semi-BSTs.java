import java.util.*;
import java.io.*;
import java.text.*;

class CC_MANCBST{
    //SOLUTION BEGIN
    long MOD = 663224321;
    int root = 3;
    void pre() throws Exception{}
    void solve(int TC) throws Exception{
        int N = 100000;
        long[] B = new long[1+N];
        for(int i = 1; i<= N; i++)B[i] = pow(i-1, i-2);
        B[0] = 1;
        for(int i = 1; i<= N; i++)
            if(B[i] != 0)
                B[i] = MOD-B[i];
        long[] A = inv(B, 1+N);
        for(int T = ni(); T>0; T--)pn(A[ni()]);
    }
    private long[] inv(long[] a, int target) throws Exception{
        int n = a.length;
        assert (n & (n - 1)) == 0;
        long r[] = new long[]{pow(a[0], MOD-2)};
        for(int len = 2; len <= 2*target; len *= 2) {
            long nr[] = new long[len];
            System.arraycopy(a, 0, nr, 0, Math.min(a.length, len));
            nr = convoluteSimply(nr, convoluteSimply(r, r, (int)MOD, root), (int)MOD, root);
            for(int i = 0; i < len; ++i) nr[i] = (MOD - nr[i]) % MOD;
            for(int i = 0; i < len / 2; ++i) nr[i] = (nr[i] + 2 * r[i]) % MOD;
            r = new long[len];
            System.arraycopy(nr, 0, r, 0, len);
        }
        return r;
    }
    long[] convoluteSimply(long[] a, long[] b, int P, int g){
        int m = Math.max(2, Integer.highestOneBit(Math.max(a.length, b.length)-1)<<2);
        long[] fa = nttmb(a, m, false, P, g);
        long[] fb = a == b ? fa : nttmb(b, m, false, P, g);
        for(int i = 0;i < m;i++)fa[i] = fa[i]*fb[i]%P;
        return nttmb(fa, m, true, P, g);
    }
    long[] nttmb(long[] src, int n, boolean inverse, int P, int g){
        long[] dst = Arrays.copyOf(src, n);
        int h = Integer.numberOfTrailingZeros(n);
        long K = Integer.highestOneBit(P)<<1;
        int H = Long.numberOfTrailingZeros(K)*2;
        long M = K*K/P;
        int[] wws = new int[1<<h-1];
        long dw = inverse ? pow(g, P-1-(P-1)/n, P) : pow(g, (P-1)/n, P);
        long w = (1L<<32)%P;
        for(int k = 0;k < 1<<h-1;k++, w = modh(w*dw, M, H, P))wws[k] = (int)w;
        long J = invl(P, 1L<<32);
        for(int i = 0;i < h;i++){
            for(int j = 0;j < 1<<i;j++){
                for(int k = 0, s = j<<h-i, t = s|1<<h-i-1;k < 1<<h-i-1;k++,s++,t++){
                    long u = (dst[s] - dst[t] + 2*P)*wws[k];
                    dst[s] += dst[t];
                    if(dst[s] >= 2*P)dst[s] -= 2*P;
                    long Q = (u<<32)*J>>>32;
                    dst[t] = (u>>>32)-(Q*P>>>32)+P;
                }
            }
            if(i < h-1)for(int k = 0;k < 1<<h-i-2;k++)wws[k] = wws[k*2];
        }
        for(int i = 0;i < n;i++)if(dst[i] >= P)dst[i] -= P;
        for(int i = 0;i < n;i++){
            int rev = Integer.reverse(i)>>>-h;
            if(i < rev){long d = dst[i]; dst[i] = dst[rev]; dst[rev] = d;}
        }
        long in = invl(n, P);
        if(inverse)for(int i = 0;i < n;i++)dst[i] = modh(dst[i]*in, M, H, P);
        return dst;
    }
    long invl(long a, long MOD) {
        long b = MOD;
        long p = 1, q = 0;
        while (b > 0) {
            long c = a / b, d = a;a = b;b = d % b;
            d = p;p = q;q = d - c * q;
        }
        return p < 0 ? p + MOD : p;
    }
    long MASK = (1L<<31)-1;
    long modh(long a, long M, int h, int MOD){
        long r = a-((M*(a&MASK)>>>31)+M*(a>>>31)>>>h-31)*MOD;
        return r < MOD ? r : r-MOD;
    }
    long pow(long a, long n, long MOD) {
        long ret = 1;
        int x = 63 - Long.numberOfLeadingZeros(n);
        for (; x >= 0; x--){
            ret = ret * ret % MOD;
            if (n << 63 - x < 0)ret = ret * a % MOD;
        }
        return ret;
    }
    long pow(long a, long p){
        long o = 1;
        for(; p>0; p>>=1){
            if((p&1)==1)o = o*a%MOD;
            a = a*a%MOD;
        }
        return o;
    }
    //SOLUTION END
    void hold(boolean b)throws Exception{if(!b)throw new Exception("Hold right there, Sparky!");}
    void exit(boolean b){if(!b)System.exit(0);}
    static void dbg(Object... o){System.err.println(Arrays.deepToString(o));}
    final long IINF = (long)1e17;
    final int INF = (int)1e9+2;
    DecimalFormat df = new DecimalFormat("0.00000000000");
    double PI = 3.141592653589793238462643383279502884197169399, eps = 1e-8;
    static boolean multipleTC = false, memory = true, fileIO = false;
    FastReader in;PrintWriter out;
    void run() throws Exception{
        long ct = System.currentTimeMillis();
        if (fileIO) {
            in = new FastReader("");
            out = new PrintWriter("");
        } else {
            in = new FastReader();
            out = new PrintWriter(System.out);
        }
        //Solution Credits: Taranpreet Singh
        int T = multipleTC? ni():1;
        pre();
        for (int t = 1; t <= T; t++) solve(t);
        out.flush();
        out.close();
        System.err.println(System.currentTimeMillis() - ct);
    }
    public static void main(String[] args) throws Exception{
        if(memory)new Thread(null, new Runnable() {public void run(){try{new CC_MANCBST().run();}catch(Exception e){e.printStackTrace();System.exit(1);}}}, "1", 1 << 28).start();
        else new CC_MANCBST().run();
    }
    int[][] make(int n, int e, int[] from, int[] to, boolean f){
        int[][] g = new int[n][];int[]cnt = new int[n];
        for(int i = 0; i< e; i++){
            cnt[from[i]]++;
            if(f)cnt[to[i]]++;
        }
        for(int i = 0; i< n; i++)g[i] = new int[cnt[i]];
        for(int i = 0; i< e; i++){
            g[from[i]][--cnt[from[i]]] = to[i];
            if(f)g[to[i]][--cnt[to[i]]] = from[i];
        }
        return g;
    }
    int[][][] makeS(int n, int e, int[] from, int[] to, boolean f){
        int[][][] g = new int[n][][];int[]cnt = new int[n];
        for(int i = 0; i< e; i++){
            cnt[from[i]]++;
            if(f)cnt[to[i]]++;
        }
        for(int i = 0; i< n; i++)g[i] = new int[cnt[i]][];
        for(int i = 0; i< e; i++){
            g[from[i]][--cnt[from[i]]] = new int[]{to[i], i, 0};
            if(f)g[to[i]][--cnt[to[i]]] = new int[]{from[i], i, 1};
        }
        return g;
    }
    int find(int[] set, int u){return set[u] = (set[u] == u?u:find(set, set[u]));}
    int digit(long s){int ans = 0;while(s>0){s/=10;ans++;}return ans;}
    long gcd(long a, long b){return (b==0)?a:gcd(b,a%b);}
    int gcd(int a, int b){return (b==0)?a:gcd(b,a%b);}
    int bit(long n){return (n==0)?0:(1+bit(n&(n-1)));}
    void p(Object... o){for(Object oo:o)out.print(oo+" ");}
    void pn(Object... o){for(int i = 0; i< o.length; i++)out.print(o[i]+(i+1 < o.length?" ":"\n"));}
    void pni(Object... o){for(Object oo:o)out.print(oo+" ");out.println();out.flush();}
    String n()throws Exception{return in.next();}
    String nln()throws Exception{return in.nextLine();}
    int ni()throws Exception{return Integer.parseInt(in.next());}
    long nl()throws Exception{return Long.parseLong(in.next());}
    double nd()throws Exception{return Double.parseDouble(in.next());}

    class FastReader{
        BufferedReader br;
        StringTokenizer st;
        public FastReader(){
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        public FastReader(String s) throws Exception{
            br = new BufferedReader(new FileReader(s));
        }

        String next() throws Exception{
            while (st == null || !st.hasMoreElements()){
                try{
                    st = new StringTokenizer(br.readLine());
                }catch (IOException  e){
                    throw new Exception(e.toString());
                }
            }
            return st.nextToken();
        }

        String nextLine() throws Exception{
            String str;
            try{
                str = br.readLine();
            }catch (IOException e){
                throw new Exception(e.toString());
            }
            return str;
        }
    }
}