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
		    String s=scan.next();
		    int k=0,f=0;
		    for(int i=0;i<n;i++)
	        {
	            if(s.charAt(i)=='.')
	                continue;
	            else if(k==0&&s.charAt(i)=='H')
	                k=1;
	            else if(k==1&&s.charAt(i)=='T')
	                k=0;
	            else{
	                f=1;
	                break;
	            }
	        }
	        if(f==0&&k==0)
	            System.out.println("Valid");
	        else
	            System.out.println("Invalid");
		}
	}
}
