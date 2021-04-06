#include <bits/stdc++.h>

using namespace std;

vector<int> adj[105];
bool vis[105];
int dis[105];
int sum;

int nodes, edges;

void bfs(int s)
{
  queue<int> q;
  q.push(s);
  vis[s] = true;
  dis[s] = 0; //setting the intial distance to 0

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    for (int i = 0; i < adj[u].size(); i++)
    {
      int v = adj[u][i];
      if (vis[v] == false)
      {
        //incrementing the distance
        dis[v] = dis[u] + 1;
        vis[v] = true;
        sum += dis[v]; //total dis sum from the starting node
        q.push(v);
      }
    }
  }
}



int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  cin >> t;

  for (int i = 1; i <= t; i++) //test cases
  {
    cin >> nodes;
    string ch;
    getline(cin, ch); //for getting the garbage when enter is clicked

    for (int i = 1; i <= nodes; i++)
    {
      adj[i].clear();
      string s;
      getline(cin, s); //getting the input as line

      stringstream ss(s); //for breaking the words and putting it in the integet variable
      int v;
      while (ss >> v)
      {
        adj[i].push_back(v);
        adj[v].push_back(i);
      }
    }

    int mx = INT_MAX, n;

    for (int i = 1; i <= nodes; i++)
    {

      memset(vis, 0, nodes + 1);
      memset(dis, 0, nodes + 1);
      sum = 0;
      bfs(i);
      if (sum < mx)
      {
        mx = sum;
        n = i;
      }
    }

    double ans = (double)mx / (double)nodes;

    cout << n << " " << fixed << setprecision(6) << ans << "\n";
  }

  return 0;
}