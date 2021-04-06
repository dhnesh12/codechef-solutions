import java.util.*;
import java.lang.*;
import java.io.*;
class amit{
	public static void main(String[] args){
		
		
		try
		{
			 BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
			int t=Integer.parseInt(br.readLine());
			while(t-->0)
			{
				String a=br.readLine();
				String b=br.readLine();
				int arr1[]=new int[123];
				int arr2[]=new int[123];
				Arrays.fill(arr1, 0);
				Arrays.fill(arr2,0);
				long cnt=0;
				for(int i=0;i<a.length();i++)
				{
					char c=a.charAt(i);
					arr1[c]++;
				}
				for(int i=0;i<b.length();i++)
				{
					char c=b.charAt(i);
					arr2[c]++;
				}
				for(int i=0;i<123;i++)
				{
					
					if(arr1[i]!=0&&arr2[i]!=0)
					{
						cnt=cnt+Math.min(arr1[i], arr2[i]);
					}
				}
				System.out.print(cnt+"\n");
			}
		}
				catch(Exception e)
		{
			
		}
	}
}