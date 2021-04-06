#ifdef _MSC_VER
#define LOCAL
#endif
#ifdef LOCAL
//#define DEBUG
#ifdef DEBUG
#define DEBUG_SLOW
#endif
#define TEST_TIME
#endif

const double TIME_LIMIT_STEP1=0.5;
const double TIME_LIMIT_ALL=0.95;

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <stdarg.h>

using namespace std;

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define POW2(X) (((uint)1)<<(X))
typedef vector<int> VI;
typedef pair<int,int> ipair;

#ifdef DEBUG
#define ASSERT(_Expression) (void)((!!(_Expression)||(__assert((#_Expression),__LINE__),0)))
void __assert(const char *_Message,const unsigned _Line) {printf("ASSERTION FAILED\n");printf("Message = %ls\n",_Message);printf("Line = %u\n",_Line); exit(0);}
#endif

#ifdef _MSC_VER
#define TIMES_PER_SEC (2.2e9)
#else
#define TIMES_PER_SEC (3.05e9)
#endif

uint64 rdtsc()
{
#ifdef _MSC_VER
	__asm { rdtsc }
#else
	uint64 time;
	__asm__ volatile ("rdtsc" : "=A" (time));
	return time;
#endif
}

double gettime()
{
#ifdef LOCAL
#ifndef _MSC_VER
	return (double)clock()/CLOCKS_PER_SEC/1.5;
#endif
#endif
	return (double)rdtsc()/TIMES_PER_SEC;
}

#ifdef LOCAL
class Timer
{
public:
	static uint64 timeUsed[1024];
	int id;
	uint64 startTime;
	Timer(int id=0) { this->id=id; startTime=rdtsc(); }
	~Timer() { timeUsed[id]+=(rdtsc()-startTime); }
	static void show()
	{
		for (int i=0;i<1024;i++) if (timeUsed[i]>0)
		{
			char str[100]; sprintf(str,"%.6lf",timeUsed[i]/TIMES_PER_SEC);
			string s=str; if (LENGTH(s)<15) s=" "+s;
			printf("Timer   %4d %s\n",i,s.c_str());
		}
	}
};
uint64 Timer::timeUsed[1024]={0};

class Counter
{
public:
	static int cnt[1024];
	Counter(int id=0) {  cnt[id]++; }
	~Counter() { }
	static void show()
	{
		for (int i=0;i<1024;i++) if (cnt[i]>0) printf("Counter %4d %9d\n",i,cnt[i]);
	}
};
int Counter::cnt[1024]={0};
#endif

#define MT_N 624
#define MT_M 397
#define MT_MSB 0x80000000U
#define MT_LS31B 0x7FFFFFFFU
#define MT_A 2567483615U

class MersenneTwister // pseudo-random number generator
{
	uint twistory[MT_N]; // history (i.e., previous states) of the generator
	int pos;
public:
	MersenneTwister(uint seed=0)
	{
		twistory[0]=seed;
		for (int i=1;i<MT_N;i++) twistory[i]=1812433253U*(twistory[i-1]^(twistory[i-1]>>30))+i;
		pos=0;
	}
	void reset(uint seed=0)
	{
		twistory[0]=seed;
		for (int i=1;i<MT_N;i++) twistory[i]=1812433253U*(twistory[i-1]^(twistory[i-1]>>30))+i;
		pos=0;
	}
	void generate(void)
	{
		uint tmp; int i;
		for (i=0;i<MT_N-MT_M;i++)
		{
			tmp=(twistory[i]&MT_MSB)+(twistory[i+1]&MT_LS31B);
			twistory[i]=twistory[i+MT_M]^(tmp>>1)^(MT_A&-(tmp&1));
		}
		for (;i<MT_N-1;i++)
		{
			tmp=(twistory[i]&MT_MSB)+(twistory[i+1]&MT_LS31B);
			twistory[i]=twistory[i+MT_M-MT_N]^(tmp>>1)^(MT_A&-(tmp&1));
		}
		tmp=(twistory[i]&MT_MSB)+(twistory[0]&MT_LS31B);
		twistory[i]=twistory[MT_M-1]^(tmp>>1)^(MT_A&-(tmp&1));
	}
	uint rand_unsigned()
	{
		if (pos==0) generate();
		uint ans=twistory[pos++];
		pos&=-(pos!=624); // if (pos == 624) pos = 0;
		ans^=ans>>11;
		ans^=(ans<<7)&2636928640U;
		ans^=(ans<<15)&4022730752U;
		ans^=ans>>18;
		return ans;
	}
	double next_double()
	{
		return next_int(32768)/32768.0;
	}
	int rand_signed()
	{
		return rand_unsigned()>>1;
	}
	int next_int(int n)
	{
		if (n==1) return 0;
		return rand_unsigned()%n; // close enough
	}
	int next_int(int a,int b)
	{
		if (a==b) return a;
		return rand_unsigned()%(b-a+1)+a; // close enough
	}
};

const int MAXN=64;
const int MAX_NUM_PREVPATH=128;

#define ID(x,y) (((x)<<6)|(y))
#define ID3(x,y,z) (((x)<<12)|((y)<<6)|(z))

struct Params
{
	int weight_base;
	int weight_crosscount;
	int weight_crosscount_sq;
	int num_nn_path;
	int num_dp_path;
	int num_sa_path;
	int num_sa_path_current_round_only;
	int min_shuffle_count;
	int max_shuffle_count;
};

int n;
int x[MAXN],y[MAXN];
int g[MAXN*MAXN];
MersenneTwister rnd;

int degree[MAXN];
int h[MAXN*MAXN];
int w[MAXN*MAXN];
int ow[MAXN*MAXN],cutw[MAXN*MAXN];
int64 best_weight;
int best_length;
int best_pts[MAXN];
int crosscount[MAXN*MAXN];

int num_path;
int path_length[MAXN*MAXN];
int path_pts[MAXN*MAXN][MAXN];

int candidate_path_score[MAX_NUM_PREVPATH];
int candidate_path_length[MAX_NUM_PREVPATH];
int candidate_path_pts[MAX_NUM_PREVPATH][MAXN];

