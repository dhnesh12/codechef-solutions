int main()
{
int i,j,p[50000],n,m,a,b;
scanf("%d",&i);
int ch=0;
while(i>0)
{ch++;
scanf("%d",&j);
while(j--)
scanf("%d",&p[j]);
scanf("%d %d",&n,&m);
while(m--)
scanf("%d %d",&a,&b);
printf("city %d N\n",ch);
i--;}
return 0;
}    