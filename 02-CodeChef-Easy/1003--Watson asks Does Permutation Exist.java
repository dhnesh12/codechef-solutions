/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main(String[] args) {

        Scanner fk = new Scanner(System.in);
        PrintWriter pr = new PrintWriter(System.out);

        int t = fk.nextInt();

        while(t-- > 0){
            int n = fk.nextInt();
            int[] arr = new int[n];

            for(int i =0; i<n; i++)
                arr[i] = fk.nextInt();

            Arrays.sort(arr);

            pr.println(fxn(arr,n));
        }

        pr.close();
    }

    private static String fxn(int[] arr, int n){
        for(int i=0; i<n-1; i++){
            if(Math.abs(arr[i]-arr[i+1]) > 1)
                return "NO";
        }

        return "YES";
    }
}
