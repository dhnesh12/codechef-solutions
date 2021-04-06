import java.util.*;
import java.io.*;
import java.text.*;
public class Main{
    //SOLUTION BEGIN
    //Into the Hardware Mode
    void pre() throws Exception{}
    void solve(int TC)throws Exception{
        int n = ni(), k = ni(), mx = 131072;
        int p = 0;
        while(1<<p <= n)++p;
        long[][] w = new long[p][mx];
        for(int i = 0; i< k; i++)w[0][ni()]++;
        NTT ntt = new NTT(998244353);
        for(int i = 1; i< p; i++){
            w[i] = ntt.multiply(w[i-1], w[i-1]);
            w[i] = Arrays.copyOf(w[i], mx);
        }
        long mod = 998244353;
        for(int qq = ni(); qq>0; qq--){
            int s = ni();
            long sum = 0, phi = n/2;
            for(int bit = 0, f = 1; bit < p; bit++, f<<=1, phi = (phi==1)?1:(phi>>1)){
                if(s%(n/f) == 0){
                    sum += phi*w[bit][s/(n/f)];
                    if(sum >= mod)sum %= mod;
                }
            }
            pn((sum*ntt.pow(n, mod-2))%mod);
        }
    }
    class NTT{
        long root, mod;
        public NTT(long m){
            mod = m;
            long[] s = pFact();
            for(root = 3; true; root++){
                boolean f = true;
                for(long x:s)if(pow(root, (mod-1)/x) == 1)f = false;
                if(f)break;
            }
        }
        long[] multiply(long[] a, long[] b) throws Exception{
            int l = Integer.highestOneBit(Math.max(a.length, b.length)-1)<<2;
            l = Math.max(l, 1);
            hold(mod%l == 1);
            long[] p = new long[l];
            if(a == b){
                for(int i = 0; i< a.length; i++)p[i] = a[i];
                ntt(p, false);
                for(int i = 0; i< l; i++)p[i] = (p[i]*p[i])%mod;
            }else{
                long[] q = new long[l];
                for(int i = 0; i< a.length; i++)p[i] = a[i];
                for(int i = 0; i< b.length; i++)q[i] = b[i];
                ntt(p, false);
                ntt(q, false);
                for(int i = 0; i< l; i++)p[i] = (p[i]*q[i])%mod;
            }
            ntt(p, true);
            return p;   
        }
        void ntt(long[] p, boolean invert) throws Exception{
            int n = p.length;
            hold(bit(n) == 1);
            for(int i = 1, j = 0; i< n; i++){
                int bit = n >> 1;
                for (; j >= bit; bit >>= 1)
                    j -= bit;
                j += bit;
                if(i< j){
                    p[i] += p[j];
                    p[j] = p[i]-p[j];
                    p[i] -= p[j];
                }
            }
            hold(mod%n == 1);
            for(int len = 2; len <= n; len<<=1){
                int half = len>>1;
                hold((mod-1)%len == 0);
                long wlen = pow(root, (mod-1)/len);
                if(invert)wlen = pow(root, mod-1-(mod-1)/len);
                for(int i = 0; i< n; i+= len){
                    long w = 1;
                    for(int j = 0; j< half; j++){
                        long a = p[i+j], b = (p[i+j+half]*w)%mod;
                        p[i+j] = (a+b)%mod;
                        p[i+j+half] = (a-b+mod)%mod;
                        w = (w*wlen)%mod;
                    }
                }
            }
            long invN = pow(n, mod-2);
            if(invert)for(int i = 0; i< n; i++)p[i] = (p[i]*invN)%mod;
        }
        long pow(long a, long p){
            long o = 1;a %= mod;
            while(p>0){
                if((p&1)==1)o = (o*a)%mod;
                a = (a*a)%mod;
                p>>=1;
            }
            return o;
        }
        final long[] pFact(){
            long x = mod-1;
            long[] s = new long[15];int c = 0;
            for(long i = 2; i*i <= mod-1; i++){
                if(x%i != 0)continue;
                s[c++] = i;
                while(x%i == 0)x/= i;
            }
            if(x > 1)s[c++] = x;
            s = Arrays.copyOfRange(s, 0, c);
            return s;
        }
    }
    //SOLUTION END
    void hold(boolean b)throws Exception{if(!b)throw new Exception("Hold right there, Sparky!");}
    void exit(boolean b){if(!b)System.exit(0);}
    long IINF = (long)1e18;
    final int INF = (int)1e9+2, MX = (int)2e6+5;
    DecimalFormat df = new DecimalFormat("0.00000000000");
    double PI = 3.141592653589793238462643383279502884197169399, eps = 1e-7;
    static boolean multipleTC = false, memory = false, fileIO = false;
    FastReader in;PrintWriter out;
    void run() throws Exception{
        if(fileIO){
            in = new FastReader("C:/users/user/desktop/inp.in");
            out = new PrintWriter("C:/users/user/desktop/out.out");
        }else {
            in = new FastReader();
            out = new PrintWriter(System.out);
        }
        //Solution Credits: Taranpreet Singh
        int T = (multipleTC)?ni():1;
        pre();
        for(int t = 1; t<= T; t++)solve(t);
        out.flush();
        out.close();
    }
    public static void main(String[] args) throws Exception{
        if(memory)new Thread(null, new Runnable() {public void run(){try{new Main().run();}catch(Exception e){e.printStackTrace();}}}, "1", 1 << 28).start();
        else new Main().run();
    }
    int find(int[] set, int u){return set[u] = (set[u] == u?u:find(set, set[u]));}
    int digit(long s){int ans = 0;while(s>0){s/=10;ans++;}return ans;}
    long gcd(long a, long b){return (b==0)?a:gcd(b,a%b);}
    int gcd(int a, int b){return (b==0)?a:gcd(b,a%b);}
    int bit(long n){return (n==0)?0:(1+bit(n&(n-1)));}
    void p(Object o){out.print(o);}
    void pn(Object o){out.println(o);}
    void pni(Object o){out.println(o);out.flush();}
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
            String str = "";
            try{   
                str = br.readLine();	
            }catch (IOException e){
                throw new Exception(e.toString());
            }  
            return str;
        }
    }   
}