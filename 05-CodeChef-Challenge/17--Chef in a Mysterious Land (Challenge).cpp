// https://www.codechef.com/AUG18A/problems/MYST
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

// Hungarian algorithm taken from https://github.com/RoboJackets/hungarian
// Comments stripped for brevity, go to link for copyright and licensing info
/** Begin of reused code **/
#include <vector>

typedef enum {
	HUNGARIAN_MODE_MINIMIZE_COST,
	HUNGARIAN_MODE_MAXIMIZE_UTIL,
} MODE;

typedef enum {
	HUNGARIAN_NOT_ASSIGNED,
	HUNGARIAN_ASSIGNED,
} ASSIGN;

class Hungarian
{

public:
	/** This method initialize the hungarian_problem structure and init 
	 *  the  cost matrices (missing lines or columns are filled with 0).
	 *  It returns the size of the quadratic(!) assignment matrix. **/

	Hungarian();
	Hungarian(const vector<vector<int> >&, int, int, MODE);

	int init(const vector<vector<int> >& input_matrix, 
			   int rows, 
			   int cols, 
			   MODE mode);

	/** This method computes the optimal assignment. **/
	bool solve();

	/** Accessor for the cost **/
	int cost() const;

	/** Reference accessor for assignment **/
	const vector<vector<int> >& assignment() const;

	/** Print the computed optimal assignment. **/
	void print_assignment();

	/** Print the cost matrix. **/
	void print_cost();

	/** Print cost matrix and assignment matrix. **/
	void print_status();

protected:
	bool check_solution(const vector<int>& row_dec, const vector<int>& col_inc, const vector<int>& col_vertex);
	bool assign_solution(const vector<int>& row_dec, const vector<int>& col_inc, const vector<int>& col_vertex);

private:

	int m_cost;
	int m_rows;
	int m_cols;
	vector<vector<int> > m_costmatrix;
	vector<vector<int> > m_assignment;   

};

#define verbose (0)

Hungarian::Hungarian()
{
	//much ado about nothing
	m_rows = 1;
	m_cols = 1;

	m_costmatrix.resize(m_rows, vector<int>(m_cols,0));
	m_assignment.resize(m_rows, vector<int>(m_cols,0));
}

Hungarian::Hungarian(const vector<vector<int> >& input_matrix, int rows, int cols, MODE mode)
{
  int i,j, org_cols, org_rows;
  int max_cost;
  max_cost = 0;
  
  org_cols = cols;
  org_rows = rows;

  // is the matrix square? 
  // if no, expand with 0-cols / 0-cols

  if(rows!=cols)
  {
	  rows = std::max(cols, rows);
	  cols = rows;
  }
  
  m_rows = rows;
  m_cols = cols;

  m_costmatrix.resize(rows, vector<int>(cols,0));
  m_assignment.resize(rows, vector<int>(cols,0));

  for(i=0; i<m_rows; i++) 
  {
	  for(j=0; j<m_cols; j++) 
	  {
		  m_costmatrix[i][j] =  (i < org_rows && j < org_cols) ? input_matrix[i][j] : 0;
		  m_assignment[i][j] = 0;

		  if (max_cost < m_costmatrix[i][j])
		  {
			  max_cost = m_costmatrix[i][j];
		  }
	  }
  }


  if (mode == HUNGARIAN_MODE_MAXIMIZE_UTIL) 
  {
	  for(i=0; i<m_rows; i++) 
	  {
		  for(j=0; j<m_cols; j++) 
		  {
			  m_costmatrix[i][j] =  max_cost - m_costmatrix[i][j];
		  }
	  }
  }
  else if (mode == HUNGARIAN_MODE_MINIMIZE_COST) 
  {
    // nothing to do
  }
  else 
    fprintf(stderr,"%s: unknown mode. Mode was set to HUNGARIAN_MODE_MINIMIZE_COST !\n", __FUNCTION__);
}


void hungarian_print_matrix(const vector<vector<int> >& C, int rows, int cols) 
{
	int i,j;
	fprintf(stderr , "\n");
	for(i=0; i<rows; i++) 
	{
		fprintf(stderr, " [");
		for(j=0; j<cols; j++) 
		{
		fprintf(stderr, "%5d ",C[i][j]);
		}
		fprintf(stderr, "]\n");
	}
	fprintf(stderr, "\n");
}

void Hungarian::print_assignment() {
  hungarian_print_matrix(m_assignment, m_rows, m_cols) ;
}

