import java.util.*;
import java.lang.*;
import java.io.*;
public class Main {
	
  
	public static void main(String[] args)throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while(t-->0){
		    String[] st  = br.readLine().split(" ");
		    long m = Long.parseLong(String.valueOf(st[0]));
		    long n = Long.parseLong(String.valueOf(st[1]));
		    
		    long val = m+n;
		    long val2 = val*(val+1)/2 + m + 1;
		    System.out.println(val2);
		    
		}
	}

}


