
//#include<iostream>
#include<stdio.h>
#include<math.h>

#define MOD 1000000007
#define llu long long unsigned
#define lld long long
#define ld long
#define BSIZE 20
using namespace std;

//end of definitions


//fast input

int scan_d()    {int ip=getchar_unlocked(),ret=0;for(;ip<'0'||ip>'9';ip=getchar_unlocked());for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return ret;}
long scan_ld()    {long ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}
long long scan_lld()    {long long ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}
long long unsigned scan_llu()    {long long unsigned ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}

//end of fast input
char sp;
void print_d(int n)     {int i=10;char output_buffer[11];output_buffer[10]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
void print_lld(lld n)     {int i=21;char output_buffer[22];output_buffer[21]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<22);}


//extra functions

int first(int n,int k)
{
    long double nlogn=n*log10l(n);
    long double first=pow(10,nlogn-floor(nlogn)+k-1);
    return (int)(first);
}

long long e_b_sq(int bs,int po,int mod)
{
    long long y=bs%mod,x=1;
    int i;
    while(po>0)
    {
        if(po&1)
        {
            long long temp=0;
            for(i=0;i<x;i++)
                temp+=y;
            x=temp%mod;
        }
        long long temp=0;
        for(i=0;i<y;i++)
            temp+=y;
        y=temp%mod;
        po>>=1;
    }
    return x;
}

//end of extra fnctions


//main

int p[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
char ch[][10]={{'\0'},{'0','\0'},{'0','0','\0'},{'0','0','0','\0'},{'0','0','0','0','\0'},{'0','0','0','0','0','\0'},{'0','0','0','0','0','0','\0'},{'0','0','0','0','0','0','0','\0'},{'0','0','0','0','0','0','0','0','\0'}};

int main()
{
    int t;
    t=scan_d();
    while(t--)
    {
        int n=scan_d();
        int k=scan_d();
        long long l=e_b_sq(n,n,p[k]);
        long long temp=l,len=0;
        do
        {
            len++;
            temp/=10;
        }while(temp);
        sp=' ';
        print_d(first(n,k));
        printf("%s",ch[k-len]);
        sp='\n';
        print_lld(l);
    }
    return 0;
}
