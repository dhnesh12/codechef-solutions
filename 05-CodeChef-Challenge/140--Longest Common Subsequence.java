import java.io.IOException;
import java.io.InputStream;
import java.util.InputMismatchException;

public class Main {
	

	private static void solveCommonSubstring(InputReader in) {
		
		in.readInt();
		in.readInt();
		
		char [] a = in.readString().toCharArray();
		char [] b = in.readString().toCharArray();
		
		int [][] T = new int [a.length + 1][b.length + 1];
		
		int max = 0;
		for (int i = 1; i < T.length; i++) {
			for (int j = 1; j < T[0].length; j++) {
				if(a[j-1] == b[i-1]) {
					T[i][j] = T[i-1][j-1] + 1;
					max = Math.max(T[i][j], max);
				} else {
					T[i][j] = 0;//Math.max(T[i-1][j], T[i][j-1]);
				}
			}
		}
	
		System.out.println(max);
		
        for (int i = 0; i < T.length; i++) {
			for (int j = 0; j < T[0].length; j++) {
				System.err.print(T[i][j] + " ");
			}
			System.err.println();
		}
	}
	
	public static void solve(InputReader in, int caseId) {
		
		int xLength = in.readInt();
		char [] a = in.readString().toCharArray();
		int yLength = in.readInt();
		char [] b = in.readString().toCharArray();
		
		int [][] T = new int[xLength + 1][yLength + 1];
		StringBuilder builder = new StringBuilder(1000);
		
		int ti = 0, tj = 0;
		int max = 0;
		for (int i = 1; i < T.length; i++) {
			for (int j = 1; j < T[0].length; j++) {
				if(a[i-1] == b[j-1]) {
					T[i][j] = T[i-1][j-1] + 1;
				}else {
					if(T[i-1][j] > T[i][j-1]) {
						T[i][j] = T[i-1][j];
					}else {
						T[i][j] = T[i][j-1];
					}
				}
				max = Math.max(max, T[i][j]);
			}
		}
		
		if(max < 2) { 
			builder.insert(0, "case " + caseId + " N" +"\n");
		} else {
			int i = T.length-1;
			int j = T[0].length-1;
			int min = T[i][j];
			while(i > 0 && j > 0) {
				if(min == T[i-1][j]) {
					i--;
				} else if(min == T[i][j-1]) {
					j--;
				} else if(min - 1 == T[i-1][j-1]) {
					builder.insert(0, a[i-1] + " " + i + " " + j + "\n");
					i--;
					j--;
					min = T[i][j]; 
				} 
			}
		
			builder.insert(0, max + "\n");
			builder.insert(0, "case " + caseId + " Y" +"\n");
		}
		System.out.print(builder.toString());
		System.out.flush();
		
	}

	public static void main(String[] args) {

		InputReader in = new InputReader(System.in);
		
		int t = in.readInt();
		for(int i = 1; i <= t; i++) {
			solve(in, i);
		}
		
	}
	
}

class InputReader {
	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;

	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public int[] readIntArr(int len) {
		return readIntArr(0, len);
	}

	public int[] readIntArr(int offset, int len) {
		int[] arr = new int[len];
		for (int i = offset; i < len; i++)
			arr[i] = readInt();
		return arr;
	}

	public int read() {
		if (numChars == -1)
			throw new InputMismatchException();
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars <= 0)
				return -1;
		}
		return buf[curChar++];
	}

	public int readInt() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public String readString(int n) {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		StringBuffer res = new StringBuffer(n);
		do {
			res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
	}

	public String readString() {
		return readString(500);
	}

	public Long readLong() {
		return Long.parseLong(readString());
	}

	public Double readDouble() {
		return Double.parseDouble(readString());
	}

	public boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

}
