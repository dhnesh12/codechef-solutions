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
		Scanner sc = new Scanner(System.in);
        int testCase = sc.nextInt();
        while(testCase>0){
             int n = sc.nextInt();
            int max = 0;
            int b = sc.nextInt();
            int a;
            for(int i=0; i<n-1; i++){
               a = sc.nextInt();
               if(a<b) {
                   b = a;
               }
               if((a-b)>max) {
                   max = a-b;
               }
            }
            if(max==0){
                System.out.println("UNFIT");
            }
            else{
                System.out.println(max);
            }
            testCase--;
        }
	}
}
