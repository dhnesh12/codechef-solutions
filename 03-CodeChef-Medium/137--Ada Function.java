import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Deque;
import java.util.InputMismatchException;
import java.util.List;
class ADAFUN
{
	InputStream is;
	PrintWriter out;
	String INPUT = "";
	long[][] ai;
	void solve()
	{
		for(int T = ni();T > 0;T--)
		{
			int n = ni();
			long[] a = new long[n];
			for(int i = 0;i < n;i++)
			a[i] = nl();
			ai = new long[n][];
			for(int i = 0;i < n;i++)
			{
				ai[i] = new long[]{Long.reverse(a[i])>>>1, i};
			}
			Arrays.sort(ai, new Comparator<long[]>()
			{
				public int compare(long[] x, long[] y)
				{
					return Long.compare(x[0], y[0]);
				}
			});
			int[] par = new int[2*n+10];
			long[] val = new long[2*n+10];
			long[] has = new long[2*n+10];
			Arrays.fill(has, -1);
			LST lst = new LST(n+3);
			lst.setRange(n);
			int[] real = new int[n];
			for(int i = 0;i < n;i++)
			real[i] = i;
			for(int i = 0;i < n;i++)
			has[i] = a[(int)ai[i][1]];
			int gen = n;
			for(int d = 1;d <= 63;d++)
			{
				for(int j = 0;j < n;j++)
				{
					if(lst.get(j))
					{
						int ne = lst.next(j+1);
						if(ne != -1 && ai[ne][0]>>>d == ai[j][0]>>>d)
						{
							par[real[j]] = gen;
							par[real[ne]] = gen;
							val[gen] = val[real[j]] ^ val[real[ne]];
							if(has[real[j]] != -1 && has[real[ne]] != -1)
							{
								val[gen] ^= (has[real[j]] ^ has[real[ne]]) - 1;
								has[gen] = -1;
							}
							else if(has[real[j]] != -1)
							{
								has[gen] = has[real[j]];
							}
							else if(has[real[ne]] != -1)
							{
								has[gen] = has[real[ne]];
							}
							else
							{
								has[gen] = -1;
							}
							real[j] = gen;
							gen++;
							lst.unset(ne);
						}
					}
				}
			}
			par[gen-1] = -1;
			par = Arrays.copyOf(par, gen);
			int[][] ch = parentToChildren(par);
			ans = new long[n];
			dfs(gen-1, ch, val, has, 0L, new ArrayDeque<Long>());
			for(int i = 0;i < n;i++)
			{
				out.print(ans[i] + " ");
			}
			out.println();
		}
	}
	long[] ans;
	void dfs(int cur, int[][] ch, long[] val, long[] has, long cval, Deque<Long> hass)
	{
		if(ch[cur].length == 0)
		{
			long an = cval;
			long my = -1;
			for(long h : hass)
			{
				if(my == -1)
				{
					my = h;
				}
				else
				{
					an ^= (my^h)-1;
					my = -1;
				}
			}
			if(my != -1)
			an ^= my;
			ans[(int)ai[cur][1]] = an;
			return;
		}
		int l = ch[cur][0], r = ch[cur][1];
		{
			long nval = cval ^ val[r];
			if(has[r] != -1)
			hass.addFirst(has[r]);
			dfs(l, ch, val, has, nval, hass);
			if(has[r] != -1)
			hass.pollFirst();
		}
		{
			long nval = cval ^ val[l];
			if(has[l] != -1)
			hass.addFirst(has[l]);
			dfs(r, ch, val, has, nval, hass);
			if(has[l] != -1)hass.pollFirst();
		}
	}
	
	public static int[][] parentToChildren(int[] par)
	{
		int n = par.length;
		int[] ct = new int[n];
		for(int i = 0;i < n;i++){
			if(par[i] >= 0){
				ct[par[i]]++;
			}
		}
		int[][] g = new int[n][];
		for(int i = 0;i < n;i++){
			g[i] = new int[ct[i]];
		}
		for(int i = 0;i < n;i++){
			if(par[i] >= 0){
				g[par[i]][--ct[par[i]]] = i;
			}
		}
		
		return g;
	}

	
	public static class LST {
		public long[][] set;
		public int n;
//		public int size;
		
