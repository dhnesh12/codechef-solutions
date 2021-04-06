#include<iostream>
using namespace std;
int main()
{
// 	#ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif

	int t;
	cin>>t;
	while(t--)
	{
		int N;
		cin>>N;

		int A[N][N];

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				cin>>A[i][j];
			}
		}


		int a=0;
		int b=0;

		int i=0;

		while(i<N)
		{
			for (int j = 0; j < N; ++j)
			{
				if (A[i][j]==0)
				{
					a++;
					break;
				}
			}
			i++;
		}
		// cout<<a<<endl;
		int j=0;
		while(j<N)
		{
			for (int i = 0; i < N; ++i)
			{
				if (A[i][j]==0)
				{
					b++;
					break;
				}
			}
			j++;
		}
		// cout<<b<<endl;

		if (a+b==2*N)
		{
			cout<<"YES"<<endl;
		}
		else 
			cout<<"NO"<<endl;
		
	}
}