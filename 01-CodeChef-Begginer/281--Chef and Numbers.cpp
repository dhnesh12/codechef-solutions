#include <bits/stdc++.h>
using namespace std;
bool checkByNinga(vector<int> me,vector<int> nin)
{	
	if(me[0]==nin[0]||me[1]==nin[1]||(me[0]-me[1]==nin[0]-nin[1])||(me[0]+me[1]==nin[0]+nin[1]))
	 return true;
	// find all valid knight positions of ninja 
	int xMove[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int yMove[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };
	for(int i=0;i<8;i++)
	{
		if(me[0]==nin[0]+xMove[i]&&me[1]==nin[1]+yMove[i])
		return true;
	}
	return false;
}
bool checkByKing(vector<int> me,vector<int> king)
{
	// find all 8 (valid only) positions of king 
	int xMove[8] = { 1, 1, -1, -1, 0, 0, 1, -1 };
    int yMove[8] = { 1, -1, 1, -1, 1, -1, 0, 0 };
	for(int i=0;i<8;i++)
	{
		if(me[0]==king[0]+xMove[i]&&me[1]==king[1]+yMove[i])
		return true;
	}
	return false;
}
bool checkStale(vector<int> me,vector<int> nin,vector<int> king)
{
	// find all 8 positions of Me in vector allMe	
	int xMove[8] = { 1, 1, -1, -1, 0, 0, 1, -1 };
    int yMove[8] = { 1, -1, 1, -1, 1, -1, 0, 0 };
	for(int i=0;i<8;i++)
	{	// check validity
		vector<int> newMe{me[0]+xMove[i],me[1]+yMove[i]};
		if(!(newMe[0]>=0&&newMe[0]<8&&newMe[1]>=0&&newMe[1]<8))
		continue;
		if((!checkByNinga(newMe,nin))&&(!checkByKing(newMe,king)))
		return false;
	}
	return true;
}
	
int main(){ 
	int t,n,k,x,ev,sm,a,mx,mxPos,ct,prv;
	cin>>t;
	while(t--)
	{	cin>>n;
		mx=0;
		mxPos=-1;
		vector<int> mp(1001,0);
		prv=-1;
		ct=0;
		while(n--)
		{
			cin>>a;
			if(a==prv)
			ct++;
			else 
			{
				if(prv!=-1)
				{
					mp[prv]+=ceil((double)ct/2.0);
					if(mp[prv]>mx){mx=mp[prv];mxPos=prv;}
					else if(mp[prv]==mx)mxPos=min(mxPos,prv);
				}
				ct=1;
			}
			prv=a;
		}
		mp[prv]+=ceil((double)ct/2.0);
		if(mp[prv]>mx){mx=mp[prv];mxPos=prv;}
		else if(mp[prv]==mx)mxPos=min(mxPos,prv);
		cout<<mxPos<<endl;
	}
		return 0;  	
}