// result
int result_num_path;
int result_path_length[MAXN*MAXN];
int result_path_pts[MAXN*MAXN][MAXN];
int num_solutions;
int solutions_path_length[MAXN][MAXN*MAXN];
int solutions_path_pts[MAXN][MAXN*MAXN][MAXN];

// cross
#define CHECK_MASK(m1,m2,b) (((b)&32)?((m2)&POW2((b)-32)):((m1)&POW2(b)))
#define MASK_OR(m1,m2,d1,d2) { (m1)|=(d1); (m2)|=(d2); }
#define ADD_TO_MASK(m1,m2,d) { if ((d)&32) (m2)|=POW2((d)-32); else (m1)|=POW2(d); }
int outer_sign[MAXN*MAXN*MAXN];
bool cross[MAXN*MAXN][MAXN*MAXN];
uint cross_mask1[MAXN*MAXN][MAXN],cross_mask2[MAXN*MAXN][MAXN];
int cross_cnt[MAXN*MAXN],cross_lst[MAXN*MAXN][MAXN*MAXN];

// directions
const int MAX_DIRECTIONS=100;
int od[MAX_DIRECTIONS][MAXN];

Params get_default_params()
{
	Params p;
	p.weight_base=10000;
	p.weight_crosscount=2000;
	p.weight_crosscount_sq=10;
	p.num_nn_path=200;
	p.num_dp_path=35;
	p.num_sa_path=30;
	p.num_sa_path_current_round_only=25;
	p.min_shuffle_count=5;
	p.max_shuffle_count=8;
	return p;
}

inline int outer(int x1,int y1,int x2,int y2,int x3,int y3)
{
	return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

void precompute_directions()
{
	pair<double,int> q[MAXN];
	for (int d=0;d<MAX_DIRECTIONS;d++)
	{
		double ptr=(double)d/MAX_DIRECTIONS*acos(-1.0);
		double cos_ptr=cos(ptr);
		double sin_ptr=sin(ptr);
		for (int i=0;i<n;i++) q[i]=MP(cos_ptr*x[i]+sin_ptr*y[i],i);
		sort(q,q+n);
		for (int i=0;i<n;i++) od[d][i]=q[i].second;
	}
}

void precompute_cross()
{
	for (int a=0;a<n;a++) for (int b=0;b<n;b++) for (int c=0;c<n;c++)
	{
		int t=outer(x[a],y[a],x[b],y[b],x[c],y[c]);
		outer_sign[ID3(a,b,c)]=((t==0)?0:((t<0)?-1:1));
	}
	memset(cross,false,sizeof(cross));
	for (int a=0;a<n;a++) for (int b=a+1;b<n;b++) if (g[ID(a,b)])
		for (int c=a+1;c<n;c++) if (b!=c) for (int d=c+1;d<n;d++) if (b!=d && g[ID(c,d)])
			if ((outer_sign[ID3(a,b,c)]^outer_sign[ID3(a,b,d)])==-2 &&
				(outer_sign[ID3(c,d,a)]^outer_sign[ID3(c,d,b)])==-2)
			{
				cross[ID(a,b)][ID(c,d)]=true;
				cross[ID(a,b)][ID(d,c)]=true;
				cross[ID(b,a)][ID(c,d)]=true;
				cross[ID(b,a)][ID(d,c)]=true;
				cross[ID(c,d)][ID(a,b)]=true;
				cross[ID(d,c)][ID(a,b)]=true;
				cross[ID(c,d)][ID(b,a)]=true;
				cross[ID(d,c)][ID(b,a)]=true;
			}
	memset(cross_mask1,0,sizeof(cross_mask1));
	memset(cross_mask2,0,sizeof(cross_mask2));
	memset(cross_cnt,0,sizeof(cross_cnt));
	for (int a=0;a<n;a++) for (int b=0;b<n;b++) if (g[ID(a,b)])
		for (int id_ab=ID(a,b),c=0;c<n;c++) for (int d=0;d<n;d++) if (g[ID(c,d)] && cross[id_ab][ID(c,d)])
		{
			if (c<d) cross_lst[id_ab][cross_cnt[id_ab]++]=ID(c,d);
			ADD_TO_MASK(cross_mask1[id_ab][c],cross_mask2[id_ab][c],d);
		}
}

void init_result()
{
	result_num_path=0;
	for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (g[ID(i,j)])
	{
		result_path_length[result_num_path]=1;
		result_path_pts[result_num_path][0]=i;
		result_path_pts[result_num_path][1]=j;
		result_num_path++;
	}
}

void update_result(int num_path,int path_length[],int path_pts[][MAXN])
{
	if (num_path>result_num_path) return;
	if (num_path<result_num_path)
	{
		result_num_path=num_path;
		memcpy(result_path_length,path_length,num_path*sizeof(int));
		for (int i=0;i<num_path;i++) memcpy(result_path_pts[i],path_pts[i],(path_length[i]+1)*sizeof(int));
		num_solutions=0;
	}
	if (num_solutions<MAXN)
	{
		memcpy(solutions_path_length[num_solutions],path_length,num_path*sizeof(int));
		for (int i=0;i<num_path;i++) memcpy(solutions_path_pts[num_solutions][i],path_pts[i],(path_length[i]+1)*sizeof(int));
		num_solutions++;
	}
}

void verify_path(int length,int pts[],bool checkg=true)
{
#ifdef DEBUG
	ASSERT(length<=n);
	if (pts[0]==pts[length]) ASSERT(length>=3);
	for (int i=0;i<length;i++) for (int j=i+1;j<=length;j++)
		ASSERT(i==0 && j==length || pts[i]!=pts[j]);
	for (int i=0;i<length;i++) for (int j=i+1;j<length;j++)
		ASSERT(!cross[ID(pts[i],pts[i+1])][ID(pts[j],pts[j+1])]);
	if (checkg) for (int i=0;i<length;i++) ASSERT(g[ID(pts[i],pts[i+1])] && g[ID(pts[i+1],pts[i])]);
#endif
}

void sanity_check()
{
#ifdef DEBUG
	ASSERT(MAXN>=50+1);
	ASSERT(n>=20 && n<=50);
	for (int i=0;i<n;i++) ASSERT(x[i]>=0 && x[i]<=100 && y[i]>=0 && y[i]<=100);
	for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=j+1;k<n;k++) ASSERT(outer(x[i],y[i],x[j],y[j],x[k],y[k])!=0);
	for (int i=0;i<n;i++) ASSERT(g[ID(i,i)]==0);
	for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) ASSERT(g[ID(i,j)]==g[ID(j,i)]);
	for (int i=0;i<n;i++) { int c=0; for (int k=0;k<n;k++) c+=g[ID(i,k)]; ASSERT(c>0); }
