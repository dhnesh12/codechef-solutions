import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	static Scanner in;
	static PrintWriter out;
	static String INPUT = "";
	
	static void solve()
	{
		int h = ni();
		int w = ni();
		char[][] r = create(h, w);
		char[][] r2 = create(w, h);
		
		if(count(r) < count(r2)) {
			for(int i = 0;i < h;i++) {
				for(int j = 0;j < w;j++) {
					r[i][j] = r2[j][i];
				}
			}
		}
		for(int i = 0;i < h;i++){
			out.println(new String(r[i]));
		}
		out.println();
	}
	
	static int count(char[][] x)
	{
		int ct = 0;
		for(int i = 0;i < x.length;i++) {
			for(int j = 0;j < x[0].length;j++) {
				if(x[i][j] == '#')ct++;
			}
		}
		return ct;
	}
	
	static char[][] create(int h, int w)
	{
		char[][] c = new char[h][w];
		for(int i = 0;i < h;i++) {
			Arrays.fill(c[i], '.');
		}
		if(w == 1) {
			for(int i = 0;i < h;i++) {
				c[i][0] = '#';
			}
		}else if(w == 2) {
			for(int i = 0;i < h;i++) {
				c[i][0] = '#';
				if(i % 2 == 0) {
					c[i][1] = '#';
				}
			}
		}else if(w == 3) {
			for(int i = 0;i < h;i++) {
				c[i][0] = '#';
				c[i][2] = '#';
			}
			c[0][1] = '#';
		}else if(h <= 3){
			return c;
		}else {
			int hh = h - h%2;
			int ww = w - (w-1)%3;
			for(int j = 0;j < ww;j++) {
				c[0][j] = '#';
				c[hh-1][j] = '#';
			}
			c[0][0] = '.';
			c[hh-1][ww-2] = '.';
			for(int i = 1;i < hh-1;i++) {
				for(int j = 0;j < ww;j++) {
					if(i == 1) {
						if(j % 2 == 1 || j == 0) {
							c[i][j] = '#';
						}
					}else if(i == hh-2) {
						if(j % 2 == 0 || j == ww-1) {
							c[i][j] = '#';
						}
					}else if(i % 2 == 0) {
						if(j % 6 == 1 || j % 6 == 5) {
						}else {
							c[i][j] = '#';
						}
					}else {
						if(j % 6 == 2 || j % 6 == 4) {
						}else {
							c[i][j] = '#';
						}
					}
				}
			}
			for(int i = hh;i < h;i++) {
				for(int j = 0;j < ww-2;j+=2) {
					c[i][j] = '#';
				}
				c[i][ww-1] = '#';
				if(ww-3 >= 0 && c[i][ww-3] == '.')c[i][ww-2] = '#';
			}
			for(int i = ww;i < w;i++) {
				for(int j = 0;j < h;j+=2) {
					c[j][i] = '#';
				}
			}
			if(ww % 6 == 1) {
				c[1][ww-2] = '.';
				c[1][ww-1] = '#';
			}
		}
		return c;
	}
	
	public static void main(String[] args) throws Exception
	{
		in = INPUT.isEmpty() ? new Scanner(System.in) : new Scanner(INPUT);
		out = new PrintWriter(System.out);

		int T = ni();
		for(int i = 0;i < T;i++){
			solve();
		}
		out.flush();
	}
	
	static int ni() { return Integer.parseInt(in.next()); }
	static long nl() { return Long.parseLong(in.next()); }
	static void tr(Object... o) { if(INPUT.length() != 0)System.out.println(Arrays.deepToString(o)); }
}
