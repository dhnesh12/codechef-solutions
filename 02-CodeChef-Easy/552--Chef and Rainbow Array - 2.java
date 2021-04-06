import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

class RainbowArray {

	public static void main(String args[]) throws NumberFormatException, IOException{

		BufferedReader inp = new BufferedReader (new InputStreamReader(System.in));
		//BufferedReader inp = new BufferedReader (new FileReader("rainbowArray.txt"));
		int N= Integer.parseInt(inp.readLine());
		if(N<13){
			System.out.println(0);
		}else{
			int half=(N%2==0)?N/2:N/2+1;
			long mod_base= 720 * (long) (Math.pow(10, 9)+7);
			long result=1;
			for(int i=0;i<6;i++){
				result=(result*(half-1-i))%mod_base;
			}
			result=result/720;
			System.out.println(result);
		}
		
	}
}