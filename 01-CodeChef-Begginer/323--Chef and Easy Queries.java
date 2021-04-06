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
		while(t-->0){
		    long n=sc.nextLong();
		    long k=sc.nextLong();
		    long sum=0;
		    long x=0;
		    for(long  i=1;i<=n;i++){
		        long a=sc.nextLong();
		        sum +=a;
		       if(sum<i*k){
		           x=i;
		           break;
		       }
		    }
		    if(x==0){
		        System.out.println((long)sum/k+1);
		    }else{
		        System.out.println(x);
		    }
		
		}// your code goes here
	}
}
