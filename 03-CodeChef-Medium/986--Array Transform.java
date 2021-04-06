/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc =new Scanner(System.in);
		  int t=sc.nextInt();
		  while(t>0)
		  {
		      int n=sc.nextInt();
		      int k=sc.nextInt();
		      k=k+1;
		      int count=0;
		      int[] b= new int[k];
		      for(int i=0;i<n;i++){
		          int N=sc.nextInt();
		          (b[N%k])++;
		          if(b[N%k]==n-1)
		          count=1;
		      }
		      if(count==1)
		      System.out.println("YES");
		      else
		      System.out.println("NO");
		      t--;
		  }
	}
}

