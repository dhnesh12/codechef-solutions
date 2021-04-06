#include <bits/stdc++.h>
using namespace std;

int main(){
  int T;
  cin>>T;

  for(int i=0;i<T;++i){
    
    int N,R;
    cin>>N>>R;
    long long int arr[N][N];
    
    for (int i=0; i<N; i++){
      for (int j=0; j<N; j++){
        arr[i][j]=9999999;
      }
    }

    for (int i=0; i<R; i++){
      int u,v,w;
      cin>>u>>v>>w;
      arr[u-1][v-1]=w;
      arr[v-1][u-1]=w;
    }
    long long int dist[N][N]; 
    for (int i=0; i<N; i++){
      for (int j=0; j<N; j++){
        dist[i][j]=arr[i][j];
      }
    }
    long long int fuel[N];
    for (int i=0; i<N; i++){
      cin>>fuel[i];
    }

    int P, Q;
    cin>>P>>Q;
    for (int k=0; k<N; k++){
      for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
          if (dist[i][k]+dist[k][j]<dist[i][j]){
            dist[i][j]=dist[i][k]+dist[k][j];
          }
       }
      }
    }
    for (int i=0; i<N;i++){
      dist[i][i]=0;
    }
    long long int graph[N][N];
    for (int i=0; i<N; i++){
      for (int j=0; j<N; j++){
          if(dist[i][j]!=9999999)
        graph[i][j]=dist[i][j]*fuel[i];
      }
    }

    for (int k=0; k<N; k++){
      for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
          if (graph[i][k]+graph[k][j]<graph[i][j]){
            graph[i][j]=graph[i][k]+graph[k][j];
          }
        }
      }
    }
    cout<<graph[P-1][Q-1]<<endl;
  }

  return 0; 
}