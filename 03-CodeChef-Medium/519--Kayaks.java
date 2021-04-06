/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st ;
		int n = Integer.parseInt(br.readLine());
		int[] s = new int[n];
		int[] w = new int[n];
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			w[i] = Integer.parseInt(st.nextToken()) + 10;
			s[i] = Integer.parseInt(st.nextToken());
		}
		double max = (100.0 + 100.0) / (120.0);
		double min = (50.0 + 50.0) / (220.0);
		double mid = 0.0;
		double eps = 1e-8;
		while (max - min > eps) {
			mid = (max + min) / 2;
			if (isPossible(mid, w, s)) {
				min = mid;
			} else {
				max = mid;
			}
		}
		System.out.printf("%.7f",mid);
	}

	static boolean isPossible(double mid, int[] w, int[] s) {
		double[] delta = new double[w.length];
		for (int i = 0; i < w.length; i++) {
			delta[i] = s[i] - mid * w[i];
		}
		Arrays.sort(delta);
		for (int i = 0; i < delta.length; i++) {
			if (delta[i] + delta[delta.length - 1 - i] < 0)
				return false;
		}
		return true;
	}
}
