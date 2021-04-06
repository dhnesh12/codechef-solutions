import java.util.*;

class StackBracket {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n=sc.nextInt();
        int[][] ar=new int[n][5];
        int[] count=new int[n];
        for(int i=0;i<n;i++){
            for(int j=0;j<5;j++){
                ar[i][j]=sc.nextInt();
                count[i]+=ar[i][j];
            }
        }
        Map<Integer,String> map=new HashMap<>();
        map.put(0,"Beginner");
        map.put(1,"Junior Developer");
        map.put(2,"Middle Developer");
        map.put(3,"Senior Developer");
        map.put(4,"Hacker");
        map.put(5,"Jeff Dean");
        for(int i=0;i<n;i++){
            System.out.println(map.get(count[i]));
        }


    }

    public static boolean strive(String s) {
        Stack<Character> stack = new Stack<>();
        stack.push(s.charAt(0));
        for (int i = 1; i < s.length(); i++) {
            char ch1 = s.charAt(i);
            if (ch1 == ')') {
                if (!stack.isEmpty() && stack.peek() == '(') {
                    stack.pop();
                } else {
                    return false;
                }
            } else {
                stack.push('(');
            }
        }
        /*if(stack.size()!=0){
           // System.out.println("NO");
        }else {
            System.out.println("YES");
        }*/
        return stack.size() == 0;
    }

    public static int getAns(int[] ar, int bigger, int[][] dp, int i, int j) {

        if (i < 0 || j < 0) {
            return 0;
        }


        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        int ans1 = 0, ans2 = 0, ans3 = 0;

        if (ar[i] < bigger) {
            ans1 = 1 + getAns(ar, ar[i], dp, i - 1, j);
            // ans3=1+getAns(ar, ar[i],dp, i - 1,j-1);
        } else {
            ans2 = getAns(ar, bigger, dp, i - 1, j - 1);
        }

        dp[i][j] = Math.max(ans1, ans2);
        return dp[i][j];

    }


    public static long power(long a, long b, long c) {
        long ans = 1;
        while (b != 0) {
            if (b % 2 == 1) {
                ans = ans * a;
                ans %= c;
            }
            a = a * a;
            a %= c;
            b /= 2;
        }
        return ans;
    }

    public static long power1(long a, long b, long c) {
        long ans = 1;
        while (b != 0) {
            if (b % 2 == 1) {
                ans = multiply(ans, a, c);
            }
            a = multiply(a, a, c);
            b /= 2;

        }
        return ans;

    }

    public static long multiply(long a, long b, long c) {
        long res = 0;
        a %= c;
        while (b > 0) {
            if (b % 2 == 1) {
                res = (res + a) % c;
            }
            a = (a + a) % c;
            b /= 2;
        }

        return res % c;

    }

    public static long totient(long n) {
        long result = n;
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                //sum=sum+2*i;
                while (n % i == 0) {
                    n /= i;
                    // sum=sum+n;
                }
                result -= result / i;

            }
        }
        if (n > 1) {
            result -= result / n;

        }
        return result;
    }


    public static long gcd(long a, long b) {
        if (b == 0) {
            return a;
        } else {
            return gcd(b, a % b);
        }
    }

    public static boolean[] primes(int n) {
        boolean[] p = new boolean[n + 1];
        p[0] = false;
        p[1] = false;
        for (int i = 2; i <= n; i++) {
            p[i] = true;
        }

        for (int i = 2; i * i <= n; i++) {
            if (p[i]) {
                for (int j = i * i; j <= n; j += i) {
                    p[j] = false;
                }
            }

        }
        return p;
    }

    static int val(char c) {
        if (c >= '0' && c <= '9')
            return (int) c - '0';
        else
            return (int) c - 'A' + 10;
    }

    // Function to convert a
// number from given base
// 'b' to decimal
    static int toDeci(String str,
                      int base) {
        int len = str.length();
        int power = 1; // Initialize
        // power of base
        int num = 0; // Initialize result
        int i;

        // Decimal equivalent is
        // str[len-1]*1 + str[len-2] *
        // base + str[len-3]*(base^2) + ...
        for (i = len - 1; i >= 0; i--) {
            // A digit in input number
            // must be less than
            // number's base
            if (val(str.charAt(i)) >= base) {
                System.out.println("Invalid Number");
                return -1;
            }

            num += val(str.charAt(i)) * power;
            power = power * base;
        }

        return num;
    }
}