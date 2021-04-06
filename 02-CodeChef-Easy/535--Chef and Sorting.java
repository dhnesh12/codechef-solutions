import java.io.*;
import java.util.*;

class steps{
	public static void main(String[] bb) throws IOException
	{
		Scanner sc =  new Scanner(System.in);
		int t = sc.nextInt();
		while(t-->0)
		{
			int n = sc.nextInt();
			int[] arr = new int[n];
			int[] arr1 = new int[n];
			for(int i=0;i<n;i++)
			{
				arr[i] = sc.nextInt();
				arr1[i] = arr[i];
			}
			Arrays.sort(arr1);
			int cur=0;
			int sub = 0;
			for(int i=0;i<n;i++)
			{
				if(arr[i]==arr1[cur])
				{
					sub++;
					cur++;
				}		
			}
			int ans = n-sub;
			System.out.println(ans);
		}
	}
}