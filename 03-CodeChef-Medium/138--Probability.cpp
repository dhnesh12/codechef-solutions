#include<iostream>
#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
int N, M, K, S, R[2]; //N-> No.of rows ,M-> No. of coln R-> visibilty K-> no. of minions S-> no. of states
int t;// Number of times <= 10^9, can be stored in int
typedef long long ll;
struct minion {
	pair<int, int> p1;//starting point of the minion -- first row no , second col no
	pair<int, int> p2;//destination point of the minion
};
minion arr[10];
ll land[100][100];
ll init[2][100][100] = { 0 };//initial matrices, sum of each row(r) corresponds to probabilty of being in rth state 
ll trans[2][24][100][100];//to compute 24 transition matrices--and--1 for prince, 1 for princess each
ll pro_t[2][100][100];// to store product of matrices up to t
ll probabilty[2][100];//probabilty stored in modulo manner
pair<int, int>pos[10][25];// to denote positions of minions at different times(t=1 to t=24)
pair<int, int>states[100];//to denote all the states - 100 is maximum possible states
bool mas_k[24][100][100]; // this mask matrix used to mask positions of minion in the next step
void compute_posn(void);//compute positions for each minion for 24 times
void compute_state(void);//Get all N*M states
void compute_trans(void); // to compute transitive functions
void compute_mask(void);// to compute mask matrices
ll power(ll x, ll y);
inline int man_dis(pair<int, int> &p1, pair<int, int> &p2) // to calculate manhattan distance between 2 points
{
	int d;
	d = 0;
	if (p1.first >= p2.first)
		d = d + p1.first - p2.first;
	else
		d = d + p2.first - p1.first;

	if (p1.second >= p2.second)
		d = d + p1.second - p2.second;
	else
		d = d + p2.second - p1.second;
	return d;
}
void MAT_MUL(ll(&m1)[100][100],ll(&m2)[100][100],ll(&m3)[100][100]); //m3=m1*m2 (note order)--(Matrix multiplications)
void compute_prob(void);

int main()
{
	ll ans = 0;
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> M >> R[0] >> R[1] >> K >> t;//R[0] for prince, R[1] for princess
	S = N*M;
	for (int i = 0; i < K; i++)
	{
		cin >> arr[i].p1.first >> arr[i].p1.second >> arr[i].p2.first >> arr[i].p2.second;
	}
	for (int t = 0; t < 24; t++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				mas_k[t][i][j] = true;
			}
		}
	}
	init[0][0][0] = 1;
	init[1][S - 1][S - 1] = 1;
	compute_posn();
	compute_mask();
	compute_state();
	compute_trans();
	compute_prob();
	for (int r = 0; r < 2; r++)
	{
		for (int s = 0; s < S; s++)
		{
			probabilty[r][s] = 0;
			for (int i = 0; i < S; i++)
			{
				probabilty[r][s] += pro_t[r][s][i];
			}
			probabilty[r][s] = (probabilty[r][s]) % MOD;
		}
	}
	for (int s = 0; s < S; s++)
	{
		ans = (ans + (probabilty[0][s] * probabilty[1][s])) % MOD;
	}
	ans = ans % MOD;
	cout << ans << endl;
    return 0;
}

void compute_posn(void)
{
	for (int k = 0; k < K; k++)
	{
		pair<int, int>p_1 = arr[k].p1;
		pair<int, int>p_2 = arr[k].p2;
		if (p_1.first == p_2.first)
		{
			bool dir;//direction true--forward, false--backward
			dir = true;
			int ind;
			ind = p_1.second;
			for (int t = 1; t <= 24; t++)
			{
				if (dir)
				{
					if (ind == p_2.second)
					{
						dir = false;
						ind--;
					}
					else
					{
						ind++;
					}
				}
				else
				{
					if (ind == p_1.second)
					{
						dir = true;
						ind++;
					}
					else
					{
						ind--;
					}
				}
				pos[k][t] = make_pair(p_1.first, ind);
			}
		}
		else if (p_1.second == p_2.second)
		{
			bool dir;//direction true--forward, false--backward
			dir = true;
			int ind;
			ind = p_1.first;
			for (int t = 1; t <= 24; t++)
			{
				if (dir)
				{
					if (ind == p_2.first)
					{
						dir = false;
						ind--;
					}
					else
					{
						ind++;
					}
				}
				else
				{
					if (ind == p_1.first)
					{
						dir = true;
						ind++;
					}
					else
					{
						ind--;
					}
				}
				pos[k][t] = make_pair(ind,p_1.second);
			}
		}
	}
	return;
}

