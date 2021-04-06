/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
  	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	    String str=br.readLine();
	    int i,j,count=0,flag=0,am=0;
	    int l=str.length();
	    BigInteger b=new BigInteger("0");
	   
	    
	   
	        for(i=0;i<l;i++)
	        {
	            count=0;
	            j=i+1;
	            StringBuffer sb=new StringBuffer("");
	            char ch=str.charAt(i);
	            if(ch>='A' && ch<='Z')
	            {
	                sb.append("9");
	                count=1;
	             }
	           else
	           {
	                sb.append(String.valueOf(ch));
	            }
	            while(j<l)
	            {
	            char ch2=str.charAt(j);
	                if(ch2>='A' && ch2<='Z')
	                {
	                   
	                    if(count==0)
	                    {
	                    sb.append("9");
	                    count=1;
	                    }
	                    else
	                    break;    
	                   
	                }
	                else
	                {
	                    
	                   
	                     sb.append(String.valueOf(ch2));   
	                     
	                    
	                }
	                j++;
	            }
	            BigInteger b2=new BigInteger(sb.toString());
	            b=b.max(b2);
	            
	           
	        }
	        System.out.println(b);
	    
	}
}
