import java.util.*;
import java.lang.*;
import java.io.*;
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t>0){
		    int f=0;
		    String s=sc.next();
		    int n=s.length();
		    String color="Red";
		    for(int i=0;i<n;i++){
		        if (color=="Red"){
		            if (s.charAt(i)=='1')
		            color="Blue";
		        }
		        else
		        if (color=="Blue"){
		            if (s.charAt(i)=='0')
		            color="Yellow";
		            }
		        else
		        if (color=="Yellow"){
		            if (s.charAt(i)=='0')
		            color="Pink";
		            if (s.charAt(i)=='1')
		            color="Blue";
		            }
		        else
		        if (color=="Pink"){
		            if (s.charAt(i)=='0'){
		            color="Green";
		            if (i==n-1){
		            f=1;
		            break;}
		            }
		            if (s.charAt(i)=='1')
		            color="Blue";
		            }
		        else
		        if (color=="Green"){
		            if (s.charAt(i)=='0')
		            color="Red";
		            if (s.charAt(i)=='1')
		            color="Blue";
		            }
		    }
	if (f==0)
	System.out.println("NO");
	else
	System.out.println("YES");
	t=t-1;	    
	}
	}
}
