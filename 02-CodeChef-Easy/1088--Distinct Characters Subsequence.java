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
				String s=br.readLine();
				int[]arr=new int[123];
				for(int i=0;i<s.length();i++)
				{
					arr[s.charAt(i)]++;
				}
				int cnt=0;
				for(int c ='a';c<='z';c++)
				{
					if(arr[c]!=0)
					{
						cnt++;
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
			
			/*int n=Integer.parseInt(br.readLine());
			int pos[]=new int[n];
			long k=Long.parseLong(br.readLine());
			int p=Integer.parseInt(br.readLine());
			String []s=br.readLine().split(" ");
			HashMap<Integer,Integer> map=new HashMap();
			for(int i=0;i<n;i++)
			{
				pos[i]=Integer.parseInt(s[i]);
				map.put(i+1,pos[i]);
			}
			Arrays.sort(pos);
			HashMap<Integer,Integer> h=new HashMap();
			for(int i=0;i<n;i++)
			{
				h.put(pos[i],i);
			}
			for(int i=0;i<p;i++)
			{
				
				
				int c=map.get(Integer.parseInt(br.readLine()));
				int d=map.get(Integer.parseInt(br.readLine()));
				//System.out.print(c+" "+d+"\n");
				if(Math.abs(c-d)<=k)
				{
					System.out.print("Yes"+"\n");
				}
				else
				{
				int max=Math.max(h.get(c), h.get(d));
				int min=Math.min(h.get(c), h.get(d));
				int flag=0;
				for(int j=min;j<max;j++)
				{
					if(pos[j+1]-pos[j]>k)
					{
						flag=1;
						break;
					}
						
					
				}
				if(flag==0)
				{
					System.out.print("Yes"+"\n");
				}
				else
				{
					System.out.print("No"+"\n");
				}
			}
			}
			
		}*/