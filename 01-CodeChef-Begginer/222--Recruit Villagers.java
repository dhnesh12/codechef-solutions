/* package codechef; // don't place package name! */

import javax.crypto.spec.PSource;
import java.security.AlgorithmConstraints;
import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Cocechef {


    public static void main(String[] args) throws java.lang.Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        int p=0,n=0;
        String s[]= br.readLine().split(" ");
        int m=Integer.parseInt(s[0]);
        int c=Integer.parseInt(s[1]);
        while (t-- > 0) {


            String s1[]= br.readLine().split(" ");
                int x=Integer.parseInt(s1[0]);
                int y=Integer.parseInt(s1[1]);
                int power=Integer.parseInt(s1[2]);
                int sum=y-(m*x)-c ;
                if(sum>0)
                    p+=power;
                if(sum<0)
                    n+=power;





                }

        System.out.println(Math.max(p,n));
            }

        }









