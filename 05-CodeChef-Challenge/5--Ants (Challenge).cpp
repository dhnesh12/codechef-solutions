#include <bits/stdc++.h>
using namespace std;

unordered_set<int > G[10005], GB[10005];
int deg[10005];

class gh {
public:
  int deg;
  int D;
  int node;
};

int n, m, k, s;

unordered_set<int> stp;
vector<pair<pair<int, int>, int> > PD[10005];

void foo(int a, int b, int clr)
{
  G[a].erase(b | (clr << 14));
  G[b].insert(a | (clr << 14));

  GB[b].erase(a | (clr << 14));
  GB[a].insert(b | (clr << 14));
}

vector<int> T[10005];
vector<int> toposort;
bool visited[10005];
unordered_map<int, int > mp;

int countingmachine[100004];
vector<int> anotherV;

void dfs(int r)
{
  visited[r] = 2;
  vector<pair<int, int> > P;
  for (int i = 0; i < T[r].size(); ++i)
  {
    if(visited[T[r][i]] == 0) {
      P.push_back(pair<int, int>(deg[T[r][i]], T[r][i]) );
    }
  }

  sort(P.begin(), P.end());
  reverse(P.begin(), P.end());

  for (int i = 0; i < P.size(); ++i)
  {
    if(visited[P[i].second] == 0)
    dfs(P[i].second);
  }
  toposort.push_back(r);
}

int depth[10005];
int AO[1000][1000];


void depcalc()
{
  int r = 2;
  queue<pair<int, int> > q;
  q.push(pair<int, int>(r, 0) );
  visited[r] = 1;
  while((int)q.size() != 0)
  {
    pair<int, int> P = q.front();

    q.pop();

    depth[P.first] = P.second;

    for (int i = 0; i < T[P.first].size(); ++i)
    {
      if(visited[T[P.first][i]] == 1) continue;

      visited[T[P.first][i]] = 1;

      q.push(pair<int, int>(T[P.first][i], P.second + 1));
    }
  }
}

int qwertycounting;

void coo(int A, int ignr, int pos[])
{
   for (int i = 0; i < PD[A].size(); ++i)
   {
      qwertycounting++;
      int a = PD[A][i].first.first;
      int b = PD[A][i].first.second;
      int clr = PD[A][i].second;
      // assert(b == A);
      // assert(pos[a] < pos[b]);

      if(a == ignr) continue;

      foo(a, b, clr);


      int qw;
      if(n != 1000)
      qw = mp[a | (b << 14) ];
      else qw = AO[a][b];
      // if(stp.find(qw) == stp.end()) {
      //   stp.insert(qw);
        // assert(false);
      // }
      // else
      // {
      countingmachine[qw]++;
      if(countingmachine[qw] == 1)
      anotherV.push_back(qw);
      //}
   }

   PD[A].clear();

   int szx = PD[A].size();

   // assert(szx == 0);
}

bool cmp(gh g1, gh g2)
{
  if(g1.D != g2.D) return g1.D > g2.D;

  if(g1.deg != g2.deg) return g1.deg < g2.deg;

  return g1.node > g2.node;
}


