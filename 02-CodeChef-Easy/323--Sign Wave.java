import java.util.*;
public class Main {
	public static void main(String args[])
	{
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0)
		{
			long s=sc.nextLong();
			long c=sc.nextLong();
			long k=sc.nextLong();
			long ans=0;
			
			if(s>=k)
				ans=3;
			int i=0;
			
			for(i=1;i<=Math.min(s, c);i++)
			{
						if(s-i+1>=k)
							ans+=Math.pow(2, i);
			}
					while(i<=c && k==1)
					{	
						ans+=Math.pow(2, i);
						i++;
					}
					for(;i<=s;i++)
					{
						if(s-i>=k)
							ans+=Math.pow(2, i);
					}
					
					System.out.println(ans);
		}
		sc.close();
	}
}