void Hungarian::print_cost() {
  hungarian_print_matrix(m_costmatrix, m_rows, m_cols) ;
}

void Hungarian::print_status() 
{
  
  fprintf(stderr,"cost:\n");
  print_cost();

  fprintf(stderr,"assignment:\n");
  print_assignment();
  
}

int Hungarian::init(const vector<vector<int> >& input_matrix, int rows, int cols, MODE mode) 
{

  int i,j, org_cols, org_rows;
  int max_cost;
  max_cost = 0;
  
  org_cols = cols;
  org_rows = rows;

  // is the number of cols  not equal to number of rows ? 
  // if yes, expand with 0-cols / 0-cols
  rows = std::max(cols, rows);
  cols = rows;
  
  m_rows = rows;
  m_cols = cols;

  m_costmatrix.resize(rows, vector<int>(cols,0));
  m_assignment.resize(rows, vector<int>(cols,0));

  for(i=0; i<m_rows; i++) 
  {
    for(j=0; j<m_cols; j++) 
	{
      m_costmatrix[i][j] =  (i < org_rows && j < org_cols) ? input_matrix[i][j] : 0;
      m_assignment[i][j] = 0;

      if (max_cost < m_costmatrix[i][j])
	   max_cost = m_costmatrix[i][j];
    }
  }


  if (mode == HUNGARIAN_MODE_MAXIMIZE_UTIL) {
    for(i=0; i<m_rows; i++) {
      for(j=0; j<m_cols; j++) {
	m_costmatrix[i][j] =  max_cost - m_costmatrix[i][j];
      }
    }
  }
  else if (mode == HUNGARIAN_MODE_MINIMIZE_COST) {
    // nothing to do
  }
  else 
    fprintf(stderr,"%s: unknown mode. Mode was set to HUNGARIAN_MODE_MINIMIZE_COST !\n", __FUNCTION__);
  
  return rows;
}

bool Hungarian::check_solution(const vector<int>& row_dec, const vector<int>& col_inc, const vector<int>& col_vertex)
{
	int k, l, m, n;

	m = m_rows;
	n = m_cols;
	// Begin doublecheck the solution 23
	for (k=0;k<m;k++)
		for (l=0;l<n;l++)
			if (m_costmatrix[k][l]<row_dec[k]-col_inc[l])
			return false;

	for (k=0;k<m;k++)
	{
		l=col_vertex[k];
		if (l<0 || m_costmatrix[k][l]!=row_dec[k]-col_inc[l])
			return false;
	}
	k=0;
	
	for (l=0;l<n;l++)
	{
		if (col_inc[l])
		{
			k++;
		}
	}
	if (k>m)
	{
		return false;
	}

	//everything checks out, then
	return true;
  // End doublecheck the solution 23
}
bool Hungarian::assign_solution(const vector<int>& row_dec,const vector<int>&  col_inc, const vector<int>&  col_vertex)
{
	  // End Hungarian algorithm 18
	int i, j, k, l, m, n;

	m = m_rows;
	n = m_cols;

	for (i=0;i<m;++i)
	{
		m_assignment[i][col_vertex[i]]=HUNGARIAN_ASSIGNED;
		/*TRACE("%d - %d\n", i, col_vertex[i]);*/
	}
	for (k=0;k<m;++k)
	{
		for (l=0;l<n;++l)
		{
		/*TRACE("%d ",m_costmatrix[k][l]-row_dec[k]+col_inc[l]);*/
			m_costmatrix[k][l]=m_costmatrix[k][l]-row_dec[k]+col_inc[l];
		}
		/*TRACE("\n");*/
	}
	for (i=0;i<m;i++)
	{
		m_cost+=row_dec[i];
	}
	for (i=0;i<n;i++)
	{
		m_cost-=col_inc[i];
	}
	if (verbose)
		fprintf(stderr, "Cost is %d\n",m_cost);

	return true;

}

