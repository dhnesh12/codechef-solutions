import java.util.*;
class codechef
{
    public static void main(String args[])
    {
        Scanner sc=new Scanner(System.in);
        int mod=1000007;
        int t=sc.nextInt();
        while(t-->0)
        {
            int n=sc.nextInt();
            int w=sc.nextInt();
            int dp[][][]=new int[201][21][10];
            for(int i=0;i<201;i++)
            {
                for(int j=0;j<21;j++)
                {
                    for(int k=0;k<10;k++)
                        dp[i][j][k]=-1;
                }
            }
            for(int i=0;i<10;i++)
                dp[0][0][i]=1;
            for(int i=0;i<n;i++)
            {
                for(int j=(i==0)?1:0;j<10;j++)
                {
                    for(int k=0;k<10;k++)
                    {
                        int diff=Math.abs(j-k);
                        for(int l=0;l<=w;l++)
                        {
                            if(dp[l][i][j]!=-1)
                            {
                                int next=l+diff;
                                if(next<=w)
                                {
                                    if(dp[next][i+1][k]==-1)
                                        dp[next][i+1][k]=dp[l][i][j]%mod;   
                                    else
                                        dp[next][i+1][k]=(dp[next][i+1][k]+dp[l][i][j])%mod;
                                }
                            }
                        }
                    }
                }
            }
            long total=0;
            for(int i=0;i<10;i++)
            {
                if(dp[w][n-1][i]!=-1)
                    total=(total+dp[w][n-1][i])%mod;
            }
            System.out.println(total);
        }
    }
} 