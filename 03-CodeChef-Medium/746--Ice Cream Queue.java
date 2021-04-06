/**
 * @author sakt_coder
 * created on 2021-02-27 23:15
 */
import java.io.*;
import java.util.*;
public class Main
{
	private void solve()throws Exception
	{
		int n = nextInt();
		int w[] = new int[n+1];
		int p[] = new int[n+1];
		int v[] = new int[n+1];
		for(int i=1;i<=n;i++)
		{
			w[i] = nextInt();
			p[i] = nextInt();
			v[i] = nextInt();
		}

		int m = n/2;
		HashMap<Long, Long> map1 = new HashMap<>();
		outer: for(int mask=0;mask<(1<<m);mask++)
		{
			long sump = 0;
			long sumv = 0;
			for(int i=1;i<=m;i++)
				if(((mask>>(i-1))&1)==1)
				{
					if(w[i]<sump)
						continue outer;
					sump += p[i];
					sumv += v[i];
				}
			map1.put(sump, Math.max(sumv, map1.getOrDefault(sump, 0l)));
		}

		m = (n+1)/2;
		HashMap<Long, Long> map2 = new HashMap<>();
		outer: for(int mask=0;mask<(1<<m);mask++)
		{
			long sump = 0;
			long sumv = 0;
			long minp = Long.MAX_VALUE;
			for(int i=n/2+1;i<=n/2+m;i++)
				if(((mask>>(i-1-n/2))&1)==1)
				{
					if(w[i]<sump)
						continue outer;
					minp = Math.min(minp, w[i]-sump);
					sump += p[i];
					sumv += v[i];
				}
			map2.put(minp, Math.max(sumv, map2.getOrDefault(minp, 0l)));
		}

		List<Map.Entry<Long, Long>> list1 = new ArrayList<Map.Entry<Long, Long>>(map1.entrySet());
		List<Map.Entry<Long, Long>> list2 = new ArrayList<Map.Entry<Long, Long>>(map2.entrySet());

		Collections.sort(list1, (a, b)->Long.compare(a.getKey(), b.getKey()));
		Collections.sort(list2, (a, b)->Long.compare(a.getKey(), b.getKey()));

		long max = 0, ans=0;
		for(int j=0,i=0;j<list2.size();j++)
		{
			while(i<list1.size() && list1.get(i).getKey()<=list2.get(j).getKey())
			{
				max = Math.max(max, list1.get(i).getValue());
				i++;
			}
			ans = Math.max(ans, max+list2.get(j).getValue());
		}
		out.println(ans);
	}

	 
	///////////////////////////////////////////////////////////

	public void run()throws Exception
	{
		br=new BufferedReader(new InputStreamReader(System.in));
		st=null;
		out=new PrintWriter(System.out);

		try{
			int t=nextInt();
			while(t-->0)
				solve();

		}catch(Exception e){e.printStackTrace();}
		finally{
			br.close();
			out.close();
		}
		
	}
	public static void main(String args[])throws Exception{
		new Main().run();
	}
	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	String nextToken()throws Exception{
		while(st==null || !st.hasMoreTokens())
		st=new StringTokenizer(br.readLine());
		return st.nextToken();
	}
	String nextLine()throws Exception{
		return br.readLine();
	}
	int nextInt()throws Exception{
		return Integer.parseInt(nextToken());
	}
	long nextLong()throws Exception{
		return Long.parseLong(nextToken());
	}
	double nextDouble()throws Exception{
		return Double.parseDouble(nextToken());
	}
}
