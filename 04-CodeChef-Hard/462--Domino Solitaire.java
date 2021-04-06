/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
    public static int dominoSolitaire(int[][] grid){
        int n = grid[0].length;
        int[] dp = new int[n + 1];
      
        dp[1] = Math.abs(grid[0][0] - grid[1][0]);
        
        
        for(int j = 2; j <= n; j++){
            int max = 0;
            int nm1 = dp[j - 1] + Math.abs(grid[0][j - 1] - grid[1][j - 1]);
                                           
            
            int nm2 = dp[j - 2] + Math.abs(grid[0][j - 1] - grid[0][j - 2]) +
                                           Math.abs(grid[1][j - 1] - grid[1][j - 2]);
            max = Math.max(nm1,nm2);    
            
            
            dp[j] = max;
        }
        
        return dp[n];
    }
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader br  = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int[][] grid = new int[2][n];
		for(int i = 0; i < 2; i++){
		    String[] parts = br.readLine().split(" ");
		    for(int j = 0; j < n; j++){
		        grid[i][j] = Integer.parseInt(parts[j]);
		    }
		}
		
		System.out.println(dominoSolitaire(grid));
	}
}
