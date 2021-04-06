import java.io.*;
import java.util.*;

// https://www.codechef.com/viewsolution/15742894 (dukkha)
class LKYEDGE {
	static final int N = 10000;
	static class E {
		int h, i, j, cnt, sum;
		E(int h, int i, int j) {
			this.h = h; this.i = i; this.j = j;
		}
	}
	static E[] ee;
	static int[] ij;
	static int[] hh = new int[N];
	static int[] pp = new int[N];
	static int[] tt = new int[N];
	static int[] cc = new int[N];
	static boolean[] marked = new boolean[N];
	static void initv(int i) {
		hh[i] = pp[i] = tt[i] = cc[i] = -1;
	}
	static int find_tree(int i) {
		return tt[i] < 0 ? i : (tt[i] = find_tree(tt[i]));
	}	
	static int find_cycle(int i) {
		return cc[i] < 0 ? i : (cc[i] = find_cycle(cc[i]));
	}
	static void link(int h, int i, int j) {
		j = find_cycle(j);
		while (i >= 0) {
			i = find_cycle(i);
			int i_ = pp[i];
			int h_ = hh[i];
			pp[i] = j;
			hh[i] = h;
			j = i;
			i = i_;
			h = h_;
		}
	}
	static boolean join_tree(E e) {
		int i = find_tree(e.i);
		int j = find_tree(e.j);
		if (i == j)
			return true;
		if (tt[i] > tt[j]) {
			tt[i] = j;
			link(e.h, e.j, e.i);
		} else {
			if (tt[i] == tt[j])
				tt[i]--;
			tt[j] = i;
			link(e.h, e.i, e.j);
		}
		return false;
	}
	static void join_cycle(int k) {
		int i = find_cycle(ij[--k]);
		while (k-- > 0) {
			int j = find_cycle(ij[k]);
			if (cc[i] > cc[j]) {
				cc[i] = j;
				i = j;
			} else {
				if (cc[i] == cc[j])
					cc[i]--;
				cc[j] = i;
			}
		}
	}
	static int lca(E e) {
		int i = find_cycle(e.i);
		int j = find_cycle(e.j);
		marked[i] = marked[j] = true;
		int a = -1;
		while (true) {
			if (i >= 0) {
				i = pp[i];
				if (i >= 0) {
					i = find_cycle(i);
					if (marked[i]) {
						a = i;
						break;
					}
					marked[i] = true;
				}
			}
			if (j >= 0) {
				j = pp[j];
				if (j >= 0) {
					j = find_cycle(j);
					if (marked[j]) {
						a = j;
						break;
					}
					marked[j] = true;
				}
			}
		}
		for (i = e.i; i >= 0 && marked[i = find_cycle(i)]; i = pp[i])
			marked[i] = false;
		for (j = e.j; j >= 0 && marked[j = find_cycle(j)]; j = pp[j])
			marked[j] = false;
		return a;
	}
	static void walk_tree(E e, int cnt) {
		if (e.cnt == 0)
			e.cnt = cnt;
		int i = find_cycle(e.i);
		int j = find_cycle(e.j);
		if (i == j)
			return;
		int a = lca(e);
		int k = 0;
		ij[k++] = a;
		while (i != a) {
			ij[k++] = i;
			int h = hh[i];
			if (ee[h].cnt == 0)
				ee[h].cnt = cnt;
			i = find_cycle(pp[i]);
		}
		while (j != a) {
			ij[k++] = j;
			int h = hh[j];
			if (ee[h].cnt == 0)
				ee[h].cnt = cnt;
			j = find_cycle(pp[j]);
		}
		join_cycle(k);
		int c = find_cycle(a);
		if (c != a) {
			hh[c] = hh[a];
			pp[c] = pp[a];
		}
	}
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(System.out);
		int t = Integer.parseInt(br.readLine());
		while (t-- > 0) {
			int m = Integer.parseInt(br.readLine());
			ee = new E[m];
			for (int h = 0; h < m; h++) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				int i = Integer.parseInt(st.nextToken()) - 1;
				int j = Integer.parseInt(st.nextToken()) - 1;
				ee[h] = new E(h, i, j);
			}
			ij = new int[m];
			for (int g = 0; g < m; g++) {
				for (int h = g; h < m; h++) {
					initv(ee[h].i);
					initv(ee[h].j);
				}
				for (int h = g; h < m; h++)
					if (join_tree(ee[h]))
						walk_tree(ee[h], m - h);
				for (int h = g; h < m; h++) {
					ee[h].sum += ee[h].cnt;
					ee[h].cnt = 0;
				}
			}
			StringBuilder sb = new StringBuilder();
			for (int h = 0; h < m; h++)
				sb.append(ee[h].sum + " ");
			pw.println(sb);
		}
		pw.close();
	}
}
