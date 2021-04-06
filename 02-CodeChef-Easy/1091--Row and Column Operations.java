import java.util.*;
import java.lang.*;
import java.io.*;
class amit{
	public static void main(String[] args){
		
		
		try
		{
			Scanner sc=new Scanner(System.in);
			
			int n=sc.nextInt();
			long q=sc.nextInt();
			long row[]=new long[n+1];
			long col[]=new long[n+1];
			long max1=0;
			long max2=0;
			while(q-->0)
			{
				
				String s=sc.next();
				int val=sc.nextInt();
				int x=sc.nextInt();
				if(s.charAt(0)=='R')
				{
					row[val]=row[val]+x;
					max1=Math.max(max1,row[val]);
				}
				else if(s.charAt(0)=='C')
				{
					col[val]=col[val]+x;
					max2=Math.max(max2,col[val]);
				}
			}
			System.out.print(max1+max2+"\n");
		
		}
				catch(Exception e)
		{
			
		}
	}
}