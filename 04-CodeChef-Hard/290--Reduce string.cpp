#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#include<stack>
#include<vector>
#include<cmath>
//This code is written by Itst
using namespace std;

inline int read(){
	int a = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c != EOF){
		if(c == '-')
			f = 1;
		c = getchar();
	}
	if(c == EOF)
		exit(0);
	while(isdigit(c)){
		a = a * 10 + c - 48;
		c = getchar();
	}
	return f ? -a : a;
}

struct node{
	int ch[26];
}Trie[610];
int dp[251] , cntN = 1 , N , S;
bool can[251][251];
bitset < 610 > f[251][251];
char s[251] , mod[31];
vector < int > End;

void insert(){
	int L = strlen(mod + 1) , cur = 1;
	for(int i = 1 ; i <= L ; ++i){
		if(!Trie[cur].ch[mod[i] - 'a'])
			Trie[cur].ch[mod[i] - 'a'] = ++cntN;
		cur = Trie[cur].ch[mod[i] - 'a'];
	}
	End.push_back(cur);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif
	scanf("%s" , s + 1);
	N = strlen(s + 1);
	for(int i = 1 ; i <= N ; ++i)
		f[i][i - 1][1] = 1;
	S = read();
	for(int i = 1 ; i <= S ; ++i){
		scanf("%s" , mod + 1);
		insert();
	}
	for(int i = 1 ; i <= N ; ++i)
		for(int j = i ; j ; --j){
			for(int k = 1 ; k <= cntN ; ++k)
				if(f[j][i - 1][k] && Trie[k].ch[s[i] - 'a'])
					f[j][i][Trie[k].ch[s[i] - 'a']] = 1;
			for(int k = j + 1 ; k <= i ; ++k)
				if(can[k][i])
					f[j][i] |= f[j][k - 1];
			for(int k = 0 ; k < S ; ++k)
				if(f[j][i][End[k]])
					f[j][i][1] = 1;
			can[j][i] = f[j][i][1];
		}
	for(int i = 1 ; i <= N ; ++i){
		dp[i] = dp[i - 1] + 1;
		for(int j = i ; j >= 0 ; --j)
			if(can[j][i])
				dp[i] = min(dp[i] , dp[j - 1]);
	}
	cout << dp[N];
	return 0;
}
