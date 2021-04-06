import java.util.*;
import java.lang.*;
import java.util.concurrent.atomic.AtomicBoolean;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
    public static void main (String[] args) throws java.lang.Exception
    {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while( t-- > 0 ){
           String[] colors = new String[6];
           for(int i=-0;i<6;i++){
               colors[i]=sc.next();
           }
           if(colors[0].equals(colors[2]) && colors[0].equals(colors[4])
           ||colors[0].equals(colors[2]) && colors[0].equals(colors[5])
           ||colors[0].equals(colors[3]) && colors[0].equals(colors[4])
           ||colors[0].equals(colors[3]) && colors[0].equals(colors[5])
           ||colors[1].equals(colors[2]) && colors[1].equals(colors[4])
           ||colors[1].equals(colors[2]) && colors[1].equals(colors[5])
           ||colors[1].equals(colors[3]) && colors[1].equals(colors[4])
           ||colors[1].equals(colors[3]) && colors[1].equals(colors[5])){
               System.out.println("YES");
               continue;
           }
            System.out.println("NO");
        }
    }
}
