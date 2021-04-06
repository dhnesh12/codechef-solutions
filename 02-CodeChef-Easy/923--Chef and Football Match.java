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
		int output[]=new int[t];
		for(int i=0;i<t;i++)
		{
			int n=sc.nextInt();
			int r_type[]=new int[n];
			int A[]=new int[n];
			int B[]=new int[n];
			for(int j=0;j<n;j++)
			{
				r_type[j]=sc.nextInt();
				A[j]=sc.nextInt();
				B[j]=sc.nextInt();
			}
			int last_confirm=-1;
			for(int j=0;j<n;j++)
			{
				if(r_type[j]==1)
				{
					last_confirm=j;
					System.out.println("YES");
				}
				else if(A[j]==B[j])
					{
						last_confirm=j;
						System.out.println("YES");
					}
				else
				{
					if(last_confirm==-1)
					System.out.println("NO");
					else
					{
						if(Math.max(A[last_confirm],B[last_confirm])<=Math.min(A[j],B[j]))
						System.out.println("NO");
						else
						{
							System.out.println("YES");
							if(A[last_confirm]<B[last_confirm])
							{
								int a=Math.min(A[j],B[j]);
								B[j]=Math.max(A[j],B[j]);
								A[j]=a;
							}
							else
							{
								int a=Math.max(A[j],B[j]);
								B[j]=Math.min(A[j],B[j]);
								A[j]=a;
							}
							last_confirm=j;
						}
					}
				}
			}
			
		}
	}
}
