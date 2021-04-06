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
		int n=Integer.parseInt(br.readLine());
		int arr[]=new int[n];
		String str[]=br.readLine().split(" ");
		for(int i=0;i<n;i++)
		    arr[i]=Integer.parseInt(str[i]);
	    for(int i=0;i<n;i++)
	    {
	        long num=arr[i];
	        String s=String.valueOf(num);
	        int j=s.length()-1;
	        while(s.charAt(j)=='0') j--;
	        long last=Integer.parseInt(s.substring(j,j+1));
	        while(last==5)
	        {
	            num=num*4;
	            s=String.valueOf(num);
	            j=s.length()-1;
	            while(s.charAt(j)=='0') j--;
	            last=Integer.parseInt(s.substring(j,j+1));
	        
	        }
	       System.out.println(num);
	        
	    }
	}
}
