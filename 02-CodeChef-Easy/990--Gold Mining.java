/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class FastReader
{
    BufferedReader br;
    StringTokenizer st;
    public FastReader()
    {
        br=new BufferedReader(new InputStreamReader(System.in));
    }
    String next()
    {
        while(st==null || !st.hasMoreElements())
        {
            try {
                st=new StringTokenizer(br.readLine());
                
            } catch(Exception e) {
             e.printStackTrace();
            }
        }
        return st.nextToken();
    }
    int nextInt()
    {
        return Integer.parseInt(next());
    }
    double nextDouble()
    {
        return Double.parseDouble(next());
    }
    long nextLong()
     {
        return Long.parseLong(next());
    }
    String nextLine()
    {
        String str="";
        try
        {
            str=br.readLine();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        return str;
    }
}
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	FastReader sc = new FastReader();
        int testCase = sc.nextInt();
        while (testCase>0){
            int n = sc.nextInt();
            double chef =0;
            double chefu =0;
            for(int i=0; i<n; i++) {
                double gold = sc.nextDouble();
                double a = sc.nextDouble();
                double b = sc.nextDouble();
                chef = chef + ((gold) * a) / (a + b);
                chefu = chefu + ((gold) * b) / (a + b);
            }
            System.out.println(chefu+" "+chef);
            testCase--;
        }
	}
}
