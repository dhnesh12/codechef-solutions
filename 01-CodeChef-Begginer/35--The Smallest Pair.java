import java.util.*;

class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    
	    try {
	        Scanner sc = new Scanner(System.in);
	        int t = sc.nextInt();
	        for(int j=0;j<t;j++){
	            int n = sc.nextInt();
	            long ar[] = new long[n];
	            for(int i=0;i<n;i++){
	                ar[i] = sc.nextInt();
	            }
	            Arrays.sort(ar);
	            System.out.println(ar[0]+ar[1]);
	        }
	        
	        
	    } catch(Exception e) {
	        return;
	    } finally {
	    }
	}
}
