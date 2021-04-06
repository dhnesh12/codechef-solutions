// 1:my cell
// 2:judge cell
// -1: blocked cell

#include<bits/stdc++.h>

#define repi(n) for(int i=0;i<(n);++i)
#define repj(n) for(int j=0;j<(n);++j)
#define repr(i,m,n) for(int i=(m);i<=(n);++i)
#define rep1i(n) for(int i=1;i<=(n);++i)
#define sz(a) int((a).size)
#define pb(v) push_back(v)
#define mp(a,b)	make_pair((a),(b))
#define all(v) (v).begin(),(v).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i!=(c).end();++i)
#define pre(c,v) ((c).find()!=(c).end)
#define vpre(c,v) (find(all(c))!=(c).end())
#define nl cout<<endl

#define x first
#define y second

using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vii;
typedef vector<vl> vll;
typedef pair<int,int> ii;

typedef struct _Snake
{
	ii start,end;
}Snake;
Snake MySnake;

int n,m,k;
vii grid;
int dir[4][2] =
{
	{1,0},
	{0,1},
	{-1,0},
	{0,-1}
};

bool iHaveASnake = false;

bool moveMySnake(Snake& MySnake)
{
//	cout << "Enter in move\n";
	for(int d=0;d<4;++d)
	{
//		cout << d << endl;
//		cout << MySnake.start.x << " " << MySnake.start.y << endl;
//		cout << MySnake.end.x << " " << MySnake.end.y << endl;
		
		if( (MySnake.start.x+dir[d][0])<=n && (MySnake.start.x+dir[d][0])>=1 &&
			(MySnake.start.y+dir[d][1])<=m && (MySnake.start.y+dir[d][1])>=1 &&
			grid[MySnake.start.x+dir[d][0]][MySnake.start.y+dir[d][1]] == 0 )
		{
			cout << "MOVE " << MySnake.start.x << " " << MySnake.start.y << " " <<
			(MySnake.start.x+dir[d][0]) << " " << (MySnake.start.y+dir[d][1]) << endl;
			fflush(stdout);
			
			MySnake.start.x += dir[d][0];
			MySnake.start.y += dir[d][1];
			grid[MySnake.start.x][MySnake.start.y] = 1;
//			cout << "eXit ovme\n";
			return true;
		}
		else if( (MySnake.end.x+dir[d][0])<=n && (MySnake.end.x+dir[d][0])>=1 &&
			(MySnake.end.y+dir[d][1])<=m && (MySnake.end.y+dir[d][1])>=1
			&& grid[MySnake.end.x+dir[d][0]][MySnake.end.y+dir[d][1]]==0  )
		{
			cout << "MOVE " << MySnake.end.x << " " << MySnake.end.y << " " <<
			(MySnake.end.x+dir[d][0]) << " " << (MySnake.end.y+dir[d][1]) << endl;
			fflush(stdout);
			
			MySnake.end.x += dir[d][0];
			MySnake.end.y += dir[d][1];
			grid[MySnake.end.x][MySnake.end.y] = 1;
//			cout << "eXit ovme\n";
			return true;
		}
//		cout << "exit d" << endl;
	}
//	cout << "eXit ovme\n";
	return false;
}

Snake createNewSnake(void)
{
	Snake tmp;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(grid[i][j]==0)
			{
				tmp.start.x = tmp.end.x = i;
				tmp.start.y = tmp.end.y = j;
				grid[i][j] = 1;
				iHaveASnake = true;
				cout << "NEW " << i << " " << j << endl;
				fflush(stdout);
				return tmp;
			}
		}
	}
	cout << "EXIT\n";
	fflush(stdout);
	exit(0);
}

void printgrid(void)
{
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	cin >> n >> m >> k;
	grid.resize(n+1);
	repi(n+1)
		grid[i].resize(m+1,0);
	
	repi(k)
	{
		int p,q;
		cin >> p >> q;
		grid[p][q] = -1;
	}
	
//	printgrid();
	
	bool mychance = true;
	string move;
	while(1){
	if(mychance)
	{
		if(iHaveASnake && moveMySnake(MySnake))
		{
			
		}
		else
		{
			MySnake = createNewSnake();
		}
		mychance = false;
//		printgrid();
	}
	else
	{
		cin >> move;
		if(move=="MOVE")
		{
			int p,q,r,s;
			cin >> p >> q >> r >> s;
			grid[r][s] = 2;
		}
		else if(move=="NEW")
		{
			int p,q;
			cin >> p >> q;
			grid[p][q] = 2;
		}
		else if(move=="FREEZE")
		{
			int p;
			cin >> p;
		}
		else if(move=="EXIT")
		{
			exit(0);
		}
		else
		{
			cout << "WRONG MOVE BY JUDGE\n";
			fflush(stdout);
		}
		mychance = true;
//		printgrid();
	}


	}
  	return 0;
}
