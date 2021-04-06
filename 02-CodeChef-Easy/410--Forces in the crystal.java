/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();

        StringBuilder pol = new StringBuilder();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((i + j) % 2 == 0) {
                    pol.append("0 ");
                } else {
                    pol.append("1 ");
                }
            }
            pol.append("\n");
        }

        System.out.println(pol);
	}
}
