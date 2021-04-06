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
            long y = fk.nextLong();

            long start = Math.min(701, y);
            long counter = 0;

            for(int i=1; i<start; i++){
                counter += Math.floor(Math.sqrt(y-i));
            }

            pr.println(counter);
        }

        pr.close();

    }
}
