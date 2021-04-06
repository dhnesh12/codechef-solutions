#include <iostream>
using namespace std;

int T = 0;
int x11 = 0, y11 = 0;
int x12 = 0, y12 = 0;

int x21 = 0, y21 = 0;
int x22 = 0, y22 = 0;

int a = 0, b = 0, c = 0, d = 0;

int sameSnakeTest()
{
	int minVal = 0;

	if ((x11 == x21 && y11 == y21) ||
		(x11 == x22 && y11 == y22)||
		(x12 == x21 && y12 == y21)||
		(x12 == x22 && y12 == y22) 
		)
	{
		//90 degree connected snakes
		return 1;
	}
	
	if ((x11 == x12) && (x12 == x21) && (x21 == x22))
	{
		if (y11 >= y12)
		{
			a = y11;
			b = y12;
		}
		else
		{
			a = y12;
			b = y11;
		}
		if (y21 >= y22)
		{
			c = y21;
			d = y22;
		}
		else
		{
			c = y22;
			d = y21;
		}
		if (a > c)
		{
			if (d > b)
			{
				return 1;
			}
			else
			{
				if ((c - b) >= 1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (b > d)
			{
				return 1;
			}
			else
			{
				if ((a - d) >= 1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	else if ((y11 == y12) && (y12 == y21) && (y21 == y22))
	{
		//horizontal line
		if (x11 <= x12)
		{
			a = x11;
			b = x12;
		}
		else
		{
			a = x12;
			b = x11;
		}
		if (x21 <= x22)
		{
			c = x21;
			d = x22;
		}
		else
		{
			c = x22;
			d = x21;
		}
		if (a < c)
		{
			if (d < b)
			{
				return 1;
			}
			else
			{
				if ((b - c) >= 1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (b < d)
			{
				return 1;
			}
			else
			{
				if ((d - a) >= 1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	else
	{
		//Cannot have parallel cells
		return 0;
	}
}


void readInput()
{
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> x11 >> y11 >> x12 >> y12;
		cin >> x21 >> y21 >> x22 >> y22;

	    if (sameSnakeTest() == 1)
	    {
		    cout << "yes" << endl;
	    }
	    else
	    {
	    	cout << "no" << endl;
	    }
	}
}
int main()
{
     readInput();

	return 0;
}
