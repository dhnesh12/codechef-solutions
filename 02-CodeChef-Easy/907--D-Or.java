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
            long l = fk.nextLong(), r = fk.nextLong();

            long xor = l^r;
            long x = 0, y =1;

            while(xor > 0){
                x = x+y;
                y *= 2;
                xor >>= 1;
            }

            pr.println(x|l);
            
        }

        pr.close();
    }
}
