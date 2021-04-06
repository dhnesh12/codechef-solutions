#include <iostream>
#include <algorithm>
using namespace std;


const int vsize = 101;
const int esize = 200;
class pr
{
public:
	int p;
	int r;
};

class uv
{
public:
	int u;
	int v;
	bool operator<(uv arg)
	{
		return u < arg.u || (u == arg.u && v < arg.v);
	}
};

class venm
{
public:
	pr V[vsize];
	uv E[esize];
	int n, m;

	void set()
	{
		sort(E, E+m);
		for(int i = 1;i <= n;i++){V[i].p = V[i].r = 0;}

		V[E[0].u].p = 0;
		E[m].u = -1;

		for(int i = 1;i <= m;i++)
		{
			if(E[i-1].u != E[i].u)
			{
				V[E[i-1].u].r = i;
				V[E[i].u].p = i;
			}
		}
	}

	int ingraph(uv e)
	{
		int p = V[e.u].p;
		int r = V[e.u].r;
		int i = -1;

		while(r-p > 0)
		{
			int q = (p+r)/2;
			if(E[q].v == e.v){i = q;break;}
			else if(E[q].v < e.v){p = q+1;}
			else if(E[q].v > e.v){r = q;}
		}

		return i;
	}

	void addedge(int u,int v)
	{
		E[m].u = u;E[m].v = v;
		m++;
	}

};
venm graph;


int val[101][101][3];
int size[101];
int tgrid[101][3];
int c[3];

void merge(int i1,int i2)
{
    int n1 = size[i1];
    int n2 = size[i2];
    for(int i = 0;i <= n1+n2;i++)
    {
        tgrid[i][0] = tgrid[i][1] = tgrid[i][2] = 1000;
    }

    for(int i = 0;i <= n1;i++)
    {
        for(int j = 0;j <= n2;j++)
        {
            tgrid[i+j][0] = min(tgrid[i+j][0],  val[i1][i][0]+min(val[i2][j][0], val[i2][j][1]));
            tgrid[i+j][1] = min(tgrid[i+j][1],  val[i1][i][1]+min(val[i2][j][0], min(val[i2][j][1], val[i2][j][2])));
            tgrid[i+j][2] = min(tgrid[i+j][2],  val[i1][i][2]+min(val[i2][j][1], val[i2][j][2]));
        }
    }
    for(int i = 0;i <= n1+n2;i++)
    {
        val[i1][i][0] = tgrid[i][0];
        val[i1][i][1] = tgrid[i][1];
        val[i1][i][2] = tgrid[i][2];
    }
    size[i1] = n1+n2;
}

int stk[101];
int pushed[101];
void dfs(int n)
{
    for(int i = 1;i <= n;i++)
    {
        size[i] = 1;
        val[i][0][0] = val[i][1][0] = 1000;
        val[i][0][1] = val[i][1][1] = 1000;
        val[i][0][2] = val[i][1][2] = 1000;
        pushed[i] = 0;
    }
    
    int l = 0;
    stk[l++] = 1;

    while(l > 0)
    {
        int top = stk[l-1];
        if(pushed[top]==0)
        {
            for(int i = graph.V[top].p;i < graph.V[top].r;i++)
            {
                int v = graph.E[i].v;
                if(pushed[v] == 0)
                {
                    stk[l++] = v;
                }
            }
            pushed[top] = 1;
        }
        else
        {
            val[top][1][0] = 0;
            val[top][0][1] = 1;
            val[top][0][2] = 0;
            for(int i = graph.V[top].p;i < graph.V[top].r;i++)
            {
                int v = graph.E[i].v;
                if(pushed[v] == 2)
                {
                    merge(top, v);
                }
            }
            pushed[top] = 2;
            l--;
        }
    }
}
int main()
{
    int t;
    cin >> t;

    while(t-- > 0)
    {
        int n;
        cin >> n;
        c[0] = c[1] = c[2] = 0;

        for(int i = 0;i < n;i++)
        {
            int v;
            cin >> v;
            c[v]++;
        }

        graph.n = n;
        graph.m = 0;
        for(int i = 0;i < n-1;i++)
        {
            int u, v;
            cin >> u >> v;
            graph.addedge(u,v);
            graph.addedge(v,u);
        }
        graph.set();

        
        if(c[0] && c[1] && c[2])
        {
            dfs(n);
            int v1 = min(val[1][c[0]][0], min(val[1][c[0]][1], val[1][c[0]][2]));
            int v2 = min(val[1][c[2]][0], min(val[1][c[2]][1], val[1][c[2]][2]));
            if(min(v1,v2) <= c[1]){cout << 1 << "\n";}
            else{cout << 2 << "\n";}
        }
        else
        {
            if(c[0]==n||c[1]==n||c[2]==n){cout << 0 << "\n";}
            else if(c[1]==0){cout << 2 << "\n";}
            else{cout << 1 << "\n";}
        }
    }
}