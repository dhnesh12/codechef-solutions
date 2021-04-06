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
		while(t-->0)
		{
		    int N=sc.nextInt();
		    int k=sc.nextInt();
		    sc.nextLine();
		    String str=sc.next();
		    int upper=0,lower=0;
		    for(int i=0;i<str.length();i++)
		    {
		        if(Character.isUpperCase(str.charAt(i)))
		        {
		            upper++;
		        }
		        else{
		            lower++;
		        }
		        
		    }
		    if(upper<=k && lower<=k)
		    System.out.println("both");
		    else if(lower<=k)
		    System.out.println("brother");
		    else if(upper<=k)
		    System.out.println("chef");
		    else
		    System.out.println("none");
		}
	}
}
