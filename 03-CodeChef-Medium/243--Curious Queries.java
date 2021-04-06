import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.InputMismatchException;

class CURSQURS2 {
	InputStream is;
	PrintWriter out;
	String INPUT = "";
	
	int mod = 1000000007;
	
	void solve()
	{
		for(int T = ni();T > 0;T--){
			int n = ni(), m = ni();
			int[] a = na(n);
			int[] b = na(m);
			Datum aa = make(a, n, m);
			Datum bb = make(b, m, n);
			
			int o = Math.max(n, m);
			long[] val = new long[o+1];
			for(int d = 19;d >= 0;d--){
				long xc1 = 0;
				long yc1 = 0;
				long xc0 = 0;
				long yc0 = 0;
				for(int i = 1;i <= o;i += 2){
					xc1 += aa.xos[d][i];
					yc1 += bb.xos[d][i];
					xc0 += aa.xzs[d][i];
					yc0 += bb.xzs[d][i];
					xc0 %= mod; yc0 %= mod;
					xc1 %= mod; yc1 %= mod;
					val[i] = (val[i] * 2 + xc1 * yc0 + yc1 * xc0) % mod;
				}
			}
			for(int i = 1;i+1 <= o;i+=2){
				val[i+1] = val[i];
			}
			for(int i = 1;i <= o;i++){
				val[i] += aa.ret[i];
				val[i] += bb.ret[i];
				val[i] %= mod;
			}
			for(int i = 1;i <= o;i++){
				out.print(val[i] + " ");
			}
			out.println();
		}
	}
	
	Datum make(int[] a, int n, int m)
	{
		int o = Math.max(n, m);
		long[][] xos = new long[20][o+1];
		long[][] xzs = new long[20][o+1];
		
		for(int d = 0;d < 20;d++){
			long[] L = new long[n+1];
			long[] R = new long[n+1];
			for(int i = 0;i < n;i++){
				L[i+1] = L[i] ^ (a[i]>>>d&1);
			}
			for(int i = 0;i <= n;i++){
				R[i] = L[n-i]^1;
			}
			long[] M = convoluteSimply(L, R, 998244353, 3);
			for(int i = 1;i <= n;i++){
				xos[d][i] = (M[n+i] + M[n-i]) * i % mod;
				xzs[d][i] = ((n-i+1) - (M[n+i] + M[n-i])) * i % mod;
			}
		}
//		for(int i = 1;i <= o;i++){
//			for(int d = 0;d < 20;d++){
//				int s = 0;
//				for(int j = 0;j+i-1 < n;j++){
//					int x = 0;
//					for(int k = j;k < j+i;k++){
//						x ^= a[k]>>>d&1;
//					}
//					s += x;
//				}
//				xos[d][i] = (long)s * i % mod;
//				xzs[d][i] = (long)(n-i+1-s) * i % mod;
//			}
//		}
		
		long[] ret = new long[o+1];
		long xtot = 0;
		long ytot = 0;
		for(int i = 0;i <= o;i++){
			if(i % 2 == 0){
				long xsum = 0;
				for(int j = 19;j >= 0;j--){
					xsum = (xsum * 2 + xos[j][i]) % mod;
				}
				xtot += xsum;
				xtot %= mod;
			}
			
			if(i % 2 == 1 && m-i+1 >= 0){
				ytot += (long)(m-i+1) * i;
				ytot %= mod;
			}
			
			ret[i] = xtot * ytot % mod;
		}
		
		return new Datum(ret, xos, xzs);
	}
	
	
	
	static class Datum
	{
		long[] ret;
		long[][] xos;
		long[][] xzs;
		public Datum(long[] ret, long[][] xos, long[][] xzs) {
			this.ret = ret;
			this.xos = xos;
			this.xzs = xzs;
		}
	}
	
	public static final int[] NTTPrimes = {1053818881, 1051721729, 1045430273, 1012924417, 1007681537, 1004535809, 998244353, 985661441, 976224257, 975175681};
	public static final int[] NTTPrimitiveRoots = {7, 6, 3, 5, 3, 3, 3, 3, 3, 17};
//	public static final int[] NTTPrimes = {1012924417, 1004535809, 998244353, 985661441, 975175681, 962592769, 950009857, 943718401, 935329793, 924844033};
//	public static final int[] NTTPrimitiveRoots = {5, 3, 3, 3, 17, 7, 7, 7, 3, 5};
	
