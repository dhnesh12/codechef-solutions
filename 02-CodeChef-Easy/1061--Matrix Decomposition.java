/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
    static final int m=1000000007;
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		Scanner sc = new Scanner(System.in);
        int tst = sc.nextInt();
        long n,a;
        while (tst-- > 0) {
            n=sc.nextLong();
            a=sc.nextLong();
            System.out.println(Break(n,a));
        }
    }
    public static long Break(long n,long a){
        long p=0,k=1;
        for(int i=1;i<=n;i++){
            a=multiply(a,k);
            k=pow(a,2*i-1);
            p=add(p,k);
        }
        return p;
    }
    public static long multiply(long a, long b){
        a=a%m+(a<0?m:0);
        b=b%m+(b<0?m:0);
        return (a*b)%m;
    }
    public static long add(long a, long b){
        a=a%m+(a<0?m:0);
        b=b%m+(b<0?m:0);
        return (a+b)%m;
    }
    public static long pow(long a , long b){
        if(a==0)
            return 0;
        if(b==0)
            return 1;
        if(b%2==0) {
            long r=pow(a, b / 2);
            return multiply(r,r);
        }
        return (multiply(a,pow(a,b-1)));
    }
}