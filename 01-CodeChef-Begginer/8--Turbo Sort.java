/* package codechef; // don't place package name! */

import java.util.Arrays;
import java.util.Scanner;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args){
	    Scanner sc = new Scanner(System.in);
        int n, i;
        n = sc.nextInt();
        int[] a = new int[n];
        for (i=0; i<n; i++){
            a[i] = sc.nextInt();
        }
        Arrays.sort(a);
        for (i=0; i<n; i++){
            System.out.println(a[i]);
        }
    }
}