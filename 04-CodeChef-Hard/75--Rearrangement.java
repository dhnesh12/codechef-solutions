import static java.lang.Math.*;
 
import java.io.*;
import java.lang.reflect.*;
import java.util.*;
 
class Rearrangement {
 
	final int MOD = (int)1e9 + 7;
	final double eps = 1e-12;
	final int INF = (int)1e9;
 
	@SuppressWarnings("unchecked")
	public void solve () {
		int N = sc.nextInt();
		int M = sc.nextInt();
		int K = sc.nextInt();
		Integer [] A = sc.nextInts();
		

		int q = N/K, r = N%K;
		

		Residue [] R = classify(A, M);
		
		
		for (Residue res : R) {
			int c = res.values.size();
			res.la = max(ceil(c, 1+q), ceil(c-r, q));
			res.fa = floor(c, q) - res.la;
			if (res.fa < 0) {
				print (-1);
				return;
			}
		}
		
		int C = R.length, D = 0;
		Residue [][] U = new Residue [2][C];
		for (int i = 0; i < C; ++i) {
			for (int j = 0; j < 2; ++j) {
				U[j][i] = new Residue(R[i].key);
				U[j][i].fa = R[i].fa / 2;
			}
			if (R[i].fa % 2 == 1) {
				if (D <= 0) {
					++U[0][i].fa; ++D;
				} else {
					++U[1][i].fa; --D;
				}
			}
		}
		
		long S0 = 0; int L = K;
		for (Residue res : R) {
			S0 = (S0 + res.la * res.key) % M;
			L -= res.la;
		}
		
		// dfs
		Map<Integer, Integer> [][] W = new HashMap[2][L+1];
		for (int j = 0; j < 2; ++j) {
			for (int c = 0; c <= L; ++c)
				W[j][c] = new HashMap<Integer, Integer>();
			dfs(0, U[j], new int [C], 0, 0, W[j], L, M);
		}
		
		Integer [] X = null;
		out: for (int i = 0; i <= L; ++i)
			for (int S1 : W[0][i].keySet()) {
				int S2 = (int)(((M - S0) + (M - S1)) % M);
				if (W[1][L-i].containsKey(S2)) {
					X = new Integer [] { W[0][i].get(S1), W[1][L-i].get(S2) };
					break out;
				}
			}
		
		if (X == null) {
			print (-1);
			return;
		}
		
		int [] m = new int [2];
		for (int i = 0; i < C; ++i) {
			for (int k = 0; k < 2; ++k) {
				for (int j = 0; j < U[k][i].fa; ++j)
					if ((X[k] & (1 << (m[k] + j))) != 0)
						++R[i].a;
				m[k] += U[k][i].fa;
			}
			R[i].a += R[i].la;
		}
		
		Object [][] B = new Object [1+q][K];
		int nb = 0, nd = r;
		for (int i = 0; i < C; ++i) {
			int b = R[i].values.size() - q * R[i].a, d = R[i].a - b;
			for (int p = 0; p <= q; ++ p)
				for (int j = 0; j < b; ++j)
					B[p][nb + j] = R[i].values.poll();
			for (int p = 0; p < q; ++ p)
				for (int j = 0; j < d; ++j)
					B[p][nd + j] = R[i].values.poll();
			nb += b; nd += d;
		}
		
		Object [] res = new Object [N];
		out: for (int i = 0, n = 0; i <= q; ++i)
			for (int j = 0; j < K; ++j, ++n) {
				if (n == N)
					break out;
				res[n] = B[i][j];
			}
		
		print(res);
	}
	
	void dfs(int i, Residue [] R, int [] F, int c, long S, Map<Integer, Integer> [] W, int K, int M) {
		if (i == R.length) {
			int b = 0, m = 0;
			for (int j = 0; j < i; ++j) {
				for (int k = 0; k < F[j]; ++k)
					b |= (1 << (m + k));
				m += R[j].fa;
			}
			W[c].put((int)S, b);
		}
		else {
			// c + h <= K, h <= R.FA
			int h = min(K - c, R[i].fa);
			for (int j = 0; j <= h; ++j) {
				F[i] = j;
				dfs(i+1, R, F, c + j, (S + j * R[i].key) % M, W, K, M);
			}
		}
	}
	
	static class Residue {
		final long key;
		final Queue<Object> values = new LinkedList<Object>();
		Residue(long key) { this.key = key; }		
		int a, la, fa;
	}
		
	Residue [] classify(Integer [] A, int M) {
		Map<Object, Residue> map = new HashMap<Object, Residue>();
		for (int value : A) {
			long key = value % M;
			if (!map.containsKey(key)) 
				map.put(key, new Residue(key));
			map.get(key).values.add(value);
		}
		return map.values().toArray(new Residue [0]);		
	}
	
	int floor(int p, int q) {
		return p / q;
	}
	
	int ceil(int p, int q) {
		return (p + q - 1) / q;
	}
	
	void init () {
	}
	
	
	
	static MyScanner sc;
	
	static class MyScanner {
		public String next() {
			readToken();
			return new String(b, T[0], T[1]);
		}
		
