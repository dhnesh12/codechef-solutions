/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		int t=Integer.parseInt(br.readLine());
		while(t--> 0){
		    int b=Integer.parseInt(br.readLine());
		    int ch=b%8;
		    String ans=" ";
		    int p=0;
		    switch(ch)
		    {
		        case 0:
		            ans="SL";
		            p=b-1;
		            break;
		        case 1:
		            ans="LB";
		            p=b+3;
		            break;
                case 2:
		            ans="MB";
		            p=b+3;
		            break;
                case 3:
		            ans="UB";
		            p=b+3;
		            break;
		       case 4:
		            ans="LB";
		            p=b-3;
		            break;
		       case 5:
		            ans="MB";
		            p=b-3;
		            break;
		      case 6:
		            ans="UB";
		            p=b-3;
		            break;
		      case 7:
		            ans="SU";
		            p=b+1;
		            break;
		      
		    }
		    System.out.println(p+""+ans);
		}
	}
}
