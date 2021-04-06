import java.util.*;
import java.lang.*;
import java.io.*;


class LPair{  
    public ArrayList<Integer> first;
    public ArrayList<Integer> second; 
    public LPair(){
        first = new ArrayList<>();
        second = new ArrayList<>();
    }   
}
 class home2p3 {
	
    public static long getGCD(long num, long den){
        if(num==0)
            return den;
        return getGCD(den%num,num);
    }
    
	public static class node {
		long sp_val;
		boolean locked;
		int color;
		int parent;
		LPair pairs;
		public node(int i) {
			sp_val=0;
			locked=false;
			color=1;
			parent=i;
			pairs=new LPair();
		}	
	}
	
	 public static void setUnion(int n, int m, int obj1, int obj2, ArrayList<node> quantum) { 
	        int p1 = quantum.get(obj1).parent;
			int p2 = quantum.get(obj2).parent;        
			if(p1==p2){
			    if(quantum.get(obj1).color==quantum.get(obj2).color){
			        quantum.get(p1).locked = true;
			    }
			}
			else{ 
			    int s1 = quantum.get(p1).pairs.first.size() + quantum.get(p2).pairs.second.size();
			    int s2 = quantum.get(p2).pairs.first.size() + quantum.get(p2).pairs.second.size();
			    if(s1<s2){
			        setUnion(n, m, obj2, obj1, quantum);
			    }
			    else{
			        quantum.get(p1).locked = quantum.get(p1).locked  || quantum.get(p2).locked ;
			        if(quantum.get(obj1).color==quantum.get(obj2).color){
			            for(int i=0;i<quantum.get(p2).pairs.first.size();i++){
			                quantum.get(p1).pairs.second.add(quantum.get(p2).pairs.first.get(i));
			                quantum.get(quantum.get(p2).pairs.first.get(i)).color = 0;
			                quantum.get(quantum.get(p2).pairs.first.get(i)).parent = p1;
			            }
			            for(int i=0;i<quantum.get(p2).pairs.second.size();i++){
			                quantum.get(p1).pairs.first.add(quantum.get(p2).pairs.second.get(i));
			                quantum.get(quantum.get(p2).pairs.second.get(i)).color= 1;
			                quantum.get(quantum.get(p2).pairs.second.get(i)).parent = p1;
			            }
			        }
			        else{
			            for(int i=0;i<quantum.get(p2).pairs.first.size();i++){
			                quantum.get(p1).pairs.first.add(quantum.get(p2).pairs.first.get(i));
			                quantum.get(quantum.get(p2).pairs.first.get(i)).color = 1;
			                quantum.get(quantum.get(p2).pairs.first.get(i)).parent = p1;
			            }
			            for(int i=0;i<quantum.get(p2).pairs.second.size();i++){
			                quantum.get(p1).pairs.second.add(quantum.get(p2).pairs.second.get(i));
			                quantum.get(quantum.get(p2).pairs.second.get(i)).color = 0;
			                quantum.get(quantum.get(p2).pairs.second.get(i)).parent = p1;
			            }
			        }
			        quantum.get(p2).pairs.first.clear();
			        quantum.get(p2).pairs.second.clear();
			    }
			}
	    }
	 
	public static ArrayList<node> quantum;
	public static void main (String[] args) throws java.lang.Exception {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		quantum=new ArrayList<>();
		quantum.add(new node(0));
		for(int i=1;i<=n;i++){
			node temp=new node(i);
		    temp.sp_val = sc.nextInt();
		    temp.locked=false;
		    temp.color=1;
		    temp.parent=i;
		    temp.pairs.first.add(i);
		    quantum.add(temp);
		}
		for(int i=1;i<=m;i++){
		    int type = sc.nextInt();
		    if(type==1){
		        int obj1 = sc.nextInt();
		        int w_obj1 = sc.nextInt();
		        quantum.get(obj1).sp_val = w_obj1;
		    }
		    else if(type==2){
		        int obj1 = sc.nextInt();
		        int obj2 = sc.nextInt();
		        
		        setUnion(n, m, obj1, obj2, quantum);    
		    }
		    else if(type==3){
		        int obj1 = sc.nextInt();
		        int obj2 = sc.nextInt();
		        int w_obj1 = sc.nextInt();	        
		        int p1 = quantum.get(obj1).parent;
		        int p2 = quantum.get(obj2).parent;      
		        
		            if(quantum.get(p1).locked==true || p1!=p2){
		                System.out.println("0");
		            }
		            else{
		                long num = (long)w_obj1*(quantum.get(obj1).sp_val);
		                long den = (long)quantum.get(obj2).sp_val;
		            
		                long gcd = getGCD
		                		(num,den);
		                num = num/gcd;
		                den = den/gcd;
		                if(quantum.get(obj1).color!=quantum.get(obj2).color){
		                    num = num*(-1);
		                }
		                System.out.println(num+"/"+den);
		            }
		        

		    }
		}
	}
}
