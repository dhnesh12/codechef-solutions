#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
pair <bool,int> board[51][51];
const int Max_Vertices=50*50+10, INF = Max_Vertices+100;
int T, N, M;
vector <pair<int,int>> edges;
vector <int> adj_list[Max_Vertices];
bool is_visited[Max_Vertices];
int root_set[Max_Vertices], rank_set[Max_Vertices];
int find_root(int a){if (root_set[a] != a){root_set[a] = find_root(root_set[a]);} return root_set[a];}
void merge (int a, int b){
    int p_a = find_root(a), p_b = find_root(b);
    if (rank_set[p_a] == rank_set[p_b]){root_set[p_b] = p_a; rank_set[p_a]++;}
    if (rank_set[p_a] > rank_set[p_b]){root_set[p_b] = p_a;} else{root_set[p_a] = p_b;}}
int BFS_distance (int src){
    memset (is_visited, 0, sizeof(is_visited)); queue <int> que; que.push(src); is_visited[src] = 1;
    que.push(-1); int distance = 0;
    while (!que.empty()){int f = que.front(); que.pop();
        if (f == -1){if(!que.empty()){que.push(-1);distance++;}continue;}
        for (auto neighbour: adj_list[f]){if(is_visited[neighbour]){continue;}
            is_visited[neighbour] = 1; que.push(neighbour);}}return distance;}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); cin >> T;
    while (T--){
        for (int i = 0; i < Max_Vertices; i++){root_set[i] = i; rank_set[i] = 0; adj_list[i].clear();}    
        edges.clear(); cin >> N >> M;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){cin >> board[i][j].first; board[i][j].second = (i)*M+j;}}
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (i > 0){
                    if(board[i][j].first==board[i-1][j].first) merge(board[i-1][j].second,board[i][j].second);
                    else{edges.emplace_back(make_pair(board[i-1][j].second,board[i][j].second));}}
                if (j > 0){
                    if(board[i][j].first==board[i][j-1].first) merge(board[i][j-1].second,board[i][j].second);
                    else edges.emplace_back(make_pair(board[i][j].second,board[i][j-1].second));}}}
        for (auto edge: edges){int p_a = find_root(edge.first), p_b=find_root(edge.second);
            adj_list[p_a].push_back(p_b); adj_list[p_b].push_back(p_a);} int radius = INF;
        for (int i = 0; i < M*N; i++){
            if (find_root(i) == i){radius = min(radius, BFS_distance(i));}}cout << radius << endl;}}