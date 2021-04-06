/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class Company{
    long offer;
    long vacany;
}
/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		
		Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();

        while (t>0){
            t--;
            int n=sc.nextInt();
            int m=sc.nextInt();

            long minSalary[]=new long[n];
            for(int i=0;i<n;i++){
                minSalary[i]=sc.nextLong();
            }

            Company arr[]=new Company[m];
            for(int i=0;i<m;i++){
                arr[i]=new Company();
                arr[i].offer=sc.nextLong();
                arr[i].vacany=sc.nextLong();
            }


            sc.nextLine();
            int sel[][]=new int[n][m];

            for(int i=0;i<n;i++){
                String str=sc.nextLine();
                for(int j=0;j<m;j++){
                    sel[i][j]=Integer.parseInt(str.charAt(j)+"");
                }
            }


      /*      for(long i:minSalary)
                System.out.print(i+" ");
            System.out.println();


            for(int i=0;i<m;i++){
                System.out.println(arr[i].offer+" "+arr[i].vacany);
            }


            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    System.out.print(sel[i][j]);
                }
                System.out.println();
            }*/

            long selected=0;
            long sum=0;
            long notSelected=0;
            boolean vis[]=new boolean[m];

        for(int i=0;i<n;i++){
            long max=-1;
            int index=-1;
            for(int j=0;j<m;j++){
                if(sel[i][j]==1){
                    if(arr[j].vacany>0  &&  arr[j].offer>max &&  arr[j].offer>minSalary[i]){
                        max=arr[j].offer;
                        index=j;
                    }
                }
            }
            if(index!=-1){
                sum+=max;
                arr[index].vacany--;
                selected++;
                vis[index]=true;
            }
        }

        for(int i=0;i<m;i++){
            if(!vis[i])
                notSelected++;
        }

            System.out.println(selected+" "+sum+" "+notSelected);
        }
        
        
	}
}
