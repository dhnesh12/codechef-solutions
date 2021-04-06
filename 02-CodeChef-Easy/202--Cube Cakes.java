import java.util.Scanner;
public class Main {
 
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = Integer.parseInt(sc.nextLine());
        for (int t = 0; t < T; t++) {
            String line = sc.nextLine();
            String parts[] = line.split(" ");
            int N = Integer.parseInt(parts[0]);
            int P = Integer.parseInt(parts[1]);
            String SA = sc.nextLine();
            String SB = sc.nextLine();
            String ret = Main.calc(N, P, SA, SB);
            System.out.println(ret);
            System.out.flush();
        }
    }
 
    public static String calc(int N, int P, String SA, String SB) {
        int[][][] equals = new int[N][N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    equals[i][j][k] = SA.charAt(i * N * N + j * N + k) == SB.charAt(i * N * N + j * N + k) ? 1 : 0;
                }
            }
        }
        
        String ret = "-1";
        int[][][] temp = new int[N+1][N+1][N+1];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    temp[i+1][j+1][k+1] = 
                              temp[i][j+1][k+1]
                            + temp[i+1][j][k+1]
                            + temp[i+1][j+1][k]
                            - temp[i][j][k+1]
                            - temp[i][j+1][k]
                            - temp[i+1][j][k]
                            + temp[i][j][k]
                            + equals[i][j][k];
                }
            }
        }
 
        for (int size = N; size >= 1; size--) {
            int total = 0;
            int p2 = P * size * size * size;
            for (int i = size; i < N + 1; i++) {
                for (int j = size; j < N + 1; j++) {
                    for (int k = size; k < N + 1; k++) {
                        int count = temp[i][j][k]
                                - temp[i-size][j][k]
                                - temp[i][j-size][k]
                                - temp[i][j][k-size]
                                + temp[i-size][j-size][k]
                                + temp[i-size][j][k-size]
                                + temp[i][j-size][k-size]
                                - temp[i-size][j-size][k-size];
                        if (count * 100 >= p2) {
                            total++;
                        }
                    }
                }
            }
            
            if (total > 0) {
                ret = size + " " + total;
                break;
            }
        }
 
        return ret;
    }
}