		public LST(int n) {
			this.n = n;
			int d = 1;
			for(int m = n;m > 1;m>>>=6, d++);
			
			set = new long[d][];
			for(int i = 0, m = n>>>6;i < d;i++, m>>>=6){
				set[i] = new long[m+1];
			}
//			size = 0;
		}
		
		// [0,r)
		public LST setRange(int r)
		{
			for(int i = 0;i < set.length;i++, r=r+63>>>6){
				for(int j = 0;j < r>>>6;j++){
					set[i][j] = -1L;
				}
				if((r&63) != 0)set[i][r>>>6] |= (1L<<r)-1;
			}
			return this;
		}
		
		// [0,r)
		public LST unsetRange(int r)
		{
			if(r >= 0){
				for(int i = 0;i < set.length;i++, r=r+63>>>6){
					for(int j = 0;j < r+63>>>6;j++){
						set[i][j] = 0;
					}
					if((r&63) != 0)set[i][r>>>6] &= ~((1L<<r)-1);
				}
			}
			return this;
		}
		
		public LST set(int pos)
		{
			if(pos >= 0 && pos < n){
//				if(!get(pos))size++;
				for(int i = 0;i < set.length;i++, pos>>>=6){
					set[i][pos>>>6] |= 1L<<pos;
				}
			}
			return this;
		}
		
		public LST unset(int pos)
		{
			if(pos >= 0 && pos < n){
//				if(get(pos))size--;
				for(int i = 0;i < set.length && (i == 0 || set[i-1][pos] == 0L);i++, pos>>>=6){
					set[i][pos>>>6] &= ~(1L<<pos);
				}
			}
			return this;
		}
		
		public boolean get(int pos)
		{
			return pos >= 0 && pos < n && set[0][pos>>>6]<<~pos<0;
		}
		
		public LST toggle(int pos)
		{
			return get(pos) ? unset(pos) : set(pos);
		}
		
		public int prev(int pos)
		{
			for(int i = 0;i < set.length && pos >= 0;i++, pos>>>=6, pos--){
				int pre = prev(set[i][pos>>>6], pos&63);
				if(pre != -1){
					pos = pos>>>6<<6|pre;
					while(i > 0)pos = pos<<6|63-Long.numberOfLeadingZeros(set[--i][pos]);
					return pos;
				}
			}
			return -1;
		}
		
		public int next(int pos)
		{
			for(int i = 0;i < set.length && pos>>>6 < set[i].length;i++, pos>>>=6, pos++){
				int nex = next(set[i][pos>>>6], pos&63);
				if(nex != -1){
					pos = pos>>>6<<6|nex;
					while(i > 0)pos = pos<<6|Long.numberOfTrailingZeros(set[--i][pos]);
					return pos;
				}
			}
			return -1;
		}
		
		private static int prev(long set, int n)
		{
			long h = set<<~n;
			if(h == 0L)return -1;
			return -Long.numberOfLeadingZeros(h)+n;
		}
		
		private static int next(long set, int n)
		{
			long h = set>>>n;
			if(h == 0L)return -1;
			return Long.numberOfTrailingZeros(h)+n;
		}
		
		@Override
		public String toString()
		{
			List<Integer> list = new ArrayList<Integer>();
			for(int pos = next(0);pos != -1;pos = next(pos+1)){
				list.add(pos);
			}
			return list.toString();
		}
	}

	
	void run() throws Exception
	{
		is = INPUT.isEmpty() ? System.in : new ByteArrayInputStream(INPUT.getBytes());
		out = new PrintWriter(System.out);
		
		long s = System.currentTimeMillis();
		solve();
		out.flush();
		if(!INPUT.isEmpty())tr(System.currentTimeMillis()-s+"ms");
	}
	
	public static void main(String[] args) throws Exception { new ADAFUN().run(); }
	
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