import java.io.FileReader;
import java.util.Scanner;

class SHOOTING {
    static char[][] matrix;
    static int m;
//    static boolean[] crossed;

    static boolean solve(int i, long crossed) {
        if (i < 0) {
            return true;
        }

        int firstEnemy = -1;
        int lastEnemy = -1;
        for (int j = 0; j < m; j++) {
            boolean crossedColumn = ((1L << j) & crossed) != 0;
            if (matrix[i][j] == 'E' && !crossedColumn) {
                if (firstEnemy == -1) {
                    firstEnemy = j;
                }
                lastEnemy = j;
            }
        }

        long fullCrossed = crossed;
        boolean anyLasers = false;
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 'L') {
                fullCrossed = fullCrossed | (1L << j);
                anyLasers = true;
            }
        }
        if (firstEnemy == -1) {
            return solve(i - 1, fullCrossed);
        }
        if (!anyLasers) {
            return false;
        }
        for (int j = 0; j < m; ++j) {
            long bit = 1L << j;
            if (matrix[i][j] != 'L') {
                continue;
            }
            long nextCrossed = fullCrossed - (fullCrossed & bit) + (crossed & bit);
            if (j < firstEnemy && solve(i - 1, nextCrossed)) {
                return true;
            }
            if (j > lastEnemy && solve(i - 1, nextCrossed)) {
                return true;
            }
            for (int k = j + 1; k < m; k++) {
                if (matrix[i][k] != 'L') {
                    continue;
                }
                long bit2 = 1L << k;
                long nextCrossed2 = nextCrossed - (nextCrossed & bit2) + (crossed & bit2);
                if (solve(i - 1, nextCrossed2)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws Exception {
//        Scanner scanner = new Scanner(new FileReader("input/SHOOTING2.in"));
        Scanner scanner = new Scanner(System.in);
        long t = scanner.nextInt();
        while (t-- > 0) {
            int n = scanner.nextInt();
            m = scanner.nextInt();
            matrix = new char[n][];
            for (int i = 0; i < n; i++) {
                String s = scanner.next();
                matrix[i] = s.toCharArray();
            }

            if (solve(n - 1, 0)) {
                System.out.println("Possible");
            } else {
                System.out.println("Impossible");
            }
        }
    }
}
