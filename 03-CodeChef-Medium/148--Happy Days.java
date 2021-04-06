import java.io.*;
import java.math.*;

class HAPPY
{
	static int t;
	static int n;
	static char[][] B;
	static char[][] mem;
	static int p;
	static int[] Efir;
	static int[] Esec;
	static int[] par;
	static int[] siz;
	static BigInteger[] ways;
	static BigInteger[][] M;

	static int getPar(int x) {
		if (par[x] == x) return x;
		par[x] = getPar(par[x]);
		return par[x];
	}

	static boolean unionSet(int a, int b)
	{
		a = getPar(a); b = getPar(b);
		if (a == b) return false;
		if (siz[a] >= siz[b]) { siz[a] += siz[b]; par[b] = a; }
		else { siz[b] += siz[a]; par[a] = b; }
		return true;
	}

	static boolean Check()
	{
		par = new int[n]; siz = new int[n];
		for (int i = 0; i < n; i++) {
			par[i] = i; siz[i] = 1;
		}
		for (int i = 0; i < p; i++)
			if (!unionSet(Efir[i], Esec[i])) return false;
		return true;
	}

	static void Swap(int r1, int r2)
	{
		BigInteger tmp;
		for (int i = 0; i < n - 1; i++) {
			tmp = M[r1][i]; M[r1][i] = M[r2][i]; M[r2][i] = tmp;
		}
	}

	static BigInteger Eliminate(int r1, int r2, int c)
	{
		BigInteger g = M[r1][c].gcd(M[r2][c]);
		BigInteger mult1 = M[r2][c].divide(g);
		BigInteger mult2 = M[r1][c].divide(g);
		for (int i = c; i < n - 1; i++)
			M[r2][i] = M[r2][i].multiply(mult2).subtract(M[r1][i].multiply(mult1));
		return mult2;
	}

	static BigInteger Solve()
	{
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - 1; j++)
				if (i == j) {
					int cnt = 0;
					for (int k = 0; k < n; k++)
						if (B[i][k] == '1') cnt++;
					M[i][j] = BigInteger.valueOf(cnt);
				} else M[i][j] = BigInteger.valueOf(-(B[i][j] - '0'));
	    BigInteger dv = BigInteger.ONE;
		for (int i = 0; i < n - 1; i++) {
			int r = i;
			while (r < n - 1)
				if (M[r][i].compareTo(BigInteger.ZERO) == 0) r++;
				else break;
			if (r >= n - 1) return BigInteger.ZERO;
			if (r != i) { Swap(r, i); dv = dv.negate(); }
			r++;
			while (r < n - 1) {
				if (M[r][i].compareTo(BigInteger.ZERO) != 0) dv = dv.multiply(Eliminate(i, r, i));
				r++;
			} 
		}
		BigInteger res = BigInteger.ONE;
		for (int i = 0; i < n - 1; i++)
			res = res.multiply(M[i][i]);
		return res.divide(dv);
	}

	public static void main (String[] args) throws java.lang.Exception
	{
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter fout = new PrintWriter(new OutputStreamWriter(System.out), true);
		t = Integer.parseInt(fin.readLine());
		while (t-- > 0) {
			n = Integer.parseInt(fin.readLine());
			B = new char[n][n]; mem = new char[n][n];
			for (int i = 0; i < n; i++) {
				B[i] = fin.readLine().toCharArray();
				B[i][i] = '0';
			}
			p = Integer.parseInt(fin.readLine());
			Efir = new int[p]; Esec = new int[p];
			for (int i = 0; i < p; i++) {
				String[] tmp = fin.readLine().split(" ");
				Efir[i] = Integer.parseInt(tmp[0]) - 1;
				Esec[i] = Integer.parseInt(tmp[1]) - 1;
			}
			if (!Check()) { fout.println("0"); continue; }
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					mem[i][j] = B[i][j];
			ways = new BigInteger[1 << p];
			M = new BigInteger[n][n];
			for (int i = (1 << p) - 1; i >= 0; i--) {
				for (int j = 0; j < p; j++) if ((i & (1 << j)) != 0)
					B[Efir[j]][Esec[j]] = B[Esec[j]][Efir[j]] = '0';
				ways[i] = Solve();
				for (int j = 0; j < 1 << p; j++)
					if ((j & i) == i && i != j) ways[i] = ways[i].subtract(ways[j]);
				for (int j = 0; j < n; j++)
					for (int k = 0; k < n; k++)
						B[j][k] = mem[j][k];
			}
			fout.println(ways[0]);
		}
	}
}
