import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.OutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.io.UncheckedIOException;
import java.util.Objects;
import java.io.Closeable;
import java.io.Writer;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) throws Exception {
        Thread thread = new Thread(null, new TaskAdapter(), "", 1 << 29);
        thread.start();
        thread.join();
    }

    static class TaskAdapter implements Runnable {
        @Override
        public void run() {
            InputStream inputStream = System.in;
            OutputStream outputStream = System.out;
            FastInput in = new FastInput(inputStream);
            FastOutput out = new FastOutput(outputStream);
            BinaryPalindrome solver = new BinaryPalindrome();
            solver.solve(1, in, out);
            out.close();
        }
    }

    static class BinaryPalindrome {
        public void solve(int testNumber, FastInput in, FastOutput out) {
            int n = in.ri();
            int[] length = new int[n + 1];
            int[] data = new int[n + 1];
            int tail = 0;


            int limit = n;
            HashData[] hds = HashData.doubleHashData(limit);
            RollingHash r1 = new RollingHash(hds[0], hds[1], limit);
            RollingHash r2 = new RollingHash(hds[0], hds[1], limit);

            Machine pos = new Machine(data, 1, 0, r1);
            Machine rev = new Machine(data, 1, 0, r2);
            rev.rev = true;
            for (int i = 1; i <= n; i++) {
                int t = in.ri();
                if (t == 2) {
                    tail--;
                    if (pos.r > tail) {
                        pos.move(Math.min(pos.l, tail), tail);
                    }
                    if (rev.r > tail) {
                        rev.move(Math.min(rev.l, tail), tail);
                    }
                } else {
                    tail++;
                    data[tail] = in.ri();
                    length[tail] = length[tail - 1];

                    int now = length[tail];

                    //add 2
                    if (now + 2 <= tail) {
                        int target = now + 2;
                        int l = tail - target + 1;
                        int r = tail;
                        pos.move(l, r);
                        rev.move(l, r);
                        if (pos.hash() == rev.hash()) {
                            length[tail] = target;
                        }
                    }

                    if (now + 1 <= tail && now + 1 > length[tail]) {
                        int target = now + 1;
                        int l = tail - target + 1;
                        int r = tail;
                        pos.move(l, r);
                        rev.move(l, r);
                        if (pos.hash() == rev.hash()) {
                            length[tail] = target;
                        }
                    }
                }

                out.println(length[tail]);
            }


        }

    }

    static class FastInput {
        private final InputStream is;
        private byte[] buf = new byte[1 << 13];
        private int bufLen;
        private int bufOffset;
        private int next;

        public FastInput(InputStream is) {
            this.is = is;
        }

        private int read() {
            while (bufLen == bufOffset) {
                bufOffset = 0;
                try {
                    bufLen = is.read(buf);
                } catch (IOException e) {
                    bufLen = -1;
                }
                if (bufLen == -1) {
                    return -1;
                }
            }
            return buf[bufOffset++];
        }

        public void skipBlank() {
            while (next >= 0 && next <= 32) {
                next = read();
            }
        }

        public int ri() {
            return readInt();
        }

        public int readInt() {
            int sign = 1;

            skipBlank();
            if (next == '+' || next == '-') {
                sign = next == '+' ? 1 : -1;
                next = read();
            }

            int val = 0;
            if (sign == 1) {
                while (next >= '0' && next <= '9') {
                    val = val * 10 + next - '0';
                    next = read();
                }
            } else {
                while (next >= '0' && next <= '9') {
                    val = val * 10 - next + '0';
                    next = read();
                }
            }

            return val;
        }

    }

    static interface IntegerStack {
    }

    static class DigitUtils {
        public static long INT_TO_LONG_MASK = (1L << 32) - 1;

        private DigitUtils() {
        }

        public static long asLong(long high, long low) {
            return ((high) << 32) | ((low) & INT_TO_LONG_MASK);
        }

        public static int mod(int x, int mod) {
            if (x < -mod || x >= mod) {
                x %= mod;
            }
            if (x < 0) {
                x += mod;
            }
            return x;
        }

    }

    static class Machine {
        int[] data;
        int l;
        int r;
        RollingHash rh;
        boolean rev;

        public long hash() {
            return rh.hash();
        }

        public Machine(int[] data, int l, int r, RollingHash rh) {
            this.data = data;
            this.l = l;
            this.r = r;
            this.rh = rh;
        }

        public void move(int L, int R) {
            if (!rev) {
                while (L < l) {
                    rh.addFirst(data[--l]);
                }
                while (r < R) {
                    rh.addLast(data[++r]);
                }
                while (l < L) {
                    l++;
                    rh.removeFirst();
                }
                while (R < r) {
                    r--;
                    rh.removeLast();
                }
            } else {
                while (L < l) {
                    rh.addLast(data[--l]);
                }
                while (r < R) {
                    rh.addFirst(data[++r]);
                }
                while (l < L) {
                    l++;
                    rh.removeLast();
                }
                while (R < r) {
                    r--;
                    rh.removeFirst();
                }
            }
            assert r - l + 1 == rh.size();
        }

    }

    static class HashData {
        public int mod;
        public int[] inv;
        public int[] pow;
        public int x;

        public HashData(int n, int x, int p) {
            this.mod = p;
            this.x = x;
            inv = new int[n + 10];
            pow = new int[n + 10];
            inv[0] = 1;
            pow[0] = 1;
            int invX = new Power(p).inverse(x);
            for (int i = 1; i < n + 10; i++) {
                inv[i] = (int) ((long) inv[i - 1] * invX % mod);
                pow[i] = (int) ((long) pow[i - 1] * x % mod);
            }
        }

        public HashData(int n, int x) {
            this(n, x, (int) 1e9 + 7);
        }

        public HashData(int n) {
            this(n, RandomWrapper.INSTANCE.nextInt(3, (int) 1e9 + 6), (int) 1e9 + 7);
        }

        public static HashData[] doubleHashData(int n) {
            Pair<Integer, Integer> pairs = HashSeed.getSeed2();
            return new HashData[]{new HashData(n, pairs.a), new HashData(n, pairs.b)};
        }

    }

    static class ExtGCD {
        public static int extGCD(int a, int b, int[] xy) {
            if (a >= b) {
                return extGCD0(a, b, xy);
            }
            int ans = extGCD0(b, a, xy);
            SequenceUtils.swap(xy, 0, 1);
            return ans;
        }

        private static int extGCD0(int a, int b, int[] xy) {
            if (b == 0) {
                xy[0] = 1;
                xy[1] = 0;
                return a;
            }
            int ans = extGCD0(b, a % b, xy);
            int x = xy[0];
            int y = xy[1];
            xy[0] = y;
            xy[1] = x - a / b * y;
            return ans;
        }

    }

    static class FastOutput implements AutoCloseable, Closeable, Appendable {
        private static final int THRESHOLD = 32 << 10;
        private final Writer os;
        private StringBuilder cache = new StringBuilder(THRESHOLD * 2);

        public FastOutput append(CharSequence csq) {
            cache.append(csq);
            return this;
        }

        public FastOutput append(CharSequence csq, int start, int end) {
            cache.append(csq, start, end);
            return this;
        }

        private void afterWrite() {
            if (cache.length() < THRESHOLD) {
                return;
            }
            flush();
        }

        public FastOutput(Writer os) {
            this.os = os;
        }

        public FastOutput(OutputStream os) {
            this(new OutputStreamWriter(os));
        }

        public FastOutput append(char c) {
            cache.append(c);
            afterWrite();
            return this;
        }

        public FastOutput append(int c) {
            cache.append(c);
            afterWrite();
            return this;
        }

        public FastOutput append(String c) {
            cache.append(c);
            afterWrite();
            return this;
        }

        public FastOutput println(int c) {
            return append(c).println();
        }

        public FastOutput println() {
            return append(System.lineSeparator());
        }

        public FastOutput flush() {
            try {
//            boolean success = false;
//            if (stringBuilderValueField != null) {
//                try {
//                    char[] value = (char[]) stringBuilderValueField.get(cache);
//                    os.write(value, 0, cache.length());
//                    success = true;
//                } catch (Exception e) {
//                }
//            }
//            if (!success) {
                os.append(cache);
//            }
                os.flush();
                cache.setLength(0);
            } catch (IOException e) {
                throw new UncheckedIOException(e);
            }
            return this;
        }

        public void close() {
            flush();
            try {
                os.close();
            } catch (IOException e) {
                throw new UncheckedIOException(e);
            }
        }

        public String toString() {
            return cache.toString();
        }

    }

    static strictfp class MersenneTwisterFast implements Serializable, Cloneable {
        private static final int N = 624;
        private static final int M = 397;
        private static final int MATRIX_A = 0x9908b0df;
        private static final int UPPER_MASK = 0x80000000;
        private static final int LOWER_MASK = 0x7fffffff;
        private static final int TEMPERING_MASK_B = 0x9d2c5680;
        private static final int TEMPERING_MASK_C = 0xefc60000;
        private int[] mt;
        private int mti;
        private int[] mag01;
        private boolean __haveNextNextGaussian;

        public Object clone() {
            try {
                MersenneTwisterFast f = (MersenneTwisterFast) (super.clone());
                f.mt = (int[]) (mt.clone());
                f.mag01 = (int[]) (mag01.clone());
                return f;
            } catch (CloneNotSupportedException e) {
                throw new InternalError();
            } // should never happen
        }

        public MersenneTwisterFast() {
            this(System.currentTimeMillis());
        }

        public MersenneTwisterFast(long seed) {
            setSeed(seed);
        }

        public MersenneTwisterFast(int[] array) {
            setSeed(array);
        }

        public void setSeed(long seed) {
            // Due to a bug in java.util.Random clear up to 1.2, we're
            // doing our own Gaussian variable.
            __haveNextNextGaussian = false;

            mt = new int[N];

            mag01 = new int[2];
            mag01[0] = 0x0;
            mag01[1] = MATRIX_A;

            mt[0] = (int) (seed & 0xffffffff);
            for (mti = 1; mti < N; mti++) {
                mt[mti] =
                        (1812433253 * (mt[mti - 1] ^ (mt[mti - 1] >>> 30)) + mti);
                /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
                /* In the previous versions, MSBs of the seed affect   */
                /* only MSBs of the array mt[].                        */
                /* 2002/01/09 modified by Makoto Matsumoto             */
                // mt[mti] &= 0xffffffff;
                /* for >32 bit machines */
            }
        }

        public void setSeed(int[] array) {
            if (array.length == 0)
                throw new IllegalArgumentException("Array length must be greater than zero");
            int i, j, k;
            setSeed(19650218);
            i = 1;
            j = 0;
            k = (N > array.length ? N : array.length);
            for (; k != 0; k--) {
                mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >>> 30)) * 1664525)) + array[j] + j; /* non linear */
                // mt[i] &= 0xffffffff; /* for WORDSIZE > 32 machines */
                i++;
                j++;
                if (i >= N) {
                    mt[0] = mt[N - 1];
                    i = 1;
                }
                if (j >= array.length) j = 0;
            }
            for (k = N - 1; k != 0; k--) {
                mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >>> 30)) * 1566083941)) - i; /* non linear */
                // mt[i] &= 0xffffffff; /* for WORDSIZE > 32 machines */
                i++;
                if (i >= N) {
                    mt[0] = mt[N - 1];
                    i = 1;
                }
            }
            mt[0] = 0x80000000; /* MSB is 1; assuring non-zero initial array */
        }

        public int nextInt(int n) {
            if (n <= 0)
                throw new IllegalArgumentException("n must be positive, got: " + n);

            if ((n & -n) == n)  // i.e., n is a power of 2
            {
                int y;

                if (mti >= N)   // generate N words at one time
                {
                    int kk;
                    final int[] mt = this.mt; // locals are slightly faster
                    final int[] mag01 = this.mag01; // locals are slightly faster

                    for (kk = 0; kk < N - M; kk++) {
                        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                        mt[kk] = mt[kk + M] ^ (y >>> 1) ^ mag01[y & 0x1];
                    }
                    for (; kk < N - 1; kk++) {
                        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                        mt[kk] = mt[kk + (M - N)] ^ (y >>> 1) ^ mag01[y & 0x1];
                    }
                    y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
                    mt[N - 1] = mt[M - 1] ^ (y >>> 1) ^ mag01[y & 0x1];

                    mti = 0;
                }

                y = mt[mti++];
                y ^= y >>> 11;                          // TEMPERING_SHIFT_U(y)
                y ^= (y << 7) & TEMPERING_MASK_B;       // TEMPERING_SHIFT_S(y)
                y ^= (y << 15) & TEMPERING_MASK_C;      // TEMPERING_SHIFT_T(y)
                y ^= (y >>> 18);                        // TEMPERING_SHIFT_L(y)

                return (int) ((n * (long) (y >>> 1)) >> 31);
            }

            int bits, val;
            do {
                int y;

                if (mti >= N)   // generate N words at one time
                {
                    int kk;
                    final int[] mt = this.mt; // locals are slightly faster
                    final int[] mag01 = this.mag01; // locals are slightly faster

                    for (kk = 0; kk < N - M; kk++) {
                        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                        mt[kk] = mt[kk + M] ^ (y >>> 1) ^ mag01[y & 0x1];
                    }
                    for (; kk < N - 1; kk++) {
                        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                        mt[kk] = mt[kk + (M - N)] ^ (y >>> 1) ^ mag01[y & 0x1];
                    }
                    y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
                    mt[N - 1] = mt[M - 1] ^ (y >>> 1) ^ mag01[y & 0x1];

                    mti = 0;
                }

                y = mt[mti++];
                y ^= y >>> 11;                          // TEMPERING_SHIFT_U(y)
                y ^= (y << 7) & TEMPERING_MASK_B;       // TEMPERING_SHIFT_S(y)
                y ^= (y << 15) & TEMPERING_MASK_C;      // TEMPERING_SHIFT_T(y)
                y ^= (y >>> 18);                        // TEMPERING_SHIFT_L(y)

                bits = (y >>> 1);
                val = bits % n;
            } while (bits - val + (n - 1) < 0);
            return val;
        }

    }

    static interface IntegerDeque extends IntegerStack {
    }

    static class Pair<A, B> implements Cloneable {
        public A a;
        public B b;

        public Pair(A a, B b) {
            this.a = a;
            this.b = b;
        }

        public String toString() {
            return "a=" + a + ",b=" + b;
        }

        public int hashCode() {
            return a.hashCode() * 31 + b.hashCode();
        }

        public boolean equals(Object obj) {
            Pair<A, B> casted = (Pair<A, B>) obj;
            return Objects.equals(casted.a, a) && Objects.equals(casted.b, b);
        }

        public Pair<A, B> clone() {
            try {
                return (Pair<A, B>) super.clone();
            } catch (CloneNotSupportedException e) {
                throw new RuntimeException(e);
            }
        }

    }

    static class IntegerDequeImpl implements IntegerDeque {
        private int[] data;
        private int bpos;
        private int epos;
        private static final int[] EMPTY = new int[0];
        private int n;

        public IntegerDequeImpl(int cap) {
            if (cap == 0) {
                data = EMPTY;
            } else {
                data = new int[cap];
            }
            bpos = 0;
            epos = 0;
            n = cap;
        }

        private void expandSpace(int len) {
            while (n < len) {
                n = Math.max(n + 10, n * 2);
            }
            int[] newData = new int[n];
            if (bpos <= epos) {
                if (bpos < epos) {
                    System.arraycopy(data, bpos, newData, 0, epos - bpos);
                }
            } else {
                System.arraycopy(data, bpos, newData, 0, data.length - bpos);
                System.arraycopy(data, 0, newData, data.length - bpos, epos);
            }
            epos = size();
            bpos = 0;
            data = newData;
        }

        public IntegerIterator iterator() {
            return new IntegerIterator() {
                int index = bpos;


                public boolean hasNext() {
                    return index != epos;
                }


                public int next() {
                    int ans = data[index];
                    index = IntegerDequeImpl.this.next(index);
                    return ans;
                }
            };
        }

        public int removeFirst() {
            int ans = data[bpos];
            bpos = next(bpos);
            return ans;
        }

        public int removeLast() {
            int ans = data[last(epos)];
            epos = last(epos);
            return ans;
        }

        public void addLast(int x) {
            ensureMore();
            data[epos] = x;
            epos = next(epos);
        }

        public void addFirst(int x) {
            ensureMore();
            bpos = last(bpos);
            data[bpos] = x;
        }

        private int last(int x) {
            return (x == 0 ? n : x) - 1;
        }

        private int next(int x) {
            return x + 1 >= n ? 0 : x + 1;
        }

        private void ensureMore() {
            if (next(epos) == bpos) {
                expandSpace(n + 1);
            }
        }

        public int size() {
            int ans = epos - bpos;
            if (ans < 0) {
                ans += data.length;
            }
            return ans;
        }

        public String toString() {
            StringBuilder builder = new StringBuilder();
            for (IntegerIterator iterator = iterator(); iterator.hasNext(); ) {
                builder.append(iterator.next()).append(' ');
            }
            return builder.toString();
        }

    }

    static class RandomWrapper {
        private MersenneTwisterFast random;
        public static final RandomWrapper INSTANCE = new RandomWrapper();

        public RandomWrapper() {
            this(new MersenneTwisterFast());
        }

        public RandomWrapper(MersenneTwisterFast random) {
            this.random = random;
        }

        public RandomWrapper(long seed) {
            this(new MersenneTwisterFast(seed));
        }

        public int nextInt(int l, int r) {
            return random.nextInt(r - l + 1) + l;
        }

        public int nextInt(int n) {
            return random.nextInt(n);
        }

    }

    static class RollingHash {
        HashData hd1;
        HashData hd2;
        IntegerDequeImpl dq;
        long h1;
        long h2;

        public RollingHash(HashData hd1, HashData hd2, int n) {
            this.hd1 = hd1;
            this.hd2 = hd2;
            dq = new IntegerDequeImpl(n + 10);
        }

        public int size() {
            return dq.size();
        }

        public void addLast(int x) {
            h1 = (h1 + (long) hd1.pow[dq.size()] * x) % hd1.mod;
            h2 = (h2 + (long) hd2.pow[dq.size()] * x) % hd2.mod;
            dq.addLast(x);
        }

        public void addFirst(int x) {
            h1 = (h1 * hd1.pow[1] + x) % hd1.mod;
            h2 = (h2 * hd2.pow[1] + x) % hd2.mod;
            dq.addFirst(x);
        }

        public void removeLast() {
            int x = dq.removeLast();
            h1 = (h1 + (long) hd1.pow[dq.size()] * (hd1.mod - x)) % hd1.mod;
            h2 = (h2 + (long) hd2.pow[dq.size()] * (hd2.mod - x)) % hd2.mod;
        }

        public void removeFirst() {
            int x = dq.removeFirst();
            h1 = (h1 - x + hd1.mod) * hd1.inv[1] % hd1.mod;
            h2 = (h2 - x + hd2.mod) * hd2.inv[1] % hd2.mod;
        }

        public long hash() {
            return DigitUtils.asLong(h1, h2);
        }

    }

    static interface InverseNumber {
    }

    static class IntExtGCDObject {
        private int[] xy = new int[2];

        public int extgcd(int a, int b) {
            return ExtGCD.extGCD(a, b, xy);
        }

        public int getX() {
            return xy[0];
        }

    }

    static class SequenceUtils {
        public static void swap(int[] data, int i, int j) {
            int tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }

    }

    static class HashSeed {
        private static int[] seeds = new int[]{11, 13, 17, 29, 31, 41, 43, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103};

        public static Pair<Integer, Integer> getSeed2() {
            int a = seeds[RandomWrapper.INSTANCE.nextInt(seeds.length)];
            int b = a;
            while (b == a) {
                b = seeds[RandomWrapper.INSTANCE.nextInt(seeds.length)];
            }
            return new Pair<>(a, b);
        }

    }

    static class Power implements InverseNumber {
        static IntExtGCDObject extGCD = new IntExtGCDObject();
        int mod;

        public Power(int mod) {
            this.mod = mod;
        }

        public int inverse(int x) {
            int ans = inverseExtGCD(x);
//        if(modular.mul(ans, x) != 1){
//            throw new IllegalStateException();
//        }
            return ans;
        }

        public int inverseExtGCD(int x) {
            if (extGCD.extgcd(x, mod) != 1) {
                throw new IllegalArgumentException();
            }
            return DigitUtils.mod(extGCD.getX(), mod);
        }

    }

    static interface IntegerIterator {
        boolean hasNext();

        int next();

    }
}

