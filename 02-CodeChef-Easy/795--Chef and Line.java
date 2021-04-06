/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{   
	public static void main (String[] args) throws java.lang.Exception
	{
	   Scanner sc=new Scanner(System.in);
	   int t=sc.nextInt();
	   while(t-->0)
	   {
	       int n=sc.nextInt();
	       long k=sc.nextInt();
	       long b=sc.nextInt();
	       long a[]=new long[n];
	       for(int i=0;i<n;i++)
	       {
	          a[i]=sc.nextLong(); 
	       }
	       Arrays.sort(a);
	       long x=k*a[0]+b;
	       long sum=1;
	           for(int i=1;i<n;i++)
	           {
	               if(a[i]>=x)
	              { x=(k*a[i])+b;
	               sum++;
	              }
	           }
	       System.out.println(sum);
	   }
	}
}
