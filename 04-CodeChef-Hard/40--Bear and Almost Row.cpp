#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;
#define INF 99999
int dist[100][100];

void printSolution(int V)
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall (int graph[][100],int v)
{
    int V=v;
    int i, j, k;
    
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    // Print the shortest distance matrix
    //printSolution(V);
}
 

int main()
{
    // int graph[V][V] = { {0,   5,  INF, 10},
    //                     {INF, 0,   3, INF},
    //                     {INF, INF, 0,   1},
    //                     {INF, INF, INF, 0}
    //                   };
    
    int t;
    cin>>t;
    while(t--){
        
        int graph[100][100];
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                graph[i][j]=INF;
            }
        }
    	int n;
    	cin>>n;
        
    	for(int i=0;i<n-1;i++){
    		graph[i][i+1]=1;
            graph[i+1][i]=1;
    	}
    	int e;
    	cin>>e;
    	for(int i=0;i<e;i++){
    		int x,y;
    		cin>>x>>y;
            x--;
            y--;
    		graph[x][y]=1;
    		graph[y][x]=1;
    	}
        
        floydWarshall(graph,n);
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                //cout<<dist[i][j]<<" ";
                ans+=dist[i][j];
            }
        }
        cout<<ans<<"\n";
        
    }
 
    return 0;
}