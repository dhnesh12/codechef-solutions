#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-7
#define N 505

double flores[N][2];
double dist[N][N];

int maxPoints(double radius,int n,int p)
{		
	int res = 1;
	
	//Calculando os ângulos de entrada e saída entre todos os pontos	
	for(int i = 0;i<n;++i)
	{
		double x1 = flores[i][0];
		double y1 = flores[i][1];
		
		vector<pair<double,int>> angles;
		
		for(int j = 0;j<n;++j)
		{
			double x2 = flores[j][0];
			double y2 = flores[j][1];			
			
			//Se for verdade, é possivel incluí-lo ao círculo
			if(i != j && dist[i][j] <= 2.0*radius)
			{				
				//ângulo que a reta PQ faz em relação ao eixo x
				double A = atan2(y2-y1,x2-x1);
				
				//ângulo entre a reta PQ e a PO
				double B = acos(dist[i][j]/(2.0*radius));
				
				//ângulo necessário para que o ponto Q "Entre"
				double alpha = A-B;
				
				//Ângulo necessário para que o ponto Q "Saia"
				double beta = A+B;
				
				angles.push_back(make_pair(alpha,-1));
				angles.push_back(make_pair(beta + 1e-9,1));
			}
		}
		sort(angles.begin(),angles.end()); //Ordenando para usar o Line Sweep
		
		//Line sweeping
		
		int cont = 1;
		
		for(auto it = angles.begin();it != angles.end();++it)
		{
			cont = cont - (*it).second;
			res = max(res,cont);
			
			if (res >= p) return res;
		}
		
	}
	return res;
}
inline double binary_search(double low,double high,int n,int p)
{					
	while((low + EPS < high))
	{
		double r = 0.5*(high+low);		
		
		if(maxPoints(r,n,p) < p)
			low = r;
		else									
			high = r;				
	}
		
	return high;
}
int main()
{	
	int n,p;

	scanf("%d %d",&n,&p);
			
	for(int i = 0;i<n;i++)			
		scanf("%lf %lf",&flores[i][0],&flores[i][1]);
	
	//Calculando as distâncias
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
			dist[i][j] = sqrt((flores[i][0]-flores[j][0])*(flores[i][0]-flores[j][0]) + (flores[i][1]-flores[j][1])*(flores[i][1]-flores[j][1]));
		
	if(p > 1)
		printf("%.5f\n",binary_search(0.0,2829.0,n,p));		
		
	else
		printf("0.00000\n");
	
	return 0;
}