bool Hungarian::solve()
{
	int i, j, m, n, k, l, s, t, q, unmatched, cost;

	m = m_rows;
	n = m_cols;

	int INF = std::numeric_limits<int>::max();

	//vertex alternating paths,
	vector<int> col_vertex(m), row_vertex(n), unchosen_row(m), parent_row(n),
				row_dec(m),  col_inc(n),  slack_row(m),    slack(n);

	cost=0;

	for (i=0;i<m_rows;i++) 
	{
		col_vertex[i]=0;
		unchosen_row[i]=0;
		row_dec[i]=0;
		slack_row[i]=0;
	}

	for (j=0;j<m_cols;j++) 
	{
		row_vertex[j]=0;
		parent_row[j] = 0;
		col_inc[j]=0;
		slack[j]=0;
	}

	//Double check assignment matrix is 0
	m_assignment.assign(m, vector<int>(n, HUNGARIAN_NOT_ASSIGNED));

  // Begin subtract column minima in order to start with lots of zeroes 12
	if (verbose)
	{
		fprintf(stderr, "Using heuristic\n");
	}

	for (l=0;l<n;l++)
	{
		s = m_costmatrix[0][l];

		for (k=1;k<m;k++) 
		{
			if (m_costmatrix[k][l] < s)
			{
				s=m_costmatrix[k][l];
			}
			cost += s;
		}

		if (s!=0)
		{
			for (k=0;k<m;k++)
			{
				m_costmatrix[k][l]-=s;
			}
		}

		//pre-initialize state 16
		row_vertex[l]= -1;
		parent_row[l]= -1;
		col_inc[l]=0;
		slack[l]=INF;
	}
  // End subtract column minima in order to start with lots of zeroes 12

  // Begin initial state 16
	t=0;

	for (k=0;k<m;k++)
	{
		bool row_done = false;
		s=m_costmatrix[k][0];

		for (l=0;l<n;l++)
		{

			if(l > 0)
			{
				if (m_costmatrix[k][l] < s)
				{
					s = m_costmatrix[k][l];
				}
				row_dec[k]=s;
			}

			if (s == m_costmatrix[k][l] && row_vertex[l]<0)
				{
					col_vertex[k]=l;
					row_vertex[l]=k;

					if (verbose)
					{
						fprintf(stderr, "matching col %d==row %d\n",l,k);
					}
					row_done = true;
					break;
				}
		}

		if(!row_done)
		{
			col_vertex[k]= -1;

			if (verbose)
			{
				fprintf(stderr, "node %d: unmatched row %d\n",t,k);
			}
		
			unchosen_row[t++]=k;
		}

	}
  // End initial state 16

	bool checked = false;

  // Begin Hungarian algorithm 18

	//is matching already complete?
	if (t == 0)
	{
		checked = check_solution(row_dec, col_inc, col_vertex);
		if (checked)
		{
			//finish assignment, wrap up and done.
			bool assign = assign_solution(row_dec, col_inc, col_vertex);
			return true;
		}
		else
		{
			if(verbose)
			{
				fprintf(stderr, "Could not solve. Error.\n");
			}
			return false;
		}
	}

	unmatched=t;


	while (1)
	{
		if (verbose)
		{
			fprintf(stderr, "Matched %d rows.\n",m-t);
		}
		q=0;
		bool try_matching;
		while (1)
		{
			while (q<t)
			{
			// Begin explore node q of the forest 19
				
				k=unchosen_row[q];
				s=row_dec[k];
				for (l=0;l<n;l++)
				{
					if (slack[l])
					{
						int del;
						del=m_costmatrix[k][l]-s+col_inc[l];
						if (del<slack[l])
						{
							if (del==0)
							{
								if (row_vertex[l]<0)
								{
									goto breakthru;
								}
								slack[l]=0;
								parent_row[l]=k;
								if (verbose)
									fprintf(stderr, "node %d: row %d==col %d--row %d\n",
									t,row_vertex[l],l,k);
									unchosen_row[t++]=row_vertex[l];
							}
							else
							{
								slack[l]=del;
								slack_row[l]=k;
							}
						}
					}
				}
			// End explore node q of the forest 19
				q++;	
			}
 
	  // Begin introduce a new zero into the matrix 21
		s=INF;
		for (l=0;l<n;l++)
		{
			if (slack[l] && slack[l]<s)
			{
				s=slack[l];
			}
		}
		for (q=0;q<t;q++)
		{
			row_dec[unchosen_row[q]]+=s;
		}
		for (l=0;l<n;l++)
		{
			//check slack
			if (slack[l])
			{
				slack[l]-=s;
				if (slack[l]==0)
				{
					// Begin look at a new zero 22
					k=slack_row[l];
					if (verbose)
					{
						fprintf(stderr, 
						"Decreasing uncovered elements by %d produces zero at [%d,%d]\n",
						s,k,l);
					}
					if (row_vertex[l]<0)
					{
						for (j=l+1;j<n;j++)
							if (slack[j]==0)
							{
								col_inc[j]+=s;
							}

						goto breakthru;
					}
					else
					{
						parent_row[l]=k;
						if (verbose)
						{
							fprintf(stderr, "node %d: row %d==col %d--row %d\n",t,row_vertex[l],l,k);
							unchosen_row[t++]=row_vertex[l];
						}
					}
		// End look at a new zero 22
				}
			}
			else
			{
				col_inc[l]+=s;
			}
		}
	// End introduce a new zero into the matrix 21
	}

    breakthru:
      // Begin update the matching 20
		if (verbose)
		{
			fprintf(stderr, "Breakthrough at node %d of %d!\n",q,t);
		}
		while (1)
		{	
		j=col_vertex[k];
			col_vertex[k]=l;
			row_vertex[l]=k;
			if (verbose)
			{
				fprintf(stderr, "rematching col %d==row %d\n",l,k);
			}
			if (j<0)
			{
				break;
			}
			k=parent_row[j];
			l=j;
		}
		// End update the matching 20
		if (--unmatched == 0)
		{
			checked = check_solution(row_dec, col_inc, col_vertex);
			if (checked)
			{
				//finish assignment, wrap up and done.
				bool assign = assign_solution(row_dec, col_inc, col_vertex);
				return true;
			}
			else
			{
				if(verbose)
				{
					fprintf(stderr, "Could not solve. Error.\n");
				}
				return false;
			}
		}
		
		// Begin get ready for another stage 17
			t=0;
			for (l=0;l<n;l++)
			{
				parent_row[l]= -1;
				slack[l]=INF;
			}
			for (k=0;k<m;k++)
			{
				if (col_vertex[k]<0)
				{
					if (verbose)
						fprintf(stderr, "node %d: unmatched row %d\n",t,k);
					unchosen_row[t++]=k;
				}
			}
		// End get ready for another stage 17
	}// back to while loop


}

