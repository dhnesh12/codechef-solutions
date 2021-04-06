/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		int t=Integer.parseInt(br.readLine());
		while(t-->0)
		{
		    int n=Integer.parseInt(br.readLine());
		    if(n<3){System.out.println("0");continue;}
		    long ans=getPow(2,n-1);
		    ans-=2;
		    ans%=1000000007;
		    System.out.println(ans);
		}
	}
	static long getPow(int x,int n)
	{
	    if(n==0)return 1;
	    if(n%2==0)
	    {
	       long ans=getPow(x,n/2);
	       ans=ans*ans;
	       return ans%1000000007;
	    }
	    else{
	        long ans=getPow(x,n/2);
	        ans=ans*ans*x;
	        return ans%1000000007;
	    }
	}
}
