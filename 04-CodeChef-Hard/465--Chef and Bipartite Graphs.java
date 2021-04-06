import java.util.*;
import java.lang.*;
import java.io.*;
class Codechef
{
        
	public static void main (String[] args) throws java.lang.Exception
	{
	    BufferedWriter output = new BufferedWriter(
            new OutputStreamWriter(System.out));
        FastReader sc = new FastReader();
        int testCase = sc.nextInt();
        while(testCase-->0){
            int n = sc.nextInt();
            int m = sc.nextInt();
            int minDeg = sc.nextInt();
            int maxDeg = sc.nextInt();
            if(m>maxDeg*n || m<minDeg*n || m>(n*n)){
                System.out.println(-1);
            }else{
                int a;
                for(int i=1; i<=n; i++){
                    a = i;
                    for(int j=0; j<minDeg; j++){
                        output.write(i+" "+a + "\n");
                        //System.out.println(i+" "+a);
                        a++; if(a==n+1) a= 1;
                    }
                }
                int remaining = m - n*(minDeg);
                //System.out.println(remaining);
                if(remaining>0){
                    for(int i=1; i<=n; i++){
                        a = (i+minDeg)%n;
                        if(a==0) a = n;
                        for(int j =minDeg+1; j<=maxDeg; j++){
                            if(a==n+1) a = 1;
                             output.write(i+" "+a + "\n");
                            // System.out.println(i+" "+a+);
                            a++;
                            remaining--;
                            if(remaining==0) {
                                break;
                            }
                        }
                        if(remaining==0) break;
                    }
                }
            }
            output.flush();
        }
         
    }
    
    // Fast Reader Class
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new
                    InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}
