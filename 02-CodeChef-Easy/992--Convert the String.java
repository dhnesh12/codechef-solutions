/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class Codechef
{ 
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0){
		    int n=sc.nextInt();
		    String a=sc.next();
		    String b=sc.next();
		    int[] pos=new int[26];
		    Arrays.fill(pos,-1);
		    ArrayList<ArrayList<Integer>> l=new ArrayList<>();
		    for(int i=0;i<26;i++)
		    l.add(new ArrayList<Integer>());
		    boolean f=false;
		    for(int i=0;i<n;i++){
		        pos[a.charAt(i)-'a']=i;
		        if(a.charAt(i)!=b.charAt(i)){
		            if(a.charAt(i)<b.charAt(i)){
		                f=true;
		                break;
		            }else{
		                l.get(b.charAt(i)-'a').add(i);
		            }
		        }
		    }if(f){
		        System.out.println("-1");
		        continue;
		    }
		    StringBuilder sb=new StringBuilder();
		    int count=0;
		    for(int i=25;i>=0;i--){
		        ArrayList<Integer> list=l.get(i);
		        if(list.size()>0&&pos[i]==-1){
		            f=true;
		            break;
		        }else if(list.size()==0)continue;
		        else{
		            sb.append(list.size()+1).append(" ");
		            sb.append(pos[i]+" ");
		            for(int j:list)sb.append(j+" ");
		            sb.append("\n");
		            count++;
		        }
		    }if(f){
		        System.out.println("-1");
		    }else{
		        System.out.println(count);
		        System.out.print(sb);
		    }
		}
	}
}
