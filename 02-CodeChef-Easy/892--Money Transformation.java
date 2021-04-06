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
			String s[]=br.readLine().split(" ");
			int A=Integer.parseInt(s[0]);
			int B=Integer.parseInt(s[1]);
			int C=Integer.parseInt(s[2]);
			double max=Double.parseDouble(String.valueOf(A)+"."+String.valueOf(B));
			int c=0;
			int max_c=c;
			int i=0;
			while(i<10000 && (A>0 || B>=C))
			{
				c++;
				if(B>=C)
				{
					B=B-C;
				}
				else
				{
					A=A-1;
					B=B+100;
					B=B-C;
				}
				int tmp=A;
				A=B;
				B=tmp;
				//System.out.println(A+B*0.01);
				if(max<(A+B*0.01))
				{
					max=A+B*0.01;
					//if(max_c<c)
				    	max_c=c;
				}
				i++;

			}
			System.out.println(max_c);
		}

	}
}
