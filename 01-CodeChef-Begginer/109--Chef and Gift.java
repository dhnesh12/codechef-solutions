/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner scan=new Scanner(System.in);
		int t=scan.nextInt();
		for(int z=0;z<t;z++)
		{
		    int n=scan.nextInt();
		    int k=scan.nextInt();
		    int arr[]=new int[n];
		    for(int i=0;i<n;i++)
		        arr[i]=scan.nextInt();
		    int count=0;
		    for(int i=0;i<n;i++)
		    {
		        if(arr[i]%2==0)
		            count++;
		    }
		    if(k==0&&count==n)
                System.out.println("NO");
            else if(count>=k)
                    System.out.println("YES");
            else
                    System.out.println("NO");
		}
	}
}
