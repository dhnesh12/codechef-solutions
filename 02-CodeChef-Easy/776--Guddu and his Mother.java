import java.io.*;
import java.util.*;
class code5
{
    public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t>0)
		{
			int n = sc.nextInt();
			int[] arr = new int[n+1];
			for(int i = 1;i<n+1;i++)
			{
				arr[i] = sc.nextInt();
			}
			
			int arr1[][] = new int[n+1][n+1];
			for(int i = 0;i<n+1;i++)
			{
				arr1[i][0] = 0;
				arr1[0][i] = 0;
			}
			
			for(int i = 1;i<n+1;i++)
			{
				arr1[i][i] = arr[i];
				for(int j = i+1;j<n+1;j++)
				{
					arr1[i][j] = arr[j]^arr1[i][j-1];
				}
			}
			
			int count=0;
			
			for(int i = 1;i<n;i++)//arr1[1][]
			{
				for(int j = i+1;j<n+1;j++)
				{
					for(int k = j;k<n+1;k++)
				    {
						//System.out.println(arr1[i][j-1] +  " " + arr1[j][k] + " i ="+  i + " j = " + j + " k =  " + k );
						if(arr1[i][j-1]==arr1[j][k])
						{
							count = count + 1;
						}
					}       
				}
			}
			System.out.println(count);
			/*for(int i = 1;i<n+1;i++)
			{
				
				for(int j = 1;j<n+1;j++)
				{
					System.out.print(arr1[i][j] + " ");
				}
				System.out.println();
			}*/
			t=t-1;
		}
		
	}
}