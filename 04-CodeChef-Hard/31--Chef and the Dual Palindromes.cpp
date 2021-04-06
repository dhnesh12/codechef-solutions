#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cassert>
 
#define FOR(k,a,b) for(int k(a); k < (b); ++k)
#define REP(k,a) for(int k=0; k < (a); ++k)
using namespace std;
typedef long long LL;
typedef vector<pair<int,LL> > VGT;
 
struct Palindrom
{
	int prefix;
	int mxprefix;
	int suffix;//the inverse representation of the prefix
	int prlen;
	int base;
	int mi;//the middle digit
	LL ba[66];
	bool hmi;
	int tmp1, tmp2;
	void initbase(int b)
	{
		base = b;
		ba[0]=1;
		FOR(i,1,66)
		{
			ba[i]=ba[i-1]*base;
			if(ba[i]<ba[i-1])
				ba[i]=1LL<<61;
		}
	}
	void init(int pl, bool st,bool midexist)
	{
		prlen = pl;
		hmi = midexist;
		mi=0;
		mxprefix = ba[pl];
		if(st)
		{
			prefix = 0;
			suffix = 0;
		}
		else
		{
			prefix = ba[pl-1];
			suffix = 1;
		}
	}
	bool step()
	{
		if( hmi )
		{
			if(++mi == base)
			{
				mi = 0;
				incprefix();
			}
		}
		else
		{
			incprefix();
		}
		return prefix == mxprefix;
	}
 
	void incprefix()
	{
		++prefix;
		tmp1=prefix;
		tmp2=prlen;
		while(tmp2>0)
		{
			if(tmp1%base)
			{
				suffix+=ba[tmp2-1];
				return;
			}
			suffix-=ba[tmp2-1]*(base-1);
			tmp2--;
			tmp1/=base;
		}
	}
	LL calculate()
	{
		return hmi?(prefix*base+mi)*ba[prlen]+suffix:prefix*ba[prlen]+suffix;
	}
	LL calculate(int midlen)
	{
		return prefix*ba[prlen+midlen]+suffix;
	}
};
 
struct PRTYPE
{
	LL mVal;
	int prefix;
	int suffix;
	int prlen;
	int midlen;
	bool type;
	PRTYPE(LL mv, int pr, int su, int pl, int ml, bool ty):
	mVal(mv), prefix(pr), suffix(su),prlen(pl), midlen(ml), type(ty) {}
 
	bool operator<(const PRTYPE& o) const
	{
		return mVal < o.mVal;
	}
};
 
int gcd(int a, int b)
{
	return b?gcd(b,a%b):a;
}
 
struct GTYPE{
	int ml1;
	int pl1;
	int ml2;
	int pl2;
	GTYPE(int m1, int p1, int m2, int p2): ml1(m1),pl1(p1),ml2(m2),pl2(p2){}
	bool operator<(const GTYPE& o) const
	{
		return ml1 < o.ml1 || (ml1 == o.ml1 && (ml2 < o.ml2 || (ml2 == o.ml2 && ( pl1 < o.pl1
			|| (pl1 == o.pl1 && pl2 < o.pl2)))));
	}
};
 
void generate(int base1, int base2, int pl1, int ml1, int pl2, int ml2, VGT& vm)
{
	Palindrom p1, p2;
	p1.initbase(base1);
	p2.initbase(base2);
	assert(vm.empty());
	vm.clear();
	p1.init(ml1/2,1,ml1&1);
	LL MOD = p2.ba[pl2];
	LL prod = p1.ba[pl1];
	LL tmp;
	do 
	{
		tmp = p1.calculate()*prod;
		vm.push_back(pair<int,LL>((tmp)%MOD, tmp));
	} while (!p1.step());
	sort(vm.begin(),vm.end());
}
 
inline bool isPal(LL val,int base)
{
	LL rev = 0;
	while(val>rev)
	{
		rev*=base;
		rev+=val%base;
		val/=base;
	}
	return val == rev || val==rev/base;
}
 
