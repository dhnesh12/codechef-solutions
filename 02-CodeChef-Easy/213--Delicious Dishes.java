import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {

	/**
	 * @param args
	 */
	static char[] X;
	static int[] fact;
	public static void main(String[] args) {
		fact = new int[20];
		fact[0] = 1;
		for(int i = 1; i < 20; i++)
			fact[i] = fact[i - 1] * i;
		
		InputReader r = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		
		int T = r.nextInt();
		
		while(T-- > 0){
			X = ((r.nextLong() - 1) + "").toCharArray();
			int ret = -get();
			
			X = r.next().toCharArray();
			ret += get();
			
			out.println(ret);
		}
		out.close();

	}
	private static int get() {
		int ans = 0;
		for(int i = 1; i < X.length; i++){
			int rem = X.length - i - 1;
			if(rem <= 9)ans += 9 * (fact[9] / fact[9 - rem]);
		}
		
		if(X.length <= 10){
			int m = 0;
			boolean can = true;
			for(int i = 0; i < X.length; i++){
				int rem = X.length - i - 1;
				if(i == 0){
					if(rem <= 9)ans += (X[0] - '1') * (fact[9] / fact[9 - rem]); 
					m |= 1 << (X[0] - '0');
				}else{
	//				if(rem <= 9 - i){
						for(int d = 0; d < X[i] - '0'; d++)if((m & (1 << d)) == 0){
							ans += fact[9 - i] / fact[9 - rem - i]; 
						}
	//				}
					
					if((m & (1 << (X[i] - '0'))) != 0){
						can = false;
						break;
					}
					
					m |= 1 << (X[i] - '0');	
				}
			}
			if(can)ans++;
		}
		
		return ans;
	}
	static class InputReader {
		private BufferedReader reader;
		private StringTokenizer tokenizer;

		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream));
			tokenizer = null;
		}

		public String nextLine() {
			try {
				return reader.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			}
		}

		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public long nextLong() {
			return Long.parseLong(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}
