import java.util.*;
class Chetan{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int test=sc.nextInt();
        while(test!=0){
            String s=sc.next();int count=0;
            for(int i=0;i<s.length();i++){
                if(s.charAt(i)=='4' || s.charAt(i)=='7'){
                    count++;
                }
            }
            System.out.println(s.length()-count);
            test--;
        }
    }
}