#endif
}

void prepare_get_path(const Params& params)
{
#ifdef TEST_TIME
	Timer t10(10);
	Counter c10(10);
#endif
	memset(degree,0,n*sizeof(int));
	memset(h,255,sizeof(h));
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (g[ID(i,j)]) degree[i]++;
	for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (g[ID(i,j)])
		w[ID(i,j)]=w[ID(j,i)]=params.weight_base+
							  params.weight_crosscount*crosscount[ID(i,j)]+
							  params.weight_crosscount_sq*crosscount[ID(i,j)]*crosscount[ID(i,j)];
	for (int k=0;k<num_path;k++) for (int s=0;s<2;s++)
	{
		if (s==1 && (path_length[k]<=1 || path_pts[k][0]==path_pts[k][path_length[k]])) continue;
		int a=((s==0)?path_pts[k][0]:path_pts[k][path_length[k]]);
		int b=((s==0)?path_pts[k][1]:path_pts[k][path_length[k]-1]);
#ifdef DEBUG
		ASSERT(!g[ID(a,b)] && !g[ID(b,a)] && h[ID(a,b)]<0 && h[ID(b,a)]<0);
#endif
		h[ID(a,b)]=h[ID(b,a)]=k;
		g[ID(a,b)]=g[ID(b,a)]=1;
		w[ID(a,b)]=w[ID(b,a)]=0;
		degree[a]++;
		degree[b]++;
	}
	int q[MAXN];
	for (int i=0;i<n;i++)
	{
		int c=0,*pw=w+ID(i,0),*zw=ow+ID(i,0);
		for (int j=0;j<n;j++) if (g[ID(i,j)]) q[c++]=(pw[j]<<6)|j;
		sort(q,q+c);
		reverse(q,q+c);
		for (int j=0;j<c;j++) zw[j]=(q[j]&63);
		for (int j=0;j<c;j++) cutw[ID(i,j)]=(int)(j==c-1 || pw[zw[j]]!=pw[zw[j+1]]);
#ifdef DEBUG
		ASSERT(c==degree[i]);
#endif
	}
}

