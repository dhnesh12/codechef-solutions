/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef {
    
	public static void main(String[] args) {

        Scanner fk = new Scanner(System.in);
        PrintWriter pr = new PrintWriter(System.out);

        int t = fk.nextInt();

        while(t-- > 0){
            int n = fk.nextInt();
            int[] arr = new int[n];
            for(int i =0; i<n; i++)
                arr[i] = fk.nextInt();
            
            HashSet<Integer> set = new HashSet<>();
            int counter = 0;

            for(int i =0; i<n; i++){
                if(arr[i] > n)
                    counter++;
                else{
                    if(set.contains(arr[i]))
                        counter++;
                    else
                        set.add(arr[i]);
                }
            }

            pr.println(counter);
        }

        pr.close();
    }

}
