import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/* Name of the class has to be "Main" only if the class is public. */

class Codechef
{
    private static BufferedReader br;
    private static String input; 
    private static final long MOD = 1000000007;
    
    static{
        br = new BufferedReader(new InputStreamReader(System.in));
    }
    
    private static String[] getInput() throws java.lang.Exception{
        input  = br.readLine();
        return input.split(" ");
    }
    
    private static int sToi(String string){
        return Integer.parseInt(string);
    }
    
    private static long sTol(String string){
        return Long.parseLong(string);
    }
    
	public static void main (String[] args) throws java.lang.Exception
	{
        String tokens[] = getInput();
        int TEST = sToi(tokens[0]);
        for(int test=0; test < TEST; test++){
            int n, m, x, y;
            tokens = getInput();
            n = sToi(tokens[0]);
            m = sToi(tokens[1]);
            x = sToi(tokens[2]);
            y = sToi(tokens[3]);
            
            System.out.println(solve(n, m, x, y));
        }
	}
	
	private static long solve(int n, int m, int x, int y){
	    long total = 0;
	    
	    for(int i=1; i<=n; i++){
	        for(int j=1; j<=m; j++){
	            if(i == x && j== y)
	                continue;
	                
	            long count = ((n*m)-2)-(n+m-2 + countDiag(i, j, n, m));
                total += count;
	        }
	    }
	    
	    long topL = Math.min(x-1, y-1) * (Math.min(n-x, m-y)+1);
        long topR = Math.min(x-1, m-y) * (Math.min(n-x, y-1)+1);
        long botL = Math.min(n-x, y-1) * (Math.min(x-1, m-y)+1);
        long botR = Math.min(n-x, m-y) * (Math.min(x-1, y-1)+1);
        long top  = (x-1) * (n-(x-1));
        long bot  = (n-x) * (n-(n-x));
        long left = (y-1) * (m-(y-1));
        long right = (m-y) * (m-(m-y));
	    
	    return total + topL + topR + botL + botR + top + bot + left + right;
	}
	
	static long countDiag(int currRow, int currCol, int totalRow, int totalCol){
 	    int topLeft = Math.min(currRow-1, currCol-1);
 	    int topRight = Math.min(currRow-1, totalCol-currCol);
	    
 	    int bottomLeft = Math.min(totalRow-currRow, currCol-1);
 	    int bottomRight = Math.min(totalRow-currRow, totalCol-currCol);
	    
 	    return topLeft + topRight + bottomLeft + bottomRight;
 	}
	
}