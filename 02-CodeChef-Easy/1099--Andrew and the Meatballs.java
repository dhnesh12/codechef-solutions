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
            long k = sc.nextLong();
            long[] longArr = new long[n];
            for(int i=0; i<n; i++){
                longArr[i] = sc.nextLong();
            }
            java.util.Arrays.parallelSort(longArr);
            long sum=0;
            int count=0;
            boolean check = false;
            for(int i=n-1; i>=0; i--){
                sum = sum + longArr[i];
                count++;
                if(sum>=k){
                    check = true;
                    break;
                }
            }
            if(check)
                System.out.println(count);
            else{
                System.out.println(-1);
            }
            testCase--;
        }
	}
}