//ACCESSORS

int Hungarian::cost() const
{
	return m_cost;
}

const vector<vector<int> >& Hungarian::assignment() const
{
	return m_assignment;
}

/** end of reused code */

typedef tuple<int, int> ii;
typedef tuple<int, int, int> iii;
typedef tuple<int, int, int, int> iiii;
typedef tuple<int, int, int, int, int> iiiii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<iiii> viiii;
typedef vector<iiiii> viiiii;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef queue<int> qi;

const int MAXITER = 3;
const int INF = 100000000;

int t, nn, n, b, x, c, l, gc;
vii p;
int a[100][100], d[100][100], e[100][100];
iii pp;
bool ppf;

vi h(vvi &g, int u, int v) {
  vb visited(n);
  vi distance(n);
  vi parent(n);
  qi q;
  visited[u] = true;
  q.push(u);
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    for (int z:g[i]) {
      if (visited[z]) continue;
      visited[z] = true;
      parent[z] = i;
      if (z == v) {
        vi p;
        do {
          p.push_back(z);
          z = parent[z];
        } while (z != u);
        reverse(p.begin(), p.end());
        return p;
      }
      q.push(z);
    }
  }
  return vi();
}

vi hh(const vvi &g, int u) {
  vb visited(n);
  vi distance(n, INF);
  qi q;
  visited[u] = true;
  distance[u] = 0;
  q.push(u);
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    for (int z:g[i]) {
      if (visited[z]) continue;
      visited[z] = true;
      distance[z] = distance[i] + 1;
      q.push(z);
    }
  }
  return distance;
}


int f(int u, int v, int k) {
  vvi g(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] > 0)
        g[i].push_back(j);
  vi p1 = h(g, c, u);
  if (!p1.size() && c != u) return 0;
  g = vvi(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] > (i == u && j == k))
        g[i].push_back(j);
  vi p2 = h(g, u, v);
  if (!p2.size() && u != v) return 0;
  for (int z:p1) {
    p.push_back({z, 0});
  }
  for (int z:p2) {
    p.push_back({z, k + 1});
  }
  return p1.size() + p2.size();
}

