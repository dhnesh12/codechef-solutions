import java.io.*;
import java.util.*;
 
public class Main {
 
	private void solve() throws IOException {
		int tests = nextInt();
		for (int i = 0; i < tests; i++) {
			solve2();
		}
	}
 
	final static double EPS = 1e-7;
 
	static class Point {
		final double x, y;
 
		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}
 
		Point add(Point p) {
			return new Point(x + p.x, y + p.y);
		}
 
		Point sub(Point p) {
			return new Point(x - p.x, y - p.y);
		}
 
		Point mul(Point p) {
			return new Point(x * p.x - y * p.y, x * p.y + y * p.x);
		}
 
		double abs() {
			return Math.sqrt(x * x + y * y);
		}
 
		Point norm() {
			double abs = abs();
			return new Point(x / abs, y / abs);
		}
 
		double vect(Point p) {
			return x * p.y - y * p.x;
		}
 
		public String toString() {
			return String.format(Locale.US, "(%.2f, %.2f)", x, y);
		}
	}
 
	static class ByX implements Comparator<Point> {
 
		public int compare(Point o1, Point o2) {
			if (Math.abs(o1.x - o2.x) > EPS) {
				return o1.x < o2.x ? -1 : 1;
			}
			return o1.y < o2.y ? -1 : 1;
		}
	}
 
	Point[] a;
	double[] d1, d2;
 
	static double sign(double a) {
		if (Math.abs(a) < EPS)
			return 0;
		return a < 0 ? -1 : 1;
	}
 
	static double cmp(double a, double b) {
		return sign(a - b);
	}
 
	double get() {
		Arrays.fill(d1, 0);
		Arrays.fill(d2, 0);
		int cnt = 1;
		for (int i = 1; i < a.length - 1; i++) {
			if (sign(a[i].x) <= 0 || sign(a[i].y) <= 0
					|| cmp(a[i].x, a[a.length - 1].x) >= 0)
				continue;
			a[cnt++] = a[i];
		}
		a[cnt++] = a[a.length - 1];
		ByX cmp = new ByX();
		Arrays.sort(a, 1, cnt - 1, cmp);
		if (cnt == 2)
			return 0;
		Arrays.fill(d1, Double.NEGATIVE_INFINITY);
		Arrays.fill(d2, Double.NEGATIVE_INFINITY);
		d1[0] = 0;
		for (int i = 1; i < cnt; i++) {
			Point high = new Point(0, 1);
			boolean waslow = false;
			for (int j = i - 1; j >= 0; j--) {
				if (cmp(a[j].x, a[i].x) == 0)
					break;
				if (cmp(a[j].y, a[i].y) == 0) {
					waslow = true;
					continue;
				}
				if (cmp(a[j].y, a[i].y) > 0) {
					if (waslow)
						continue;
					Point v = a[j].sub(a[i]);
					if (sign(high.vect(v)) < 0)
						continue;
					high = v;
					double xx = a[i].x - a[j].x;
					double area = (a[j].y + a[i].y) * xx / 2;
					d1[i] = Math.max(d1[i], d2[j] + area);
				} else {
					waslow = true;
					Point v = a[j].sub(a[i]);
					if (sign(high.vect(v)) < 0)
						continue;
					high = v;
					double xx = a[i].x - a[j].x;
					double area = (a[j].y + a[i].y) * xx / 2;
					d2[i] = Math.max(d2[i], d1[j] + area);
				}
			}
		}
		return d1[cnt - 1];
	}
 
	private void solve2() throws IOException {
		int n = nextInt();
		Point[] p = new Point[n];
		for (int i = 0; i < n; i++) {
			p[i] = new Point(nextInt(), nextInt());
		}
		a = new Point[n];
		d1 = new double[n];
		d2 = new double[n];
		double res = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				a[0] = new Point(0, 0);
				Point vector = p[j].sub(p[i]);
				a[n - 1] = vector;
				vector = new Point(vector.x, -vector.y);
				vector = vector.norm();
				a[n - 1] = a[n - 1].mul(vector);
				int cnt = 0;
				for (int j2 = 0; j2 < n; j2++) {
					if (j2 == i || j2 == j)
						continue;
					a[++cnt] = p[j2].sub(p[i]).mul(vector);
				}
				res = Math.max(res, get());
				// System.err.println(Arrays.toString(a));
			}
		}
		out.printf(Locale.US, "%.1f\n", res);
	}
 
	public static void main(String[] args) {
		new Main().run();
	}
 
	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;
 
	public void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);
			st = new StringTokenizer("");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(239);
		}
	}
 
	String nextToken() throws IOException {
		while (!st.hasMoreTokens()) {
			String line = br.readLine();
			if (line == null) {
				eof = true;
				line = "0";
			}
			st = new StringTokenizer(line);
		}
		return st.nextToken();
	}
 
	int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}
 
	long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}
 
	double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}
} 