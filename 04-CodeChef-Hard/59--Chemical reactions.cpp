#include <stdio.h>


#define abs(x) ((x)>0?(x):-(x))

#define MAX 100




void mnozi(double a[][MAX], double b[][MAX], double c[][MAX], int n)
{
	int i,j,k;
	double ukupno,temp[MAX][MAX];

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			ukupno=0;
			for(k=0;k<n;k++)	
				ukupno+=a[i][k]*b[k][j];
			temp[i][j]=ukupno;
		}	

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			c[i][j]=temp[i][j];
}


void pot(double a[][MAX], int k, double b[][MAX], int n)
{
	double temp[MAX][MAX],temp2[MAX][MAX];
	int i,j;
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			temp2[i][j]=i==j;	
			temp[i][j]=a[i][j];
		}
	
	while(k)
	{
		if (k&1)
			mnozi(temp,temp2,temp2,n);
		mnozi(temp,temp,temp,n);
		k>>=1;	
	}	
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			b[i][j]=temp2[i][j];
}



void inv(double a[][MAX],double b[][MAX],int n)
{
	int i,j,k;
	double temp[MAX][MAX],temp2[MAX][MAX],tt;
	
	
	for(i=0;i<n;i++)	
		for(j=0;j<n;j++)
		{
			temp[i][j]=a[i][j];
			temp2[i][j]=i==j;
		}
			
	for(i=0;i<n;i++)
	{
		if (temp[i][i]==0)
			for(j=i+1;j<n;j++)
				if (temp[j][i]!=0)
				{
					for(k=0;k<n;k++)	
					{
						temp[i][k]+=temp[j][k];
						temp2[i][k]+=temp2[j][k];
					}
					break;
				}
		tt=temp[i][i];
		for(j=i;j<n;j++)
			temp[i][j]/=tt;
		for(j=0;j<n;j++)
			temp2[i][j]/=tt;
			
			
		for(j=0;j<n;j++)
		{
			if (j==i)
				continue;
			for(k=0;k<n;k++)
				temp2[j][k]-=temp2[i][k]*temp[j][i];

			for(k=i+1;k<n;k++)
				temp[j][k]-=temp[i][k]*temp[j][i];	
		}
	}	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			b[i][j]=temp2[i][j];
}

int main()
{
	int n,k,i,j,m,s,x,y;
	double p[MAX],rr;
	double ukupno;

	double temp1[MAX][MAX];
	double temp2[MAX][MAX];
	double temp3[MAX][MAX];
	double temp4[MAX][MAX];
	double r[2][MAX][MAX]={0};

	scanf("%d %d",&n,&k);
	
	for(i=0;i<n;i++)
	{
		scanf("%lf",&p[i]);
		p[i]=1-p[i];
	}
	
	scanf("%d",&m);
	
	while(m--)
	{
		scanf("%d %d %lf %d",&x,&y,&rr,&s);
		r[s][y][x]=p[x]*rr;	
	}

	for(i=0;i<n;i++)
	{
		r[0][i][i]=p[i];
		for(j=0;j<n;j++)
			if (i!=j)
				r[0][i][i]-=r[0][j][i]+r[1][j][i];
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			r[0][i][j]=(i==j)-r[0][i][j];

	inv(r[0],temp1,n);
	mnozi(r[1],temp1,temp2,n);
	pot(temp2,k,temp3,n);

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			temp2[i][j]=(i==j)-temp2[i][j];
			
	inv(temp2,temp2,n);


	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			temp3[i][j]=(i==j)-temp3[i][j];

	mnozi(temp1,temp2,temp1,n);
	mnozi(temp1,temp3,temp1,n);
	
	for(i=0;i<n;i++)
	{
		ukupno=0;
		for(j=0;j<n;j++)
			ukupno+=temp1[i][j];
		printf("%.10lf ",ukupno);
	}
	printf("\n");

	return 0;	
}