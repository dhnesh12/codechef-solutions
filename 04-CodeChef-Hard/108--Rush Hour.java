import java.io.*;
import java.util.*;
 
public class Main {
	
	private BufferedReader in;
	private PrintWriter out;
	private StringTokenizer st;
	private static int n, m, k;
	
	static class Position implements Comparable<Position> {
		int[] x, y;
		int d, p;
		
		Position(int[] x, int[] y, int d) {
			this.x = x;
			this.y = y;
			this.d = d;
			for (int i = 1; i < k; ++i) {
				if (x[i] <= x[0] && x[i] + lenx[i] > x[0] && y[i] > y[0]) {
					p++;
				}
			}
		}
 
		@Override
		public int compareTo(Position o) {
			return (d + p) - (o.d + o.p);
		}
 
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + Arrays.hashCode(x);
			result = prime * result + Arrays.hashCode(y);
			return result;
		}
 
		@Override
		public boolean equals(Object obj) {
			if (this == obj) {
				return true;
			}
			if (obj == null) {
				return false;
			}
			Position other = (Position) obj;
			if (d != other.d) {
				return false;
			}
			if (p != other.p) {
				return false;
			}
			if (!Arrays.equals(x, other.x)) {
				return false;
			}
			if (!Arrays.equals(y, other.y)) {
				return false;
			}
			return true;
		}
	}
	
	static int[] lenx, leny;
 
	void solve() throws IOException {
		n = nextInt();
		m = nextInt();
		k = nextInt();
		char[][] f = new char[n][];
		for (int i = 0; i < n; ++i) {
			f[i] = next().toCharArray();
		}
		lenx = new int[k];
		leny = new int[k];
		int[] x0 = new int[k];
		int[] y0 = new int[k];
		Arrays.fill(x0, -1);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (f[i][j] == '.' || x0[f[i][j] - 'a'] != -1) {
					continue;
				}
				int c = f[i][j] - 'a';
				x0[c] = i;
				y0[c] = j;
				while (i + lenx[c] < n && f[i + lenx[c]][j] == f[i][j]) {
					++lenx[c];
				}
				while (j + leny[c] < m && f[i][j + leny[c]] == f[i][j]) {
					++leny[c];
				}
			}
		}
		Position pos0 = new Position(x0, y0, 0);
		PriorityQueue<Position> pq = new PriorityQueue<Position>();
		pq.add(pos0);
		HashSet<Position> col = new HashSet<Position>();
		col.add(pos0);
		int ans = 9;
		while (!pq.isEmpty()) {
			Position pos = pq.poll();
			if (pos.d + pos.p >= ans) {
				break;
			}
			if (pos.p == 0) {
				ans = pos.d;
				continue;
			}
			for (int i = 0; i < k; ++i) {
				boolean h = lenx[i] == 1;
				int max = h ? m - leny[i] : n - lenx[i], min = 0;
				for (int j = 0; j < k; ++j) {
					if (i == j) {
						continue;
					}
					if (h) {
						if (pos.x[j] <= pos.x[i] && pos.x[j] + lenx[j] > pos.x[i]) {
							if (pos.y[j] > pos.y[i]) {
								max = Math.min(max, pos.y[j] - leny[i]);
							} else {
								min = Math.max(min, pos.y[j] + leny[j]);
							}
						}
					} else {
						if (pos.y[j] <= pos.y[i] && pos.y[j] + leny[j] > pos.y[i]) {
							if (pos.x[j] > pos.x[i]) {
								max = Math.min(max, pos.x[j] - lenx[i]);
							} else {
								min = Math.max(min, pos.x[j] + lenx[j]);
							}
						}
					}
				}
				for (int t = min; t <= max; ++t) {
					if (t == (h ? pos.y[i] : pos.x[i]) || t - min > 1 && max - t > 1) {
						continue;
					}
					int[] xx = pos.x.clone();
					int[] yy = pos.y.clone();
					if (h) {
						yy[i] = t;
					} else {
						xx[i] = t;
					}
					Position pos1 = new Position(xx, yy, pos.d + 1);
					if (!col.contains(pos1)) {
						pq.add(pos1);
						col.add(pos1);
					}
				}
			}
		}
		out.println(ans + 1);
	}
 
	Main() throws IOException {
		in = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		
		eat("");
		
		int tests = nextInt();
		for (int test = 0; test < tests; ++test) {
			solve();
		}
		
//		in.close();
		out.close();
	}
	
	private void eat(String str) {
		st = new StringTokenizer(str);
	}
	
	String next() throws IOException {
		while (!st.hasMoreTokens()) {
			String line = in.readLine();
			if (line == null) {
				return null;
			}
			eat(line);
		}
		return st.nextToken();
	}
	
	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}
	
	long nextLong() throws IOException {
		return Long.parseLong(next());
	}
	
	double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}
 
	public static void main(String[] args) throws IOException {
		new Main();
	}
} 