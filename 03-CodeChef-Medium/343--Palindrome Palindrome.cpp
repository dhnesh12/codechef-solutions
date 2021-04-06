#include <bits/stdc++.h>
using namespace std;


#define N 100050
int vs;

struct Node
{
	int start, ed; // store start and end indexes of current Node inclusively
	int length; // stores length of substring
	unordered_map<int,int>mp;// stores insertion Node for all characters a-z
	int suffixEdg; // stores the Maximum Palindromic Suffix Node for the current node
	long long times; // number of times this palindrome occurs
	int cnt; // total number of palindromes of this node
	vector<int>vc;
};

Node root1, root2; //two special dummy Nodes as explained above
Node tree[N]; //stores Node information for constant time access
int curNode; //Keeps track the current Node while insertion
int ptr; //node number track
vector<int>vx[N];

char s[N];

void add_node(int idx)
{
/* search for Node X such that s[idx] X S[idx]is maximum palindrome ending
at position
idx iterate down the suffix link of curNode to find X */
	int tmp = curNode;
	while (true)
	{
		int curLength = tree[tmp].length;
		if (idx - curLength >= 1 and s[idx] == s[idx-curLength-1])
			break;
		tmp = tree[tmp].suffixEdg;
	}
/* Now we have found X .... * X = string at Node tmp* Check : if s[idx] X s[idx] already exists or not*/
	if(tree[tmp].mp.find(s[idx]-'a') != tree[tmp].mp.end()) // s[idx] X s[idx] already exists in thetree
	{
	//tree[tmp].times++; // increase times
		curNode = tree[tmp].mp[s[idx]-'a'];
		tree[curNode].times++; // increase times
		return;
	}
	ptr++;// creating new Node
	tree[tmp].mp[s[idx]-'a'] = ptr;// making new Node as child of X withweight as s[idx]
	tree[ptr].length = tree[tmp].length + 2; // calculating length of new Node
	tree[ptr].ed = idx; // updating end point for new Node
	tree[ptr].start = idx - tree[ptr].length + 1;// updating the start for new Node
	tree[ptr].times=1; // new node
	tree[ptr].cnt=1;
/* Setting the suffix edge for the newly createdNode tree[ptr]. Finding some
String Y such that
s[idx] + Y + s[idx] is longest possible palindromic suffix for newly created
	Node.*/
	tmp = tree[tmp].suffixEdg;
	curNode = ptr;// making new Node as current Node
	if (tree[curNode].length == 1) // if new palindrome's length is 1 making itssuffix link to be null string
	{
		tree[2].vc.push_back(curNode);
		tree[curNode].suffixEdg = 2;
		return;
	}
	while (true)
	{
		int curLength = tree[tmp].length;
		if (idx-curLength >= 1 and s[idx] == s[idx-curLength-1])
			break;
		tmp = tree[tmp].suffixEdg;
	}
	// Now we have found string Y
	tree[curNode].suffixEdg = tree[tmp].mp[s[idx]-'a'];// linking current Nodes suffix link with s[idx]+Y+s[idx]
	tree[tree[curNode].suffixEdg].vc.push_back(curNode);
}
int vis[N];
int deg[N];

void init()
{
	for(int i=1; i<=ptr; i++)
	{
		tree[i].length=0;
		tree[i].times=0;
		tree[i].cnt=0;
		tree[i].mp.clear();
		tree[i].vc.clear();
	}
	tree[1].length = -1, tree[1].suffixEdg=1;
	tree[2].length = 0, tree[2].suffixEdg=1;
	tree[1].times=0,tree[2].times=0;
	tree[1].cnt=0,tree[2].cnt=0;
	tree[1].vc.clear(),tree[2].vc.clear();
	ptr = 2;
	curNode = 1;
	memset(vis,0,sizeof vis);
	memset(deg,0,sizeof deg);
	for(int i=0; i<N; i++) vx[i].clear();
}
long long ans=0;

void dfs(int u)
{
	int len=tree[u].length;
	if(len>0) vis[len]++;
	for(int i=0; i<vx[u].size(); i++)
	{
		int v=vx[u][i];
		dfs(v);
	}
	if(len>=4 && len%4==0)
	{
		if(vis[len/2]) ans+=tree[u].times;
	}
	if(len>0) vis[len]--;
}




int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();

		scanf("%s",s);
		int l = strlen(s);
		for (int i=0; i<l; i++)
		{
			add_node(i);
		}
		for(int i=ptr; i>=3; i--)
		{
			for(int j=0; j<tree[i].vc.size(); j++)
				tree[i].times+=tree[tree[i].vc[j]].times;
		}
		ans=0;
		for(int i=3; i<=ptr; i++)
		{

			vx[tree[i].suffixEdg].push_back(i);
			deg[i]++;
		}
		for(int i=1; i<=ptr; i++)
		{
			if(deg[i]==0) dfs(i);
		}
		printf("%lld\n",ans);
	}
	
}