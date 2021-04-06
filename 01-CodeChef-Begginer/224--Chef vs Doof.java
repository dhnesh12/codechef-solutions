/* package codechef; // don't place package name! */

import javax.crypto.spec.PSource;
import java.security.AlgorithmConstraints;
import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Cocechef {

    public static void main(String[] args) throws java.lang.Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
       int t=Integer.parseInt(br.readLine());
       while(t-->0){
           int n=Integer.parseInt(br.readLine());
           int nums[]= new int[n];
           String s[]= br.readLine().split(" ");
           int count=0;
           boolean flag=false;
           for(int i=0;i<n;i++){
               nums[i]=Integer.parseInt(s[i]);
               if(nums[i]%2==0){
                   flag=true;
                   break;
               }



           }
           System.out.println(flag?"NO":"YES");
       }



       }

    }











