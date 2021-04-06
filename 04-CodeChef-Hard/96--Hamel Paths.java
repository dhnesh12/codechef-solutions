import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.ArrayList;
import java.io.OutputStreamWriter;
import java.io.OutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.io.UncheckedIOException;
import java.util.List;
import java.util.stream.Stream;
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
            HamelPaths solver = new HamelPaths();
            int testCount = Integer.parseInt(in.next());
            for (int i = 1; i <= testCount; i++)
                solver.solve(i, in, out);
            out.close();
        }
    }

    static class HamelPaths {
        List<Edge>[] g;
        int[] deg;
        List<Edge> seq;

        public void solve(int testNumber, FastInput in, FastOutput out) {
            int n = in.ri();
            int m = in.ri();
            int[] a = new int[m];
            int[] b = new int[m];
            for (int i = 0; i < m; i++) {
                a[i] = in.ri() - 1;
                b[i] = in.ri() - 1;
            }
            GraphicMatroidPartition partition = new GraphicMatroidPartition();
            int[] type = partition.solve(n, 2, a, b);
            Edge[] edges = new Edge[m];
            g = Graph.createGraph(n);
            deg = new int[n];
            for (int i = 0; i < m; i++) {
                edges[i] = new Edge();
                edges[i].a = a[i];
                edges[i].b = b[i];
                edges[i].index = i;
                if (type[i] != -1) {
                    deg[edges[i].a]++;
                    deg[edges[i].b]++;
                }
                if (type[i] == 1) {
                    g[a[i]].add(edges[i]);
                    g[b[i]].add(edges[i]);
                }
            }
            dfs(0, null);
            seq = new ArrayList<>(m);
            for (int i = 0; i < m; i++) {
                if (type[i] == 0) {
                    g[a[i]].add(edges[i]);
                    g[b[i]].add(edges[i]);
                }
            }
            euler(0, null);
            out.append(seq.size()).append(' ');
            for (Edge e : seq) {
                out.append(e.index + 1).append(' ');
            }
            out.println();
        }

        void euler(int root, Edge e) {
            while (!g[root].isEmpty()) {
                Edge back = CollectionUtils.pop(g[root]);
                if (!back.enable) {
                    continue;
                }
                back.enable = false;
                euler(back.other(root), back);
            }
            if (e != null) {
                seq.add(e);
            }
        }

        void reverse(Edge e) {
            e.enable = !e.enable;
            deg[e.a] ^= 1;
            deg[e.b] ^= 1;
        }

        void dfs(int root, Edge p) {
            for (Edge e : g[root]) {
                if (e == p) {
                    continue;
                }
                int node = e.other(root);
                dfs(node, e);
            }
            if (deg[root] % 2 == 1) {
                reverse(p);
            }
        }

    }

    static class Edge {
        int a;
        int b;
        int index;
        boolean enable = true;

        int other(int x) {
            return a == x ? b : a;
        }

    }

    static class FastInput {
        private final InputStream is;
        private StringBuilder defaultStringBuf = new StringBuilder(1 << 13);
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

        public String next() {
            return readString();
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

        public String readString(StringBuilder builder) {
            skipBlank();

            while (next > 32) {
                builder.append((char) next);
                next = read();
            }

            return builder.toString();
        }

        public String readString() {
            defaultStringBuf.setLength(0);
            return readString(defaultStringBuf);
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

    static class GraphicMatroidPartition {
        IntegerMultiWayStack[] trees;
        int[] a;
        int[] b;
        int[][] depth;
        int[][] p;
        int[][] roof;
        GraphicMatroidPartition.DSUExt[] dsu;
        int[] type;
        int k;
        int n;
        int[][] buf;
        int[] bufTail;

        private int other(int e, int x) {
            return a[e] == x ? b[e] : a[e];
        }

        private void dfs(int t, int root, int f) {
            p[t][root] = f;
            if (f == -1) {
                depth[t][root] = 0;
                roof[t][root] = root;
            } else {
                int pnode = other(f, root);
                depth[t][root] = depth[t][pnode] + 1;
                roof[t][root] = roof[t][pnode];
            }
            for (IntegerIterator iterator = trees[t].iterator(root); iterator.hasNext(); ) {
                int e = iterator.next();
                if (e == f) {
                    continue;
                }
                int node = other(e, root);
                dfs(t, node, e);
            }
        }

        private void prepare() {
            for (int i = 0; i < k; i++) {
                trees[i].clear();
                dsu[i].init();
            }
            for (int i = 0; i < a.length; i++) {
                if (type[i] == -1) {
                    continue;
                }
                int t = type[i];
                trees[t].addLast(a[i], i);
                trees[t].addLast(b[i], i);
            }
            SequenceUtils.deepFill(depth, -1);
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < n; j++) {
                    if (depth[i][j] != -1) {
                        continue;
                    }
                    dfs(i, j, -1);
                }
                dsu[i].height = depth[i];
            }
        }

        private int getTop(int t, int i) {
            return dsu[t].top[dsu[t].find(i)];
        }

        private boolean augment(int t, int e) {
            int x = getTop(t, a[e]);
            int y = getTop(t, b[e]);
            if (roof[t][x] != roof[t][y]) {
                type[e] = t;
                return true;
            }
            int begin = bufTail[t];
            while (x != y) {
                if (depth[t][x] < depth[t][y]) {
                    int tmp = x;
                    x = y;
                    y = tmp;
                }
                buf[t][bufTail[t]++] = p[t][x];
                dsu[t].merge(x, other(p[t][x], x));
                x = getTop(t, x);
            }
            int end = bufTail[t];
            for (int i = begin; i < end; i++) {
                for (int j = 0; j < k; j++) {
                    if (t == j) {
                        continue;
                    }
                    if (augment(j, buf[t][i])) {
                        bufTail[t] = begin;
                        type[e] = t;
                        return true;
                    }
                }
            }
            bufTail[t] = begin;
            return false;
        }

        public int[] solve(int n, int k, int[] a, int[] b) {
            this.a = a;
            this.b = b;
            this.k = k;
            this.n = n;
            assert a.length == b.length;
            trees = new IntegerMultiWayStack[k];
            dsu = new GraphicMatroidPartition.DSUExt[k];
            depth = new int[k][n];
            p = new int[k][n];
            roof = new int[k][n];
            type = new int[a.length];
            buf = new int[k][n];
            bufTail = new int[k];
            Arrays.fill(type, -1);
            for (int i = 0; i < k; i++) {
                trees[i] = new IntegerMultiWayStack(n, n - 1);
                dsu[i] = new GraphicMatroidPartition.DSUExt(n);
            }

            //shuffle and make like better
            int[] perm = IntStream.range(0, a.length).toArray();
            DSU dsu = new DSU(n);
            for (int i = 0; i < k; i++) {
                Randomized.shuffle(perm);
                dsu.init();
                for (int index : perm) {
                    if (type[index] != -1) {
                        continue;
                    }
                    if (dsu.find(a[index]) != dsu.find(b[index])) {
                        dsu.merge(a[index], b[index]);
                        type[index] = i;
                    }
                }
            }

            prepare();
            for (int i = 0; i < a.length; i++) {
                if (type[i] != -1) {
                    continue;
                }
                for (int j = 0; j < k; j++) {
                    if (augment(j, i)) {
                        prepare();
                        break;
                    }
                }
            }

            return type;
        }

        private static class DSUExt extends DSU {
            private int[] top;
            int[] height;

            public DSUExt(int n) {
                super(n);
                top = new int[n];
            }

            public void init(int n) {
                super.init(n);
                for (int i = 0; i < n; i++) {
                    top[i] = i;
                }
            }

            protected void preMerge(int a, int b) {
                super.preMerge(a, b);
                if (height[top[a]] > height[top[b]]) {
                    top[a] = top[b];
                }
            }

        }

    }

    static class Randomized {
        public static void shuffle(int[] data) {
            shuffle(data, 0, data.length - 1);
        }

        public static void shuffle(int[] data, int from, int to) {
            to--;
            for (int i = from; i <= to; i++) {
                int s = nextInt(i, to);
                int tmp = data[i];
                data[i] = data[s];
                data[s] = tmp;
            }
        }

        public static int nextInt(int l, int r) {
            return RandomWrapper.INSTANCE.nextInt(l, r);
        }

    }

    static class DSU {
        protected int[] p;
        protected int[] rank;
        protected int n;

        public DSU(int n) {
            p = new int[n];
            rank = new int[n];
        }

        public void init() {
            init(p.length);
        }

        public void init(int n) {
            this.n = n;
            for (int i = 0; i < n; i++) {
                p[i] = i;
                rank[i] = 0;
            }
        }

        public final int find(int a) {
            if (p[a] == p[p[a]]) {
                return p[a];
            }
            find(p[a]);
            preAccess(a);
            return p[a] = p[p[a]];
        }

        protected void preAccess(int a) {

        }

        protected void preMerge(int a, int b) {

        }

        public final void merge(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) {
                return;
            }
            if (rank[a] == rank[b]) {
                rank[a]++;
            }

            if (rank[a] < rank[b]) {
                int tmp = a;
                a = b;
                b = tmp;
            }

            preMerge(a, b);
            p[b] = a;
        }

        public String toString() {
            return Arrays.toString(Arrays.copyOf(p, n));
        }

    }

    static interface IntegerIterator {
        boolean hasNext();

        int next();

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

    }

    static class FastOutput implements AutoCloseable, Closeable, Appendable {
        private static final int THRESHOLD = 1 << 13;
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

        public FastOutput println() {
            return append(System.lineSeparator());
        }

        public FastOutput flush() {
            try {
                os.append(cache);
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

    static class Graph {
        public static List[] createGraph(int n) {
            return IntStream.range(0, n).mapToObj(i -> new ArrayList<>()).toArray(i -> new List[i]);
        }

    }

    static class CollectionUtils {
        public static <T> T pop(List<T> list) {
            return list.remove(list.size() - 1);
        }

    }

    static class IntegerMultiWayStack {
        private int[] values;
        private int[] next;
        private int[] heads;
        private int alloc;
        private int stackNum;

        public IntegerIterator iterator(final int queue) {
            return new IntegerIterator() {
                int ele = heads[queue];


                public boolean hasNext() {
                    return ele != 0;
                }


                public int next() {
                    int ans = values[ele];
                    ele = next[ele];
                    return ans;
                }
            };
        }

        private void doubleCapacity() {
            int newSize = Math.max(next.length + 10, next.length * 2);
            next = Arrays.copyOf(next, newSize);
            values = Arrays.copyOf(values, newSize);
        }

        public void alloc() {
            alloc++;
            if (alloc >= next.length) {
                doubleCapacity();
            }
            next[alloc] = 0;
        }

        public void clear() {
            alloc = 0;
            Arrays.fill(heads, 0, stackNum, 0);
        }

        public boolean isEmpty(int qId) {
            return heads[qId] == 0;
        }

        public IntegerMultiWayStack(int qNum, int totalCapacity) {
            values = new int[totalCapacity + 1];
            next = new int[totalCapacity + 1];
            heads = new int[qNum];
            stackNum = qNum;
        }

        public void addLast(int qId, int x) {
            alloc();
            values[alloc] = x;
            next[alloc] = heads[qId];
            heads[qId] = alloc;
        }

        public String toString() {
            StringBuilder builder = new StringBuilder();
            for (int i = 0; i < stackNum; i++) {
                if (isEmpty(i)) {
                    continue;
                }
                builder.append(i).append(": ");
                for (IntegerIterator iterator = iterator(i); iterator.hasNext(); ) {
                    builder.append(iterator.next()).append(",");
                }
                if (builder.charAt(builder.length() - 1) == ',') {
                    builder.setLength(builder.length() - 1);
                }
                builder.append('\n');
            }
            return builder.toString();
        }

    }

    static class SequenceUtils {
        public static void deepFill(Object array, int val) {
            if (!array.getClass().isArray()) {
                throw new IllegalArgumentException();
            }
            if (array instanceof int[]) {
                int[] intArray = (int[]) array;
                Arrays.fill(intArray, val);
            } else {
                Object[] objArray = (Object[]) array;
                for (Object obj : objArray) {
                    deepFill(obj, val);
                }
            }
        }

    }
}

