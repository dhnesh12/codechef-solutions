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
        int tst = sc.nextInt();
        int n,m,p;
        int a[],b[],lcm,pos,temp;
        while (tst-- > 0) {
            n=sc.nextInt();
            m=sc.nextInt();
            a=new int[m+1];
            a[1]=1;
            p=sc.nextInt();
            primeFactors(p,p,2,a);
            for (int i=1;i<n;i++) {
                p=sc.nextInt();
                b=new int[m+1];
                primeFactors(p,p, 2, b);
                match(a,b);
            }
            temp=0;
            pos=1;
            for(int i=1;i<=m;i++){
                b=new int[m+1];
                b[1]=1;
                primeFactors(i,i,2,b);
                /*for(int j=1;j<=m;j++)
                    if (b[j]>0)
                        System.out.print(j+"^"+b[j]+" ");*/
                lcm=lcm(a,b);
                //System.out.println(" : "+i+" lcm : "+lcm);
                if(lcm>temp) {
                    temp=lcm;
                    pos=i;
                }
            }
            System.out.println(pos);
        }
    }
    public static void primeFactors(int k,int n,int i,int[] primeFactors){
        //System.out.println((int)Math.sqrt(k)+" n : "+n+" i : "+i+" prime factors : "+Arrays.toString(primeFactors));
        if(i>Math.sqrt(k)||n==1) {
            if(i>Math.sqrt(k))
                primeFactors[n]++;
            return;
        }
        if(n%i==0) {
            primeFactors[i]++;
            primeFactors(k,n / i, i, primeFactors);
            return;
        }
        primeFactors(k,n,i+1,primeFactors);
    }
    public static void match(int[] a,int[] b){
        for(int i=2;i<a.length;i++)
            if(a[i]<b[i])
                a[i]=b[i];
    }
    public static int lcm(int[] a,int[] b){
        int lcm=1;
        for(int i=2;i<a.length;i++)
            if(a[i]<b[i]){
                lcm*=(int)Math.pow(i,b[i]-a[i]);
            }
        return lcm;
    }
}