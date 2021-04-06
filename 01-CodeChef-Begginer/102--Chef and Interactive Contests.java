/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	   Scanner sc = new Scanner(System.in);
	   int n = sc.nextInt();
	   int r = sc.nextInt();
	   while(n-->0){
	   int R = sc.nextInt();
	   
	   if(R>0 && R<r)
	   System.out.println("Bad boi");
	   
	   else if(R>=r)
	   System.out.println("Good boi");
	   }
	}
}
