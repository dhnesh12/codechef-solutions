#include<bits/stdc++.h>
#define For(i,j,k) for (int i=j;i<=k;i++)
using namespace std;
char s[555][555];
int cut,color;
int fl,n,m;
void out(){
	printf("%d %d\n",cut,color);
	if (fl){
		For(i,1,m){
			For(j,1,n) putchar(s[j][i]);
			puts("");
		}
	}
	else{
		For(i,1,n){
			For(j,1,m) putchar(s[i][j]);
			puts("");
		}
	}
}
char get(char x,char y){
	if (x!='a'&&y!='a') return 'a';
	if (x!='b'&&y!='b') return 'b';
	return 'c';
}
void solve1(){
	cut=m/2-1; color=1+(m>2); s[1][1]='a';
	For(i,2,m)
		if (i&1) s[1][i]='a'+'b'-s[1][i-1];
		else s[1][i]=s[1][i-1];
	out();
}
void solve2(){
	cut=m/2; color=2+(m&1);
	For(i,1,m/2){
		s[1][i*2-1]=s[1][i*2]='a'+(i&1);
		s[2][i*2-1]=s[2][i*2]='a'+((i&1)^1);
	}
	if (m&1)
		s[1][m]=s[2][m]='c';
	out();
}
void solve34(){
	cut=1; color=3;
	s[1][1]='a'; s[1][2]='a'; s[1][3]='b'; s[1][4]='c';
	s[2][1]='b'; s[2][2]='c'; s[2][3]='b'; s[2][4]='c';
	s[3][1]='b'; s[3][2]='c'; s[3][3]='a'; s[3][4]='a';
	out();
}
void solve3(){
	cut=1; color=3;
	s[1][1]='a'; s[1][2]='a';
	s[2][1]='b'; s[3][1]='b';
	For(i,2,m-1){
		if (!s[1][i]) s[1][i]=s[1][i+1]=get(s[1][i-1],s[2][i]);
		if (!s[2][i]) s[2][i]=s[2][i+1]=get(s[2][i-1],s[1][i]);
		if (!s[3][i]) s[3][i]=s[3][i+1]=get(s[3][i-1],s[2][i]);
	}
	s[2][m]=s[3][m]=get(s[2][m-1],s[3][m-1]);
	if (s[2][m]==s[1][m]){
		s[3][m-1]=s[3][m-2]=s[2][m];
		s[2][m]=s[3][m]=get(s[2][m-1],s[3][m-1]);
	}
	out();
}
/*    
aabbccaabbcc
bccaabbccaab
baaccaabbccb
*/
void solve44(){
	cut=2; color=3;
	s[1][1]='a'; s[1][2]='a'; s[1][3]='c'; s[1][4]='a';
	s[2][1]='b'; s[2][2]='b'; s[2][3]='c'; s[2][4]='a';
	s[3][1]='a'; s[3][2]='c'; s[3][3]='b'; s[3][4]='b';
	s[4][1]='a'; s[4][2]='c'; s[4][3]='a'; s[4][4]='a';
	out();
}
void solve4J(){
	cut=1; color=3;
	s[1][1]=s[1][2]='a';
	s[2][1]=s[2][2]='b';
	s[3][1]=s[4][1]='c';
	For(i,2,m){
		if (!s[2][i]) s[2][i]=s[2][i+1]=get(s[2][i-1],s[3][i]);
		if (!s[1][i]) s[1][i]=s[1][i+1]=get(s[1][i-1],s[2][i]);
		if (!s[3][i]) s[3][i]=s[3][i+1]=get(s[3][i-1],s[2][i]);
		if (!s[4][i]) s[4][i]=s[4][i+1]=get(s[4][i-1],s[3][i]);
	}
	s[1][m]=s[2][m];
	out();
}
/*
aabb
bbcc
caabb
cbbcc
*/
void solve4O(){
	cut=2; color=3;
	s[1][1]=s[1][2]='a';
	s[2][1]=s[2][2]='b';
	s[4][1]=s[3][1]='c';
	For(i,2,m){
		if (!s[2][i]) s[2][i]=s[2][i+1]=get(s[2][i-1],s[3][i]);
		if (!s[1][i]) s[1][i]=s[1][i+1]=get(s[1][i-1],s[2][i]);
		if (!s[3][i]) s[3][i]=s[3][i+1]=get(s[3][i-1],s[2][i]);
		if (!s[4][i]) s[4][i]=s[4][i+1]=get(s[4][i-1],s[3][i]);
	}
	s[4][m]=s[3][m]=get(s[3][m-1],s[4][m-1]);
	out();
}
/*
aabbccaa
bbccaabb
caabbcc
cbbaabb
*/
void solveJ(){
	cut=0; color=3;
	s[1][1]='a'; s[1][2]='a'; s[1][3]='b'; s[1][4]='a'; s[1][5]='a';
	s[2][1]='b'; s[2][2]='c'; s[2][3]='b'; s[2][4]='c'; s[2][5]='c';
	s[3][1]='b'; s[3][2]='c'; s[3][3]='a'; s[3][4]='a';
	for (int i=4;i<=n;i+=2){
		if (i<=6) s[i][1]=s[i+1][1]=s[i][4]=s[i+1][4]=get(s[i-1][1],'a');
		else s[i][1]=s[i+1][1]=s[i][4]=s[i+1][4]=get(s[i-1][1],s[i-3][1]);
		s[i][2]=s[i][3]=get(s[i][1],s[i-1][3]);
		s[i+1][2]=s[i+1][3]=get(s[i][1],s[i][3]);
	}
	For(j,5,m-2){
		For(i,3,n) if (!s[i][j]){
			if (s[i-1][j]==s[i][j-1]&&j==m-3)
				s[i][j]=s[i][j+1]=get(s[i-1][j],s[i-2][j]);
			else s[i][j]=s[i][j+1]=get(s[i][j-1],s[i-1][j]); 
		}
		if (!s[2][j]) s[2][j]=s[2][j+1]=get(s[2][j-1],s[3][j]);
		if (!s[1][j]) s[1][j]=s[1][j+1]=get(s[1][j-1],s[2][j]);
	} 
	s[1][m]=s[2][m]=get(s[1][m-1],s[2][m-1]);
	for (int i=3;i<n;i+=2){
		s[i][m-1]=s[i+1][m-1]=get(s[i][m-2],s[i+1][m-2]);
		s[i][m]=s[i+1][m]=get(s[i][m-1],s[i-1][m]);
	}
	s[n][m-1]=s[n][m]=get(s[n-1][m-1],s[n-1][m]);
	if (s[n][m-1]==s[n][m-2]){
		s[n][m-1]=s[n][m]=get(s[n][m-2],s[n-1][m-1]);
		for (int i=n-1;i>=4;i-=2)
			if (s[i][m]==s[i+1][m])
				s[i][m]=s[i-1][m]=get(s[i+1][m],s[i][m-1]);
			else break;
	}
	out();
}
/*
aabaabbc
bcbccaac
bcaabbc.
cbbcaac.
caacbb..
bccbaa..
baabcc..
*/
void solve66(){
	cut=1; color=3;
	s[1][1]='a'; s[1][2]='a'; s[1][3]='c'; s[1][4]='a'; s[1][5]='a'; s[1][6]='c';
	s[2][1]='b'; s[2][2]='b'; s[2][3]='c'; s[2][4]='b'; s[2][5]='b'; s[2][6]='c';
	s[3][1]='c'; s[3][2]='a'; s[3][3]='a'; s[3][4]='c'; s[3][5]='a'; s[3][6]='a';
	s[4][1]='c'; s[4][2]='b'; s[4][3]='b'; s[4][4]='c'; s[4][5]='b'; s[4][6]='c';
	s[5][1]='a'; s[5][2]='c'; s[5][3]='a'; s[5][4]='a'; s[5][5]='b'; s[5][6]='c';
	s[6][1]='a'; s[6][2]='c'; s[6][3]='b'; s[6][4]='b'; s[6][5]='a'; s[6][6]='a';
	out();
}
/*
aacaac
bbcbbc
caacaa
cbbcbc
acaabc
acbbaa
*/
void solveO(){
	cut=0; color=3;
	s[1][1]='a'; s[1][2]='a'; s[1][3]='c'; s[1][4]='c';
	s[2][1]='b'; s[2][2]='c'; s[2][3]='a'; s[2][4]='a';
	s[3][1]='b'; s[3][2]='c'; s[3][3]='b'; s[3][4]='c'; s[3][5]='c';
	s[4][1]='a'; s[4][2]='a'; s[4][3]='b'; s[4][4]='a'; s[4][5]='a';
	for (int i=5;i<=n;i+=2){
		s[i][1]=s[i][4]=s[i+1][1]=s[i+1][4]=get(s[i-1][1],s[i-1][1]);
		s[i][2]=s[i][3]=get(s[i][1],s[i-1][2]);
		s[i+1][2]=s[i+1][3]=get(s[i][1],s[i][3]);
	}
	For(j,1,m-3){
		For(i,5,n)
			if (!s[i][j]){
				if (s[i-1][j]==s[i][j-1]&&j==m-3){
					if (i!=6) s[i][j]=s[i][j+1]=get(s[i-1][j],s[i-2][j]);
					else s[i][j]=s[i][j+1]=s[i-2][j]; 
				}
				else s[i][j]=s[i][j+1]=get(s[i-1][j],s[i][j-1]);
			}
		if (!s[4][j]) s[4][j]=s[4][j+1]=get(s[4][j-1],s[5][j]);
		if (!s[3][j]) s[3][j]=s[3][j+1]=get(s[3][j-1],s[4][j]);
		if (j!=m-3&&!s[2][j]) s[2][j]=s[2][j+1]=get(s[2][j-1],s[3][j]);
		if (j!=m-3&&!s[1][j]) s[1][j]=s[1][j+1]=get(s[1][j-1],s[2][j]);
	}
	s[1][m-3]=s[2][m-3]=get(s[1][m-4],s[2][m-4]);
	s[3][m-2]=s[4][m-2]=get(s[3][m-3],s[4][m-3]);
	s[2][m-2]=s[2][m-1]=get(s[3][m-2],s[5][m-2]);
	s[1][m-2]=s[1][m-1]=get(s[1][m-3],s[2][m-2]);
	s[1][m]=s[2][m]=get(s[1][m-1],s[2][m-2]);
	s[3][m-1]=s[3][m]=get(s[2][m],s[2][m-1]);
	for (int i=4;i<n;i+=2){
		s[i][m-1]=s[i+1][m-1]=get(s[i][m-2],s[i+1][m-2]);
		s[i][m]=s[i+1][m]=get(s[i][m-1],s[i-1][m]); 
	}
	s[n][m-1]=s[n][m]=get(s[n-1][m-1],s[n-1][m]);
	out();
}
/*
aaccbaab
bcaabaab
bcbccbcc
aabaabab
bccbccab
baabaab.
accaccb.
abbabbaa
*/
void solve(){
	scanf("%d%d",&n,&m);
	if (n&m&1) return puts("IMPOSSIBLE"),void(0);
	if (n>m) fl=1,swap(n,m); 
	else fl=0;
	For(i,0,n+1) For(j,0,m+1) s[i][j]=0;
	if (n==1) return solve1();
	if (n==2) return solve2(); 
	if (n==3){
		if (m==4) return solve34();
		return solve3();
	}
	if (n==4){
		if (m==4) return solve44();
		if (m&1) return solve4J();
		return solve4O();
	}
	if (m&1){
		swap(n,m); fl^=1;
		For(i,0,n+1) For(j,0,m+1) s[i][j]=0;
	}
	if (n&1) return solveJ();
	if (n==6&&m==6) return solve66();
	solveO(); 
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
 