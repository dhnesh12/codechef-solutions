import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException; 
import java.io.InputStreamReader; 
import java.util.Scanner; 
import java.util.StringTokenizer; 
import java.util.*;
import java.io.*;
class codeforces 
{ 
   static class Student{
       int x,y;
        Student(int x,int y){
            this.x=x;
            this.y=y;
        }
    }
    static int prime[];
    static void sieveOfEratosthenes(int n) 
    { 
        // Create a boolean array "prime[0..n]" and initialize 
        // all entries it as true. A value in prime[i] will 
        // finally be false if i is Not a prime, else true. 
        int pos=0;
        prime= new int[n+1]; 
        for(int p = 2; p*p <=n; p++) 
        { 
            // If prime[p] is not changed, then it is a prime 
            if(prime[p] == 0)
            { 
                // Update all multiples of p
                prime[p]=p;
                for(int i = p*p; i <= n; i += p) 
                    prime[i] = p; 
            } 
        } 
    }
static    class Sortbyroll implements Comparator<Student> 
{ 
    // Used for sorting in ascending order of 
    // roll number 
    public int compare(Student c, Student b) 
    { 
        return c.y-b.y;
    } 
} 
    static class FastReader 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public FastReader() 
        { 
            br = new BufferedReader(new
                     InputStreamReader(System.in)); 
        } 
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
            { 
                try
                { 
                    st = new StringTokenizer(br.readLine()); 
                } 
                catch (IOException  e) 
                { 
                    e.printStackTrace(); 
                } 
            } 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            String str = ""; 
            try
            { 
                str = br.readLine(); 
            } 
            catch (IOException e) 
            { 
                e.printStackTrace(); 
            } 
            return str; 
        } 
    }
    static class Edge{
        int a,b;
        Edge(int a,int b){
            this.a=a;
            this.b=b;
        }
    }
    static int parent[];
    static int rank[];
    static int k;
    //static int seg[];
    static class Node{
        int x,ans;
        int left[],right[];
        Node(){
            this.x=0;
            this.left=new int[k];
            this.right=new int[k];
            this.ans=Integer.MAX_VALUE;
        }
    }
    static Node seg[];
    public static void main(String[] args){
        //long sum=0;
        FastReader sc=new FastReader();
        int n,m,i;
        n=sc.nextInt();
        k=sc.nextInt();
        m=sc.nextInt();
        int a[]=new int[n];
        for(i=0;i<n;i++)
            a[i]=sc.nextInt();
        seg=new Node[4*n];
        int q[][]=new int[m][2];
        for(i=0;i<m;i++){
            q[i][0]=sc.nextInt();
            q[i][1]=sc.nextInt();
        }
        if(k!=1){
        build(0,n-1,0,k);
       for(i=0;i<n;i++){
            update(i,i,0,n-1,a[i],a[i],0,k);
        }
        //System.out.println(seg[0].ans);
        for(i=0;i<m;i++){
            //if(k!=1)
            update(q[i][0]-1,q[i][0]-1,0,n-1,q[i][1],a[q[i][0]-1],0,k);
            a[q[i][0]-1]=q[i][1];
            if(seg[0].ans==Integer.MAX_VALUE)
                System.out.println(-1);
            else
            System.out.println(seg[0].ans);
        }
        }
        else{
            for(i=0;i<m;i++)
            System.out.println(1);
        }
       // System.out.println(seg[0].ans);
    }
    static void combine(Node p,Node left,Node right,int k){
        int i,j;
        for(i=0;i<k;i++){
            p.left[i]=Math.min(left.left[i],right.left[i]);
            p.right[i]=Math.max(right.right[i],left.right[i]);
        }
        p.ans=Math.min(left.ans,right.ans);
        ArrayList<Student>lp=new ArrayList<>();
        ArrayList<Student>rp=new ArrayList<>();
        for(i=0;i<k;i++){
            if(left.right[i]!=Integer.MIN_VALUE)
                lp.add(new Student(i,left.right[i]));
            if(right.left[i]!=Integer.MAX_VALUE)
                rp.add(new Student(i,right.left[i]));
        }
       /* if(lp.size()==0||rp.size()==0)
        return;*/
        if(lp.size()==0||rp.size()==0)
        return;
        Collections.sort(lp,new Sortbyroll());
        Collections.sort(rp,new Sortbyroll());
        HashMap<Integer,Integer>map=new HashMap<>();
        ArrayList<Student>a=new ArrayList<>();
        for(i=0;i<lp.size();i++)
        a.add(new Student(lp.get(i).x,lp.get(i).y));
        for(i=0;i<rp.size();i++)
        a.add(new Student(rp.get(i).x,rp.get(i).y));
        i=0;j=0;
        while(i<a.size()){
            if(map.size()<k){
                if(!map.containsKey(a.get(i).x))
                map.put(a.get(i).x,1);
                else
                map.put(a.get(i).x,map.get(a.get(i).x)+1);
                ++i;
            }
            else{
                p.ans=Math.min(p.ans,a.get(i-1).y-a.get(j).y+1);
                map.put(a.get(j).x,map.get(a.get(j).x)-1);
                if(map.get(a.get(j).x)==0)
                map.remove(a.get(j).x);
                ++j;
            }
        }
        while(j<a.size()&&map.size()>=k){
            p.ans=Math.min(p.ans,a.get(i-1).y-a.get(j).y+1);
                map.put(a.get(j).x,map.get(a.get(j).x)-1);
                if(map.get(a.get(j).x)==0)
                map.remove(a.get(j).x);
                ++j;
        }
    }
    static void update(int l,int r,int s,int e,int c,int o,int in,int k){
        if(s>e||e<l||s>r)
            return;
        if(s==e&&s==l){
           /* for(int i=0;i<k;i++)
		{
			seg[in].left[i]=Integer.MAX_VALUE;
			seg[in].right[i]=Integer.MIN_VALUE;
		}*/
		seg[in].left[o-1]=Integer.MAX_VALUE;
		seg[in].right[o-1]=Integer.MIN_VALUE;
		//seg[in].ans=Integer.MAX_VALUE;
		seg[in].left[c-1]=s;
		seg[in].right[c-1]=s;
		return;
        }
        update(l,r,s,(s+e)/2,c,o,2*in+1,k);
        update(l,r,(s+e)/2+1,e,c,o,2*in+2,k);
        combine(seg[in],seg[2*in+1],seg[2*in+2],k);
    }
    static void build(int s,int e,int in,int k){
        int i;
        if(s>e)
            return;
        if(s==e){
            seg[in]=new Node();
            for(i=0;i<k;i++){
                seg[in].left[i]=Integer.MAX_VALUE;
                seg[in].right[i]=Integer.MIN_VALUE;
            }
            return;
        }
        build(s,(s+e)/2,2*in+1,k);
        build((s+e)/2+1,e,2*in+2,k);
        seg[in]=new Node();
        for(i=0;i<k;i++){
            seg[in].left[i]=Math.min(seg[2*in+1].left[i],seg[2*in+2].left[i]);
            seg[in].right[i]=Math.max(seg[2*in+1].right[i],seg[2*in+2].right[i]);
        }
    }
 /*static long power(long x, long y, long p) 
{ 
    long res = 1;      // Initialize result 
  
    x = x % p;  // Update x if it is more than or  
                // equal to p 
  
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if ((y & (long)1)%2!=0) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y>>1; // y = y/2 
        x = (x*x) % p;   
    } 
    return res%p; 
} */
   static int find(int x) 
    { 
        // Finds the representative of the set 
        // that x is an element of 
        while(parent[x]!=x) 
        { 
            // if x is not the parent of itself 
            // Then x is not the representative of 
            // his set,
            x=parent[x];
  
            // so we recursively call Find on its parent 
            // and move i's node directly under the 
            // representative of this set 
        } 
  
        return x; 
    }
    static void union(int x, int y) 
    { 
        // Find representatives of two sets 
        int xRoot = find(x), yRoot = find(y); 
  
        // Elements are in the same set, no need 
        // to unite anything. 
        if (xRoot == yRoot) 
            return; 
  
         // If x's rank is less than y's rank 
        if (rank[xRoot] < rank[yRoot]) 
  
            // Then move x under y  so that depth 
            // of tree remains less 
            parent[xRoot] = yRoot; 
  
        // Else if y's rank is less than x's rank 
        else if (rank[yRoot] < rank[xRoot]) 
  
            // Then move y under x so that depth of 
            // tree remains less 
            parent[yRoot] = xRoot; 
  
        else // if ranks are the same 
        { 
            // Then move y under x (doesn't matter 
            // which one goes where) 
            parent[yRoot] = xRoot; 
  
            // And increment the the result tree's 
            // rank by 1 
            rank[xRoot] = rank[xRoot] + 1; 
        } 
    } 
    static long gcd(long a, long b) 
    { 
        if (a == 0) 
            return b; 
        return gcd(b % a, a); 
    }
}