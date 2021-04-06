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
		for(int i=0;i<t;i++){
		    int n=sc.nextInt();
		    int a=sc.nextInt();
		    int b=sc.nextInt();
		    int c=sc.nextInt();
		    int d=sc.nextInt();
		    long s[]=new long[n];
		    s[0]=d;
		    long first=0;
		    long second=0;
		    for(int j=1;j<n;j++){
		        s[j]=((a*s[j-1]*s[j-1]+(b*s[j-1]+c)));
		        s[j]=s[j]%1000000;
		    }
		    Arrays.sort(s);
		    //System.out.println(s);
		    for(int j=n-1;j>=0;j--){
		         if(j%2!=0){
		          first+=s[j];
		           }
		       else{
		         second+=s[j];
	         }
		        }
		    //System.out.println(first+" "+second);
		    System.out.println(Math.abs(first-second));
		}
	}
}
