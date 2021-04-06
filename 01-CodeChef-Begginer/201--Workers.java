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
		int min1=99999999,min2=99999999,min3=99999999;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		String[] input = br.readLine().split("\\s+");
		int[] cost = new int[n];
		for(int i=0;i<n;i++){
		    cost[i] = Integer.parseInt(input[i]);
		}
		
		input = br.readLine().split("\\s+");
		int[] type = new int[n];
		for(int i=0;i<n;i++){
		    type[i] = Integer.parseInt(input[i]);
		}
		
		for(int i=0;i<n;i++){
		    if(type[i]==1 && cost[i]<min1) min1 = cost[i];
		    if(type[i]==2 && cost[i]<min2) min2 = cost[i];
		    if(type[i]==3 && cost[i]<min3) min3 = cost[i];
		}
		
		if(min1+min2 < min3) System.out.print(min1+min2);
		else System.out.print(min3);
	}
}
