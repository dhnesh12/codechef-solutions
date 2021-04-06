/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		int t=Integer.parseInt(br.readLine());
		while(t-->0)
		{
		    String str=br.readLine();
		    PriorityQueue<int[]>q=new PriorityQueue<>((a,b)->{if(a[1]==b[1]) return a[0]-b[0];
		        else return b[1]-a[1];
		    });
		    int count[]=new int[26];
		    for(int i=0;i<str.length();i++)
		        count[str.charAt(i)-'a']++;
		    for(int i=0;i<26;i++)
		    {
		        if(count[i]>0)
		            q.add(new int[]{'a'+i,count[i]});
		    }
		    StringBuffer ans=new StringBuffer();
		    int cur[]=new int[2];
		    int prev[]=new int[2];
		    if(q.size()>0)
		    {
		        cur=q.poll();
		        cur[1]-=1;
		        ans.append(String.valueOf((char)cur[0]));
		        prev=cur;
		    }
		    while(q.size()>0)
		    {
		        cur=q.poll();
		        cur[1]=cur[1]-1;
		        ans.append(String.valueOf((char)cur[0]));
		        if(prev[1]>0)
		            q.add(prev);
		        prev=cur;
		    }
		    if(ans.length()!=str.length())
		        System.out.println("-1");
		    else
		    System.out.println(ans);
		}
	}
}
