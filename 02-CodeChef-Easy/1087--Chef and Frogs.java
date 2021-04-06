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
        int n=sc.nextInt();
        int k=sc.nextInt();
        int p=sc.nextInt();
        int arr[]=new int[n];
        int sortArr[][]=new int[n][2];
        int nearest[] =new int[n];
        int nearestAdj[]=new int[n];
        for(int i=0;i<n;i++)
        {
            arr[i]=sc.nextInt();
            sortArr[i][0]=arr[i];
            sortArr[i][1]=i;
            nearest[i]=i;
        }
        Arrays.sort(sortArr,(a,b)->a[0]-b[0]);
        for(int i=1;i<n;i++)
        {
            if(sortArr[i][0]-sortArr[i-1][0]<=k)
            {
                nearest[i]=nearest[i-1];
                
            }
            
        }
        for(int i = 0; i<n; i++) {
	        nearestAdj[sortArr[i][1]] = nearest[i];
	    }
       
        while(p-->0)
        {
            int low=sc.nextInt()-1;
            int high=sc.nextInt()-1;
            if(nearestAdj[low]==nearestAdj[high])
                System.out.println("Yes");
            else
                System.out.println("No");
        }
	}
}
