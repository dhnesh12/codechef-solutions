

#include<stdio.h>
int main(){

  int t;
  scanf("%d",&t);
  while (t--)
  {
   float p,q;
   scanf("%f %f",&p,&q);
   if(p>1000) printf("%f\n",p*q*0.9);
   else printf("%f\n",p*q);
  }
}