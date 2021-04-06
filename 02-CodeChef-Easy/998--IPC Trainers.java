//package com.company;
//whenever you are not able to understand the before and after thingy, use the concept of cycles and memoisation.
import java.io.BufferedReader;
import java.io.InputStream;
import java.util.*;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
//    static Integer[][] tokens;
    static int n;
    public static void main(String[] args) throws IOException {
        FastReader reader = new FastReader();
        int test = reader.nextInt();

        for (int o =  0; o < test; o++) {
            ArrayList<Node> list_of_nodes = new ArrayList<>();
            int N = reader.nextInt();
            int D = reader.nextInt();
            for (int i = N; i >= 1; i--) {
                Node aj = new Node(reader.nextInt(), reader.nextInt(), reader.nextInt());

                list_of_nodes.add(aj);
            }
            list_of_nodes.sort(new Comparator<Node>() {
                @Override
                public int compare(Node o1, Node o2) {
                    return Long.compare(o1.day , o2.day);
                }
            });
            PriorityQueue<Node> pq = new PriorityQueue<>(new Comparator<Node>() {
                @Override
                public int compare(Node o1, Node o2) {
                    return Long.compare(o2.sadness, o1.sadness);
                }
            });
         //   System.out.println(list_of_nodes.size());
            int u1 = 0;
            for (int jk = 1; jk <= D; jk++) {
                    for (int s = u1; s < N; s++) {
                        Node n = list_of_nodes.get(s);
                        u1 +=1;
                        if (n.day <= jk && !n.f) {n.f = true; pq.add(n); }
                        else if (n.day > jk) {u1 = s; break;}
                    }

                    if (!pq.isEmpty()) {
                        Node ayushi = pq.poll();
                 //       System.out.println("AYUSHI: " + ayushi.sadness);
                        ayushi.demand -= 1;
                        if (ayushi.demand != 0) {
                            pq.add(ayushi);
                        }
                    }

            }
            long ans  = 0;
            while (!pq.isEmpty()){
                Node hp = pq.poll();
                ans += (long) hp.demand* hp.sadness;
            }
            System.out.println(ans);
        }
        }
}
class Node {
    long demand = 0;
    long day = 0; long sadness = 0; boolean f = false;
    public Node(long day, long demand, long sadness){
        this.demand = demand;
        this.day = day;
        this.sadness = sadness;
    }
}








class FastReader
{
    BufferedReader br;
    StringTokenizer st;

    public FastReader()
    {
        br = new BufferedReader(new
                InputStreamReader(System.in));
    }

    String next()
    {
        while (st == null || !st.hasMoreElements())
        {
            try
            {
                st = new StringTokenizer(br.readLine());
            }
            catch (IOException  e)
            {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    int nextInt()
    {
        return Integer.parseInt(next());
    }

    long nextLong()
    {
        return Long.parseLong(next());
    }

    double nextDouble()
    {
        return Double.parseDouble(next());
    }

    String nextLine()
    {
        String str = "";
        try
        {
            str = br.readLine();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        return str;
    }
}

/** Class for buffered reading int and double values */
class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                    reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}
