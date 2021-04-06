#include<bits/stdc++.h>

using namespace std;

#define N 200

bool marked[201]={0};
bool prime[201]={0};
bool semiprime[201]={0};

void seive(void)
{
	for(int i=2;i<=N;i++)
	{
		if(!marked[i])
		{
			for(int step = 2*i; step <= N;step += i)
			{
				marked[step] =1;

				if(prime[step/i])
					semiprime[step] = 1;
			}
			prime[i] = 1;
		}
	}
}

// bool semiprime(int x)
// {
// 	return (marked[x] == 2);
// }

int main()
{
	int t;
	cin>>t;

	seive();

	while(t--)
	{
		int n;
		cin>>n;

		bool flag = 0;
		for(int i=1;i<=n/2;i++)
		{
			int j = n-i;

			if(semiprime[i] & semiprime[j])
			{
				//cout<<i<<" "<<j<<endl;

				flag = 1;

				break;
			}
		}

		if(flag)
			cout<<"YES";
		else
			cout<<"NO";

		cout<<endl;
	}
	return 0;
}