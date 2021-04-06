import java.util.*;
    import java.io.*;
    public class Main {
    public static void main(String[] args) {
    InputReader in = new StreamInputReader(System.in);
    PrintWriter out = new PrintWriter(System.out);
    run(in, out);
    }
    public static void run(InputReader in, PrintWriter out) {
    Solver solver = new HarmoniousDecorating();
    int testCount = in.readInt();
    for (int i = 1; i <= testCount; i++)
    solver.solve(i, in, out);
    Exit.exit(in, out);
    }
    }
    abstract class InputReader {
    private boolean finished = false;
    public abstract int read();
    public int readInt() {
    int c = read();
    while (isSpaceChar(c))
    c = read();
    int sgn = 1;
    if (c == '-') {
    sgn = -1;
    c = read();
    }
    int res = 0;
    do {
    if (c < '0' || c > '9')
    throw new InputMismatchException();
    res *= 10;
    res += c - '0';
    c = read();
    } while (!isSpaceChar(c));
    return res * sgn;
    }
    public String readString() {
    int c = read();
    while (isSpaceChar(c))
    c = read();
    StringBuffer res = new StringBuffer();
    do {
    res.appendCodePoint(c);
    c = read();
    } while (!isSpaceChar(c));
    return res.toString();
    }
    private boolean isSpaceChar(int c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
    public void setFinished(boolean finished) {
    this.finished = finished;
    }
    public abstract void close();
    }
    class StreamInputReader extends InputReader {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar, numChars;
    public StreamInputReader(InputStream stream) {
    this.stream = stream;
    }
    public int read() {
    if (numChars == -1)
    throw new InputMismatchException();
    if (curChar >= numChars) {
    curChar = 0;
    try {
    numChars = stream.read(buf);
    } catch (IOException e) {
    throw new InputMismatchException();
    }
    if (numChars <= 0)
    return -1;
    }
    return buf[curChar++];
    }
    @Override
    public void close() {
    try {
    stream.close();
    } catch (IOException ignored) {
    }
    }
    }
    class Exit {
    private Exit() {
    }
    public static void exit(InputReader in, PrintWriter out) {
    in.setFinished(true);
    in.close();
    out.close();
    }
    }
    interface Solver {
    public void solve(int testNumber, InputReader in, PrintWriter out);
    }
    class CollectionUtils {
    public static<T> T minElement(Iterable<T> collection, Comparator<T> comparator) {
    T result = null;
    for (T element : collection) {
    if (result == null || comparator.compare(result, element) > 0)
    result = element;
    }
    return result;
    }
    }
    class Pair<U, V> {
    public static class Comparator<U extends Comparable<U>, V extends Comparable<V>> implements java.util.Comparator<Pair<U, V>> {
    public int compare(Pair<U, V> o1, Pair<U, V> o2) {
    int result = o1.first.compareTo(o2.first);
    if (result != 0)
    return result;
    return o1.second.compareTo(o2.second);
    }
    }
    public final U first;
    public final V second;
    public static<U, V> Pair<U, V> makePair(U first, V second) {
    return new Pair<U, V>(first, second);
    }
    private Pair(U first, V second) {
    this.first = first;
    this.second = second;
    }
    @Override
    public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Pair pair = (Pair) o;
    return !(first != null ? !first.equals(pair.first) : pair.first != null) && !(second != null ? !second.equals(pair.second) : pair.second != null);
    }
    @Override
    public int hashCode() {
    int result = first != null ? first.hashCode() : 0;
    result = 31 * result + (second != null ? second.hashCode() : 0);
    return result;
    }
    @Override
    public String toString() {
    return "(" + first + "," + second + ")";
    }
    }
    abstract class ReadOnlyIterator<T> implements Iterator<T> {
    public final void remove() {
    throw new UnsupportedOperationException();
    }
    }
    class IOUtils {
    public static void printArray(int[] array, PrintWriter out) {
    if (array.length == 0) {
    out.println();
    return;
    }
    out.print(array[0]);
    for (int i = 1; i < array.length; i++)
    out.print(" " + array[i]);
    out.println();
    }
    public static<T> void printCollection(Iterable<T> collection, PrintWriter out, String delimiter) {
    boolean isFirst = true;
    for (T element : collection) {
    if (isFirst)
    isFirst = false;
    else
    out.print(delimiter);
    out.print(element);
    }
    out.println();
    }
    public static Pair<Integer, Integer> readIntPair(InputReader in) {
    int first = in.readInt();
    int second = in.readInt();
    return Pair.makePair(first, second);
    }
    public static Pair<Integer, Integer>[] readIntPairArray(InputReader in, int size) {
    @SuppressWarnings({"unchecked"})
    Pair<Integer, Integer>[] result = new Pair[size];
    for (int i = 0; i < size; i++)
    result[i] = readIntPair(in);
    return result;
    }
    public static void readIntArrays(InputReader in, int[]... arrays) {
    for (int i = 0; i < arrays[0].length; i++) {
    for (int j = 0; j < arrays.length; j++)
    arrays[j][i] = in.readInt();
    }
    }
    }
    abstract class AbstractSequence<T> implements Sequence<T> {
    public Iterator<T> iterator() {
    return new ReadOnlyIterator<T>() {
    private int index = 0;
    public boolean hasNext() {
    return index != size();
    }
    public T next() {
    if (!hasNext())
    throw new NoSuchElementException();
    return get(index++);
    }
    };
    }
    @Override
    public String toString() {
    StringWriter writer = new StringWriter();
    IOUtils.printCollection(this, new PrintWriter(writer), ",");
    return "[" + writer.toString().substring(0, writer.toString().length() - 1) + "]";
    }
    }
    abstract class AbstractWritableSequence<T> extends AbstractSequence<T> implements WritableSequence<T> {
    }
    abstract class ArrayWrapper<T> extends AbstractWritableSequence<T> {
    public static<T> ArrayWrapper<T> wrap(T...array) {
    return new ReferenceArrayWrapper<T>(array);
    }
    protected static class ReferenceArrayWrapper<T> extends ArrayWrapper<T> {
    protected final T[] array;
    protected ReferenceArrayWrapper(T[] array) {
    this.array = array;
    }
    public int size() {
    return array.length;
    }
    public T get(int index) {
    return array[index];
    }
    }
    }
    interface Sequence<T> extends Iterable<T> {
    public int size();
    public T get(int index);
    }
    class MiscUtils {
    public static<T> boolean equals(T first, T second) {
    return first == null && second == null || first != null && first.equals(second);
    }
    }
    class SequenceUtils {
    public static<T> int find(Sequence<T> sequence, T value) {
    int size = sequence.size();
    for (int i = 0; i < size; i++) {
    if (MiscUtils.equals(sequence.get(i), value))
    return i;
    }
    return -1;
    }
    public static<T> int minIndex(Sequence<T> sequence, Comparator<T> comparator) {
    return find(sequence, CollectionUtils.minElement(sequence, comparator));
    }
    }
    interface WritableSequence<T> extends Sequence<T> {
    }
    class GraphUtils {
    public static int[][] buildGraph(int vertexCount, int[] from, int[] to) {
    int edgeCount = from.length;
    int[] degree = new int[vertexCount];
    for (int i = 0; i < edgeCount; i++) {
    degree[from[i]]++;
    degree[to[i]]++;
    }
    int[][] graph = new int[vertexCount][];
    for (int i = 0; i < vertexCount; i++)
    graph[i] = new int[degree[i]];
    for (int i = 0; i < edgeCount; i++) {
    graph[from[i]][--degree[from[i]]] = i;
    graph[to[i]][--degree[to[i]]] = i;
    }
    return graph;
    }
    public static int otherVertex(int vertex, int from, int to) {
    return from + to - vertex;
    }
    }
    class HarmoniousDecorating implements Solver {
    public void solve(int testNumber, InputReader in, PrintWriter out) {
    int vertexCount = in.readInt();
    int edgeCount = in.readInt();
    Pair<Integer, Integer>[] vertices = IOUtils.readIntPairArray(in, vertexCount);
    int[] from = new int[edgeCount];
    int[] to = new int[edgeCount];
    IOUtils.readIntArrays(in, from, to);
    int[][] graph = GraphUtils.buildGraph(vertexCount, from, to);
    @SuppressWarnings({"unchecked"})
    Pair<Integer, Double>[][] edges = new Pair[vertexCount][];
    Comparator<Pair<Integer, Double>> comparator = new Comparator<Pair<Integer, Double>>() {
    public int compare(Pair<Integer, Double> first, Pair<Integer, Double> second) {
    return Double.compare(first.second, second.second);
    }
    };
    for (int i = 0; i < vertexCount; i++) {
    //noinspection unchecked
    edges[i] = new Pair[graph[i].length];
    for (int j = 0; j < graph[i].length; j++) {
    int otherVertex = GraphUtils.otherVertex(i, from[graph[i][j]], to[graph[i][j]]);
    edges[i][j] = Pair.makePair(graph[i][j], Math.atan2(vertices[otherVertex].second - vertices[i].second,
    vertices[otherVertex].first - vertices[i].first));
    }
    Arrays.sort(edges[i], comparator);
    }
    Set<Pair<Integer, Integer>> processed = new HashSet<Pair<Integer, Integer>>();
    List<Set<Integer>> faces = new ArrayList<Set<Integer>>();
    int outerIndex = -1;
    int minIndex = SequenceUtils.minIndex(ArrayWrapper.wrap(vertices), new Pair.Comparator<Integer, Integer>());
    for (int i = 0; i < edgeCount; i++) {
    for (int j = 0; j < 2; j++) {
    int currentVertex = j == 0 ? from[i] : to[i];
    int startVertex = currentVertex;
    int lastEdge = i;
    if (processed.contains(Pair.makePair(currentVertex, lastEdge)))
    continue;
    Set<Integer> face = new HashSet<Integer>();
    do {
    int lastVertex = GraphUtils.otherVertex(currentVertex, from[lastEdge], to[lastEdge]);
    int index = Arrays.binarySearch(edges[currentVertex], Pair.makePair(lastEdge, Math.atan2(
    vertices[lastVertex].second - vertices[currentVertex].second,
    vertices[lastVertex].first - vertices[currentVertex].first)), comparator);
    index--;
    if (index < 0)
    index = edges[currentVertex].length - 1;
    lastEdge = edges[currentVertex][index].first;
    face.add(lastEdge);
    currentVertex = GraphUtils.otherVertex(currentVertex, from[lastEdge], to[lastEdge]);
    processed.add(Pair.makePair(currentVertex, lastEdge));
    if (currentVertex == minIndex && lastEdge == edges[currentVertex][0].first)
    outerIndex = faces.size();
    } while (currentVertex != startVertex);
    faces.add(face);
    }
    }
    int newVertexCount = faces.size();
    int[] newFrom = new int[edgeCount];
    int[] newTo = new int[edgeCount];
    Arrays.fill(newFrom, -1);
    Arrays.fill(newTo, -1);
    for (int i = 0; i < faces.size(); i++) {
    for (int edge : faces.get(i)) {
    if (newFrom[edge] == -1)
    newFrom[edge] = i;
    else
    newTo[edge] = i;
    }
    }
    int[][] newGraph = GraphUtils.buildGraph(newVertexCount, newFrom, newTo);
    int[] answer = new int[edgeCount];
    Arrays.fill(answer, 1);
    boolean[] visited = new boolean[newVertexCount];
    dfs(outerIndex, -1, newGraph, visited, answer, newFrom, newTo);
    IOUtils.printArray(answer, out);
    }
    private int dfs(int vertex, int edge, int[][] newGraph, boolean[] visited, int[] answer, int[] newFrom, int[] newTo) {
    int result = 1 - newGraph[vertex].length % 2;
    visited[vertex] = true;
    for (int nextEdge : newGraph[vertex]) {
    int nextVertex = GraphUtils.otherVertex(vertex, newFrom[nextEdge], newTo[nextEdge]);
    if (!visited[nextVertex])
    result = (result + dfs(nextVertex, nextEdge, newGraph, visited, answer, newFrom, newTo)) % 2;
    }
    if (result == 1 && edge != -1)
    answer[edge] = 0;
    return result;
    }
    } 