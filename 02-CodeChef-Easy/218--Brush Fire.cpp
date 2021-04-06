#include<algorithm>
#include<cstdio>
using namespace std;
struct BushNode
{
    void clear()
	{
		n[0]=nullptr;
		n[1]=nullptr;
		n[2]=nullptr;
		t=false;
	}
	BushNode* n[3];
	bool t;
};
bool isT(BushNode* baseNode,BushNode* parent)
{
	if(!baseNode)
	return false;
	if(baseNode->t)
	return true;
	if(parent == baseNode->n[1])
	swap(baseNode->n[0],baseNode->n[1]);
	else if(parent == baseNode->n[2])
	swap(baseNode->n[0],baseNode->n[2]);
	return isT(baseNode->n[1],baseNode) && isT(baseNode->n[2],baseNode);
}
int main()
{
	int T,n,s,t,children,neighbour,toSave;
	BushNode bushes[10000];
	scanf("%d",&T);
	for (int r=0;r<T;++r)
	{
		scanf("%d %d %d",&n,&s,&t);
		for(int bush=1;bush <=n;++bush)
		{
			bushes[bush].t=false;
			scanf("%d",&children);
			for(int child=0;child<3;++child)
			{
				if(child<children)
				{
					scanf("%d",&neighbour);
					bushes[bush].n[child]=&bushes[neighbour];
				}
				else
				{
					bushes[bush].n[child]=nullptr;
				}
			}
		}
		for(int save=0;save<t;++save)
		{
			scanf("%d",&toSave);
			bushes[toSave].t=true;
		}
		printf(!isT(&bushes[s],nullptr) ? "yes\n" : "no\n" );
	}
	return 0;
}