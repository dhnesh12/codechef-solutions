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
            int n = fk.nextInt(), k = fk.nextInt();
            String s = fk.next();
            long counter = 0;

            for(int i =1; i<n-k+1; i++){
                for(int j=i; j<i+k; j++){
                    if(s.charAt(j-1) != s.charAt(j))
                        counter++;
                }
            }

            pr.println(counter);
        }
        
        pr.close();
    }
}
