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
	    for(int x=0;x<t;x++)
	    {
	        
	        int a[]=new int[5];
	        for(int i=0;i<a.length;i++)
	        a[i]=sc.nextInt();
	        int temp=sc.nextInt();
	        System.out.println(solve(a,temp)?"Yes":"No");
	    }
		// your code goes here
	}
	public static boolean solve(int a[],int temp)
	{
	    return Arrays.stream(a).sum()*temp>120;
	}
}
