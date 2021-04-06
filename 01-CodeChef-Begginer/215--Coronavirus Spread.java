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
            int min = 100, max =0;

            for(int i =0; i<n-1; i++){
                boolean b = false;
                int mic =1, mac =1;
                while(Math.abs(arr[i]-arr[i+1])<=2) {
                    mic++;
                    mac++;
                    i++;
                    b = true;
                    if(i == n-1)
                        break;
                }
                if(b)
                    i--;

                min = Math.min(min, mic);
                max = Math.max(max, mac);
            }

            pr.println(min +" "+ max);
        }

        pr.close();
    }

}
