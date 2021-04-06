import java.util.Scanner;
public class Main {
  public static long solve(long n, long k, long kth) {
    if (n == kth) return (k - 1) % n;
    if (k >= n) return (k + solve(n - 1, k, kth)) % n;
    long winningSeat = solve(n - n / k, k, kth);
    long cntTail = n - k * (n / k);
    if (cntTail >= (winningSeat + 1)) return (k * (n / k)) + winningSeat;
    return (((winningSeat - cntTail) * k) )/ (k - 1);
  }
  public static void main(String args[]) {
    Scanner in = new Scanner(System.in);
    long n = in.nextLong();
    long k = in.nextLong();
    while(n != 0 && k != 0) {
      if (k == 1) {
        System.out.println(n - 1);
      } else {
        System.out.println(solve(n, k, 2) + 1);
      }
      n = in.nextLong(); k = in.nextLong();
    }
  }
}
