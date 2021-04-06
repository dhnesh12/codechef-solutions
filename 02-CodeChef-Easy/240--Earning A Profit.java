
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;


class ClgLf {
	static StringBuilder solution = new StringBuilder();
	static PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) {
		int t = nextInt();
		while(t-- != 0)
		{
			StringTokenizer st = new StringTokenizer(nextLine());
			int N = Integer.parseInt(st.nextToken());
			int A = Integer.parseInt(st.nextToken());
			
			long[] coin = new long[N+1];
			long[] sum = new long[N+1];
			long[] d = new long[N+1];
			long max ,min;
			int i = 0;
			sum[i] = 0;
			coin[i] = 0;
			int y = N;
			while(y-- != 0)
			{
				st = new StringTokenizer(nextLine());
				i++;
				coin[i] = Integer.parseInt(st.nextToken());
				sum[i] = sum[i-1]+coin[i];
				d[i] = Integer.parseInt(st.nextToken());
			}
			long profit = 0l;
			for(int p = 1;p<=N;p++)
			{   min = d[p];
				max = d[p];
				for(int q = p;q<=N;q++)
				{
					min = Math.min(min, d[q]);
					max = Math.max(max, d[q]);
					profit = Math.max(profit, A*(q-p+1)-(sum[q]-sum[p-1])-(int)Math.pow(max-min, 2));
				}
			}
			solution.append(profit+"\n");
		}
		pw.print(solution);
		pw.flush();
		pw.close();
	}

	static StringTokenizer st;
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	public static String nextLine() {
		String s = "";
		try {
			s = br.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return s;
	}

	public static String next() {
		try {
			st = new StringTokenizer(br.readLine());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return st.nextToken();
	}

	public static int nextInt() {
		return Integer.parseInt(next());
	}
}
