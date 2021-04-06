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
	    sc.nextLine();
	    for(int x=0;x<t;x++)
	    {
	        String s[]=sc.nextLine().split(" ");
	        System.out.println(solve(s));
	    }
		// your code goes here
	}
	public static String solve(String s[])
	{
	    StringBuilder str=new StringBuilder();
	    for(int i=0;i<s.length;i++)
	    {
	        if(i!=0)
	        str.append(" ");
	        str.append(Character.toUpperCase(s[i].charAt(0)));
	        if(i==s.length-1)
	        str.append(s[i].substring(1).toLowerCase());
	        else
	        str.append(".");
	    }
	    return str.toString();
	}
}
