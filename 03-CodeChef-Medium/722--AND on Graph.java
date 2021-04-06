/**
 * @author sakt_coder
 * created on 2021-02-28 12:01
 */
import java.io.*;
import java.util.*;
public class Main
{
	int t ;
	int s ;
	ArrayList<Edge> edges[] ;
	int m ;
	int n ;
	private void solve()throws Exception
	{
		n = nextInt();
		m = nextInt();
		edges = new ArrayList[n+1];
		for(int i=1;i<=n;i++)
			edges[i] = new ArrayList<>();
		for(int i=1;i<=m;i++)
		{
			Edge e = new Edge(nextInt(), nextInt(), nextInt(), nextInt());
			edges[e.a].add(e);
			edges[e.b].add(e);
		}
		s = nextInt();
		t = nextInt();
		int k = nextInt();

		int mask = 0;
		long ans = Long.MAX_VALUE;
		for(int bit=29;bit>=0;bit--){
			if(((k>>bit)&1)==1){
				mask |= 1<<bit;
				continue;
			}
			ans = Math.min(ans, dijkstra(mask | (1<<bit)));
		}
		ans = Math.min(ans, dijkstra(k));
		out.println(ans==Long.MAX_VALUE?-1:ans);
	}

	long dijkstra(int mask) {

		PriorityQueue<Pair> pq = new PriorityQueue<>((p, q)->Long.compare(p.second, q.second));
		long dist[] = new long[n+1];
		Arrays.fill(dist, Long.MAX_VALUE);
		pq.add(new Pair(s, 0));
		dist[s] = 0;

		while(!pq.isEmpty()){
			Pair p = pq.remove();
			int v = p.first;
			long d = p.second;
			if(d != dist[v])
				continue;
			for(Edge e:edges[v]) {
				int next = e.adjacent(v);
				if((e.v & mask)==mask && dist[next] > d+e.c)
				{
					dist[next] = d + e.c;
					pq.add(new Pair(next, dist[next]));
				}
			}
		}
		return dist[t];

	}

	class Pair {
		int first;
		long second;
		Pair(int first, long second){
			this.first = first;
			this.second = second;
		}
	}

	class Edge
	{
		int a, b, c, v;
		Edge(int a, int b, int c, int v){
			this.a = a;
			this.b = b;
			this.c = c;
			this.v = v;
		}
		int adjacent(int x){
			return x==a?b:a;
		}
	}

	 
	///////////////////////////////////////////////////////////

	public void run()throws Exception
	{
		br=new BufferedReader(new InputStreamReader(System.in));
		st=null;
		out=new PrintWriter(System.out);

		try{
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
