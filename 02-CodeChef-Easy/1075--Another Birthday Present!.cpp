#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Ele
{
	int n;
	int original_index;
}Ele;

vector<Ele> list(100000);
int n;
int k;

void getInput()
{
	cin >> n >> k;
	for(int i=0;i<n;i++)
	{
		cin >> list.at(i).n;
		list.at(i).original_index=i;
	}
}

bool compare(Ele &a, Ele &b)
{
	return a.n < b.n;
}

void compute()
{
	sort(list.begin(), list.begin() + n, compare);

	long long diff_sum=0;
	int diff=-1;
	for(int i=0;i<n;i++)
	{
		diff = i - list.at(i).original_index;
		if(diff % k != 0)
		{
			cout << "no" << endl;
			return;
		}

		diff_sum += diff;
	}

	if(diff_sum == 0)
		cout << "yes" << endl;
	else 
		cout << "no" << endl;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		getInput();
		compute();
	}
	return 0;
}