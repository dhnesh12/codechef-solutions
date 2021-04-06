/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
   
    static Scanner sc=new Scanner(System.in);
    static int n,m,k;
	public static void main (String[] args) 
	{
	   try{
		n=sc.nextInt();
		m=sc.nextInt();
		k=sc.nextInt();
        int arr[][]=new int[n][m];

		for(int i=0;i<n;i++){
			for (int j=0;j<m ;j++ ) {
				arr[i][j]=sc.nextInt();

			}
		}

		int a=1;
		for(int i=0;i<arr.length;i++){
			for (int j=0;j<arr[i].length ;j++ ) {

                System.out.print(a+" ");
                a++;
                if(a>k)
                	a--;
            }
            a=1;
            System.out.println();    

	}
	}
	catch(Exception e)
	{
	    
	}
	}
}