int main()
{
  
  cin >> n >> m >> k >> s;

  int klopio[m];

  

  vector<pair<int, int> > Pvec(n), DPvec(n);
  for (int i = 0; i < n; ++i)
  {
    Pvec[i].first = 0;
    Pvec[i].second = i;
  }
  double op = 0.5;
  mp.reserve(op);

  for (int i = 0; i < n; ++i)
  {
    G[i].reserve(op);
    GB[i].reserve(op);
    visited[i] = 0;
    deg[i] = 0;
    depth[i] = 0;
  }


  gh yas[n];

  for (int i = 0; i < n; ++i)
  {
    yas[i].node = i;
    yas[i].deg = 0;
  }


  for (int i = 0; i < m; ++i)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    T[a].push_back(b);
    T[b].push_back(a);
    mp[a | (b << 14)] = i;
    mp[b | (a << 14)] = i;

    if(n == 1000) {
      AO[a][b] = i;
      AO[b][a] = i;
    }
    G[a].insert(b | (c << 14) );
    GB[b].insert(a | (c << 14) );
    Pvec[a].first++;
    Pvec[b].first++;
     klopio[i] = c;
    yas[a].deg++;
    yas[b].deg++;
  }

   for (int i = 0; i < n; ++i)  
   {
     visited[i] = 0;
   }

   depcalc();

   for (int i = 0; i < n; ++i)
   {
     // assert(visited[i] == 1);
   }

   for (int i = 0; i < n; ++i)
   {
     yas[i].D = depth[i];
   }

   sort(yas, yas + n, cmp);

   for (int i = 0; i < n; ++i)
   {

     Pvec[i].second = yas[i].node;
     Pvec[i].first = yas[i].D;
     //mkop = max(mkop, yas[i].D);
   }





  // random_shuffle(Pvec.begin(), Pvec.end());
  // random_shuffle(Pvec.begin(), Pvec.end());

   //sort(Pvec.begin(), Pvec.end());

  // reverse(Pvec.begin(), Pvec.end());

  int doneTimes = 0;
  int cntAnts[n];
  for (int i = 0; i < n; ++i)
  {
    cntAnts[i] = 1;
  }

  int nodesWithAnts = n;

  int pos[n];

  for (int i = 0; i < n; ++i)
  {
    pos[Pvec[i].second] = i;
  }


  int SIW[n];

  for (int i = 0; i < n; ++i)
  {
    int maxpos = -1;
    int ele;
    for (int j = 0; j < T[i].size(); ++j)
    {
      if(pos[T[i][j]] > maxpos) {
        maxpos = pos[T[i][j]];
        ele = T[i][j];
      }
    }
    SIW[i] = ele;
  }



  // for (int i = 0; i < n; ++i)
  // {
  //   cout << Pvec[i].second + 1 << "\n";
  // }


  vector<pair<int, int> > ansvec;

  int cnty = 0, klopcnty = 0;

  //cout << pos[4] << " " << pos[3] << "gfgd\n";

  while(nodesWithAnts > k)
  {
    //vector<pair<pair<int, int>, int> > PD[n];

    for (int i = 0; i < n; ++i)
    {
      PD[i].clear();
    }
    //double nmd = 100000.0;
    //stp.reserve(nmd);
    for (int i = 0; i < n; ++i)
    {
       vector<pair<int, pair<int, int> > > correctionVector;
       int r = Pvec[i].second;
       if(cntAnts[r] == 0) continue;
       //cout << r << "\n";

       for(auto it = G[r].begin(); it != G[r].end(); ++it)
       {
         int olp = ((*it) >> 14);
         int node = ((*it) ^ (olp << 14));

         if(pos[r] > pos[node])
         {
            int clr = olp;
            correctionVector.push_back(pair<int, pair<int, int> >(r, pair<int, int>(node, clr) ));
         }
       }

       for (int j = 0; j < correctionVector.size(); ++j)
       {
          int a = correctionVector[j].first;
          int b = correctionVector[j].second.first;
          int c = correctionVector[j].second.second;

          foo(a, b, c);

          // cout << a << " " << b << "\n";
          int qw;
          if(n != 1000)
          qw = mp[a | (b << 14) ];
          else qw = AO[a][b];
          //if(stp.find(qw) == stp.end())
          countingmachine[qw]++;
          if(countingmachine[qw] == 1)
          anotherV.push_back(qw);
          //else
          //stp.erase(qw);
          PD[a].push_back(pair<pair<int, int>, int>(pair<int, int>(b, a), c));
          qwertycounting++;
          //ansvec.push_back(pair<int, int>(1, qw) );
          cnty++;
          // assert(cnty <= 500000);
       }
    }

    // cout << "dfd\n";
    // for(auto it = stp.begin(); it != stp.end(); ++it) cout << (*it).second << "\n";

    // break;


    





    bool banny[n], Pbanny[n];
    for (int i = 0; i < n; ++i)
    {
       banny[i] = 0;
       if(cntAnts[i] == 0) 
        banny[i] = 1;

       Pbanny[i] = 0;
    }

    int FT = -1;
    Pbanny[Pvec[n - 1].second] = 1;



    for (int i = 0; i < n; ++i)
    {
      int r = Pvec[i].second;
      if(banny[r] == 1 || Pbanny[r] == 1) continue;

      int sz = G[r].size();

        bool klop = 0;
         // assert(sz != 0);
      if(FT == -1 && sz >= 1) {
        FT = r;
        klop = 1;
      }
      if(sz == 0) continue;



      vector<pair<int, pair<int, int> > > correctionVector;

      bool fg = 0;
      int maxm = -1;
      int cn;


      int cantalope = 0;

      for (int j = 0; j < T[r].size(); ++j)
      {
         if(pos[T[r][j]] < pos[r] && (banny[T[r][j]] == 1 || Pbanny[T[r][j]] == 1) && cntAnts[T[r][j]] != 0) {
          if(SIW[T[r][j]] == r) cantalope++;
         }
      }

      if(n == 1000)
      if(cantalope >= 5)
      {
         coo(r, -1, pos);
         banny[r] = 1;
         continue;
      }

      if(n == 10000)
      if(cantalope >= 1)
      {
         coo(r, -1, pos);
         banny[r] = 1;
         continue;
      }

      for(auto it = G[r].begin(); it != G[r].end(); ++it)
      {
        int olp = ((*it) >> 14);
        pair<int, int> P;
        P.first = ((*it) ^ (olp << 14));
        P.second = olp;

        int node = P.first;
        int clr = P.second;

       

        int sz = G[node].size();
        // if(Pbanny[node] == 1 && sz == 0) {
        //   fg = 1;
        //   break;
        // }

        correctionVector.push_back(pair<int, pair<int, int> >(pos[node], pair<int, int>(node, clr) ) );
        if(pos[node] > maxm) {
          maxm = pos[node];
          cn = node;
        }
      }

      //if(nodesWithAnts == 4) break;

      //Pbanny[cn] = 1;

      for (int j = 0; j < correctionVector.size(); ++j)
      {
        //int uisz = G[correctionVector[j].second.first].size();
         coo(correctionVector[j].second.first, r, pos);
         //int uisz1 = G[correctionVector[j].second.first].size();
         // assert(uisz1 >= uisz);

         if(correctionVector[j].second.first == cn) {
          Pbanny[cn] = 1;
          continue;
         }

         int node = correctionVector[j].second.first;
         int clr = correctionVector[j].second.second;

        int qw;
        if(n != 1000)
        qw = mp[r | (node << 14) ];
        else qw = AO[r][node];
          //ansvec.push_back(pair<int, int>(1, qw) );
         countingmachine[qw]++;
          if(countingmachine[qw] == 1)
         anotherV.push_back(qw);
         cnty++;
         qwertycounting++;
         // assert(cnty <= 500000);
         banny[node] = 1;

         foo(r, node, clr);

         int sz = G[node].size();
        // assert(sz >= 1);
         if(sz >= 2) continue;

         // assert(false);
         int op = GB[node].size();
         // assert(op != 0);
         auto it = (GB[node].begin());

          int olp = ((*it) >> 14);
          pair<int, int> P;
          P.first = ((*it) ^ (olp << 14));
          P.second = olp;

          if(n != 1000)
          qw = mp[P.first | (node << 14) ];
          else qw = AO[P.first][node];
          //ansvec.push_back(pair<int, int>(1, qw) );
          countingmachine[qw]++;
          if(countingmachine[qw] == 1)
         anotherV.push_back(qw);
         qwertycounting++;
          cnty++;
         // assert(cnty <= 500000);
         foo(P.first, node, P.second);
      }
      //  if(FT != -1)
      // {
      //   int nm = G[FT].size();
        // assert(nm <= 1);
      // }
    }





    // assert(cnty <= 500000);

    int minm = 100000;
    int temp[n];
    for (int i = 0; i < n; ++i)
    {
      temp[i] = 0;
    }


    for (int i = 0; i < n; ++i)
    {  
       int sz = G[i].size();
       if(cntAnts[i] != 0) minm = min(minm, pos[i]);
       if(sz != 1) {
        temp[i] += cntAnts[i];
        continue;
       }

       auto it = (G[i].begin());

       int olp = ((*it) >> 14);
        pair<int, int> P;
        P.first = ((*it) ^ (olp << 14));
        P.second = olp;
       temp[P.first] += cntAnts[i];
    }

    int ol = nodesWithAnts;
    nodesWithAnts = 0;

    int minm1 = 100000;
    for (int i = 0; i < n; ++i)
    {
      cntAnts[i] = temp[i];
      if(cntAnts[i] >= 1) {
        minm1 = min(minm1, pos[i]);
        nodesWithAnts++;
      }
    }

    // if(minm1 == minm) {
    //   cout << minm << " ffgf\n";
    //   break;
    // }
    // assert(minm < minm1);

    // if(doneTimes == 2)
    // {
    //   cout << "\n";
    //   cout << ansvec.size() << " fdf\n";

    //   for (int i = 0; i < ansvec.size(); ++i)
    //   {
    //     cout << ansvec[i].first << " " << ansvec[i].second << "gf\n";
    //   }

    //   for (int i = 0; i < n; ++i)
    //   {
    //      cout << i << " --> ";
    //      for(auto it = G[i].begin(); it != G[i].end(); ++it) {
    //         int olp = ((*it) >> 14);
    //         pair<int, int> P;
    //         P.first = ((*it) ^ (olp << 14));
    //         P.second = olp;
    //         cout << P.first << ", " << P.second <<"  ";
    //      }
    //      cout << "\n";
    //   }
    //   cout << "\n";
    //   for (int i = 0; i < n; ++i)
    //   {
    //     cout << cntAnts[i] << " ";
    //   }
    //   cout << "\n";
    //   cout << nodesWithAnts << "\n";
    //   cout << "\n";
    // }

    for(int ii = 0; ii < anotherV.size(); ++ii)
    {
      if(countingmachine[anotherV[ii]] % 2 == 1)
      ansvec.push_back(pair<int, int>(1, anotherV[ii]));

      countingmachine[anotherV[ii]] = 0;
    }

    anotherV.clear();

    


    if(true) {
      doneTimes++;
      klopcnty++;
      // assert(klopcnty <= 700);
      ansvec.push_back(pair<int, int>(2, 8) );
    }


    // if(doneTimes == 3)
    // {
    //   cout << "\n";
    //   cout << ansvec.size() << " fdf\n";

    //   for (int i = 0; i < ansvec.size(); ++i)
    //   {
    //     cout << ansvec[i].first << " " << ansvec[i].second << "gf\n";
    //   }

    //   for (int i = 0; i < n; ++i)
    //   {
    //      cout << i << " --> ";
    //      for(auto it = G[i].begin(); it != G[i].end(); ++it) {
    //         int olp = ((*it) >> 14);
    //         pair<int, int> P;
    //         P.first = ((*it) ^ (olp << 14));
    //         P.second = olp;
    //         cout << P.first << ", " << P.second <<"  ";
    //      }
    //      cout << "\n";
    //   }
    //   cout << "\n";
    //   for (int i = 0; i < n; ++i)
    //   {
    //     cout << cntAnts[i] << " ";
    //   }
    //   cout << "\n";
    //   cout << nodesWithAnts << "\n";
    //   cout << "\n";
    // }


    
  }

  //cout << qwertycounting << " rgfdg\n";

 //cout << doneTimes << endl;
 int costy = 0;

  int sz = ansvec.size();
  cout << sz << "\n";

  cnty = 0;


  for (int i = 0; i < ansvec.size(); ++i)
  {
    if(ansvec[i].first == 2) {
    cout << "2\n";
      costy += s;
      continue;
    }
    cout << "1 " << ansvec[i].second + 1 << "\n";
    cnty += klopio[ansvec[i].second];
  }
   //cout << cnty << " ";
   //cout << costy << "\n";
}
