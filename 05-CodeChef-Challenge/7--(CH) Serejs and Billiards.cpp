#include <bits/stdc++.h>
 
using namespace std;
 
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define UB upper_bound
#define LB lower_bound
#define ER erase
#define EN end()
#define B begin()
#define I insert
#define OPTIMIZE ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int ll
#define endl "\n"
#define CO cout << 
#define CI cin >> 
#define EMPTY -555555
#define NL cout << endl;
#define DBG cin >> debug;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef long double ld;
 
const ll maxn=1e2 +5;
const ll MOD = 1e9+7;
 
bool comparator(int i , int j)
{
    return (i < j);
}
 
ll power(ll x, ll i)
{
	ll ans = 1;
	while(i > 0)
	{
		if(i&1)
			ans = (ans*x)%MOD;
		i >>=1;
		x = (x*x)%MOD;
	}
	return ans;
}
 
ll power(ll x, ll i,ll mod)
{
	ll ans = 1;
	while(i > 0)
	{
		if(i&1)
			ans = (ans*x)%mod;
		i >>=1;
		x = (x*x)%mod;
	}
	return ans;
}
 
ll modInverse(ll x, ll mod)
{
	return power(x , mod-2,mod);
}
 
bool isPalindrome(string s)
{
	int limit = s.length()/2;
	for(int i =  0 ; i < limit ; i++)
	{
		if(s[i] != s[s.length()-i-1])
			return 0;
	}
	return true;
}
 
ll gcd(ll x, ll y)
{
	ll t;
	while(y != 0)
	{
		t = x%y;
		x = y;
		y = t;
	}
	return x;
}
///////////////////////////////////
// declaration section ////////////
///////////////////////////////////
int a[maxn][maxn],n,m,x,y,counter,backup[maxn][maxn],curScore,bestScore,newScore;
int secondaryBackup[maxn][maxn];
bool hasNegetive;
char debug;
vector< pair < pair<ii,ii> , int > > bestAns,t1,t2,newAns,lastAns;
int lastBallInRow[maxn];
void printGrid()
{
	for(int i = 0 ; i<=n ;i++)
	{
		for(int j = 0 ; j <= n ;j++)
			cout << a[i][j] << " " ;
		cout << endl;
	}
}
void printBackup()
{
	for(int i = 0 ; i<=n ;i++)
	{
		for(int j = 0 ; j <= n ;j++)
			cout << backup[i][j] << " " ;
		cout << endl;
	}
}
 
void getInput()
{
	hasNegetive = false;
	CI n >> m;
	for(int i = 0 ; i <= n; i++) for(int j = 0 ; j <= n ; j++) backup[i][j] = EMPTY;
	for(int i = 0 ; i < m ; i++)
	{
		CI x >> y , CI backup[x][y];
		if(backup[x][y] <= 0) hasNegetive = true;
	}
	//~ printGrid();
	//~ cout << " fater optimization " << endl;
	//~ printGrid();
}
 
