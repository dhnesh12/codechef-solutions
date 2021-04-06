/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    Scanner s = new Scanner(System.in);
	    int t = s.nextInt();
	    while(t-- != 0){
	        int n = s.nextInt();
	        int turn = s.nextInt();
	        int p = s.nextInt();
	        int arr[] = new int[n];
	        for(int i = 0; i < n; i++){
	            arr[i] = s.nextInt();
	        }
	        int max = -1,min = Integer.MAX_VALUE;
	        if(turn % 2 == 1){
	          for(int i = 0; i < n; i++){
	              max = Math.max(max,arr[i]);
	              min = Math.min(min,arr[i]);
	          }
	        }
	        else{
	            for(int i = 0; i < n; i++){
	                int curr_min = Integer.MAX_VALUE;
	                int curr_max = -1;
	                if(i > 0){
	                    curr_min = Math.min(curr_min,arr[i - 1]);
	                    curr_max = Math.max(curr_max,arr[i - 1]);
	                }
	                if(i < n - 1){
	                    curr_min = Math.min(curr_min,arr[i + 1]);
	                    curr_max = Math.max(curr_max,arr[i + 1]);
	                }
	                max = Math.max(max,curr_min);
	                min = Math.min(min,curr_max);
	                
	            }
	        }
	        int ans = max;
	        if(p == 1){
	            ans = min;
	          }
	          System.out.println(ans);
	        
	    }
	    
		// your code goes here
	}
}