viiii initial_path(int position, bool rec=0) {
  viiii p;
  vvi g(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] > 0)
        g[i].push_back(j);
  vvi c = vvi(n);
  for (int i = 0; i < n; i++)
    c[i] = hh(g, i);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (c[i][j] >= INF) return p;
  for (int j = 0; j < n; j++) {
    vi x, y;
    for (int i = 0; i < n; i++)
      if (a[i][j] > d[i][j]) {
        for (int k = d[i][j]; k < a[i][j]; k++)
          x.push_back(i);
      }
      else if (a[i][j] < d[i][j]) {
        for (int k = a[i][j]; k < d[i][j]; k++)
          y.push_back(i);
      }
    assert(x.size() == y.size());
    int l = x.size();
    if (!l) continue;
    if (l == 1) {
      p.push_back({c[position][x[0]] + c[x[0]][y[0]], x[0], y[0], j});
      continue;
    }
    vvi m(l, vi(l));
    for (int ii = 0; ii < l; ii++)
      for (int jj = 0; jj < l; jj++) {
        int from = x[ii];
        int to = y[jj];
        m[ii][jj] = c[position][from] + c[from][to];
      }
    Hungarian hungarian(m, l, l, HUNGARIAN_MODE_MINIMIZE_COST);
    hungarian.solve();
    vvi a = hungarian.assignment();
    int cc = 0;
    for (int i = 0; i < l; i++)
      for (int k = 0; k < l; k++)
        if (a[i][k]) {
          cc++;
          int from = x[i];
          int to = y[k];
          p.push_back({c[position][from] + c[from][to], from, to, j});
        }
    if (!cc)
      for (int i = 0; i < l; i++) {
        int from = x[i];
        int o = gc ? gc - 1 : 0;
        int to = y[(i+o)%l];
        p.push_back({c[position][from] + c[from][to], from, to, j});
      }
  }
  sort(p.begin(), p.end());
  if (p.size() > 1 && rec < 1) {
    viiiii ranking;
    int x = 3;
    if (n < 50) x++;
    if (n < 80) x++;
    for (int i = 0; i < min(x, int(p.size())); i++) {
      int l, u, v, k;
      tie(l, u, v, k) = p[i];
      a[u][k]--;
      a[v][k]++;
      viiii p2 = initial_path(v, rec+1);
      if (p2.size()) {
        int l2, u2, v2, k2;
        tie(l2, u2, v2, k2) = p2[0];
        ranking.push_back({l + l2, i, u2, v2, k2});
      }
      a[u][k]++;
      a[v][k]--;
    }
    if (!ranking.size()) return p;
    sort(ranking.begin(), ranking.end());
    viiii p3;
    int l, i, u, v, k;
    tie(l, i, u, v, k) = ranking[0];
    pp = {u, v, k};
    ppf = true;
    for (auto z:ranking) p3.push_back(p[i]);
    return p3;
  }
  return p;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
  cin >> t;
  while (t--) {
    cin >> n;
    nn+=n;
    p = vii();
    c = 0;
    memset(e, 0, sizeof(int)*100*100);
    memset(d, 0, sizeof(int)*100*100);
    for (int i = 0; i < n; i++) {
      cin >> b;
      for (int j = 0; j < b; j++) {
        cin >> x;
        x--;
        e[x][i]++;
      }
      for (int j = 0; j < b; j++) {
        cin >> x;
        x--;
        d[x][i]++;
      }
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        a[i][j] = e[i][j];
    do {
      viiii ir = initial_path(c);
      if (!ir.size()) break;
      int i = 0, l, u, v, k;
      tie(l, u, v, k) = ir[i];
      while (!(l = f(u, v, k))) tie(l, u, v, k) = ir[++i];
      a[u][k]--;
      a[v][k]++;
      c = v;
    } while(true);
    vii bp(p.size());
    copy(p.begin(), p.end(), bp.begin());
    gc = 0;
    while (true) {
      p = vii();
      gc++;
      if (gc == MAXITER) break;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          a[i][j] = e[i][j];
      c = 0;
      do {
        ppf = false;
        viiii ir = initial_path(c);
        if (!ir.size()) break;
        int i = 0, l, u, v, k;
        tie(l, u, v, k) = ir[i];
        l = f(u, v, k);
        if (l) {
          a[u][k]--;
          a[v][k]++;
          c = v;
          if (ppf) {
            tie(u, v, k) = pp;
            l = f(u, v, k);
            if (l) {
              a[u][k]--;
              a[v][k]++;
              c = v;
            }
          }
        } else {
          while (!(l = f(u, v, k))) tie(l, u, v, k) = ir[++i];
          a[u][k]--;
          a[v][k]++;
          c = v;
        }
      } while(true);
      if (p.size() < bp.size()) {
        bp = vii(p.size());
        copy(p.begin(), p.end(), bp.begin());
      }
    }
    cout << bp.size() << endl;
    for (auto z:bp) {
      int u, v;
      tie(u, v) = z;
      cout << u + 1 << " " << v << endl;
    }
  }
}
