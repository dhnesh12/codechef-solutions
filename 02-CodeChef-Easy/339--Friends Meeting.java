import java.util.*;
 class test3
{
	static long ans;
	static long gcd(long a , long b)
	{
		if(a==0)
			return b;
		
		return gcd(b%a,a);
	}
	static void dfs(int n , LinkedList<Integer> arr[] , boolean visited[] , boolean con[] , int dp[])
	{
		visited[n] = true;
		for(Integer i : arr[n])
		{
			if(!visited[i])
			{
				dfs(i,arr,visited,con,dp);
				dp[n] += dp[i];
			}
		}
		if(con[n])
			dp[n]++;
	}
	static void dfs2(int n , LinkedList<Integer> arr[] , boolean visited[] , int dp[] , TreeMap<pair,Integer> map , int parent,int m)
	{
		visited[n] = true;
		if(parent != -1)
		{
			int val = 0;
			if(map.containsKey(new pair(parent , n)))
				val = map.get(new pair(parent,n));
			
			else
				val = map.get(new pair(n,parent));
			
			ans += (long)dp[n]*(long)(m-dp[n])*(long)val;
			//System.out.println(val + " " + dp[n]);
		}
		for(Integer i : arr[n])
		{
			if(!visited[i])
			{
			dfs2(i,arr,visited,dp,map,n,m);
			}
		}
	}
	public static void main(String []args)
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-- > 0)
		{
			int n  = sc.nextInt();
			int m = sc.nextInt();
			LinkedList<Integer> arr[] = new LinkedList[n+1];
			for(int i =1 ; i <= n ; i++)
			{
				arr[i] = new LinkedList<Integer>();
			}
			boolean visited[] = new boolean[n+1];
			TreeMap<pair,Integer> map = new TreeMap<pair,Integer>(new Compare());
			boolean con[] = new boolean[n+1];
			
			for(int i = 1 ; i <= n-1 ; i++)
			{
				int x = sc.nextInt();
				int y = sc.nextInt();
				int w = sc.nextInt();
				arr[x].add(y);
			    arr[y].add(x);
			   map.put(new pair(x,y), w);
			}
			
			for(int i = 0 ; i < m ; i++)
			{
				con[sc.nextInt()] = true;
			}
			ans = 0;
			int dp[] = new int[n+1];
			dfs(1,arr,visited,con,dp);
			for(int i = 1 ; i <= n ; i++)
			{
				visited[i] = false;
			}
			dfs2(1,arr,visited,dp,map,-1,m);
			//System.out.println(ans);
			ans = ans*2;
			long den = (long)m*(long)m;
			long gc = gcd(ans,den);
			ans = ans/gc;
			den = den/gc;
			System.out.println(ans + " " + den);
		}
	}
}

class pair
{
	int x , y;
	public pair(int x , int y)
	{
		this.x = x;
		this.y = y;
	}
}

class Compare implements Comparator<pair>
{
	public int compare(pair a , pair b)
	{
		if(a.x !=  b.x)
			return a.x - b.x;
		
		return a.y-b.y;
	}
}