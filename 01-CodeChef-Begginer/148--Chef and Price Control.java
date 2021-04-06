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
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		
		for(int i=0;i<t;i++)
		{
		    int n=sc.nextInt();
		    int k=sc.nextInt();
		    int ar[]=new int[n];
		    for(int j=0;j<n;j++)
		    {
		        ar[j]=sc.nextInt();
		    }
		    int c=0;
		    for(int j=0;j<n;j++)
		    {
		        if(ar[j]>k){
		           c+=ar[j]-k;
		           //System.out.println(c);
		           
		        }
		        
		    }
		    System.out.println(c);
		    
		   
		     
		}
	}
}
