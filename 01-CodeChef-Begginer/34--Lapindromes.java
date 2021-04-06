import java.util.*;

class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    
	    try {
	        Scanner sc = new Scanner(System.in);
	        int t = sc.nextInt();
	        for(int j=0;j<t;j++){
	            String str = sc.next();
	            if(isLapindrome(str)){
	                System.out.println("YES");
	            }else{
	                System.out.println("NO");
	            }
	            
	        }
	        
	        
	    } catch(Exception e) {
	        return;
	    } finally {
	    }
	}
	static boolean isLapindrome(String str){
	    int len=str.length();
	    char sub1[] = str.substring(0,len/2).toCharArray();
	    char sub2[] = str.substring(len-sub1.length,len).toCharArray();
	    Arrays.sort(sub1);
	    Arrays.sort(sub2);
	    int count=0;
	    for(int i=0;i<sub1.length;i++){
	        if(sub1[i] == sub2[i]){
	            count++;
	        }else{
	            break;
	        }
	    }
	    if(count == sub1.length){
	        return true;
	    }else{
	        return false;
	    }
	}
}