		public char nextChar() {
			readToken();
			return (char)b[T[0]];
		}
				
		public int nextInt() {
			return (int)nextLong();
		}
		
		public long nextLong() {
			readToken();
			return calc(T[0], T[1]);
		}
		
		public double nextDouble() {
			return Double.parseDouble(next());
		}
		
		public String nextLine() {
			readLine();
			return new String(b, T[0], T[1]);
		}
		
		public String [] nextStrings() {
			readLine();
			int s = T[0], c = 0;
			String [] res = new String[count(T[0], T[1])];
			for (int i = T[0]; i < T[1]; ++i)
				if (b[i] == ' ') {
					res[c++] = new String(b, s, i - s);
					s = i+1;
				}
			res[c] = new String (b, s, T[1] - s);
			return res;
		}
		
		public char [] nextChars() {
			readToken();
			char [] res = new char[T[1] - T[0]];
			for (int i = T[0]; i < T[1]; ++i)
				res[i] = (char)b[i];
			return res;
		}
 
		public Integer [] nextInts() {
			readLine();
			int s = T[0], c = 0;
			Integer [] res = new Integer[count(T[0], T[1])];
			for (int i = T[0]; i < T[1]; ++i)
				if (b[i] == ' ') {
					res[c++] = (int)calc(s, i);
					s = i+1;
				}
			res[c] = (int)calc(s, T[1]);
			return res;
		}	
		
		public Long [] nextLongs() {
			readLine();
			int s = T[0], c = 0;
			Long [] res = new Long[count(T[0], T[1])];
			for (int i = T[0]; i < T[1]; ++i)
				if (b[i] == ' ') {
					res[c++] = calc(s, i);
					s = i+1;
				}
			res[c] = calc(s, T[1]);
			return res;
		}
 
		public Double [] nextDoubles() {
			readLine();
			int s = T[0], c = 0;
			Double [] res = new Double[count(T[0], T[1])];
			for (int i = T[0]; i < T[1]; ++i)
				if (b[i] == ' ') {
					res[c++] = Double.parseDouble(new String(b, s, i - s));
					s = i+1;
				}
			res[c] = Double.parseDouble(new String(b, s, T[1] - s));
			return res;
		}
 
		
		
		private final static int MAX_SZ = 12000000;
		private final byte [] b = new byte[MAX_SZ];
		private final int [] T = new int [2];
		private int cur = 0; 
 
		MyScanner () {
			try {
				InputStream is = new BufferedInputStream(System.in);
				while (is.available() == 0)
					Thread.sleep(1);
				start();
				is.read(b);
			} catch (Exception e) {
				throw new Error(e);
			}
		}
		
		private void readLine() {
			int c;
			for (c = cur; b[c] != '\n' && b[c] != '\r'; ++c);
			T[0] = cur; T[1] = c;
			for (cur = c; b[cur] == '\n' || b[cur] == '\r'; ++cur);
		}
		
		private void readToken() {
			int c;
			for (c = cur; b[c] != ' ' && b[c] != '\n' && b[c] != '\r'; ++c);
			T[0] = cur; T[1] = c;
			for (cur = c; b[cur] == ' ' || b[cur] == '\n' || b[cur] == '\r'; ++cur);
		}
 
		private int count(int s, int e) {
			int cnt = 1;
			for (int i = s; i < e; ++i)
				if (b[i] == ' ')
					++cnt;		
			return cnt;
		}
		
		private long calc(int s, int e) {
			long res = 0, f = 1;
			for (int i = s; i < e; ++i)
				if (b[i] == '-')
					f = -1;
				else
					res = 10 * res + b[i] - '0';
			return res * f;			
		}
	}
	
	static void print (Object... a) {
		pw.println(build(a));
	}
 
	static void exit (Object... a) {
		print(a);
		exit();
	}
 
	static void exit () {
		pw.close();
		System.out.flush();
		Thread.yield();
		System.err.println("------------------");
		System.err.println("Time: " + ((millis() - t) / 1000.0));
		System.exit(0);
	}
	
	void NO() {
		throw new Error("NO!");
	}
 
	
	
	public Rearrangement () {
		init();
		int T = sc.nextInt();
		for (int t = 1; t <= T; ++t)
			solve();
	}
	
	static String build(Object... a) {
		StringBuilder b = new StringBuilder();
		for (Object o : a)
			append(b, o);
		return b.toString().trim();		
	}
	
	static void append(StringBuilder b, Object o) {
		if (o.getClass().isArray()) {
			int L = Array.getLength(o);
			for (int i = 0; i < L; ++i)
				append(b, Array.get(o, i));
		} else if (o instanceof Iterable<?>) {
			for (Object p : (Iterable<?>)o)
				append(b, p);
		} else
			b.append(" ").append(o);		
	}
	

	
	public static void main(String[] args) throws IOException {
		sc = new MyScanner ();
		new Rearrangement();
		exit();
	}
 
	static void start() {
		t = millis();
	}
 
	static PrintWriter pw = new PrintWriter(System.out);
	
	static long t;
	
	static long millis() {
		return System.currentTimeMillis();
	}	
}