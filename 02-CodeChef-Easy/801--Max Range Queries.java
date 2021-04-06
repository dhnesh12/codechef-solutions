/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
    public static void maxremov(int [][] query , int [] array ,int k, int n)
    {
        int [] prefixsum = new int [array.length];
        Arrays.fill(prefixsum,0);
        for(int i=0;i<query.length;i++)
        {
            int sp = query[i][0];
            int ep = query[i][1];
            int inc = 1;
            int dec = -1;
            
            array[sp]+=1;
            if(ep+1>=array.length)
            {
                continue;
            }
            array[ep+1]+=dec;
            
        }
        
        prefixsum[0] = array[0];
        
        for(int i=1;i<array.length;i++)
        {
            prefixsum[i] = prefixsum[i-1] + array[i];
        }
        
        int count =0;
        
        int [] pcak = new int [array.length];
        int [] pcakpo = new int [array.length];
        Arrays.fill(pcak,0);
        Arrays.fill(pcakpo,0);
        
          if (prefixsum[0]==k)
            {
                pcak[0] =1;
            }
            
             if (prefixsum[0]==k+1)
            {
                pcakpo[0]=1;
            }
            
        for (int i=1;i<prefixsum.length;i++)
        {
            if (prefixsum[i]==k)
            {
                count ++;
                pcak[i] = pcak[i-1] + 1;
            }
            
            else{
                pcak[i] = pcak[i-1];
            }
            
            if (prefixsum[i]==k+1)
            {
               
                pcakpo[i] = pcakpo[i-1] + 1;
            }
             
             else{
                pcakpo[i] = pcakpo[i-1];
            }
        }
        
        int ans = 0;
        for (int i=0;i<query.length;i++)
        {
             int sp = query[i][0];
             int ep = query[i][1];
            
            int profit =  pcakpo[ep] - pcakpo[sp-1];
            int loss =    pcak[ep] - pcak[sp-1];
             if(count-loss+profit > ans) ans = count-loss+profit;
            
        }
        
        System.out.println(ans);
        
    }
    
    public static Scanner scn = new Scanner(System.in);
	public static void main (String[] args) throws java.lang.Exception
	{
		int tc = scn.nextInt();
	
		while(tc-->0)
		{
    		int nofq = scn.nextInt();
    		int kmax = scn.nextInt();
    		
    		int [][] query = new int [nofq][2];
    		
    		for (int i=0;i<nofq;i++)
    		{
    		    query[i][0] = scn.nextInt();
    		    query[i][1] = scn.nextInt();
    		}
    		
    		int [] array = new int [100000];
    		Arrays.fill(array,0);
    		
    		maxremov(query,array,kmax,nofq);
    		
		}
	}
}
