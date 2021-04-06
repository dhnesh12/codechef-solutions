import java.lang.*;
import java.util.*;
class Main
{
	public static void main (String[] args) {
		Scanner sc=new Scanner(System.in);
		int test=sc.nextInt();
		for(int k=0;k<test;k++)
		{
			int m=sc.nextInt();
			int n=sc.nextInt();
			long a[][]=new long[m][n];
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<n;j++)
				{
					a[i][j]=sc.nextLong();
				}
			}
			long b[][]=new long[m][n];
			for(int i=0;i<m;i++)
			{
				b[i][n-1]=a[i][n-1];
			}
			for(int i=0;i<m;i++)
			{
				for(int j=n-2;j>=0;j--)
				{
					b[i][j]+=a[i][j]+b[i][j+1];
				}
			}
			
			long sum=0;
			for(int j=0;j<n;j++)
			{
				for(int i=1;i<m;i++)
				{
					sum=Math.max(sum,b[i][j]+b[i-1][j]);
					b[i][j]=Math.max(b[i][j],a[i][j]+b[i-1][j]);
				}
			}
			System.out.println(sum);
		}
		
	}
}