void extend_path(int &ref_length,int ref_pts[MAXN])
{
#ifdef TEST_TIME
	Timer t12(12);
	Counter c12(12);
#endif
	int length=ref_length,*pts=ref_pts;
	uint smask1=0,smask2=0;
	for (int i=0;i<=length;i++) ADD_TO_MASK(smask1,smask2,pts[i]);
	int lst[MAXN],tmp[MAXN];
	while (1)
	{
		int can_extend[2]={1,1};
		while (pts[0]!=pts[length] && (can_extend[0] || can_extend[1]))
		{
			bool success=false;
			for (int refside=rnd.next_int(2),side=0;side<2;side++)
			{
				int selected_side=(side^refside);
				if (!can_extend[selected_side]) continue;
				int p=(selected_side?pts[length]:pts[0]);
				uint mask1=smask1,mask2=smask2;
				if (n<=32)
					for (int k=0;k<length;k++) mask1|=cross_mask1[ID(pts[k],pts[k+1])][p];
				else
					for (int k=0;k<length;k++)
					{
						int id=ID(pts[k],pts[k+1]);
						MASK_OR(mask1,mask2,cross_mask1[id][p],cross_mask2[id][p]);
					}
				int cnt=0,*pw=ow+ID(p,0),*cw=cutw+ID(p,0);
				for (int i=0;i<degree[p];i++)
				{
					int k=pw[i];
					if (!CHECK_MASK(mask1,mask2,k))
					{
						lst[cnt++]=k;
						for (;!cw[i];) { int k=pw[++i]; if (!CHECK_MASK(mask1,mask2,k)) lst[cnt++]=k; }
						break;
					}
				}
				if (cnt==0) { can_extend[selected_side]=0; continue; }
				int next_p=lst[rnd.next_int(cnt)];
				if (selected_side==0)
				{
					for (int i=(++length);i>0;i--) pts[i]=pts[i-1];
					pts[0]=next_p;
				}
				else
					pts[++length]=next_p;
				ADD_TO_MASK(smask1,smask2,next_p);
				success=true;
				break;
			}
			if (!success) break;
		}
		if (length>=2 && g[ID(pts[0],pts[length])])
		{
			int visited[MAXN];
			memset(visited,0,n*sizeof(int));
			for (int i=0;i<=length;i++) visited[pts[i]]=1;
			bool is_intersect=false;
			for (int i=1;i<length-1;i++) if (cross[ID(pts[0],pts[length])][ID(pts[i],pts[i+1])]) { is_intersect=true; break; }
			if (!is_intersect)
			{
				pts[++length]=pts[0];
				int best_delta=0;
				int add_pos=-1,add_pt=-1;
				for (int p=0;p<n;p++) if (!visited[p])
				{
					uint mask1=0,mask2=0;
					for (int k=0;k<length;k++)
					{
						int id=ID(pts[k],pts[k+1]);
						MASK_OR(mask1,mask2,cross_mask1[id][p],cross_mask2[id][p]);
					}
					for (int k=1;k<length;k++)
					{
						int key=pts[k];
						if (g[ID(key,p)] && !CHECK_MASK(mask1,mask2,key))
						{
							int *wkey=w+ID(key,0);
							int d=wkey[p]-min(wkey[pts[k-1]],wkey[pts[k+1]]);
							if (d>best_delta) best_delta=d,add_pos=k,add_pt=p;
						}
					}
				}
				if (add_pt>=0)
				{
					ADD_TO_MASK(smask1,smask2,add_pt);
					memcpy(tmp,pts,length*sizeof(int));
					if (w[ID(pts[add_pos],pts[add_pos-1])]<=w[ID(pts[add_pos],pts[add_pos+1])])
					{
						pts[0]=add_pt;
						memcpy(pts+1,tmp+add_pos,(length-add_pos)*sizeof(int));
						memcpy(pts+1+(length-add_pos),tmp,add_pos*sizeof(int));
					}
					else
					{
						memcpy(pts,tmp+add_pos+1,(length-add_pos-1)*sizeof(int));
						memcpy(pts+(length-add_pos-1),tmp,(add_pos+1)*sizeof(int));
						pts[length]=add_pt;
					}
					continue;
				}
			}
		}
		break;
	}
	ref_length=length;
}
void sa_path(int &ref_length,int ref_pts[MAXN])
{
#ifdef TEST_TIME
	Timer t11(11);
	Counter c11(11);
#endif
	int length=ref_length,*pts=ref_pts;
	bool visited[MAXN];
	memset(visited,false,n*sizeof(bool));
	for (int i=0;i<=length;i++) visited[pts[i]]=true;
	int sizeq=0,q[MAXN],e[MAXN];
	for (int i=0;i<n;i++) q[sizeq++]=i;
	for (int prev_totalw=-1;;)
	{
		int totalw=0;
		for (int i=0;i<length;i++) totalw+=w[ID(pts[i],pts[i+1])];
		if (totalw<=prev_totalw) break;
		prev_totalw=totalw;
		for (int cl=0;cl<sizeq;cl++)
		{
#ifdef DEBUG_SLOW
			int expeceted_new_totalw=0;
			for (int i=0;i<length;i++) expeceted_new_totalw+=w[ID(pts[i],pts[i+1])];
#endif
			swap(q[cl],q[rnd.next_int(cl,sizeq-1)]);
			int key=q[cl];
			if (visited[key])
			{
				if (key==pts[0] || key==pts[length]) continue;
				int best_delta=0;
				int op_type=-1,op_val;
				uint mask1=0,mask2=0;
				int pos=-1;
				for (int k=0;k<length;k++) if (pts[k]==key) { pos=k; break; }
#ifdef DEBUG
				ASSERT(pos>=0);
#endif
				int prev=pts[pos-1],next=pts[pos+1];
				int p_prev_next=ID(prev,next);
				if (!g[p_prev_next]) continue;
				bool is_intersect=false;
				for (int k=0;k<length;k++) if (k!=pos-1 && k!=pos)
				{
					int id=ID(pts[k],pts[k+1]);
					MASK_OR(mask1,mask2,cross_mask1[id][key],cross_mask2[id][key]);
					if (cross[p_prev_next][id]) { is_intersect=true; break; }
				}
				if (is_intersect) continue;
				MASK_OR(mask1,mask2,cross_mask1[p_prev_next][key],cross_mask2[p_prev_next][key]);
				int *wkey=w+ID(key,0);
				int defaultw=w[p_prev_next]-wkey[prev]-wkey[next];
				// Remove point key.
				if (length>=4 && defaultw>best_delta) best_delta=defaultw,op_type=1;
				// Replace point key.
				int *gkey=g+ID(key,0);
				for (int k=0;k<length;k++) if (k!=pos-1 && k!=pos)
				{
					int a=pts[k];
					if (gkey[a] && !CHECK_MASK(mask1,mask2,a))
					{
						int b=pts[k+1];
						if (gkey[b] && !CHECK_MASK(mask1,mask2,b))
						{
							int d=wkey[a]+wkey[b]-w[ID(a,b)]+defaultw;
							if (d>best_delta) best_delta=d,op_type=0,op_val=k;
						}
						else
							k++;
					}
				}
				if (op_type<0) continue;
#ifdef DEBUG_SLOW
				expeceted_new_totalw+=best_delta;
#endif
				if (op_type==0)
				{
					if (op_val<pos) { for (int i=pos;i>op_val+1;i--) pts[i]=pts[i-1]; pts[op_val+1]=key; }
					else { for (int i=pos;i<op_val;i++) pts[i]=pts[i+1]; pts[op_val]=key; }
				}
				else
				{
					length--;
					for (int i=pos;i<=length;i++) pts[i]=pts[i+1];
					visited[key]=false;
				}
			}
			else
			{
				if (degree[key]==0 || w[ID(key,ow[ID(key,0)])]==0) continue;
				uint mask1=0,mask2=0;
				if (n<=32)
					for (int k=0;k<length;k++) mask1|=cross_mask1[ID(pts[k],pts[k+1])][key];
				else
					for (int k=0;k<length;k++)
					{
						int id=ID(pts[k],pts[k+1]);
						MASK_OR(mask1,mask2,cross_mask1[id][key],cross_mask2[id][key]);
					}
				int best_delta=0;
				int op_type=-1,op_val;
				int *gkey=g+ID(key,0),*wkey=w+ID(key,0);
				for (int k=0;k<=length;k++) 
				{
					int a=pts[k];
					e[k]=(int)(gkey[a] && !CHECK_MASK(mask1,mask2,a));
				}
				e[length+1]=0;
				for (int k=0;k<length;k++) if (e[k])
				{
					int a=pts[k],b=pts[k+1];
					if (e[k+1])
					{
						int d=wkey[a]+wkey[b]-w[ID(a,b)];
						if (d>best_delta) best_delta=d,op_type=0,op_val=k+1;
					}
					if (e[k+2])
					{
						int c=pts[k+2];
						int d=wkey[a]-w[ID(a,b)]+wkey[c]-w[ID(b,c)];
						if (d>best_delta) best_delta=d,op_type=1,op_val=k+1;
					}
				}
				if (op_type<0) continue;
#ifdef DEBUG_SLOW
				expeceted_new_totalw+=best_delta;
#endif
				if (op_type==0)
				{
					visited[key]=true;
					for (int i=(++length);i>op_val;i--) pts[i]=pts[i-1];
					pts[op_val]=key;
				}
				else
				{
					int old_pt=pts[op_val];
					visited[old_pt]=false;
					visited[key]=true;
					pts[op_val]=key;
				}
			}
#ifdef DEBUG_SLOW
			for (int i=0;i<=length;i++) ASSERT(visited[pts[i]]);
			int cnt_visited=0;
			for (int i=0;i<n;i++) if (visited[i]) cnt_visited++;
			ASSERT(cnt_visited==length+(int)(pts[0]!=pts[length]));
			for (int i=0;i<length;i++) for (int j=i+1;j<length;j++) ASSERT(!cross[ID(pts[i],pts[i+1])][ID(pts[j],pts[j+1])]);
			int new_totalw=0;
			for (int i=0;i<length;i++) new_totalw+=w[ID(pts[i],pts[i+1])];
			ASSERT(expeceted_new_totalw==new_totalw);
#endif
		}
	}
	if (length>=2 && g[ID(pts[0],pts[length])])
	{
		bool is_intersect=false;
		for (int i=1;i<length-1;i++) if (cross[ID(pts[0],pts[length])][ID(pts[i],pts[i+1])]) { is_intersect=true; break; }
		if (!is_intersect)
		{
			pts[++length]=pts[0];
			extend_path(length,pts);
		}
	}
	ref_length=length;
}

