import java.io.*;
import java.util.*;
class Codechef{
	static BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		
	public static void main(String args[])throws IOException{
		int t=Integer.parseInt(br.readLine());
		StringBuilder res1=new StringBuilder();
		while(t-->0){

			String arr[]=br.readLine().split(" ");
			int n=Integer.parseInt(arr[0]);
			int e=Integer.parseInt(arr[1]);
			Map<Integer,Set<Integer>> adj=new HashMap<>();
			for(int i=1;i<=n;i++){
				adj.put(i,new HashSet<Integer>());
			}
			for(int i=0;i<e;i++){
				arr=br.readLine().split(" ");
				int u=Integer.parseInt(arr[0]);
				int v=Integer.parseInt(arr[1]);
				adj.get(u).add(v);
				adj.get(v).add(u);
			}
			Set<Integer> vis=new HashSet<>();
			long res=1;
			long m=(long)1e9+7;
			long c=0;
			int oldSize=0;
			for(int i=1;i<=n;i++){
				if(!vis.contains(i)){
					c=(c+1)%m;
					dfs(adj,i,vis);
					if(vis.size()>oldSize){
						res=(res%m*(vis.size()-oldSize)%m)%m;
					}
					oldSize=vis.size();
				}
			}
			res1.append(c+" "+res+"\n");
		}
		System.out.print(res1.toString());
	}
	static void dfs(Map<Integer,Set<Integer>> adj,int src,Set<Integer> vis){

		vis.add(src);
		if(adj.get(src).size()==0)
			return;
		for(int d:adj.get(src)){
			if(!vis.contains(d))
				dfs(adj,d,vis);
		}
	}
}