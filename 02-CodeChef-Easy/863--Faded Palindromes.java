/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    try{
		Scanner scan = new Scanner(System.in);
		int t,n,i,j,count=0;
		String str;
		char ch,ch1;
		t=scan.nextInt();
		for(i=0;i<t;i++){
		    str=scan.next();
		    n=str.length();
		    count=0;
		    char[] c = new char[n];
		    for(j=0;j<n;j++){
		        c[j] = str.charAt(j);
		    }
		    if(n%2 == 0){
		        for(j=0;j<n;j++){
		            if(c[j] == '.' && c[(n-1)-j] != '.'){
		                c[j] = c[(n-1)-j];
		            }else if(c[j] == '.' && c[(n-1)-j] == '.'){
		                c[j] = 'a';
		                c[(n-1)-j] = 'a';
		            }
		        }

		    }else{
		        for(j=0;j<n;j++){
		            if(j!=n/2 && c[j] == '.' && c[(n-1)-j] != '.'){
		                c[j] = c[(n-1)-j];
		            }else if(c[j] == '.' && c[(n-1)-j] == '.'){
		                c[j] = 'a';
		                c[(n-1)-j] = 'a';
		            }
		        }
		    }
		    for(j=0;j<n/2;j++){
		        if(c[j] == c[(n-1)-j]){
		            count++;
		        }
		    }
            if(count == n/2){
                for(j=0;j<n;j++){
		            System.out.print(c[j]);
                }
		        System.out.println();
            }else{
                System.out.println("-1");
            }
		        
		}
	    }
	    catch(Exception e){}
	}
}
