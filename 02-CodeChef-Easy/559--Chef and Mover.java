import java.util.*;
class CHEFMOVR {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int x = 0; x < t; x++) {
            int n = sc.nextInt();
            int d = sc.nextInt();
            long[] arr = new long[n];
            for (int i = 0; i < n; i++) {
                arr[i] = sc.nextInt();
            }
            long count = 0;
            long sum = Arrays.stream(arr).sum();
            if (sum % n != 0) {
                System.out.println(-1);
            } else {
                long avg = sum / n;
                for (int j = 0; j < n - d; j++) {
                    long a1 = Math.abs(arr[j] - avg);
                    if (arr[j] < avg) {
                        count += a1;
                        arr[j] = avg;
                        arr[j + d] -= a1;
                    } else {
                        count += a1;
                        arr[j] = avg;
                        arr[j + d] += a1;
                    }
                }
                int k = 0;
                for (int i = 0; i < n; i++) {
                    if (arr[i] != avg) {
                        System.out.println(-1);
                        k = 1;
                        break;
                    }
                }
                if (k != 1) {
                    System.out.println(count);
                }
            }
        }
    }
}