int main(int argv, char** argc)
{
	int T, base1, base2, len, len2, mil, mil2, pos1, pos2;
	LL a1, a2;
	vector<LL> res;
	map<GTYPE, VGT > mG;
	VGT tmpmG;
	vector<PRTYPE> w;
	int gcda[30][30];
	res.reserve(1e4);
	scanf("%d",&T);
	while(T--)
	{
		//clock_t start=clock();
		scanf("%d %d",&base1, &base2);
		res.clear();
		mG.clear();
		tmpmG.clear();
		Palindrom p1, p2;
		p1.initbase(base1);
		p2.initbase(base2);
		len=len2=1;
		p1.init(len/2,1,len&1);
		p2.init(len2/2,1,len2&1);
		a1 = p1.calculate(), a2 =  p2.calculate();
		memset(gcda,-1, sizeof gcda);
		while( 1 )
		{
			if(a1 == a2 )
			{
				res.push_back(a1);
				if(res.size()==1001)
					goto stop;
			}
			if(a1 <= a2)
			{
				if(p1.step())
				{
					++len;
					p1.init(len/2,0,len&1);
					if(p1.ba[len]>(1LL<<40))
					{
						break;
					}
				}
				a1 = p1.calculate();
			}
			else if(a2 <= a1)
			{
				if(p2.step())
				{
					++len2;
					p2.init(len2/2,0,len2&1);
				}
				a2 = p2.calculate();
			}
		}
		//2. phase
		w.clear();
		len = 1;
		while(p1.ba[len+1]<(1LL<<40))
		{
			++len;
		}
 
		mil = len - 2*((len+3)/4);
		p1.init((len+3)/4,0,0);
		do 
		{
			a1=p1.calculate(mil);
			w.push_back(PRTYPE(a1,p1.prefix, p1.suffix, (len+3)/4, mil, 0));
			if(p1.step())
			{
				++len;
				p1.init((len+3)/4,0,0);
				mil = len - 2*((len+3)/4);
			}
		} while (a1<(1LL<<60));
		
		len2 = 0;
		while(p2.ba[len2+1] < (1LL<<40))
		{
			++len2;
		}
		mil2 = len2 - 2*((len2+3)/4);
		p2.init((len2+3)/4,0,0);
		do 
		{
			a2=p2.calculate(mil2);
			w.push_back(PRTYPE(a2,p2.prefix, p2.suffix, (len2+3)/4, mil2, 1));
			if(p2.step())
			{
				++len2;
				p2.init((len2+3)/4,0,0);
				mil2 = len2 - 2*((len2+3)/4);
			}
		} while (a2<(1LL<<60));
		sort(w.begin(),w.end());
		pos1 = pos2 = -1;
		REP(i,w.size())
		{
			if(w[i].type)
			{
				pos2 = i;
			}
			else
			{
				pos1 = i;
			}
			if(pos1 != -1 && pos2!= -1 )
			{
				LL diff = w[pos2].mVal - w[pos1].mVal;
				if(gcda[w[pos1].prlen][w[pos2].prlen] == -1)
				{
					gcda[w[pos1].prlen][w[pos2].prlen]=gcd(p1.ba[w[pos1].prlen], p2.ba[w[pos2].prlen]);
				}
				const int& gg = gcda[w[pos1].prlen][w[pos2].prlen];
				if( diff%gg == 0)
				{
					GTYPE gt( w[pos1].prlen, w[pos1].midlen, w[pos2].prlen, w[pos2].midlen);
					if(!mG.count(gt))
					{
						tmpmG.clear();
						generate(base1,base2,w[pos1].prlen, w[pos1].midlen, w[pos2].prlen, w[pos2].midlen,tmpmG);
						mG[gt]=tmpmG;
					}
					const VGT& tmG = mG[gt];
					//search for candidates
					//calc diff%MOD
					LL mod = p2.ba[w[pos2].prlen], td;//(base2)^w[pos2].prlen;
					if(diff<0)
					{
						td = (-diff)%mod;
						if(td) td = mod- td; 
					}
					else
					{
						td = diff%mod;
					}
					VGT::const_iterator tmGit = lower_bound(tmG.begin(),tmG.end(),make_pair<int,LL>(td,0LL));
					for(;tmGit != tmG.end() && tmGit->first == td;++tmGit)
					{
						LL candidate = w[pos1].mVal + tmGit->second;
						if( (res.empty() || candidate > res.back() ) && isPal(candidate, base2) && candidate < 1LL<<60 )
						{
							res.push_back(candidate);
							if(res.size()==1001)
								goto stop;
						}
					}
				}
			}
		}
stop:
		FOR(i,1, res.size())
		{
			printf("%lld ",res[i]);
		}
		printf("\n");
	}
	return 0;
}  