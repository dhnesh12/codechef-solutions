import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.InputMismatchException;

// 1356
class ENETIRE {
	InputStream is;
	PrintWriter out;
	String INPUT = "";
	
	void solve()
	{
		int Y = ni(), X = ni(), m = ni(), n = ni();
		int[] u = na(m);
		int[][] obs = new int[n][];
		for(int i = 0;i < n;i++){
			obs[i] = new int[]{ni()-2, ni()};
		}
		Arrays.sort(obs, new Comparator<int[]>() {
			public int compare(int[] a, int[] b) {
				if(a[0] != b[0])return a[0] - b[0];
				return a[1] - b[1];
			}
		});
		
		int[][] M = new int[Y][Y];
		for(int i = 0;i < Y;i++)M[i][i] = 1;
		for(int i = 0;i < Y-1;i++)M[i][i+1] = 1;
		for(int i = 0;i < Y-1;i++)M[i+1][i] = 1;
		
		int[][][] MS = generateP2(M, 30);
		int px = 0;
		int[] v = new int[Y];
		for(int w : u)v[w]++;
		boolean[] pbed = new boolean[Y];
		for(int i = 0;i < n;){
			int j = i;
			while(j < n && obs[j][0] == obs[i][0])j++;
			
			int x = obs[i][0];
			if(px < x-1){
				v = pow(MS, v, x-1-px);
			}
			boolean[] bed = new boolean[Y];
			for(int k = i;k < j;k++)bed[obs[k][1]] = true;
			
			long[] nv = new long[Y];
			for(int k = 0;k < Y;k++){
				if(!bed[k]){
					nv[k] += v[k];
				}
				if(k+1 < Y && !bed[k+1]){
					nv[k+1] += v[k];
				}
				if(k-1 >= 0 && !bed[k-1]){
					nv[k-1] += v[k];
				}
				if(k+1 < Y && bed[k] && bed[k+1]){
					for(int y = k+2;y < Y;y++){
						if(i-1 >= 0 && obs[i-1][0] == obs[i][0]-1 && pbed[y-1])break;
						if(!bed[y]){
							nv[y] += v[k];
							break;
						}
					}
				}
				if(k-1 >= 0 && bed[k] && bed[k-1]){
					for(int y = k-2;y >= 0;y--){
						if(i-1 >= 0 && obs[i-1][0] == obs[i][0]-1 && pbed[y+1])break;
						if(!bed[y]){
							nv[y] += v[k];
							break;
						}
					}
				}
			}
			for(int k = 0;k < Y;k++)v[k] = (int)(nv[k] % mod);
			
			px = obs[i][0];
			pbed = bed;
			i = j;
		}
		
		if(px < X){
			v = pow(MS, v, X-px);
		}
		long ans = 0;
		for(int w : v){
			ans += w;
		}
		out.println(ans%mod);
	}
	
	///////// begin
	public static final int mod = 1000000007;
	public static final long m2 = (long)mod*mod;
	public static final long BIG = 8L*m2;
	
	// A^e*v
	public static int[] pow(int[][] A, int[] v, long e)
	{
		for(int i = 0;i < v.length;i++){
			if(v[i] >= mod)v[i] %= mod;
		}
		int[][] MUL = A;
		for(;e > 0;e>>>=1) {
			if((e&1)==1)v = mul(MUL, v);
			MUL = p2(MUL);
		}
		return v;
	}
	
	// int matrix*int vector
	public static int[] mul(int[][] A, int[] v)
	{
		int m = A.length;
		int n = v.length;
		int[] w = new int[m];
		for(int i = 0;i < m;i++){
			long sum = 0;
			for(int k = 0;k < n;k++){
				sum += (long)A[i][k] * v[k];
				if(sum >= BIG)sum -= BIG;
			}
			w[i] = (int)(sum % mod);
		}
		return w;
	}
	
	// int matrix^2 (be careful about negative value)
	public static int[][] p2(int[][] A)
	{
		int n = A.length;
		int[][] C = new int[n][n];
		for(int i = 0;i < n;i++){
			long[] sum = new long[n];
			for(int k = 0;k < n;k++){
				for(int j = 0;j < n;j++){
					sum[j] += (long)A[i][k] * A[k][j];
					if(sum[j] >= BIG)sum[j] -= BIG;
				}
			}
			for(int j = 0;j < n;j++){
				C[i][j] = (int)(sum[j] % mod);
			}
		}
		return C;
	}
	
	//////////// end
	
	// ret[n]=A^(2^n)
	public static int[][][] generateP2(int[][] A, int n)
	{
		int[][][] ret = new int[n+1][][];
		ret[0] = A;
		for(int i = 1;i <= n;i++)ret[i] = p2(ret[i-1]);
		return ret;
	}
	
	// A[0]^e*v
	// A[n]=A[0]^(2^n)
	public static int[] pow(int[][][] A, int[] v, long e)
	{
		for(int i = 0;e > 0;e>>>=1,i++) {
			if((e&1)==1)v = mul(A[i], v);
		}
		return v;
	}
	
	public static int[][] mul(int[][]... a)
	{
		int[][] base = a[0];
		for(int i = 1;i < a.length;i++){
			base = mul(base, a[i]);
		}
		return base;
	}
	
	void run() throws Exception
	{
//		int n = 200, m = 1000000000;
//		Random gen = new Random();
//		StringBuilder sb = new StringBuilder();
//		sb.append(n + " ");
//		sb.append(m + " ");
//		sb.append(n + " ");
//		sb.append(0 + " ");
//		for (int i = 0; i < n; i++) {
//			sb.append(i + " ");
//		}
//		INPUT = sb.toString();

		
		is = INPUT.isEmpty() ? System.in : new ByteArrayInputStream(INPUT.getBytes());
		out = new PrintWriter(System.out);
		
		long s = System.currentTimeMillis();
		solve();
		out.flush();
		if(!INPUT.isEmpty())tr(System.currentTimeMillis()-s+"ms");
	}
	
	public static void main(String[] args) throws Exception { new ENETIRE().run(); }
	
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
