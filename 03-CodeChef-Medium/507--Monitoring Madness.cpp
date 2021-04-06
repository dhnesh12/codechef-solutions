#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<map>
using namespace std;
typedef pair<int, int> pii;
int BruteForce(bool **AdjMat, int N);
int Greedy(bool **AdjMat, int N);
int MinSet(bool **AdjMat, int N, int Lower, int Upper);
bool Complete(bool *Cover, int N);
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string A, B;
		map<string, int> idx;
		vector<pii> list;
		int N=0, Ans;
		int E;
		cin>>E;
		while(E--)
		{
			cin>>A>>B;
			if(idx.find(A)==idx.end())
			idx[A]=N++;
			if(idx.find(B)==idx.end())
			idx[B]=N++;
			list.push_back(pii(idx[A], idx[B]));
		}
		bool **AdjMat;
		AdjMat=new bool*[N];
		for(int i=0; i<N; i++)
		AdjMat[i]=new bool[N];
		for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
		{
			if(i==j)
			AdjMat[i][j]=true;
			else
			AdjMat[i][j]=false;
		}
		for(vector<pii>::iterator i=list.begin(); i!=list.end(); i++)
		{
			AdjMat[i->first][i->second]=true;
			AdjMat[i->second][i->first]=true;
		}
		if(N<25)
		Ans=BruteForce(AdjMat, N);
		else
		{
			Ans=Greedy(AdjMat, N);
			int Count, MaxCnt=0;
			for(int i=0; i<N; i++)
			{
				Count=0;
				for(int j=0; j<N; j++)
				if(AdjMat[i][j])
				Count++;
				if(MaxCnt<Count)
				MaxCnt=Count;
			}
			double HRatio=0;
			for(int i=1; i<=MaxCnt; i++)
			HRatio+=1.0/(double)i;
			if(Ans*log10(N)<8)
			Ans=MinSet(AdjMat, N, (int)Ans/HRatio, Ans);
		}
		cout<<100*Ans<<endl;
	}
	return 0;
}
int BruteForce(bool **AdjMat, int N)
{
	int BitMask[N];
	for(int i=0; i<N; i++)
	{
		BitMask[i]=0;
		for(int j=0; j<N; j++)
		if(AdjMat[i][j])
		BitMask[i]|=1<<j;
	}
 	int TotalSets=1<<N;
	int MinSz=N;
 	for(int Mask=1, Cover, SetSz; Mask<TotalSets; Mask++)
 	{
		Cover=0;
		SetSz=0;
		for(int i=0; i<N; i++)
		if((Mask>>i)&1)
		{
			Cover|=BitMask[i];
			SetSz++;
		}
		if(Cover==(TotalSets-1) && SetSz<MinSz)
		MinSz=SetSz;
	}
	return MinSz;
}
int Greedy(bool **AdjMat, int N)
{
	bool Cover[N];
	for(int i=0; i<N; i++)
	Cover[i]=false;
	int Count[N];
	for(int i=0; i<N; i++)
	{
		Count[i]=0;
		for(int j=0; j<N; j++)
		if(AdjMat[i][j] && !Cover[j])
		Count[i]++;
	}
 	int Sz=0, SetSz=0;
	while(Sz<N)
	{
		int MaxIdx=0;
		for(int i=1; i<N; i++)
		if(Count[MaxIdx]<Count[i])
		MaxIdx=i;
 	Sz+=Count[MaxIdx];
		SetSz++;
		for(int i=0; i<N; i++)
		if(AdjMat[MaxIdx][i])
		Cover[i]=true;
		for(int i=0; i<N; i++)
		if(Count[i]!=0)
		{
			Count[i]=0;
			for(int j=0; j<N; j++)
			if(AdjMat[i][j] && !Cover[j])
			Count[i]++;
		}
	}
	return SetSz;
}
int MinSet(bool **AdjMat, int N, int Lower, int Upper)
{
	bool SetMask[N+1], Cover[N];
	int Mid;
	while(1)
	{
		Mid=(Lower+Upper)/2;
		for(int i=0; i<Mid; i++)
		SetMask[i]=true;
		for(int i=Mid; i<=N; i++)
		SetMask[i]=false;
		while (!SetMask[N])
		{
			for(int i=0; i<N; i++)
			Cover[i]=false;
			for(int i=0; i<N; i++)
			if(SetMask[i])
			for(int j=0; j<N; j++)
			if(AdjMat[i][j])
			Cover[j]=true;
			if(Complete(Cover, N))
			break;
			int k=0, cnt=0;
			while(SetMask[k]==false)
			k++;
			while(SetMask[k]==true)
			{
			    SetMask[k]=false;
			    k++;
			    cnt++;
			}
			SetMask[k]=true;
			for(int i=0; i<cnt-1; i++)
			SetMask[i]=true;
		}
		if(Lower==Upper)
		break;
		if(Complete(Cover, N))
		Upper=Mid;
		else
		Lower=Mid+1;
	}
	return Lower;
}
bool Complete(bool *Cover, int N)
{
	for(int i=0; i<N; i++)
	if(!Cover[i])
	return false;
	return true;
}