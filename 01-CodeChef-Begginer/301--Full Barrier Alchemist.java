/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
        static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader()
        {
            br = new BufferedReader(
                    new InputStreamReader(System.in));
        }

        String next()
        {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() { return Integer.parseInt(next()); }

        long nextLong() { return Long.parseLong(next()); }

        double nextDouble()
        {
            return Double.parseDouble(next());
        }

        String nextLine()
        {
            String str = "";
            try {
                str = br.readLine();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
        FastReader sc=new FastReader();
        int T=sc.nextInt();
        while(T-- >0){
            int N= sc.nextInt();
            int H= sc.nextInt();
            int Y1= sc.nextInt();
            int Y2= sc.nextInt();
            int L= sc.nextInt();
            int flag=0;
            while(N-- >0){
                
                int t= sc.nextInt();
                int X= sc.nextInt();
              if(L != 0){
                if(t==1){
                    if((H-Y1) <= X) {
                        flag = flag + 1;
                    }else{
                            L=L-1;
                            if(L != 0) {
                                flag = flag + 1;
                            }
                    }
                }
                if (t==2){
                    if(Y2 >= X){
                        flag=flag+1;
                    }else{
                        L=L-1;
                        if(L != 0) {
                            flag = flag + 1;
                        }
                    }
                }
              }
            }
            System.out.println(flag);
        }
    }
}
