#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cassert>

using namespace std;

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define maxd 1000000000
#define maxl 100000

typedef long long  LL;

char str[maxl+1];
int n;

// Converts number to string
string ToStr(LL x)
{
    char num[25];
    sprintf(num,"%lld",x);
    string s=(string)num;
    return s;
}
// Checks if the prefix of P upto index p is is a suffix of the number x
int checkSuf(int p,LL x)
{
    int j,k,ok=1;
    string num=ToStr(x);
    k=(int)num.size()-1;
    for(j=p;j>=0 && k>=0 && ok;j--,k--)
        if(num[k]!=str[j]) ok=0;
    if(j>=0) ok=0;
    return ok;
}

// Solves for the case when Q is catenation of 2 numbers partially
int solve2()
{
    int i,j,k,sol=0;
    LL u=0;

    // Solves the case where the last number is 10^9
    string lastP = ToStr(maxd-1);
    lastP += ToStr(maxd);
    string Q=string(str);
    for(i=0;i+n-1<lastP.size() && !sol;i++)
    {
        string sub = lastP.substr(i,n);
        if(sub==Q)  sol=1;
    }

    for(i=0;i<n && !sol;i++)
    {
        u=(u*10+ str[i]-'0');
        if(u>maxd) break;

        int carry=1;
        string suf;

        for(j=i;j>=0;j--)
        {
           int d=str[j]-'0';
           suf+=(char)((d+carry)%10+'0');
           carry=(d+carry)/10;
        }

        reverse(suf.begin(),suf.end());

        LL v=0;
        for(j=i+1;j<n;j++)
        {
           v=(v*10+str[j]-'0');
           if(v>maxd) break;
        }

        if(v>maxd) continue;

        for(int l=1;l<=9 && !sol;l++)
        {
           int ok=1;
           string pref(l,'x');
           for(k=0,j=i+1;j<n && k<l;j++,k++)
              pref[k]= str[j];

           if(k==l && j<n) ok=0;

           int pl=suf.size();

           for(k=l-1,j=pl-1;j>=0 && k>=0 && ok;j--,k--)
           {
              if(pref[k]!='x' && pref[k]!=suf[j]) ok=0;
              pref[k]=suf[j];
           }

           if(k<0 && j>=0) ok=0;

           for(v=k=0;k<l;k++)
           {
              if(pref[k]=='x') ok=0;
              v=v*10+pref[k]-'0';
           }

           if(v<=1 || v>maxd) ok=0;
           if(pref[0]=='0') ok=0;
           if(checkSuf(i,v-1)==0) ok=0;

           if(ok) sol=1;
         }
    }
    return sol;
}

// Solves the case when atleast one number appears fully
int solve()
{
    int offs,j,k,sol=0;

     for(offs=0;offs<11 && !sol;offs++)
         for(int l=1;l<=10 && !sol;l++)
         {
            if(offs+l-1>=n) break;
            LL u=0,v=0;

            for(k=0;k<l;k++) u=(u*10+str[k+offs]-'0');
            v=u;j=offs;

            int ok=1;

            while(j<n && ok)
            {
               string num = ToStr(v);
               for(k=0;k<num.size() && j<n && ok;j++,k++)
                  if(num[k]!=str[j]) ok=0;
               ++v;
            }

            if( u<1 || (offs && u-1<1) || v-1>maxd) ok=0;
            if(offs && !checkSuf(offs-1,u-1)) ok=0;

            if(ok) sol=1;
         }
    return sol;
}



int main()
{
   int T;

   scanf("%d",&T);
   assert(T>=1 && T<=10);

   while(T--)
   {
      scanf("%s",str);

      n=strlen(str);
      assert(n>=1 && n<=maxl);
      int sol=0,zero=0;

      for(int i=0;i<n;i++) if(str[i]=='0') zero++;

      if(n<=8 || (n==9 && str[0]!='0')) sol=1;
      if(n==9  && zero==9) sol=1;
      if(n<=19 && solve2()) sol=1;
      if(!sol && solve()) sol=1;

      if(sol)
         puts("YES");
      else
         puts("NO");
   }

	return 0;
}


