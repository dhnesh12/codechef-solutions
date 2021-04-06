#include<bits/stdc++.h>

#define For(i,x,y) for (int i=x;i<y;i++)

using namespace std;
 
int ch;
int IN(){
	int f,x;
	while (!isdigit(ch=getchar())&&ch!='-');ch=='-'?(f=1,x=0):(f=0,x=ch-'0');
	while (isdigit(ch=getchar())) x=(x<<1)+(x<<3)+ch-'0';return !f?x:-x;
}
 
char s[10],t[10];
int a1,a2,b1,b2,b3,c,d,e,val,l,r,res;
int f[11][4][11][21][6][2][91];
 
int main(){
	for (int Qc=IN();Qc--;){
		scanf("%s",s);
		a1=IN()+1;
		if (ch=='.') a2=IN()+1;else a2=0;
		b1=IN()+1;
		if (ch=='.'){
			b2=IN()+1;
			if (ch=='.') b3=IN()+1;else b3=0;
		} else b2=b3=0;
		scanf("%s",t);
		c=IN();
		if (s[0]=='I'){
			val=IN();
			For(A1,0,11) if (A1==0||A1==a1)
				For(A2,0,4) if (A2==0||A2==a2)
					For(B1,0,11) if (B1==0||B1==b1)
						For(B2,0,21) if (B2==0||B2==b2)
							For(B3,0,6) if (B3==0||B3==b3){
								for (int i=c;i<91;i++) f[A1][A2][B1][B2][B3][t[0]=='M'][i]+=val;
							}
		} else{
			l=c;
			if (ch=='-') r=IN();else r=l;
			res=0;
			res+=f[a1][a2][b1][b2][b3][t[0]=='M'][r];
			res-=f[a1][a2][b1][b2][b3][t[0]=='M'][l-1];
			printf("%d\n",res);
		}
	}
} 