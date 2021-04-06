import java.util.*;
class pals {
    public static void main (String[] args) throws java.lang.Exception {
        Scanner sc = new Scanner (System.in);
        int N = sc.nextInt();
        int w[] = new int[N];
        int b[] = new int[N];
        StringBuffer ans = new StringBuffer();
        for (int i = 0; i < N; i++) {
            w[i] = sc.nextInt();
        }
        for (int i = 0; i < N; i++) {
            b[i] = sc.nextInt();
        }
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < w[j] - b[j]; i++) {
                ans.append ('w');
            }
            for (int i = 0; i < b[j]; i++) {
                ans.append ('b');
            }
            ans.append("\n");
        }
        System.out.print(ans);
        for (int i = 1; i <= N; i++) {
            System.out.print(i + " ");
        }
    }
}