	public static long[] convoluteSimply(long[] a, long[] b, int P, int g)
	{
		int m = Math.max(2, Integer.highestOneBit(Math.max(a.length, b.length)-1)<<2);
		long[] fa = nttmb(a, m, false, P, g);
		long[] fb = a == b ? fa : nttmb(b, m, false, P, g);
		for(int i = 0;i < m;i++){
			fa[i] = fa[i]*fb[i]%P;
		}
		return nttmb(fa, m, true, P, g);
	}
	
	public static long[] convolute(long[] a, long[] b)
	{
		int USE = 2;
		int m = Math.max(2, Integer.highestOneBit(Math.max(a.length, b.length)-1)<<2);
		long[][] fs = new long[USE][];
		for(int k = 0;k < USE;k++){
			int P = NTTPrimes[k], g = NTTPrimitiveRoots[k];
			long[] fa = nttmb(a, m, false, P, g);
			long[] fb = a == b ? fa : nttmb(b, m, false, P, g);
			for(int i = 0;i < m;i++){
				fa[i] = fa[i]*fb[i]%P;
			}
			fs[k] = nttmb(fa, m, true, P, g);
		}
		
		int[] mods = Arrays.copyOf(NTTPrimes, USE);
		long[] gammas = garnerPrepare(mods);
		int[] buf = new int[USE];
		for(int i = 0;i < fs[0].length;i++){
			for(int j = 0;j < USE;j++)buf[j] = (int)fs[j][i];
			long[] res = garnerBatch(buf, mods, gammas);
			long ret = 0;
			for(int j = res.length-1;j >= 0;j--)ret = ret * mods[j] + res[j];
			fs[0][i] = ret;
		}
		return fs[0];
	}
	
	public static long[] convolute(long[] a, long[] b, int USE, int mod)
	{
		int m = Math.max(2, Integer.highestOneBit(Math.max(a.length, b.length)-1)<<2);
		long[][] fs = new long[USE][];
		for(int k = 0;k < USE;k++){
			int P = NTTPrimes[k], g = NTTPrimitiveRoots[k];
			long[] fa = nttmb(a, m, false, P, g);
			long[] fb = a == b ? fa : nttmb(b, m, false, P, g);
			for(int i = 0;i < m;i++){
				fa[i] = fa[i]*fb[i]%P;
			}
			fs[k] = nttmb(fa, m, true, P, g);
		}
		
		int[] mods = Arrays.copyOf(NTTPrimes, USE);
		long[] gammas = garnerPrepare(mods);
		int[] buf = new int[USE];
		for(int i = 0;i < fs[0].length;i++){
			for(int j = 0;j < USE;j++)buf[j] = (int)fs[j][i];
			long[] res = garnerBatch(buf, mods, gammas);
			long ret = 0;
			for(int j = res.length-1;j >= 0;j--)ret = (ret * mods[j] + res[j]) % mod;
			fs[0][i] = ret;
		}
		return fs[0];
	}
	
	// static int[] wws = new int[270000]; // outer faster
	
