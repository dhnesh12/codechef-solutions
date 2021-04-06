import java.io.*;
import java.math.*;
import java.util.*;

 class Codechef {
	
	public static void main(String[] args) {
	    Scanner fs   =  new Scanner(System.in);
		int test = fs.nextInt();
//		int test = 1;
		for (int cases = 0; cases < test; cases++) {
			int n = fs.nextInt();
			int a[] = new int[n];
			int b[] = new int[n];
			int c[] = new int[n];
			for (int i = 0; i < n; i++) {
				a[i] = fs.nextInt();
			}
			for (int i = 0; i < n; i++) {
				b[i] = fs.nextInt();
			}
			int x = 0, y = 0;
			for (int i = 0; i < n; i++) {
				x ^= a[i];
			}
			for (int i = 0; i < n; i++) {
				y ^= b[i];
			}
			int z = x ^ y;
			for (int i = 0; i < n; i++) {
				c[i] = z ^ a[i];
			}
			int d[] = Arrays.copyOf(c, n);
			Arrays.sort(b);
			Arrays.sort(d);
			if (Arrays.equals(b, d)) {
				for (int i : c) {
					System.out.print(i + " ");
				}
				System.out.print("\n");
			} else {
				System.out.print(-1 + "\n");
			}
			
		}

	}

}
