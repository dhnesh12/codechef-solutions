#include <iostream>
#include <vector>
using namespace std;

// Adapted from: https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
// A class that represents an undirected graph 
class Graph
{
    struct Node {
        vector<int> adj; // adjacency list
        bool visited;
        int disc;
        int low;
        int parent;
        bool ap;
        Node() : visited(false), disc(0), low(0), parent(NIL), ap(false) {}
    };
    vector<Node> nodes;

    enum { NIL = -1 };
    int V;    // No. of vertices 
    void APUtil(int v);
public:
    Graph(int V);   // Constructor 
    void addEdge(int v, int w);   // function to add an edge to graph 
    int AP();    // returns count of articulation points 
};

Graph::Graph(int V)
  : nodes(V)
{
    this->V = V;
}

void Graph::addEdge(int v, int w)
{
    nodes[v].adj.push_back(w);
    nodes[w].adj.push_back(v);  // Note: the graph is undirected 
}

// A recursive function that find articulation points using DFS traversal 
// u --> The vertex to be visited next 
// visited[] --> keeps tract of visited vertices 
// disc[] --> Stores discovery times of visited vertices 
// parent[] --> Stores parent vertices in DFS tree 
// ap[] --> Store articulation points 
void Graph::APUtil(int u)
{
    Node& uNode = nodes[u];

    // A static variable is used for simplicity, we can avoid use of static 
    // variable by passing a pointer. 
    static int time = 0;

    // Count of children in DFS Tree 
    int children = 0;

    // Mark the current node as visited 
    uNode.visited = true;

    // Initialize discovery time and low value 
    uNode.disc = uNode.low = ++time;

    // Go through all vertices aadjacent to this 
    vector<int>::iterator i;
    for (i = uNode.adj.begin(); i != uNode.adj.end(); ++i)
    {
        int v = *i;  // v is current adjacent of u
        Node& vNode = nodes[v];

        // If v is not visited yet, then make it a child of u 
        // in DFS tree and recur for it 
        if (!vNode.visited)
        {
            children++;
            vNode.parent = u;
            APUtil(v);

            // Check if the subtree rooted with v has a connection to 
            // one of the ancestors of u 
            uNode.low = min(uNode.low, vNode.low);

            // u is an articulation point in following cases 

            // (1) u is root of DFS tree and has two or more chilren. 
            if (uNode.parent == NIL && children > 1)
                uNode.ap = true;

            // (2) If u is not root and low value of one of its child is more 
            // than discovery value of u. 
            if (uNode.parent != NIL && vNode.low >= uNode.disc)
                uNode.ap = true;
        }

        // Update low value of u for parent function calls. 
        else if (v != uNode.parent)
            uNode.low = min(uNode.low, vNode.disc);
    }
}

// The function to do DFS traversal. It uses recursive function APUtil() 
int Graph::AP()
{
    // Call the recursive helper function to find articulation points 
    // in DFS tree rooted with vertex 'i' 
    for (int i = 0; i < V; i++)
        if (!nodes[i].visited)
            APUtil(i);

    // Now ap contains articulation point status
    int articulationPointCount = 0;
    for (int i = 0; i < V; i++)
        if (nodes[i].ap)
            articulationPointCount++;

    return articulationPointCount;
}

int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t-- > 0) {
        int n, m, k;
        cin >> n >> m >> k;

        Graph g(n);

        // build the graph
        while (m-- > 0) {
            int a, b;
            cin >> a >> b;
            g.addEdge(a, b);
        }

        const int articulationPoints = g.AP();

        cout << articulationPoints * k << '\n';
    }

    return 0;
}