	// Modifed Montgomery + Barrett
	private static long[] nttmb(long[] src, int n, boolean inverse, int P, int g)
	{
		long[] dst = Arrays.copyOf(src, n);
		
		int h = Integer.numberOfTrailingZeros(n);
		long K = Integer.highestOneBit(P)<<1;
		int H = Long.numberOfTrailingZeros(K)*2;
		long M = K*K/P;
		
		int[] wws = new int[1<<h-1];
		long dw = inverse ? pow(g, P-1-(P-1)/n, P) : pow(g, (P-1)/n, P);
		long w = (1L<<32)%P;
		for(int k = 0;k < 1<<h-1;k++){
			wws[k] = (int)w;
			w = modh(w*dw, M, H, P);
		}
		long J = invl(P, 1L<<32);
		for(int i = 0;i < h;i++){
			for(int j = 0;j < 1<<i;j++){
				for(int k = 0, s = j<<h-i, t = s|1<<h-i-1;k < 1<<h-i-1;k++,s++,t++){
					long u = (dst[s] - dst[t] + 2*P)*wws[k];
					dst[s] += dst[t];
					if(dst[s] >= 2*P)dst[s] -= 2*P;
//					long Q = (u&(1L<<32)-1)*J&(1L<<32)-1;
					long Q = (u<<32)*J>>>32;
					dst[t] = (u>>>32)-(Q*P>>>32)+P;
				}
			}
			if(i < h-1){
				for(int k = 0;k < 1<<h-i-2;k++)wws[k] = wws[k*2];
			}
		}
		for(int i = 0;i < n;i++){
			if(dst[i] >= P)dst[i] -= P;
		}
		for(int i = 0;i < n;i++){
			int rev = Integer.reverse(i)>>>-h;
			if(i < rev){
				long d = dst[i]; dst[i] = dst[rev]; dst[rev] = d;
			}
		}
		
		if(inverse){
			long in = invl(n, P);
			for(int i = 0;i < n;i++)dst[i] = modh(dst[i]*in, M, H, P);
		}
		
		return dst;
	}
	
	// Modified Shoup + Barrett
	private static long[] nttsb(long[] src, int n, boolean inverse, int P, int g)
	{
		long[] dst = Arrays.copyOf(src, n);
		
		int h = Integer.numberOfTrailingZeros(n);
		long K = Integer.highestOneBit(P)<<1;
		int H = Long.numberOfTrailingZeros(K)*2;
		long M = K*K/P;
		
		long dw = inverse ? pow(g, P-1-(P-1)/n, P) : pow(g, (P-1)/n, P);
		long[] wws = new long[1<<h-1];
		long[] ws = new long[1<<h-1];
		long w = 1;
		for(int k = 0;k < 1<<h-1;k++){
			wws[k] = (w<<32)/P;
			ws[k] = w;
			w = modh(w*dw, M, H, P);
		}
		for(int i = 0;i < h;i++){
			for(int j = 0;j < 1<<i;j++){
				for(int k = 0, s = j<<h-i, t = s|1<<h-i-1;k < 1<<h-i-1;k++,s++,t++){
					long ndsts = dst[s] + dst[t];
					if(ndsts >= 2*P)ndsts -= 2*P;
					long T = dst[s] - dst[t] + 2*P;
					long Q = wws[k]*T>>>32;
					dst[s] = ndsts;
					dst[t] = ws[k]*T-Q*P&(1L<<32)-1;
				}
			}
//			dw = dw * dw % P;
			if(i < h-1){
				for(int k = 0;k < 1<<h-i-2;k++){
					wws[k] = wws[k*2];
					ws[k] = ws[k*2];
				}
			}
		}
		for(int i = 0;i < n;i++){
			if(dst[i] >= P)dst[i] -= P;
		}
		for(int i = 0;i < n;i++){
			int rev = Integer.reverse(i)>>>-h;
			if(i < rev){
				long d = dst[i]; dst[i] = dst[rev]; dst[rev] = d;
			}
		}
		
		if(inverse){
			long in = invl(n, P);
			for(int i = 0;i < n;i++){
				dst[i] = modh(dst[i] * in, M, H, P);
			}
		}
		
		return dst;
	}
	
	static final long mask = (1L<<31)-1;
	
	public static long modh(long a, long M, int h, int mod)
	{
		long r = a-((M*(a&mask)>>>31)+M*(a>>>31)>>>h-31)*mod;
		return r < mod ? r : r-mod;
	}
	
	private static long[] garnerPrepare(int[] m)
	{
		int n = m.length;
		assert n == m.length;
		if(n == 0)return new long[0];
		long[] gamma = new long[n];
		for(int k = 1;k < n;k++){
			long prod = 1;
			for(int i = 0;i < k;i++){
				prod = prod * m[i] % m[k];
			}
			gamma[k] = invl(prod, m[k]);
		}
		return gamma;
	}
	