bool get_path_nn(Params params,int p1,int p2,int &length,int pts[])
{
	length=1;
	pts[0]=p1;
	pts[1]=p2;
	extend_path(length,pts);
#ifdef DEBUG_SLOW
	verify_path(length,pts);
#endif
	return true;
}

bool get_path_dp(Params params,int &length,int pts[])
{
#ifdef TEST_TIME
	Timer t14(14);
	Counter c14(14);
#endif
	int f[MAXN],p[MAXN],o[MAXN],pos[MAXN];
	int direction=rnd.next_int(MAX_DIRECTIONS)*2;
	memcpy(o,od[direction/2],n*sizeof(int));
	for (int i=0;i<n;i++) pos[o[i]]=i;
	if (direction&1) reverse(o,o+n);
	int key=-1;
	for (int k=0;k<n;k++)
	{
		f[k]=0;
		p[k]=-1;
		int c=o[k],*gc=ow+ID(c,0),*wc=w+ID(c,0);
		for (int j=degree[c]-1;j>=0;j--)
		{
			int i=gc[j],z=pos[i];
			if (z<k && f[z]+wc[i]>f[k]) f[k]=f[z]+wc[i],p[k]=z;
		}
		if (p[k]>=0 && (key<0 || f[k]>f[key])) key=k;
	}
	if (key<0) return false;
	length=0;
	for (;key>=0;key=p[key]) pts[length++]=o[key];
	length--;
#ifdef DEBUG
	ASSERT(length>0);
#endif
	extend_path(length,pts);
#ifdef DEBUG_SLOW
	verify_path(length,pts);
#endif
	return true;
}

bool twist_two_path(int a,int side,int b)
{
	if (path_pts[a][0]==path_pts[a][path_length[a]] || path_pts[b][0]==path_pts[b][path_length[b]]) return false;
	int p=path_pts[a][(side==0)?0:path_length[a]];
	int pos=-1;
	for (int k=0;k<=path_length[b];k++) if (path_pts[b][k]==p) { pos=k; break; }
	if (pos<0) return false;
#ifdef DEBUG_SLOW
	multiset<ipair> ss;
	for (int k=0;k<path_length[a];k++) ss.insert(MP(min(path_pts[a][k],path_pts[a][k+1]),max(path_pts[a][k],path_pts[a][k+1])));
	for (int k=0;k<path_length[b];k++) ss.insert(MP(min(path_pts[b][k],path_pts[b][k+1]),max(path_pts[b][k],path_pts[b][k+1])));
#endif
	int visited[MAXN];
	memset(visited,0,n*sizeof(int));
	for (int k=0;k<=path_length[a];k++) visited[path_pts[a][k]]=1;
	for (int delta=-1;delta<=1;delta+=2) for (int newpos=pos+delta;newpos>=0 && newpos<=path_length[b];newpos+=delta)
	{
		int current=path_pts[b][newpos];
		if (visited[current]) break;
		int prev=path_pts[b][newpos-delta];
		bool is_intersect=false;
		for (int k=0;k<path_length[a];k++) if (cross[ID(prev,current)][ID(path_pts[a][k],path_pts[a][k+1])]) { is_intersect=true; break; }
		if (is_intersect) break;
		if (pos==0 || pos==path_length[b] || newpos==0 || newpos==path_length[b])
		{
			if (side==0) reverse(path_pts[a],path_pts[a]+path_length[a]+1);
			for (int k=pos;k!=newpos;k+=delta) path_pts[a][++path_length[a]]=path_pts[b][k+delta];
			if (pos==0 || newpos==0) reverse(path_pts[b],path_pts[b]+path_length[b]+1);
			path_length[b]-=abs(pos-newpos);
#ifdef DEBUG_SLOW
			multiset<ipair> tt;
			for (int k=0;k<path_length[a];k++) tt.insert(MP(min(path_pts[a][k],path_pts[a][k+1]),max(path_pts[a][k],path_pts[a][k+1])));
			for (int k=0;k<path_length[b];k++) tt.insert(MP(min(path_pts[b][k],path_pts[b][k+1]),max(path_pts[b][k],path_pts[b][k+1])));
			ASSERT(ss==tt);
#endif
			if (path_length[b]==0)
			{
				num_path--;
				if (b>=num_path) break;
				path_length[b]=path_length[num_path];
				memcpy(path_pts[b],path_pts[num_path],(path_length[b]+1)*sizeof(int));
			}
			return true;
		}
	}
	return false;
}

