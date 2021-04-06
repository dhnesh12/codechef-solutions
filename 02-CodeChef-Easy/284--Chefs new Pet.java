import java.util.*;
import java.io.*;
class harejump 
{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        for(int z=1;z<=t;z++)
        {
            long n=sc.nextLong();
            int k=sc.nextInt();
            long mat1[][]=new long[16][16];
            long mat2[][]=new long[16][16];
            for(int i=0;i<k;i++)
            {
                int num=sc.nextInt();
                mat1[0][num-1]=1;
                mat2[0][num-1]=1;
            }
            for(int i=1;i<16;i++)
            {
                mat1[i][i-1]=1;
                mat2[i][i-1]=1;
            }
            matrix(mat1, mat2, n);
            System.out.println(mat1[0][0]);
        }
    }
    static void matrix(long[][] mat,long[][] mat2,long n)
    {
        if(n==0||n==1)
        return;
        matrix(mat,mat2,n/2);
        multiply(mat,mat);
        if(n%2!=0)
        {
            multiply(mat,mat2);
        }
        /*while(n>0)
        {
        if(n%2!=0)
        {
            multiply(mat,mat2);
        }
        multiply(mat,mat);
        n/=2;*/

    }
    static void multiply(long[][] mat,long [][] copy)
    {
        long[][] result=new long[mat.length][mat.length];
        
        for(int i=0;i<mat.length;i++)
        {
            for(int j=0;j<mat.length;j++)
            {
                for(int k=0;k<mat.length;k++)
                {
                    result[i][j]=(result[i][j]+mat[i][k]*copy[k][j])%1000000007;
                }
            }
        }
        for(int i=0;i<mat.length;i++)
            for(int j=0;j<mat.length;j++)
            {
                mat[i][j]=result[i][j];
            }
    }
    
}
 