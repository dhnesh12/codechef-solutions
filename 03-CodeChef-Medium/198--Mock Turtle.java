/*
    Answer = (K*F[2n-k-1])/(F[n-k]*F[n])
           k =blocks
           2*n =length
           k should be minimum and 
           length should be maximum
*/
import java.util.*;
import java.io.*;
class abc{

      static int mod=1000000007;
      static void  Fact(long F[]){
                       F[0]=1;
                    for(int i=1;i<F.length;i++)
                           F[i]=(i*F[i-1])%mod;
               } 
      static long Fermat(long a,long p){
                        long ans=1,b=p-2;
                            while(b>0){
                                if(b%2==1)
                                  ans=(ans*a)%mod;
                                  a=(a*a)%mod;
                                   b=b/2;
                            }
                         return(ans);
                   }
      static void Fact_Inv(long F_I[],long F[]){
                           int n=F.length;
                           F_I[n-1]=Fermat(F[n-1],mod); 
                         for(int i=n-2;i>=0;i--)
                             F_I[i]=((i+1)*F_I[i+1])%mod;
                   }
          static void fun(int STMax[][],int STMin[][],int n,int k,int a[],int b[]){
                            for (int i = 0; i <n; i++)
                               {
                                 STMax[i][0] = a[i];
                                 STMin[i][0] = b[i];
                               }
                            for (int j = 1; j <k; j++)
                               for (int i = 0; (i+(1 << j))<=n; i++)
                                     {
                                       STMin[i][j] = Math.min(STMin[i][j-1], STMin[i + (1 << (j - 1))][j - 1]);
                                       STMax[i][j] = Math.max(STMax[i][j-1], STMax[i + (1 << (j - 1))][j - 1]);
                                    }
                    } 

    public static void main(String[] args){ 

                 Scanner sc = new Scanner(System.in);
                 PrintWriter out = new PrintWriter(System.out);
                    
                        long F[] = new long[300000];
                        long F_I[] = new long[300000];
                        Fact(F); Fact_Inv(F_I,F);
                     int n = sc.nextInt();
                     int t = sc.nextInt();
                     int a[] = new int[n];
                     int b[] = new int[n];
                          for(int i=0;i<n;i++)
                               a[i] = sc.nextInt();
                          for(int i=0;i<n;i++)
                               b[i] = sc.nextInt();

                          int k = (int)(Math.log(n)/Math.log(2))+1;
                   int STMax[][] = new int[n][k]; // Sparse Table for storing maximum
                   int STMin[][] = new int[n][k]; // Sparse Table for storing minimum
                   int Log[] = new int[n+1];
                       fun(STMax,STMin,n,k,a,b);
                       fun(STMax,STMin,n,k,a,b);
                            Log[1] = 0;
                      for (int i = 2; i <=n; i++)
                            Log[i] = Log[i/2]+1; 

                      for(int ii=1;ii<=t;ii++){
                            int l = sc.nextInt()-1;
                            int r = sc.nextInt()-1;
                             int j=Log[r-l+1];
                           int min = Math.min(STMin[l][j],STMin[r-(1<<j)+1][j]);
                           int max = Math.max(STMax[l][j],STMax[r-(1<<j)+1][j]);
                                n=max/2;   
                            int   B=min;
                            long ans=0;
                            if(B<=n){
                                     ans=(F[2*n-B-1]*B)%mod;
                                     ans=(ans*F_I[n-B])%mod;
                                     ans=(ans*F_I[n])%mod;
                             }
                          out.println(ans);
                     }
                    out.flush();
    }
}