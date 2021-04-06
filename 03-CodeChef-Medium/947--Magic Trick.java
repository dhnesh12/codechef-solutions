/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.BigInteger;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		
		FastScanner fs = new FastScanner();
		//Scanner fs = new Scanner(System.in);
		int t = fs.nextInt();
		int n,low,high;
		BigInteger a,b,c,mul,add;
		LinkedList<BigInteger> list;
		String s;
		char cur;boolean rev;
		while(t-- > 0){
		   rev = false;
		    n = fs.nextInt();
		    list = new LinkedList<>();
		    for(int i=0; i<n; i++)
		        list.add(BigInteger.valueOf(fs.nextLong()));
		        
		    a = BigInteger.valueOf(fs.nextLong());
		    b = BigInteger.valueOf(fs.nextLong());
		    c = BigInteger.valueOf(fs.nextLong());
		    add = BigInteger.ZERO;
		    mul = BigInteger.ONE;
		    s = fs.nextToken();
		    
		    for(int j=0; j<n; j++){
		        
		        cur = s.charAt(j);
		        if(cur == 'R'){
		            rev = !rev;
		        }else if(cur == 'A'){
		            add = add.add(a).mod(c);
		        }else if(cur == 'M'){
		            mul = mul.multiply(b).mod(c);
		            add = add.multiply(b).mod(c);
		        }
		        
		        if(!rev){
                    System.out.print(list.poll().multiply(mul).add(add).mod(c).longValue());
                }
                if(rev){
                    System.out.print(list.pollLast().multiply(mul).add(add).mod(c).longValue());
                }
                if(j<n-1)
                    System.out.print(" ");
		        
		    }
		    
		    System.out.println();
            
		}
		
		
	}
	 public static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(String s) {
            try {
                br = new BufferedReader(new FileReader(s));
            } catch (FileNotFoundException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String nextToken() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(nextToken());
        }

        long nextLong() {
            return Long.parseLong(nextToken());
        }

        double nextDouble() {
            return Double.parseDouble(nextToken());
        }
    }
}
