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

        public FastReader() {
            br = new BufferedReader(
                    new InputStreamReader(System.in));
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


    public static void main(String args[]) throws java.lang.Exception {
        FastReader f = new FastReader();
        int T = f.nextInt();
        for (int i = 1; i <= T; i++) {
            int n = f.nextInt();
            int k = f.nextInt();
            int x = f.nextInt();
            int y = f.nextInt();
            int c = 0;
            int flag = 0;
            for (int j = 0; j < n; j++) {
                  if (x == y)
                  {
                    flag=1;
                     break;
                  }
                  else{
                        c = (x + k) % n;
                        if (y == c) {
                                     flag = 1;
                                        break;
                        }
                     else {
                    //flag = 0;
                    x=c;
                    //continue;
                
                }
                  }

               
            }
            if(flag==1)
                System.out.println("YES");
            else
                System.out.println("NO");

        }
    }
}