bool merge_two_path(int a,int side,int b)
{
#ifdef DEBUG
	int total_path_length=0;
	for (int i=0;i<num_path;i++) total_path_length+=path_length[i];
#endif
	int la=path_length[a],lb=path_length[b],*pts_a=path_pts[a],*pts_b=path_pts[b];
	if (pts_a[0]==pts_a[la] || pts_b[0]==pts_b[lb]) return false;
	for (int i=0;i<=la;i++) for (int j=0;j<=lb;j++) if (pts_a[i]==pts_b[j]) return false;
	for (int i=0;i<la;i++) for (int j=0;j<lb;j++) if (cross[ID(pts_a[i],pts_a[i+1])][ID(pts_b[j],pts_b[j+1])]) return false;
	int l[MAXN],p[MAXN][MAXN],e[MAXN];
	memset(l,255,sizeof(l));
	int src=((side==0)?pts_a[0]:pts_a[la]);
	l[src]=la;
	memcpy(p[src],pts_a,(l[src]+1)*sizeof(int));
	if (side==0) reverse(p[src],p[src]+l[src]+1);
#ifdef DEBUG
	ASSERT(p[src][l[src]]==src);
#endif
	memset(e,0,sizeof(e));
	while (1)
	{
		int key=-1;
		for (int i=0;i<n;i++) if (l[i]>=0 && !e[i] && (key<0 || l[i]<l[key])) key=i;
		if (key<0) break;
		if (key==pts_b[0] || key==pts_b[lb])
		{
			if (key==pts_b[lb]) reverse(pts_b,pts_b+lb+1);
#ifdef DEBUG
			ASSERT(p[key][l[key]]==pts_b[0]);
#endif
			for (int i=1;i<=lb;i++) p[key][++l[key]]=pts_b[i];
			path_length[a]=l[key];
			memcpy(pts_a,p[key],(l[key]+1)*sizeof(int));
#ifdef DEBUG_SLOW
			verify_path(la,pts_a,false);
#endif
			path_length[b]=0;
			memset(p,0,sizeof(p));
			for (int i=0;i<path_length[a];i++) p[pts_a[i]][pts_a[i+1]]=p[pts_a[i+1]][pts_a[i]]=1;
			for (int i=0;i<num_path;i++) if (i!=a)
			{
				int s=0,t=path_length[i];
				for (;s<t && p[path_pts[i][s]][path_pts[i][s+1]];s++);
				for (;s<t && p[path_pts[i][t]][path_pts[i][t-1]];t--);
				if (s==t)
				{
					num_path--;
					if (i>=num_path) break;
					path_length[i]=path_length[num_path];
					memcpy(path_pts[i],path_pts[num_path],(path_length[i]+1)*sizeof(int));
					if (a!=num_path) i--;
				}
				else
				{
#ifdef DEBUG
					for (int k=s;k<t;k++) ASSERT(!p[path_pts[i][k]][path_pts[i][k+1]]);
#endif
					if (s>0 || t<path_length[i])
					{
						path_length[i]=t-s;
						for (int k=0;k<=path_length[i];k++) path_pts[i][k]=path_pts[i][k+s];
					}
				}
			}
#ifdef DEBUG
			int new_total_path_length=0;
			for (int i=0;i<num_path;i++) new_total_path_length+=path_length[i];
			ASSERT(new_total_path_length==total_path_length);
#endif
			return true;
		}
		e[key]=1;
		int visited[MAXN];
		memset(visited,0,sizeof(visited));
		for (int i=0;i<=l[key];i++) visited[p[key][i]]=1;
		for (int i=0;i<=lb;i++) visited[pts_b[i]]=1;
		for (int i=0;i<num_path;i++) if (i!=a && i!=b)
		{
			int pos=-1;
			for (int k=0;k<=path_length[i];k++) if (path_pts[i][k]==key) { pos=k; break; }
			if (pos<0) continue;
			for (int delta=-1;delta<=1;delta+=2) for (int newpos=pos+delta;newpos>=0 && newpos<=path_length[i];newpos+=delta)
			{
				int current=path_pts[i][newpos];
				if (visited[current] && !(current==pts_b[0] || current==pts_b[lb])) break;
				int prev=path_pts[i][newpos-delta];
				bool is_intersect=false;
				for (int k=0;k<l[key];k++) if (cross[ID(prev,current)][ID(p[key][k],p[key][k+1])]) { is_intersect=true; break; }
				if (is_intersect) break;
				for (int k=0;k<lb;k++) if (cross[ID(prev,current)][ID(pts_b[k],pts_b[k+1])]) { is_intersect=true; break; }
				if (is_intersect) break;
				if (pos==0 || pos==path_length[i] || newpos==0 || newpos==path_length[i])
				{
					int t=l[key]+abs(pos-newpos);
					if (l[current]<0 || t<l[current])
					{
						memcpy(p[current],p[key],(l[key]+1)*sizeof(int));
						l[current]=l[key];
						for (int k=pos;k!=newpos;k+=delta) p[current][++l[current]]=path_pts[i][k+delta];
#ifdef DEBUG
						ASSERT(l[current]==t && p[current][l[current]]==current);
#endif
					}
				}
				if (current==pts_b[0] || current==pts_b[lb]) break;
			}
		}
	}
	return false;
}

