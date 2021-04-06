import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

/**
 *
 * @author Fabian
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)throws IOException {
     BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
     BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
     int t=Integer.parseInt(br.readLine().trim());
        for (int i = 0; i < t; i++) {
        String cad=br.readLine().trim(),res="NO",sub="";
        
       int M=cad.length();
            if (M==1) {
                res="NO";}
            else if (M%2==0) {
                 int temp=computeLPSArray(cad,M);
             
                 if (temp==M/2) {
                    res="YES";
                }
                 
            }else{
                
                for (int j = 0; j < M; j++) {
                  StringBuilder sb=new StringBuilder(cad);
                 int temp=computeLPSArray(sb.deleteCharAt(j).toString(),M-1);
                   
                 if (temp>=M/2) {
                    res="YES";
                    break;
                }
                }
                
                
            }
           
           
       
            bw.write(res);
            bw.write("\n");
        
            
        
        }
        bw.close();
        
     
     
    }
    public static int computeLPSArray(String pat, int M) 
    { 
 
        
        int len = 0; 
        int i =M/2; 
        int lps[]=new int[M];
        lps[0] = 0; 
        int max=0;
      
        while (i < M) {

            if (pat.charAt(i) == pat.charAt(len)) { 
               
                len++; 
                lps[i] = len; 
                i++; 
            } 
            else  { 
              
                if (len != 0) {
                 
                    len = lps[len - 1]; 
  
                  
                } 
                else { 
                     
                    lps[i] = len; 
                    i++; 
                } 
            }
            if (len>max) {
                max=len;
            }
        } 
    return max;
    } 
}
