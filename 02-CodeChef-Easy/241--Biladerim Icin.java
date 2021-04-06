/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int m = 1000000007;
		long m_m = 1000000007 << 8;
		int T = Integer.parseInt(br.readLine());
		while(T-- > 0) {
		    String s = br.readLine();
		    int index1 = s.indexOf(32);
		    int index2 = s.lastIndexOf(32);
		    int A = Integer.parseInt(s.substring(0, index1));
		    int B = Integer.parseInt(s.substring(index1 + 1, index2));
		    int C = Integer.parseInt(s.substring(index2 + 1));
		    
		    --A;
		    --C;
		    
		    if (A == 0 || C == 0) {
		        bw.write("0\n");
		        bw.flush();
		        continue;
		    }
		    
		    long count = 0;
		    for(int b = 1 ; b <= B ; ++b) {
		        count += Math.max(0, (A - b)) * 1L * Math.max(0, (C - b));
		        long sq = b * 1L * b;
		        for(int i = 1; i <= b ; ++i) {
		            long j = sq / i;
		            if (i <= Math.min(A, b)) count += Math.max(0, C - j);
		            if (i <= Math.min(C, b)) count += Math.max(0, A - j);
		        }
		        if (count > m_m) count %= m;
		    }
		    if (count > m) count %= m;
		    bw.write(count + "\n");
		    bw.flush();
		}
	}
}