void greedy(Params params,int based_path_cnt,double time_limit_overall)
{
#ifdef TEST_TIME
	Timer t1(1);
#endif
	memset(candidate_path_length,255,sizeof(candidate_path_length));
	memcpy(crosscount,cross_cnt,sizeof(cross_cnt));
	num_path=0;
	int solution_id=0;
	if (based_path_cnt>0) solution_id=rnd.next_int(num_solutions);
	for (int k=0;k<based_path_cnt;k++)
	{
		int best_length=solutions_path_length[solution_id][k];
		int *best_pts=solutions_path_pts[solution_id][k];
		for (int i=0;i<best_length;i++)
		{
			int a=best_pts[i];
			int b=best_pts[i+1];
			g[ID(a,b)]=g[ID(b,a)]=0;
			int id=((a<b)?ID(a,b):ID(b,a));
			for (int *p=cross_lst[id],k=cross_cnt[id]-1;k>=0;k--)
			{
				int e=p[k];
				if (g[e]) crosscount[e]--;
			}
		}
		path_length[num_path]=best_length;
		memcpy(path_pts[num_path],best_pts,(best_length+1)*sizeof(int));
		num_path++;
	}
	while (1)
	{
		if (gettime()>time_limit_overall) return;
		prepare_get_path(params);
		best_weight=0;
		best_length=0;
		priority_queue<pair<int64,int> > prev_path_heap,current_path_heap;
		int length,pts[MAXN];
		for (int k=0;k<MAX_NUM_PREVPATH;k++) if (candidate_path_length[k]>=0)
		{
			length=candidate_path_length[k];
			memcpy(pts,candidate_path_pts[k],(length+1)*sizeof(int));
			bool ok=true;
			for (int i=0;i<length;i++) if (!g[ID(pts[i],pts[i+1])]) { ok=false; break; }
			if (!ok) { candidate_path_length[k]=-1; continue; }
			int64 weight=0;
			for (int i=0;i<length;i++) weight+=w[ID(pts[i],pts[i+1])];
			candidate_path_score[k]=weight;
			prev_path_heap.push(MP(weight,k));
		}
		int worst_prev_path_idx=0;
		for (int k=0;k<MAX_NUM_PREVPATH;k++)
			if (candidate_path_length[k]<0) { worst_prev_path_idx=k; break; }
			else if (candidate_path_score[k]<candidate_path_score[worst_prev_path_idx]) worst_prev_path_idx=k;
		ipair edges[MAXN*MAXN/2];
		int c_edges=0;
		for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (g[ID(i,j)])
			edges[c_edges++]=MP(w[ID(i,j)],(rnd.next_int(65536)<<12)|(i<<6)|j);
		sort(edges,edges+c_edges);
		reverse(edges,edges+c_edges);
		int c1=min(c_edges,params.num_nn_path),c2=params.num_dp_path;
		for (int k=0;k<c1+c2;k++)
		{
			bool success;
			if (k<c1)
				success=get_path_nn(params,(edges[k].second>>6)&63,edges[k].second&63,length,pts);
			else
				success=get_path_dp(params,length,pts);
			if (!success) continue;
			int64 weight=0;
			for (int i=0;i<length;i++) weight+=w[ID(pts[i],pts[i+1])];
			if (candidate_path_length[worst_prev_path_idx]<0 || weight>candidate_path_score[worst_prev_path_idx])
			{
				candidate_path_score[worst_prev_path_idx]=weight;
				candidate_path_length[worst_prev_path_idx]=length;
				memcpy(candidate_path_pts[worst_prev_path_idx],pts,(length+1)*sizeof(int));
				current_path_heap.push(MP(weight,worst_prev_path_idx));
				worst_prev_path_idx=0;
				for (int k=0;k<MAX_NUM_PREVPATH;k++)
					if (candidate_path_length[k]<0) { worst_prev_path_idx=k; break; }
					else if (candidate_path_score[k]<candidate_path_score[worst_prev_path_idx]) worst_prev_path_idx=k;
			}
		}
		for (int k=0;k<params.num_sa_path;k++)
		{
			int pos,expected_weight;
			if (prev_path_heap.empty() && current_path_heap.empty()) break;
			if (prev_path_heap.empty() || !current_path_heap.empty() &&
				(k<params.num_sa_path_current_round_only || current_path_heap.top()>prev_path_heap.top()))
			{
				expected_weight=current_path_heap.top().first;
				pos=current_path_heap.top().second;
				current_path_heap.pop();
			}
			else
			{
				expected_weight=prev_path_heap.top().first;
				pos=prev_path_heap.top().second;
				prev_path_heap.pop();
			}
			if (expected_weight!=candidate_path_score[pos]) continue;
			sa_path(candidate_path_length[pos],candidate_path_pts[pos]);
			length=candidate_path_length[pos];
			memcpy(pts,candidate_path_pts[pos],(length+1)*sizeof(int));
			int64 weight=0;
			for (int i=0;i<length;i++) weight+=w[ID(pts[i],pts[i+1])];
			if (weight>best_weight)
			{
				best_weight=weight;
				best_length=length;
				memcpy(best_pts,pts,(length+1)*sizeof(int));
			}
		}
		if (best_length==0) break;
#ifdef DEBUG_SLOW
		verify_path(best_length,best_pts);
#endif
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (h[ID(i,j)]>=0) g[ID(i,j)]=0;
		memset(h,0,sizeof(h));
		for (int i=0;i<best_length;i++)
		{
			int a=best_pts[i];
			int b=best_pts[i+1];
			if (g[ID(a,b)])
			{
				g[ID(a,b)]=g[ID(b,a)]=0;
				int id=((a<b)?ID(a,b):ID(b,a));
				for (int *p=cross_lst[id],k=cross_cnt[id]-1;k>=0;k--)
				{
					int e=p[k];
					if (g[e]) crosscount[e]--;
				}
			}
			else
				h[ID(a,b)]=h[ID(b,a)]=1;
		}
		for (int i=0;i<num_path;i++)
		{
			int s=0,t=path_length[i];
			for (;s<t && h[ID(path_pts[i][s],path_pts[i][s+1])];s++);
			for (;s<t && h[ID(path_pts[i][t],path_pts[i][t-1])];t--);
			if (s==t)
			{
				num_path--;
				if (i>=num_path) break;
				path_length[i]=path_length[num_path];
				memcpy(path_pts[i],path_pts[num_path],(path_length[i]+1)*sizeof(int));
				i--;
			}
			else
			{
#ifdef DEBUG
				for (int k=s;k<t;k++) ASSERT(!h[ID(path_pts[i][k],path_pts[i][k+1])]);
#endif
				if (s>0 || t<path_length[i])
				{
					path_length[i]=t-s;
					for (int k=0;k<=path_length[i];k++) path_pts[i][k]=path_pts[i][k+s];
				}
			}
		}
		path_length[num_path]=best_length;
		memcpy(path_pts[num_path],best_pts,(best_length+1)*sizeof(int));
		num_path++;
#ifdef DEBUG_SLOW
		for (int a=0;a<n;a++) for (int b=a+1;b<n;b++) if (g[ID(a,b)])
		{
			int cc=0;
			for (int c=0;c<n;c++) for (int d=c+1;d<n;d++) if (g[ID(c,d)] && cross[ID(a,b)][ID(c,d)]) cc++;
			ASSERT(cc==crosscount[ID(a,b)]);
		}
#endif
	}
	while (1)
	{
#ifdef TEST_TIME
		Timer t13(13);
		Counter c13(13);
#endif
		bool is_updated=false;
		for (int b=num_path-1;b>=0;b--)
			while (1)
			{
				bool local_updated=false;
				for (int a=0;a<num_path;a++) for (int side=0;side<2;side++)
					if (a<num_path && b<num_path && a<b && twist_two_path(a,side,b))
						local_updated=is_updated=true;
				if (!local_updated) break;
			}
		if (is_updated) continue;
		for (int a=0;a<num_path;a++) for (int sa=0;sa<2;sa++) for (int b=0;b<num_path;b++)
			if (a<num_path && b<num_path && a!=b && merge_two_path(a,sa,b))
				is_updated=true;
		if (!is_updated) break;
	}
	update_result(num_path,path_length,path_pts);
}

