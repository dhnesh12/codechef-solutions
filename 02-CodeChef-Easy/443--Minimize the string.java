import java.util.*;

class CodeChef {
    static Scanner scan = new Scanner(System.in);

    public static void main(String[] args) {
        int t = scan.nextInt();
        while(t-- > 0) {
            solve();
        }
    }

    static void solve() {
        int n = scan.nextInt();
        int ab = 0, ba = 0, a = 0, b = 0;

        for(int i=0;i<n;i++) {
            String s = scan.next();
            if("ab".equals(s))
                ab++;
            else if("ba".equals(s))
                ba++;
            else if("a".equals(s) || "aa".equals(s))
                a++;
            else
                b++;
        }

        int ans = 0;

        if(ab == 0 && ba == 0) {
            ans += (a > 0)? 1: 0;
            ans += (b > 0)? 1: 0;
        } else if(ab == 0) {
            ans = 2 * ba;
        } else if(ba == 0) {
            ans = 2 * ab;
        } else {
            if(ab == ba)
                ans = 2 * ab + 1;
            else
                ans = 2 * Math.max(ab, ba);
        }

        System.out.println(ans);
    }
}