	private static long[] garnerBatch(int[] u, int[] m, long[] gamma)
	{
		int n = u.length;
		assert n == m.length;
		long[] v = new long[n];
		v[0] = u[0];
		for(int k = 1;k < n;k++){
			long temp = v[k-1];
			for(int j = k-2;j >= 0;j--){
				temp = (temp * m[j] + v[j]) % m[k];
			}
			v[k] = (u[k] - temp) * gamma[k] % m[k];
			if(v[k] < 0)v[k] += m[k];
		}
		return v;
	}
	
	private static long pow(long a, long n, long mod) {
		//		a %= mod;
		long ret = 1;
		int x = 63 - Long.numberOfLeadingZeros(n);
		for (; x >= 0; x--) {
			ret = ret * ret % mod;
			if (n << 63 - x < 0)
				ret = ret * a % mod;
		}
		return ret;
	}
	
	private static long invl(long a, long mod) {
		long b = mod;
		long p = 1, q = 0;
		while (b > 0) {
			long c = a / b;
			long d;
			d = a;
			a = b;
			b = d % b;
			d = p;
			p = q;
			q = d - c * q;
		}
		return p < 0 ? p + mod : p;
	}

	
	void run() throws Exception
	{
		is = INPUT.isEmpty() ? System.in : new ByteArrayInputStream(INPUT.getBytes());
		out = new PrintWriter(System.out);
		
		long s = System.currentTimeMillis();
		solve();
		out.flush();
		if(!INPUT.isEmpty())tr(System.currentTimeMillis()-s+"ms");
	}
	
	public static void main(String[] args) throws Exception { new CURSQURS2().run(); }
	
	private byte[] inbuf = new byte[1024];
	public int lenbuf = 0, ptrbuf = 0;
	
	private int readByte()
	{
		if(lenbuf == -1)throw new InputMismatchException();
		if(ptrbuf >= lenbuf){
			ptrbuf = 0;
			try { lenbuf = is.read(inbuf); } catch (IOException e) { throw new InputMismatchException(); }
			if(lenbuf <= 0)return -1;
		}
		return inbuf[ptrbuf++];
	}
	
	private boolean isSpaceChar(int c) { return !(c >= 33 && c <= 126); }
	private int skip() { int b; while((b = readByte()) != -1 && isSpaceChar(b)); return b; }
	
	private double nd() { return Double.parseDouble(ns()); }
	private char nc() { return (char)skip(); }
	
	private String ns()
	{
		int b = skip();
		StringBuilder sb = new StringBuilder();
		while(!(isSpaceChar(b))){ // when nextLine, (isSpaceChar(b) && b != ' ')
			sb.appendCodePoint(b);
			b = readByte();
		}
		return sb.toString();
	}
	
	private char[] ns(int n)
	{
		char[] buf = new char[n];
		int b = skip(), p = 0;
		while(p < n && !(isSpaceChar(b))){
			buf[p++] = (char)b;
			b = readByte();
		}
		return n == p ? buf : Arrays.copyOf(buf, p);
	}
	
	private char[][] nm(int n, int m)
	{
		char[][] map = new char[n][];
		for(int i = 0;i < n;i++)map[i] = ns(m);
		return map;
	}
	
	private int[] na(int n)
	{
		int[] a = new int[n];
		for(int i = 0;i < n;i++)a[i] = ni();
		return a;
	}
	
	private int ni()
	{
		int num = 0, b;
		boolean minus = false;
		while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
		if(b == '-'){
			minus = true;
			b = readByte();
		}
		
		while(true){
			if(b >= '0' && b <= '9'){
				num = num * 10 + (b - '0');
			}else{
				return minus ? -num : num;
			}
			b = readByte();
		}
	}
	
	private long nl()
	{
		long num = 0;
		int b;
		boolean minus = false;
		while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
		if(b == '-'){
			minus = true;
			b = readByte();
		}
		
		while(true){
			if(b >= '0' && b <= '9'){
				num = num * 10 + (b - '0');
			}else{
				return minus ? -num : num;
			}
			b = readByte();
		}
	}
	
	private void tr(Object... o) { if(INPUT.length() > 0)System.out.println(Arrays.deepToString(o)); }
}
