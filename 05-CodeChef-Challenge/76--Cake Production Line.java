import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Locale;
import java.util.Random;
 
public final class Main {
 
	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}
 
	static boolean file = false;
	static boolean isLocal = false;
 
	private static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}
 
	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("f:\\var\\tmp\\in.txt")
			// : System.in);
 
			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("f:\\var\\tmp\\in.txt")
			// : System.in));
 
			in = new StreamTokenizer(new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("f:\\var\\tmp\\in.txt")
							: System.in)));
		} catch (final FileNotFoundException e) {
			e.printStackTrace();
		}
	}
 
	static PrintWriter out;
	static {
		try {
			out = file ? new PrintWriter(
					new FileWriter("f:\\var\\tmp\\out.txt")) : new PrintWriter(
					System.out);
		} catch (final IOException e) {
			e.printStackTrace();
		}
	}
 
	static PrintStream err;
	private static final Random R = new Random(129);
	private static final int[][] shouldMultiSwap_NEW_ROWS = new int[256][256];
 
	private static final int[][][] VARIANTS = {
			{},
			{},
			{},
 
			{ { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 } },
 
			{ { 1, 2, 3, 0 }, { 1, 3, 0, 2 }, { 1, 3, 2, 0 }, { 2, 0, 3, 1 },
					{ 2, 1, 3, 0 }, { 2, 3, 0, 1 }, { 2, 3, 1, 0 },
					{ 3, 0, 1, 2 }, { 3, 0, 2, 1 }, { 3, 1, 0, 2 },
					{ 3, 1, 2, 0 }, { 3, 2, 0, 1 }, { 3, 2, 1, 0 } },
 
			{ { 1, 0, 2, 4, 3 }, { 1, 0, 3, 4, 2 }, { 2, 3, 4, 0, 1 },
					{ 1, 2, 3, 4, 0 }, { 3, 4, 0, 1, 2 }, { 2, 0, 1, 4, 3 },
					{ 4, 0, 1, 2, 3 }, { 1, 0, 4, 3, 2 }, { 1, 0, 4, 2, 3 },
					{ 2, 3, 4, 1, 0 }, { 1, 2, 4, 3, 0 }, { 4, 1, 2, 3, 0 },
					{ 1, 4, 2, 3, 0 }, { 1, 2, 0, 4, 3 }, { 3, 4, 1, 2, 0 },
					{ 1, 3, 4, 2, 0 }, { 2, 0, 3, 4, 1 }, { 3, 0, 4, 1, 2 },
					{ 3, 4, 2, 0, 1 }, { 2, 4, 3, 0, 1 }, { 1, 3, 4, 0, 2 },
					{ 3, 4, 1, 0, 2 }, { 3, 4, 0, 2, 1 }, { 4, 3, 0, 1, 2 },
					{ 2, 4, 0, 1, 3 }, { 4, 0, 1, 3, 2 }, { 1, 4, 3, 2, 0 },
					{ 1, 3, 2, 4, 0 }, { 2, 1, 0, 4, 3 }, { 3, 2, 4, 0, 1 },
					{ 2, 4, 1, 3, 0 }, { 3, 4, 2, 1, 0 }, { 2, 3, 0, 4, 1 },
					{ 4, 0, 2, 3, 1 }, { 4, 1, 0, 2, 3 }, { 4, 0, 3, 1, 2 },
					{ 4, 2, 3, 0, 1 }, { 2, 4, 3, 1, 0 }, { 2, 4, 0, 3, 1 },
					{ 4, 0, 2, 1, 3 }, { 4, 1, 2, 0, 3 }, { 2, 0, 4, 3, 1 },
					{ 2, 1, 4, 3, 0 }, { 2, 1, 3, 4, 0 }, { 3, 0, 1, 4, 2 },
					{ 2, 3, 1, 4, 0 }, { 1, 4, 3, 0, 2 }, { 3, 1, 2, 4, 0 },
					{ 4, 1, 3, 2, 0 }, { 3, 0, 4, 2, 1 }, { 4, 1, 0, 3, 2 },
					{ 4, 0, 3, 2, 1 }, { 4, 2, 0, 1, 3 }, { 4, 3, 2, 0, 1 },
					{ 3, 2, 4, 1, 0 }, { 2, 4, 1, 0, 3 }, { 4, 3, 1, 2, 0 },
					{ 1, 4, 0, 2, 3 },
					{ 1, 4, 2, 0, 3 },
					{ 3, 0, 2, 4, 1 },
					// { 3, 1, 4, 2, 0 }, { 4, 2, 1, 3, 0 }, { 4, 2, 3, 1, 0 },
					// { 4, 1, 3, 0, 2 }, { 1, 4, 0, 3, 2 }, { 4, 3, 2, 1, 0 },
					// { 3, 1, 4, 0, 2 }, { 4, 3, 1, 0, 2 }, { 3, 2, 1, 4, 0 },
					{ 4, 2, 0, 3, 1 }, { 2, 0, 4, 1, 3 }, { 1, 2, 4, 0, 3 },
					{ 4, 3, 0, 2, 1 }, { 4, 2, 1, 0, 3 } },
 
			{ { 1, 0, 2, 3, 5, 4 }, { 1, 0, 2, 4, 5, 3 }, { 2, 0, 1, 3, 5, 4 },
					{ 1, 0, 2, 5, 3, 4 }, { 1, 0, 2, 5, 4, 3 },
					{ 1, 0, 3, 2, 5, 4 }, { 1, 2, 0, 3, 5, 4 },
					{ 2, 3, 4, 5, 0, 1 }, { 1, 0, 4, 5, 2, 3 },
					{ 1, 0, 3, 4, 5, 2 }, { 2, 1, 0, 3, 5, 4 },
					{ 5, 0, 1, 2, 3, 4 }, { 1, 2, 3, 4, 5, 0 },
					{ 1, 5, 2, 3, 4, 0 }, { 4, 5, 0, 1, 2, 3 },
					{ 5, 1, 2, 3, 4, 0 }, { 5, 1, 2, 3, 4, 0 },
					{ 1, 2, 5, 3, 4, 0 }, { 1, 0, 3, 5, 4, 2 },
					{ 3, 0, 1, 2, 5, 4 }, { 1, 0, 5, 3, 4, 2 },
					{ 1, 2, 3, 5, 4, 0 }, { 1, 0, 5, 4, 2, 3 },
					{ 1, 0, 4, 5, 3, 2 }, { 2, 3, 4, 5, 1, 0 },
					{ 3, 4, 5, 0, 1, 2 }, { 1, 0, 5, 2, 3, 4 },
					{ 2, 0, 1, 4, 5, 3 }, { 2, 3, 5, 4, 0, 1 },
					{ 5, 0, 1, 2, 4, 3 }, { 1, 3, 4, 5, 2, 0 },
					{ 3, 4, 5, 2, 0, 1 }, { 1, 2, 4, 5, 3, 0 },
					{ 1, 0, 4, 3, 5, 2 }, { 3, 4, 5, 1, 2, 0 },
					{ 2, 3, 0, 1, 5, 4 }, { 3, 4, 5, 1, 0, 2 },
					{ 4, 5, 1, 2, 3, 0 }, { 3, 5, 4, 0, 1, 2 },
					{ 3, 0, 4, 5, 1, 2 }, { 2, 5, 3, 4, 0, 1 },
					{ 2, 3, 5, 4, 1, 0 }, { 2, 0, 1, 5, 4, 3 },
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)),
					unBox(randomPermutation(6)), unBox(randomPermutation(6)), },
 
			{ { 6, 1, 2, 3, 4, 5, 0 }, { 5, 6, 2, 3, 4, 0, 1 }, },
 
			{ { 7, 1, 2, 3, 4, 5, 6, 0 }, { 6, 7, 2, 3, 4, 5, 0, 1 } },
 
	};
 
	private static final int[] multiSwap_TMP = new int[256];
	static {
		err = System.err;
	}
 
	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {
		try {
			final long startTime = System.nanoTime();
			final long t = nextInt();
			if (t != 30) {
				// throw new RuntimeException();
			}
			for (long i = 0; i < t; ++i) {
				solve(i + 1);
				if (file) {
					err.println(i + 1 + "/" + t);
				}
				if (!file) {
					out.flush();
				}
			}
			if (isLocal) {
				err.println(String.format("Completed after %d ms.",
						(System.nanoTime() - startTime) / 1000000));
			}
		} finally {
			out.flush();
		}
	}
 
	private static void solve(final long testId) throws IOException {
		final int n = nextInt(), m = nextInt();
 
		final int[] w = new int[n];
		final int[][] t = new int[n][];
 
		for (int i = 0; i < n; ++i) {
			w[i] = nextInt();
			t[i] = new int[m];
			for (int j = 0; j < m; ++j) {
				t[i][j] = nextInt();
			}
		}
 
		solve(n, m, w, t, testId);
	}
 
	private static void solve(final int n, final int m, final int[] w,
			final int[][] t, final long testId) {
 
		// final Integer[] permutation1 = sortByWeight(n, w, 1, t, m);
		final Integer[] permutation2 = sortByWeight(n, w, -1, t, m);
 
		final int[] permutation = unBox(// randomPermutation(n);
		// calcScore(n, m, w, t, permutation1) < calcScore(n, m, w, t,
		// permutation2) ? permutation1 :
		permutation2);
 
		bubbleSort(n, m, w, t, permutation);
 
		/*
		 * // permutation = randomPermutation(n); long bestScore =
		 * Long.MAX_VALUE; for (int k = 0; k < 10; ++k) { final Integer[]
		 * candidate = randomPermutation(n); bubbleSort(n, m, w, t, candidate);
		 * final long candidateScore = calcScore(n, m, w, t, candidate); if
		 * (candidateScore < bestScore) { bestScore = candidateScore;
		 * permutation = candidate; } }
		 */
 
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				out.print((j == 0 ? "" : " ") + (permutation[j] + 1));
			}
			out.println();
		}
	}
 
	private static int[] unBox(final Integer[] permutation) {
		final int[] ans = new int[permutation.length];
		for (int i = 0; i < ans.length; ++i) {
			ans[i] = permutation[i];
		}
		return ans;
	}
 
	private static Integer[] randomPermutation(final int n) {
 
		final Integer[] ans = normalPermutation(n);
		// err.println(Arrays.toString(ans));
		for (int i = 0; i < n - 1; ++i) {
			final int other = i + R.nextInt(n - i);
			final int q = ans[other];
			ans[other] = ans[i];
			ans[i] = q;
		}
		// err.println(Arrays.toString(ans));
		return ans;
	}
 
	private static void bubbleSort(final int n, final int m, final int[] w,
			final int[][] t, final int[] permutation) {
 
		final int[][] times = new int[n][m];
		for (int i = 0; i < m; ++i) {
			times[0][i] = t[permutation[0]][i];
		}
 
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				times[i][j] = times[i - 1][j] + t[permutation[i]][j];
			}
		}
 
		boolean improved;
		final boolean possible[][] = new boolean[VARIANTS.length][n];
 
		for (final boolean[] q : possible) {
			Arrays.fill(q, true);
		}
 
		final int[] maxes = new int[n];
		for (int i = 0; i < n; ++i) {
			maxes[i] = max(times[i], m);
		}
 
		do {
			improved = false;
 
			for (int first = n - 2; first >= 0; --first) {
				if (possible[2][first]
						&& shouldSwap(n, m, w, t, permutation, first, times,
								maxes)) {
 
					if (isLocal) {
						err.println(String.format(
								"Swapping %d (=%d) with %d (=%d)", first + 1,
								permutation[first] + 1, first + 2,
								permutation[first + 1] + 1));
					}
 
					swap(n, m, w, t, permutation, first, times, maxes);
 
					improved = true;
					updatePossible(possible, first, 2, n);
				}
 
				possible[2][first] = false;
			}
 
			for (int kkk = 3; kkk < VARIANTS.length; ++kkk) {
				if (!improved) {
					for (int first = n - kkk; first >= 0; --first) {
 
						if (possible[kkk][first]) {
							for (final int[] variant : VARIANTS[kkk]) {
								if (shouldMultiSwap(n, m, w, t, permutation,
										first, times, variant, false, maxes)) {
									multiSwap(n, m, w, t, permutation, first,
											times, variant, maxes);
									improved = true;
									updatePossible(possible, first, kkk, n);
									break;
								}
							}
 
							possible[kkk][first] = false;
						}
					}
				}
			}
		} while (improved);
	}
 
	private static void updatePossible(final boolean[][] possible,
			final int updatedFirst, final int updatedLength, final int n) {
 
		for (int l = 2; l < possible.length; ++l) {
 
			final int start = Math.max(updatedFirst - l + 1, 0);
			final int finish = Math.min(updatedFirst + updatedLength, n);
			for (int first = start; first < finish; ++first) {
 
				possible[l][first] = true;
			}
 
			// Arrays.fill(possible[l], true);
		}
	}
 
	/**
	 * Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�ÂºÃ�ï¿½Ã�Â»Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�Â¸Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�ÂµÃ�ï¿½Ã�Â»Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�Â½Ã�ï¿½Ã�Â¾.
	 * 
	 * @param a
	 * @param from
	 * @param to
	 */
	private static void reverse(final int[] a, final int from, final int to) {
		for (int l = from, r = to; l < r; ++l, --r) {
			final int t = a[r];
			a[r] = a[l];
			a[l] = t;
		}
	}
 
	private static void multiSwap(final int n, final int m, final int[] w,
			final int[][] t, final int[] permutation, final int first,
			final int[][] times, final int[] variant, final int[] maxes) {
 
		final int rowCount = variant.length;
 
		for (int i = rowCount - 2; i >= 0; --i) {
			recalcPreviousRow(times[first + i], times[first + i + 1],
					t[permutation[first + variant[i + 1]]], m);
			maxes[first + i] = max(times[first + i], m);
		}
 
		for (int i = 0; i < rowCount; ++i) {
			multiSwap_TMP[i] = permutation[first + i];
		}
 
		for (int i = 0; i < rowCount; ++i) {
			permutation[first + i] = multiSwap_TMP[variant[i]];
		}
	}
 
	private static boolean shouldMultiSwap(final int n, final int m,
			final int[] w, final int[][] t, final int[] permutation,
			final int first, final int[][] times, final int[] variant,
			final boolean debug, final int[] maxes) {
 
		final int rowCount = variant.length;
 
		final int[] preLastRow = shouldMultiSwap_NEW_ROWS[rowCount - 2];
		final int[] lastRow = times[first + rowCount - 1];
		final int[] lastT = t[permutation[first + variant[rowCount - 1]]];
		recalcPreviousRow(preLastRow, lastRow, lastT, m);
 
		for (int i = rowCount - 3; i >= 0; --i) {
			final int[] prevRow = shouldMultiSwap_NEW_ROWS[i];
			final int[] curRow = shouldMultiSwap_NEW_ROWS[i + 1];
			final int[] curT = t[permutation[first + variant[i + 1]]];
			recalcPreviousRow(prevRow, curRow, curT, m);
		}
 
		long oldScore = 0;
 
		for (int i = 0; i < rowCount; ++i) {
			final long mx = maxes[first + i];
			oldScore += mx * w[permutation[first + i]];
		}
 
		long newScore = 0;
		for (int i = 0; i < rowCount; ++i) {
			final long mx = i == rowCount - 1 ? maxes[first + i] : max(
					shouldMultiSwap_NEW_ROWS[i], m);
			newScore += mx * w[permutation[first + variant[i]]];
		}
 
		final long delta = newScore - oldScore;
 
		if (debug) {
			err.println(String
					.format("shouldMultiswap(permutation = %s, first = %d, variant = %s), delta = %d",
							Arrays.toString(permutation), first,
							Arrays.toString(variant), delta));
		}
 
		return delta < 0;
	}
 
	private static int max(final int[] q, final int size) {
 
		int mx = Integer.MIN_VALUE;
 
		for (int j = 0; j < size; ++j) {
			mx = Math.max(mx, q[j]);
		}
 
		return mx;
	}
 
	private static void recalcPreviousRow(final int[] previousPartial,
			final int[] currentPartial, final int[] currentTimes, final int m) {
 
		for (int i = 0; i < m; ++i) {
			previousPartial[i] = currentPartial[i] - currentTimes[i];
		}
 
	}
 
	/**
	 * Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�Â¾Ã�ï¿½Ã�Â´Ã�ï¿½Ã�Â¸Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�Â¸Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�Â¸Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã¯Â¿Â½Ã�ï¿½Ã�ÂµÃ�ï¿½Ã¯Â¿Â½ permutation Ã�ï¿½Ã�Â¸ times
	 * 
	 * @param n
	 * @param m
	 * @param w
	 * @param t
	 * @param permutation
	 * @param first
	 * @param times
	 */
	private static void swap(final int n, final int m, final int[] w,
			final int[][] t, final int[] permutation, final int first,
			final int[][] times, final int[] maxes) {
 
		final int second = first + 1;
 
		recalcPreviousRow(times[first], times[second], t[permutation[first]], m);
		maxes[first] = max(times[first], m);
 
		final int tmp = permutation[first];
		permutation[first] = permutation[second];
		permutation[second] = tmp;
 
	}
 
	private static boolean shouldSwap(final int n, final int m, final int[] w,
			final int[][] t, final int[] permutation, final int first,
			final int[][] times, final int[] maxes) {
 
		final int second = first + 1;
 
		final int max2 = maxes[second];
 
		final int oldMax1 = maxes[first];
 
		final int[] sTimes = times[second];
		final int[] tFirst = t[permutation[first]];
 
		int newMax1 = -1;
		for (int i = 0; i < m; ++i) {
			newMax1 = Math.max(newMax1, sTimes[i] - tFirst[i]);
		}
 
		final long w1 = w[permutation[first]], w2 = w[permutation[second]];
		final long delta = max2 * (w1 - w2) + newMax1 * w2 - oldMax1 * w1;
 
		// err.println(String.format("delta for %s when swapping %d and %d is %d",
		// Arrays.toString(permutation), first, second, delta));
 
		return delta < 0;
	}
 
	private static long calcScore(final int n, final int m, final int[] w,
			final int[][] t, final Integer[] permutation) {
 
		final int[] times = new int[m];
		Arrays.fill(times, 0);
 
		long score = 0;
 
		for (int i = 0; i < n; ++i) {
			int mx = -1;
			for (int j = 0; j < m; ++j) {
				times[j] += t[permutation[i]][j];
				mx = Math.max(mx, times[j]);
			}
			score += mx * w[permutation[i]];
		}
 
		return score;
	}
 
	private static Integer[] sortByWeight(final int n, final int[] ow,
			final int multiplierForEqualWeight, final int[][] t, final int m) {
 
		final Integer[] permutation = normalPermutation(n);
 
		// final int[] tmx = new int[n];
		final int[] tsum = new int[n];
		// final long[] tsum2 = new long[n];
 
		// Arrays.fill(tmx, Integer.MIN_VALUE);
		Arrays.fill(tsum, 0);
		// Arrays.fill(tsum2, 0);
 
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				// tmx[i] = Math.max(tmx[i], t[i][j]);
				tsum[i] += t[i][j];
				// tsum2[i] += t[i][j] * t[i][j];
			}
		}
 
		final double[] noise = new double[n];
		for (int i = 0; i < n; ++i) {
			noise[i] = 1.0 * ow[i] / tsum[i];
		}
 
		Arrays.sort(permutation, new Comparator<Integer>() {
			public int compare(final Integer o1, final Integer o2) {
				return noise[o1] > noise[o2] ? -1 : noise[o1] < noise[o2] ? 1
						: multiplierForEqualWeight * o1.compareTo(o2);
			}
		});
 
		return permutation;
	}
 
	private static Integer[] normalPermutation(final int n) {
		final Integer[] permutation = new Integer[n];
		for (int i = 0; i < n; ++i) {
			permutation[i] = i;
		}
		return permutation;
	}
}