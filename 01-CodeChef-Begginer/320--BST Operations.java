/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
static class  Node{
		int data;
		int pos;
		Node left,right;
		Node(int i,int p){
			data=i;
			pos=p;
			left=right=null;
		}
	}
	 static Node root=null;
	    static Node insert(Node node,int i,int pos){
	        if(node==null){
	        	System.out.println(pos);
	            Node n=new Node(i,pos);
	            return n;
	            
	        }
	        if(node.data>i){
	            node.left=insert(node.left,i,2*pos);
	        }if(node.data<i){
	            node.right=insert(node.right,i,2*pos+1);
	        }
	        return node;
	    }
	    static Node delete(Node node,int i,int pos){
	        if(node==null)  return node;
	        
	        if(i<node.data){
	            node.left=delete(node.left,i,2*pos);
	        }else if(i>node.data){
	            node.right=delete(node.right,i,2*pos+1);
	        }else{
	            if(node.left==null&&node.right==null) {
	            	System.out.println(node.pos);
	        		node=null;
	        		return node;
	        	}
	            if(node.left==null) {
	            	 System.out.println(node.pos);
	                return node.right;
	            }if(node.right==null){
	            	 System.out.println(node.pos);
	                return node.left;
	            }else{
	                System.out.println(node.pos);
	                int minv=min(node.right);
	               node.data=minv;
	               node.right=deleteMin(node.right,minv);
	                
	            }
	           
	        }
	        return node;
	    }
	    static Node deleteMin(Node node,int i){
	        if(node==null)  return node;
	        
	        if(i<node.data){
	            node.left=deleteMin(node.left,i);
	        }else if(i>node.data){
	            node.right=deleteMin(node.right,i);
	        }else{
	        	if(node.left==null&&node.right==null) {
	        		node=null;
	        		return node;
	        	}
	            if(node.left==null) {
	                return node.right;
	            }
	            if(node.right==null){
	                return node.left;
	            }
	             
	                int minv=min(node.right);
	               node.data=minv;
	               node.right=deleteMin(node.right,minv);
	            
	      
	           
	        }
	        return node;
	    }
	    static int min(Node node){
	       if(node.left==null)  return node.data;
	       
	       return min(node.left);
	    }
		public static void main (String[] args) throws java.lang.Exception
		{
			FastReader sc=new FastReader();
			int q=sc.nextInt();
			for(int i=0;i<q;i++){
			    char c=sc.next().charAt(0);
			    int a=sc.nextInt();
			    if(c=='i'){
			       root= insert(root,a,1);
			    }else{
			      root=  delete(root,a,1);
			    }
			}
		}
		static class FastReader {
	        BufferedReader br;
	        StringTokenizer st;
	 
	        public FastReader()
	        {
	            br = new BufferedReader(
	                new InputStreamReader(System.in));
	        }
	 
	        String next()
	        {
	            while (st == null || !st.hasMoreElements()) {
	                try {
	                    st = new StringTokenizer(br.readLine());
	                }
	                catch (IOException e) {
	                    e.printStackTrace();
	                }
	            }
	            return st.nextToken();
	        }
	 
	        int nextInt() { return Integer.parseInt(next()); }
	 
	        long nextLong() { return Long.parseLong(next()); }
	 
	        double nextDouble()
	        {
	            return Double.parseDouble(next());
	        }
	 
	        String nextLine()
	        {
	            String str = "";
	            try {
	                str = br.readLine();
	            }
	            catch (IOException e) {
	                e.printStackTrace();
	            }
	            return str;
	        }
	    }
	
 
}
