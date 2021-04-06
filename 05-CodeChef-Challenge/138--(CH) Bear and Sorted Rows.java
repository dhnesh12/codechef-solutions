/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class sortrow
{
	public static void main (String[] args) throws IOException
	{
		// your code goes here
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		Scanner sc=new Scanner(System.in);
		    int n=sc.nextInt();
		    ArrayList<ArrayList<Integer>> al=new ArrayList();
                   
		    for(int j=0;j<n;j++){
                         ArrayList<Integer> al1=new ArrayList();
		    for(int i=0;i<n;i++){
		        int tem=sc.nextInt();
		       // br.readLine();
		        al1.add(tem);
		    }
		   al.add(al1);
		}
                    for(int i=0;i<n;i++){
                        Collections.sort(al.get(i));
                        for(int j=0;j<n;j++){
                            System.out.print(al.get(i).get(j)+" ");
                        }
                        System.out.println();
                    }
                     // System.out.println(al.get(2).get(2));
                    
	}
}
