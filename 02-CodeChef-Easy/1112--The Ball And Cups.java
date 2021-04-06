/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args)
	{
		// your code goes here
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		for(int j=0;j<t;j++)
		{
    		int n=sc.nextInt();
    		int c=sc.nextInt();
    		int q=sc.nextInt();
    		int L,R;
    		for(int i=0;i<q;i++)
    		{
    			L=sc.nextInt();
    			R=sc.nextInt();
    			if(c>=L && c<=R)
    			c=L+R-c;
    		}
    		System.out.println(c);
		}	
	}
}
