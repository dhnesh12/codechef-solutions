
import java.util.*;
import java.lang.*;

class CodeChef {

    static Scanner scan = new Scanner(System.in);

    public static void main (String[] args) {
        int t = scan.nextInt();
        while(t-- > 0) {
            int n = scan.nextInt();
            int firstBlock = 0, lastBlock = 0, zeroCount = 0, largestBlock = 0, currentBlock = 0;
            boolean firstOneAppeared = false;
            String chairs = scan.next();
            for(int i=0;i<n;i++) {
                int chair = chairs.charAt(i) == '1'? 1: 0;
                if(chair == 1) {
                    firstOneAppeared = true;
                    largestBlock = Math.max(largestBlock, currentBlock);
                    currentBlock = 0;
                } else {
                    zeroCount ++;
                    currentBlock ++;
                }
                if(!firstOneAppeared) {
                    firstBlock ++;
                }
            }
            lastBlock = currentBlock;
            largestBlock = Math.max(largestBlock, firstBlock + lastBlock);

            System.out.println(zeroCount - largestBlock);
        }
    }

}