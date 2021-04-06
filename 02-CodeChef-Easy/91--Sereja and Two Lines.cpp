#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <numeric>
#include <cassert>
#include <cmath>
using namespace std;
typedef unsigned int uint;
typedef long long LL;

#define FOR(k,a,b) for(uint k(a); k < (b); ++k)
#define REP(k,a) for(uint k=0; k < (a); ++k)

const int MOD = 1e9 + 7;

#ifdef HOME
#define fread_unlocked fread
#endif

char *ipos, InpFile[7000000];
inline void InitIO()
{
	ipos = InpFile;
	fread_unlocked(InpFile,7000000,1,stdin);
}

inline int getInt()
{
	while(*ipos <= 32) ++ipos;
	int res=0;
	while(*ipos>32)
	{
		res*=10;
		res+=*ipos-'0';
		++ipos;
	}
	return res;
}

inline void checkLast(vector<pair<int,int> >& v)
{
	if(v.size()>1)
	{
		pair<int,int> mmx1 = v[v.size()-2];
		pair<int,int> mmx2 = v[v.size()-1];
		if(mmx1.second < mmx2.second)
		{
			v.clear();
			v.push_back(mmx2);
		}
		else if(mmx1.second > mmx2.second)
		{
			v.pop_back();
		}
	}
}

int main (int argc, char** argv) {
#ifdef HOME
	freopen("in.txt","rb",stdin);
	freopen("out.txt","wb",stdout);
#endif
	InitIO();
	int T,N,M;
	T = getInt();
	vector<pair<int, int> > TId(1e6+2, make_pair(-1,-1));
	while(T--)
	{
		N=getInt();
		M=getInt();
		vector<vector<int> > data(N, vector<int> (M));
		int actid = 0;
		REP(i,N)REP(j,M)
		{
			data[i][j] = getInt();
			if(TId[data[i][j]].first != T)
			{
				TId[data[i][j]] = make_pair(T, actid++);
			}
			data[i][j]=TId[data[i][j]].second;
		}
		vector<vector<pair<int,int> > > vrow(actid), vcol(actid);
		REP(i,N)
		{
			REP(j,M)
			{
				int& act = data[i][j];
				if(vrow[act].empty())
				{
					vrow[act].push_back(make_pair(i,1));
				}
				else if(vrow[act].back().first == i)
				{
					++vrow[act].back().second;
				}
				else
				{
					//check last
					checkLast(vrow[act]);
					vrow[act].push_back(make_pair(i,1));
				}
			}
		}
		REP(i,M)
		{
			REP(j,N)
			{
				int& act = data[j][i];
				if(vcol[act].empty())
				{
					vcol[act].push_back(make_pair(i,1));
				}
				else if(vcol[act].back().first == i)
				{
					++vcol[act].back().second;
				}
				else
				{
					//check last
					checkLast(vcol[act]);
					vcol[act].push_back(make_pair(i,1));
				}
			}
		}
		int ans = 0;
		vector<int> gans;
		REP(i,vrow.size())
		{
			checkLast(vrow[i]);
			checkLast(vcol[i]);
			int tmp = vrow[i].back().second + vcol[i].back().second;
			if(tmp > ans)
			{
				ans = tmp;
				gans.clear();
				gans.push_back(i);
			}
			else if (tmp == ans)
			{
				gans.push_back(i);
			}
		}
		bool found = 0;
		REP(i, gans.size())
		{
			int act = gans[i];
			REP(j, vrow[act].size()) REP(k,vcol[act].size())
			{
				if(data[vrow[act][j].first][vcol[act][k].first] != act )
					found = 1;
			}
			if(found)
				break;
		}
		if(!found)
			ans--;
		printf("%d\n",ans);
	}
	return 0;
}