void printAns()
{
	counter = 0;
	for(int i = 0 ; i < bestAns.size() ; i++)if(bestAns[i].S == 0)counter++;
	CO bestAns.size() - counter << "\n";
	for(int i = 0 ; i < bestAns.size() ; i++)if(bestAns[i].S)
		CO bestAns[i].F.F.F << " " << bestAns[i].F.F.S<< " " << bestAns[i].F.S.F << " " << bestAns[i].F.S.S << " " << bestAns[i].S << "\n";
}
 
 
void insertAllBalls()
{
	int lastBallRow=-1;
	for(int i = 0 ; i <= n ; i++)
	{
		bool hasBall = false;
		for(int j = n ; j > 0 ; j--)
		{
			if(a[i][j] != EMPTY)
			{
					bestAns.PB({ { {i,j},{0,-1}},j}),hasBall = true;
					break;
			}
		}
		if(a[i][0] != EMPTY)
			hasBall=true;
		if(hasBall)
			lastBallRow=i;
	}
	bestAns.PB({ { {lastBallRow,0},{-1,0}},lastBallRow});
	bestAns.PB({ { {0,0},{-1,-1}},1});
	newAns.clear();
	int lastBallColumn=-1;
	for(int j = 0 ; j <= n ; j++)
	{
		bool hasBall = false;
		for(int i = 0 ; i < n ; i++)
		{
			if(a[i][j] != EMPTY)
			{
				newAns.PB({ { {i,j},{1,0}},n-i});
				hasBall=true;
				break;
			}
		}
		if(a[n][j] != EMPTY)
		hasBall=true;
		if(hasBall)
		lastBallColumn=j;
	}
	newAns.PB({ { {n,lastBallColumn},{0,-1} },lastBallColumn});
	newAns.PB({ { {n,0},{1,-1}},1});
	if(newAns.size() < bestAns.size())bestAns=newAns;
}
void copyFull()
{
	for(int i = 0 ;i <= n ; i++)
			for(int j= 0 ;j <= n ; j++)
				a[i][j] = backup[i][j];
}
 
void copyLeft()
{
	for(int i = 0 ;i <= n ; i++)
	{
		if(i == n-1)
		{
			for(int j = 0; j <= n; j++)
				a[i][j] = backup[i][j];
		}
		else
		{
			int j = n;
			while(j > 0)
			{
				
				if(backup[i][j] > 0)
				{
					break;
				}
				a[i][j] = EMPTY;
				j--;
			}
			for( ; j >= 0 ; j--)
				a[i][j] = backup[i][j];
		}
	}
}
void OptimiseDiagonally()
{
	/// merge Diagonally
	int negBalls,counter,sum;
	int breakPoint = 1000;
	for(int j = 0 ; j <= n ; j++)
	{
		for(int i = 0 ; i <= n;)
		{
			if(a[i][j] != EMPTY)
			{
				if(a[i][j] < 0)
				{
					negBalls = counter = sum = 0;
					while(i + counter <= n && j + counter <= n)
					{
						if(a[i + counter][j+counter] > 0)
							break;
						if(a[i+counter][j+counter] != EMPTY && a[i+counter][j+counter] < 0)
							negBalls++;
						counter++;
					}
					
					if(negBalls >= 2)
					{
						newScore--;
						newAns.PB({ { {i,j} , {1,1}} , counter - 1 });
						sum=0;
						for(int k = i ; k < i+counter ; k++)
						{
							if(a[k+counter][j+counter] != EMPTY)
								sum = sum + a[k+counter][j+counter];
							a[k+counter][j+counter] = EMPTY;
						}
						a[i+counter-1][j+counter-1] = sum;
					}
					else
						i += counter;	
				}
				else
					i++;/// positive ball 
			}
			else
				i++;/// empty space 
		}
		if(breakPoint--)
			break;
	}
}
void secondaryOptimisationForLeft()
{
	
	/// merge balls vertically 
	int negBalls,counter,sum;
	for(int j = 0 ; j <= n ; j++)
	{
		for(int i = 0 ; i <= n;)
		{
			
			if(a[i][j] != EMPTY)
			{
				if(a[i][j] < 0)
				{
					negBalls = counter = sum = 0;
					while(i + counter <= n)
					{
						if(a[i + counter][j] > 0)
							break;
						if(a[i+counter][j] != EMPTY && a[i+counter][j] < 0)
							negBalls++;
						counter++;
					}
					
					if(negBalls >= 2)
					{
						newScore--;
						newAns.PB({ { {i,j} , {1,0}} , counter - 1 });
						sum=0;
						for(int k = i ; k < i+counter ; k++)
						{
							if(a[k][j] != EMPTY)
								sum = sum + a[k][j];
							a[k][j] = EMPTY;
						}
						a[i+counter-1][j] = sum;
						i = i+counter;
					}
					else
						i += counter;	
				}
				else
					i++;/// positive ball 
			}
			else
				i++;/// empty space 
		}
	}
}
void optimiseForLeft()
{
	for(int i = 0 ;i <= n ;i++) lastBallInRow[i] = -1;
	
	secondaryOptimisationForLeft();
	int negBalls,counter,sum;
	for(int i= 0 ; i <= n ; i++)
	{
		for(int j = 0 ; j <= n;)
		{
			
			if(a[i][j] != EMPTY)
			{
				if(a[i][j] < 0)
				{
					negBalls = counter = sum = 0;
					while(j + counter <= n)
					{
						if(a[i][j+counter] > 0)
							break;
						if(a[i][j+counter] != EMPTY && a[i][j+counter] < 0)
							negBalls++;
						counter++;
					}
					
					if(negBalls >= 2 && j + counter <= n)
					{
						newScore--;
						newAns.PB({ { {i,j} , {0,1}} , counter - 1 });
						sum=0;
						for(int k = j ; k < j+counter ; k++)
						{
							if(a[i][k] != EMPTY)
								sum = sum + a[i][k];
							a[i][k] = EMPTY;
						}
						a[i][j+counter-1] = sum;
						j = j+counter;
					}
					else
						j += counter;	
				}
				else
					j++;/// positive ball 
			}
			else
				j++;/// empty space 
		}
	}
	//~ cout << " after left up opti " << endl;
	//~ cout << " status of grid " ;
	//~ NL NL  NL
	//~ printGrid();
	
	//~ CO " new score " << newScore << endl;
	//~ DBG
}
 