void process()
{
	double start_time=gettime();
	double time_limit_step1=start_time+TIME_LIMIT_STEP1;
	double time_limit_all=start_time+TIME_LIMIT_ALL;
	rnd.reset(1028);
	sanity_check();
	precompute_cross();
	precompute_directions();
	init_result();
	int saveg[MAXN][MAXN];
	memcpy(saveg,g,sizeof(g));
	Params params=get_default_params();
	for (;gettime()<time_limit_step1;)
	{
#ifdef LOCAL
		Counter c1(1);
#endif
		greedy(params,0,time_limit_all);
		memcpy(g,saveg,sizeof(g));
	}
	for (;gettime()<time_limit_all;)
	{
#ifdef LOCAL
		Counter c2(2);
#endif
		greedy(params,max(0,result_num_path-rnd.next_int(params.min_shuffle_count,params.max_shuffle_count)),time_limit_all);
		memcpy(g,saveg,sizeof(g));
	}
}

void readin()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",&x[i],&y[i]);
	char s[64];
	memset(g,0,sizeof(g));
	for (int i=0;i<n;i++)
	{
		scanf("%s",s);
		for (int j=0;j<n;j++) g[ID(i,j)]=(int)(s[j]=='Y');
	}
}

void generate(int seed)
{
	char filename[64];
	sprintf(filename,"data\\%d.dat",seed);
	FILE *fin=fopen(filename,"r");
	if (fin!=NULL)
	{
		fscanf(fin,"%d",&n);
		for (int i=0;i<n;i++) fscanf(fin,"%d%d",&x[i],&y[i]);
		for (int i=0;i<n;i++)
		{
			char s[64];
			fscanf(fin,"%s",s);
			for (int j=0;j<n;j++) g[ID(i,j)]=(int)(s[j]=='Y');
		}
		fclose(fin);
		return;
	}
	MersenneTwister rnd(seed);
	int s=0;
	for (int i=0;i<200;i++) s|=rnd.next_int(123456789);
	if (s==0) { printf("Bad RNG\n"); exit(0); }
	n=rnd.next_int(20,50);
	int cc=0;
	while (1)
	{
		cc++;
		for (int i=0;i<n;i++) x[i]=rnd.next_int(0,100);
		for (int i=0;i<n;i++) y[i]=rnd.next_int(0,100);
		bool ok=true;
		for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (x[i]==x[j] && y[i]==y[j]) ok=false;
		if (!ok) continue;
		for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=j+1;k<n;k++) if (outer(x[i],y[i],x[j],y[j],x[k],y[k])==0) ok=false;
		if (!ok) continue;
		break;
	}
	double p=rnd.next_double()*0.7+0.3;
	while (1)
	{
		memset(g,0,sizeof(g));
		for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (rnd.next_double()<=p) g[ID(i,j)]=g[ID(j,i)]=1;
		bool ok=true;
		for (int i=0;i<n;i++)
		{
			int c=0;
			for (int j=0;j<n;j++) c+=g[ID(i,j)];
			if (c==0) ok=false;
		}
		if (!ok) continue;
		break;
	}
	FILE *fout=fopen(filename,"w");
	fprintf(fout,"%d\n",n);
	for (int i=0;i<n;i++) fprintf(fout,"%d %d\n",x[i],y[i]);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++) fprintf(fout,"%c",(g[ID(i,j)]?'Y':'N'));
		fprintf(fout,"\n");
	}
	fclose(fout);
}

int main()
{
#ifdef LOCAL
	const int MAXSEED=5;
	int case_study=-1;
	int num_cases=0;
	double sum_scores=0;
	double total_runtime=0;
	for (int seed=0;seed<MAXSEED;seed++)
	{
		if (case_study>=0 && seed!=case_study) continue;
		generate(seed);
		int n0=n;
		int x0[MAXN],y0[MAXN];
		int g0[MAXN][MAXN];
		for (int i=0;i<n;i++) x0[i]=x[i],y0[i]=y[i];
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) g0[i][j]=g[ID(i,j)];
		double start_time=gettime();
#else
		readin();
#endif
		process();
#ifdef LOCAL
		double end_time=gettime();
		int m=0;
		for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) m+=g0[i][j];
		for (int i=0;i<result_num_path;i++)
			for (int j=0;j<result_path_length[i];j++)
				if (g0[result_path_pts[i][j]][result_path_pts[i][j+1]]==0)
				{
					printf("Invalid solution : no edge."); exit(0);
				}
				else
				{
					g0[result_path_pts[i][j]][result_path_pts[i][j+1]]--;
					g0[result_path_pts[i][j+1]][result_path_pts[i][j]]--;
				}
		for (int i=0;i<n0;i++) for (int j=0;j<n0;j++) if (g0[i][j]) { printf("Invalid solution : use all edges."); exit(0); }
		for (int i=0;i<result_num_path;i++)
			for (int j=0;j<result_path_length[i];j++)
				for (int k=j+1;k<result_path_length[i];k++)
				{
					int a=result_path_pts[i][j];
					int b=result_path_pts[i][j+1];
					int c=result_path_pts[i][k];
					int d=result_path_pts[i][k+1];
					if (outer(x0[a],y0[a],x0[b],y0[b],x0[c],y0[c])*outer(x0[a],y0[a],x0[b],y0[b],x0[d],y0[d])<0 &&
						outer(x0[c],y0[c],x0[d],y0[d],x0[a],y0[a])*outer(x0[c],y0[c],x0[d],y0[d],x0[b],y0[b])<0)
					{
						printf("Invalid solution : intersection."); exit(0);
					}
				}
		double score=(double)result_num_path*(double)n0/(double)m;
		num_cases++;
		sum_scores+=score;
		total_runtime+=end_time-start_time;
		printf("seed = %d   n = %d   m = %d   score = %.3lf    runtime = %.3lf\n",seed,n0,m,score,end_time-start_time);
	}
	printf("avg_score = %.3lf\n",sum_scores/num_cases);
	printf("avg_runtime = %.3lf\n",total_runtime/num_cases);
	Timer::show();
	Counter::show();
#else
		printf("%d\n",result_num_path);
		for (int i=0;i<result_num_path;i++)
		{
			printf("%d",result_path_length[i]);
			for (int j=0;j<=result_path_length[i];j++) printf(" %d",result_path_pts[i][j]);
			printf("\n");
		}
#endif
	return 0;
}