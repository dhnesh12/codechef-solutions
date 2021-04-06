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
		while(t-->0){
		    int n=sc.nextInt();
		    int[] goal=new int[n];
		    int[] foul=new int[n];
		    for(int i=0;i<n;i++){
		        goal[i]=sc.nextInt();
		    }
		    for(int i=0;i<n;i++){
		       foul[i]=sc.nextInt();
		    }
		    int[] res=new int[n];
		    for(int i=0;i<n;i++){
		        if((goal[i]*20-foul[i]*10)<0){
		            res[i]=0;
		        }
		        else{
		            res[i]=goal[i]*20-foul[i]*10;
		        }
		    }
		    Arrays.sort(res);
		    System.out.println(res[res.length-1]);
		}
	}
}
