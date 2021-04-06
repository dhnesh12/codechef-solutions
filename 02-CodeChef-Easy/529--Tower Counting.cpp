#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

typedef struct Tower
{
	int t;
	int x;
	int a;
	int original_index;
}Tower;

vector<Tower> list(2000);
int h;
int n;
vector<int> result(2000);

bool compare(Tower &a, Tower &b)
{
	return a.x < b.x;
}

void getInput()
{
	cin >> h >> n;
	
	list.resize(n);
	result.clear();
	result.resize(n);

	for(int i=0;i<n;i++)
	{
		cin >> list.at(i).t >> list.at(i).x >> list.at(i).a;
		list.at(i).original_index = i;
	}

	sort(list.begin(), list.begin() + n, compare);
}

void compute()
{
	double up = numeric_limits<double>::max();
	double down = numeric_limits<double>::lowest();
	double temp=0;
	for(int i = 0; i < n-1; i++)
	{
		up = numeric_limits<double>::max();
		down = numeric_limits<double>::lowest();
		for(int j=i+1; j<n; j++)
		{
			if(list.at(j).x == list.at(i).x)
			{
				result[list.at(i).original_index]++;
				result[list.at(j).original_index]++;
				continue;
			}
			temp = 1.0*(list.at(j).a - list.at(i).a)/(list.at(j).x - list.at(i).x);

			if(list.at(j).t==0 && temp <= down || list.at(j).t==1 && temp >= up)
				continue;
			else if(list.at(j).t==1 && temp <= down || list.at(j).t==0 && temp >= up)
				break;

			if(list.at(j).t==0)
				down=temp;
			else
				up=temp;

			result[list.at(i).original_index]++;
			result[list.at(j).original_index]++;
		}
	}

	for(int i=0;i<n;i++)
		cout << result[i] << " ";
	cout << endl;
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