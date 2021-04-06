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
		int tc = sc.nextInt();
		while(tc!=0){
		    long X = sc.nextLong();
		    long Y = sc.nextInt();
		    long K = sc.nextLong();
		    long set = (X+Y)/K;
		    if((set+1)%2==0){
		        System.out.println("Paja");
		    }else{
		        System.out.println("Chef");
		    }
		    tc--;
		}
	}
}