void insertLeftUp()
{
	int lastBall,sum;
	int i;
	i = sum = 0;lastBall = -1;
	while(i <= n)
	{
		if(a[n][i] == EMPTY)
			i++;
		else if(a[n][i] > 0)
		{
			lastBall = i;
			sum = sum + a[n][i];
			i++;
		}
		else
			break;
	}
	if(lastBall >= 1)
	{
		newScore--,newAns.PB({ { {n , lastBall} , {0 , -1}} , lastBall});
		for(int j = lastBall ; j > 0 ; j--)
			a[n][j] = EMPTY;
		a[n][0] = sum;
	}
	for( ; i <= n ; i++)
	{
		if(a[n][i] > 1)
		{
			if(a[n-1][i] == EMPTY)
				a[n-1][i] = a[n][i],newScore-- , newAns.PB({ { {n,i} , {-1,0} } , 1}); 
			else if(a[n-1][i] >= 0)
				a[n-1][i] += a[n][i],newScore-- , newAns.PB({ { {n,i} , {-1,0} } , 1}); 
			else if(i-1 >= 0 && a[n-1][i-1] == EMPTY)
			{
				a[n-1][i-1] = a[n][i];
				newScore-- , newAns.PB({ { {n,i} , {-1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[n-1][i+1] == EMPTY)
			{
				a[n-1][i+1] = a[n][i];
				newScore-- , newAns.PB({ { {n,i} , {-1,1} } , 1}); 
			}
			else if(i-1 >= 0 && a[n-1][i-1] >=  0)
			{
				a[n-1][i-1] += a[n][i];
				newScore-- , newAns.PB({ { {n,i} , {-1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[n-1][i+1] >= 0)
			{
				a[n-1][i+1] += a[n][i];
				newScore-- , newAns.PB({ { {n,i} , {-1,1} } , 1}); 
			}
			a[n][i] = EMPTY;
		}
	}
	
	//~ cout << " after finishing last line , state of grid " << endl;
	//~ NL NL NL
	//~ printGrid() ;
	//~ NL NL NL
	//~ cout<< " new score " << newScore << endl;
	//~ DBG
	
	for(int i = n-1 ; i >= 0 ; i--)
	{
		lastBall = -1;
		sum = 0;
		for(int j = 0 ; j <= n ; j++)
		{
			if(a[i][j] == EMPTY)
				continue;
			else if(a[i][j] >= 0)
				lastBall = j,sum += a[i][j];
			else
			{
				newAns.PB({ { {i , j} , {1 , 1}} , 1});
				newScore--;
				a[i][j] = EMPTY;
			}
		}
		if(lastBall > 0)
		{
			newScore--;
			newAns.PB({ { { i , lastBall} , {0 , -1} }, lastBall});
			a[i][0] = sum;
		}
	}
	lastBall = -1;
	for(int i = n; i >= 0 ; i--)
	{
		if(a[i][0] > 0)
		{
			lastBall = i;
			break;
		}
	}
	if(lastBall > 0)
	{
		
		newScore--;
		newAns.PB({ { {lastBall , 0} , {-1 , 0} }, lastBall });
		newScore--;
		newAns.PB({ { {0,0} , {-1,-1} } , 1 });
		for(int i=0 ; i <= n ;i++)
		{
			if(a[i][0] > 0)
				newScore += a[i][0];
		}
		
	}
}
 
void insertLeftDown()
{
	int lastBall,sum;
	int i;
	i = sum = 0;lastBall = -1;
	while(i <= n)
	{
		if(a[0][i] == EMPTY)
			i++;
		else if(a[0][i] > 0)
		{
			lastBall = i;
			sum = sum + a[0][i];
			i++;
		}
		else
			break;
	}
	if(lastBall >= 1)
	{
		newScore--,newAns.PB({ { {0 , lastBall} , {0 , -1}} , lastBall});
		for(int j = lastBall ; j > 0 ; j--)
			a[0][j] = EMPTY;
		a[0][0] = sum;
	}
	for( ; i <= n ; i++)
	{
		if(a[0][i] > 1)
		{
			if(a[1][i] == EMPTY)
				a[1][i] = a[0][i],newScore-- , newAns.PB({ { {0,i} , {1,0} } , 1}); 
			else if(a[1][i] >= 0)
				a[1][i] += a[0][i],newScore-- , newAns.PB({ { {0,i} , {1,0} } , 1}); 
			else if(i-1 >= 0 && a[1][i-1] == EMPTY)
			{
				a[1][i-1] = a[0][i];
				newScore-- , newAns.PB({ { {0,i} , {1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[1][i+1] == EMPTY)
			{
				a[1][i+1] = a[0][i];
				newScore-- , newAns.PB({ { {0,i} , {1,1} } , 1}); 
			}
			else if(i-1 >= 0 && a[1][i-1] >=  0)
			{
				a[1][i-1] += a[0][i];
				newScore-- , newAns.PB({ { {0,i} , {1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[1][i+1] >= 0)
			{
				a[1][i+1] += a[0][i];
				newScore-- , newAns.PB({ { {0,i} , {1,1} } , 1}); 
			}
			a[0][i] = EMPTY;
		}
	}
	
	//~ cout << " after finishing last line , state of grid " << endl;
	//~ NL NL NL
	//~ printGrid() ;
	//~ NL NL NL
	//~ cout<< " new score " << newScore << endl;
	//~ DBG
	
	for(int i = 1 ; i <= n ; i++)
	{
		lastBall = -1;
		sum = 0;
		for(int j = 0 ; j <= n ; j++)
		{
			if(a[i][j] == EMPTY)
				continue;
			else if(a[i][j] >= 0)
				lastBall = j,sum += a[i][j];
			else
			{
				newAns.PB({ { {i , j} , {-1 , 1}} , 1});
				newScore--;
				a[i][j] = EMPTY;
			}
		}
		if(lastBall > 0)
		{
			newScore--;
			newAns.PB({ { { i , lastBall} , {0 , -1} }, lastBall});
			a[i][0] = sum;
		}
	}
	lastBall = -1;
	for(int i = 0; i >= 0 ; i--)
	{
		if(a[i][0] > 0)
		{
			lastBall = i;
			break;
		}
	}
	if(lastBall > 0)
	{
		
		newScore--;
		newAns.PB({ { {lastBall , 0} , {1 , 0} }, lastBall });
		newScore--;
		newAns.PB({ { {n,0} , {1,-1} } , 1 });
		for(int i=0 ; i <= n ;i++)
		{
			if(a[i][0] > 0)
				newScore += a[i][0];
		}
	}
}
void Left()
{
	newAns.clear(),newScore = 0;
	copyLeft();
	optimiseForLeft();
	
	/// now insert()
	int lastScore = newScore; 
	lastAns = newAns;
	
	for(int i = 0 ;i <= n ; i++)for(int j=0 ; j<= n ; j++)
		secondaryBackup[i][j] = a[i][j];
	
	insertLeftUp();
	
	if(newScore > bestScore)
		bestScore = newScore , bestAns = newAns;
	
	
	newScore = lastScore,newAns = lastAns;
	for(int i = 0 ;i <= n ; i++)for(int j=0 ; j<= n ; j++)
		a[i][j] = secondaryBackup[i][j];
		
	insertLeftDown();
	if(newScore > bestScore)
		bestScore = newScore , bestAns = newAns;
}
void copyDown()
{
	for(int j = 0 ; j <= n ; j++)
	{
		if(j != 1)
		{
			int i = 0;
			while(i <= n && a[i][j] <= 0)a[i][j] = EMPTY,i++;
			
			for( ; i <= n ; i++)
				a[i][j] = backup[i][j];
		}
		else
			for(int i = 0 ; i <= n; i++)
				a[i][j] = backup[i][j];
	}
}
void optimiseForDown()
{
	/// merge balls vertically 
	int negBalls,counter,sum,lastBall;
	for(int j = 0 ; j <= n ; j++)
	{
		for(int i = 0 ; i <= n;)
		{
			if(a[i][j] != EMPTY)
			{
				if(a[i][j] < 0)
				{
					negBalls = counter = sum = 0;
					while(i + counter <= n)
					{
						if(a[i + counter][j] > 0)
							break;
						if(a[i+counter][j] != EMPTY && a[i+counter][j] < 0)
							negBalls++;
						counter++;
					}
					
					if(negBalls >= 2)
					{
						
						sum=0;
						for(int k = i ; k < i+counter ; k++)
						{
							if(a[k][j] != EMPTY)
								sum = sum + a[k][j],lastBall=k;
							a[k][j] = EMPTY;
						}
						a[i][j] = sum;
						
						newScore--;
						newAns.PB({ { {lastBall,j} , {-1,0}} , lastBall-i });
					}
					else
						i += counter;	
				}
				else
					i++;/// positive ball 
			}
			else
				i++;/// empty space 
		}
	}
}
 
void insertDownRight()
{
	int lastBall,sum;
	int i;
	i = sum = 0;lastBall = -1;
	i = n;
	while(i >= 0)
	{
		if(a[i][0] == EMPTY)
			i--;
		else if(a[i][0] > 0)
		{
			lastBall = i;
			sum = sum + a[i][0];
			i--;
		}
		else
			break;
	}
	
	if(lastBall < n)
	{
		newScore--,newAns.PB({ { {lastBall , 0} , {1 , 0}} , n-lastBall});
		for(int i = lastBall ; i < n ; i++)
			a[i][0] = EMPTY;
		a[n][0] = sum;
	}
	
	for( ; i >= 0 ; i--)
	{
		if(a[i][0] > 1)
		{
			if(a[i][1] == EMPTY)
				a[i][1] = a[i][0],newScore-- , newAns.PB({ { {i,0} , {0,1} } , 1}); 
			else if(a[n-1][i] >= 0)
				a[i][1] += a[i][0],newScore-- , newAns.PB({ { {i,0} , {0,1} } , 1});  
			else if(i-1 >= 0 && a[i-1][1] == EMPTY)
			{
				a[i-1][1] = a[i][0];
				newScore-- , newAns.PB({ { {i,0} , {1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[i+1][1] == EMPTY)
			{
				a[i+1][1] = a[i][0];
				newScore-- , newAns.PB({ { {i,0} , {1,1} } , 1}); 
			}
			else if(i-1 >= 0 && a[i-1][1] >= 0)
			{
				a[i-1][1] += a[i][0];
				newScore-- , newAns.PB({ { {i,0} , {1,-1} } , 1}); 
			}
			else if(i+1 <= n && a[i+1][1] >= 0)
			{
				a[i+1][1] += a[i][0];
				newScore-- , newAns.PB({ { {i,0} , {1,1} } , 1}); 
			}
			a[i][0] = EMPTY;
		}
	}
	
	//~ cout << " after finishing last line , state of grid " << endl;
	//~ NL NL NL
	//~ printGrid() ;
	//~ NL NL NL
	//~ cout<< " new score " << newScore << endl;
	//~ DBG
	
	
	for(int j = 1 ; j <= n ; j++)
	{
		lastBall = -1;
		sum = 0;
		for(int i = n ; i >= 0 ; i--)
		{
			if(a[i][j] == EMPTY)
				continue;
			else if(a[i][j] >= 0)
				lastBall = i,sum += a[i][j];
			else
			{
				newAns.PB({ { {i , j} , {-1 ,-1}} , 1});
				newScore--;
				a[i][j] = EMPTY;
			}
		}
		if(lastBall < n)
		{
			newScore--;
			newAns.PB({ { { lastBall , j } , {1 , 0} }, n-lastBall});
			a[n][j] = sum;
		}
	}
	
	lastBall = -1;
	for(int i = 0; i <= n ; i++)
	{
		if(a[n][i] > 0)
		{
			lastBall = i;
			break;
		}
	}
	if(lastBall <= n)
	{
		
		newScore--;
		newAns.PB({ { {n , lastBall} , {0 , 1} }, n-lastBall });
		newScore--;
		newAns.PB({ { {n,n} , {1,1} } , 1 });
		for(int i=0 ; i <= n ;i++)
		{
			if(a[n][i] > 0)
				newScore += a[n][i];
		}
	}
}
void insertDownLeft()
{
	
	
	
}
void Down()
{
	newAns.clear(),newScore = 0;
	copyDown();
	optimiseForDown();
	
	/// now insert()
	int lastScore = newScore; 
	lastAns = newAns;
	for(int i = 0 ;i <= n ; i++)for(int j=0 ; j<= n ; j++)
		secondaryBackup[i][j] = a[i][j];
	
	insertDownRight();
	
	if(newScore > bestScore)
		bestScore = newScore , bestAns = newAns;
	
	
	//~ newScore = lastScore,newAns = lastAns;
	//~ for(int i = 0 ;i <= n ; i++)for(int j=0 ; j<= n ; j++)
		//~ a[i][j] = secondaryBackup[i][j];
		
	//~ insertDownLeft();
	//~ if(newScore > bestScore)
		//~ bestScore = newScore , bestAns = newAns;
	/// now insert
	//~ insertRightBottom();
}
void solve()
{
	bestScore = -1;
	bestAns.clear();
	if(hasNegetive == false)
	{
		copyFull();
		insertAllBalls();
	}
	else
	{
		/// firstRow is first row from bottom side that contains balls 
		/// lastBall is rightMost ball in row
		bestScore = -1;
		//~ cout << 0 << endl;
		//~ return;
		
		Left();
		
		//~ Right();
		Down();
	}
	printAns();
}
signed main()
{
	int t;
	cin >> t;
	while(t--)
		getInput(),solve();///CO "solved" , NL 
	return 0;
}