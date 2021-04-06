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
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		
		int t = Integer.parseInt(br.readLine());
		while(t-- > 0){
		    int n = Integer.parseInt(br.readLine());
		    String s = br.readLine();
		    int res = 0, i = 0;
		    while(i<s.length()){
		        if(s.charAt(i) == '0') {
		            if(!((i-1>=0 && s.charAt(i-1)=='1') || 
		                    (i+1 < s.length() && s.charAt(i+1)=='1'))){
		                        res++;
		            }
		        }
		        i++;
		    }
		    
		    out.println(res);
		}
		out.close();
	}
}
