/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
static int solved(char stm[][],int n){
    	int arr[]=new int[n];
    	for(int i=0;i<n;i++){
    		arr[i]=1;
    		for(int j=0;j<n;j++){
    			if(stm[i][j]=='T' && i!=j){
    				if(check(stm,i,j,n))
    					++arr[i];
    				else{
        				arr[i]=0;
        				break;
        			}
    			}
    			
    		}
    	}
    	int max=0;
    	for(int i=0;i<n;i++){
    		if(arr[i]>max)
    			max=arr[i];
    	}
    	return max;
    }
    static boolean check(char[][]stm,int i,int j,int n){
    	for(int k=0;k<n;k++){
    		if(stm[i][k]!=stm[j][k])
    			return false;
    	}
    	return true;
    }
	public static void main(String[] args) {
		
		Scanner scan=new Scanner(System.in);
		int n=scan.nextInt();
	    char[][] stm=new char[n][n];
	    for(int i=0;i<n;i++)
	     for(int j=0;j<n;j++)
	    	 stm[i][j]=scan.next().charAt(0);
	    System.out.println(solved(stm,n));
        scan.close();
	
	}
}