void compute_mask(void)
{
	for (int t = 0; t < 24; t++)
	{
		for (int k = 0; k < K; k++)
		{
			mas_k[t][pos[k][t + 1].first][pos[k][t + 1].second] = false;
		}
	}
}

void compute_state(void)
{
	int z = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			states[z] = make_pair(i, j);
			z++;
		}
	}
}

void compute_trans(void)
{
	int buff[100];
	ll inv;
	for (int r = 0; r < 2; r++)
	{
		for (int t = 0; t < 24; t++)
		{
			for (int s1 = 0; s1 < S; s1++)
			{
				int num;//number of places to which character can move 
				num = 0;
				for (int s2 = 0; s2 < S; s2++)
				{
					if ((man_dis(states[s1], states[s2]) <= R[r]) && (mas_k[t][states[s2].first][states[s2].second]))
					{
						buff[num] = s2;
						num++;
					}

				}
				inv = power(num, MOD-2);
				for (int j = 0; j < num; j++)
				{
					trans[r][t][buff[j]][s1] = inv;
				}
			}
		}
	}
	for (int r = 0; r < 2; r++)
	{
		for (int t = 1; t < 24; t++)
		{
			MAT_MUL(trans[r][t], trans[r][t-1], trans[r][t]);
		}
	}
}

ll power(ll x, ll y)
{
	long long ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return ans;
}

void MAT_MUL(ll(&m1)[100][100], ll(&m2)[100][100], ll(&m3)[100][100])
{
	//Actually only SxS elements are valid in this matrix
	ll m[100][100];
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			m[i][j] = 0;
			for (int k = 0; k < S; k++)
			{
				m[i][j] = (m[i][j] + (m1[i][k] * m2[k][j])) % MOD;
			}
		}
	}
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			m3[i][j] = m[i][j];
		}
	}
	return;
}

void compute_prob(void)
{
	ll rep_sq[2][100][100];// stores the result of repeated squaring upto..
	ll(&cum_pro_0)[100][100] = trans[0][23];
	ll(&cum_pro_1)[100][100] = trans[1][23];
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			rep_sq[0][i][j] = cum_pro_0[i][j];
			rep_sq[1][i][j] = cum_pro_1[i][j];
		}
	}
	for (int r = 0; r < 2; r++)
	{
		for (int i = 0; i < S; i++)
		{
			pro_t[r][i][i] = 1;
		}
	}
	int q;
	int rem;
	q = t / 24;
	rem = t - (q * 24);
	int z = 1;
	while (z <= q)
	{
		if (z&q)
		{
			MAT_MUL(pro_t[0], rep_sq[0], pro_t[0]);
			MAT_MUL(pro_t[1], rep_sq[1], pro_t[1]);
		}
		MAT_MUL(rep_sq[0], rep_sq[0], rep_sq[0]);
		MAT_MUL(rep_sq[1], rep_sq[1], rep_sq[1]);
		z = z << 1;
	}
	if (rem >= 1)
	{
		MAT_MUL(trans[0][rem - 1], pro_t[0], pro_t[0]);
		MAT_MUL(trans[1][rem - 1], pro_t[1], pro_t[1]);
	}
	MAT_MUL(pro_t[0], init[0], pro_t[0]);
	MAT_MUL(pro_t[1], init[1], pro_t[1]);
}