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
            String s = fk.next();
            int len = s.length();
            String sl = s.substring(1).concat(String.valueOf(s.charAt(0)));
            String sr = String.valueOf(s.charAt(len-1)).concat(s.substring(0,len-1));
            pr.println(sl.equals(sr)? "YES":"NO");
        }

        pr.close();
    }
}
