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
		Scanner s=new Scanner(System.in);
		try{
		int t=s.nextInt();
		int j;
		for(j=0;j<t;j++){
		    int n,c=0,k;
		    n=s.nextInt();
		    int[] a=new int[n+1];
		    int i,m=0;
		    k=(n*(n+1))/2;
		    for(i=1;i<=n;i++){
		        a[i]=s.nextInt();
		        if(a[i]==i){
		            m++;
		        }
		        c=c+a[i];
		    }
		    if((m!=n)&&c==k){
		        System.out.println("yes");
		    }
		    else{
		        System.out.println("no");
		    }
		}
	   }
	   catch(Exception e){
	       
	   }
	}
}
