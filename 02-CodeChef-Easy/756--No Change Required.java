/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class Main
{
   
	public static void main (String[] args) throws java.lang.Exception
	{
	   BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	   BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	   int t=Integer.parseInt(br.readLine());
	   while(t-->0){
	       
	           String str[] = br.readLine().trim().split(" ");
	           
	           int n = Integer.parseInt(str[0]);
	           int k = Integer.parseInt(str[1]);
	           String s[] = br.readLine().trim().split(" ");
	           int arr[] = new int[n];
	           
	           for(int i = 0; i < n; i++){
	               
	               arr[i] = Integer.parseInt(s[i]);
	               
	           }
	           
	           int brr[] = new int[n];
	           boolean flag = false;
	           
	           for(int i = n-1; i>=0 ; i--){
	               
	               if(k%arr[i] != 0){
	                   
	                   brr[i] = k/arr[i] + 1;
	                   flag = true;
	                   break;
	                   
	               }else if( i != 0 )
	               {if(arr[i]%arr[i-1] != 0 && k%arr[i-1] == 0){
	                   
	                   brr[i] = 1;
	                   brr[i-1] = ((k - arr[i]) /arr[i-1]) + 1;
	                   flag = true;
	                   break;
	               }
	               }
	               
	           }
	           
	           if(flag){
	               bw.write("YES ");
	               for(int i = 0 ; i < n; i++){
	                   
	                   bw.write(brr[i]+" ");
	                   
	               }
	           }else{
	               bw.write("NO");
	           }
	           bw.newLine();
	           bw.flush();
	   }
	   
	}
}
