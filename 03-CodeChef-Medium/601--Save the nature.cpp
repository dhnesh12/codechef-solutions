#include <iostream>
using namespace std;

// Rows, Cols starts from 0
class Matrix {
public:
	Matrix(int rows, int cols) :
		Rows(rows),
		Cols(cols)
	{
		TheMatrix = new int*[rows];
		for (int i = 0; i < rows; i++)
			TheMatrix[i] = new int[cols];
	}

	~Matrix()
	{
		for (int i = 0; i < Rows; i++)
		{
			delete[] TheMatrix[i];
		}
		delete[] TheMatrix;
	}
	void AddValue(int r, int c, int Value)
	{
		TheMatrix[r][c] = Value;
	}

	int HowManySizedCols(int rowSize, int colSize, int maxSum)
	{
		int counter = 0;
		
		for (int startR = 0; startR + rowSize <= Rows; startR++)
		{
			for (int startC = 0; startC + colSize <= Cols; startC++)
			{
				int64_t sum = 0;
				int colDone = 0, rowDone = 0;
				while (++rowDone <= rowSize)
				{
					colDone = 0;
					while (++colDone <= colSize)
					{
						sum += TheMatrix[startR + rowDone - 1][startC + colDone - 1];
					}
				}
				if (sum <= maxSum)
					++counter;
			}
		}
		return counter;
	}
private:
	int** TheMatrix;
	int Rows, Cols;
};

int main()
{
	int t; cin >> t;
	while (t--)
	{
		int n, m, s; cin >> n >> m >> s;
		Matrix MyMatrix(n, m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				int z; cin >> z;
				MyMatrix.AddValue(i, j, z);
			}
		}

		int counter = 0;
		if (n == m)
			for (int r = n; r >= 1; r--)
			{
				for (int c = r; c >= 1; c--)
				{
					if (r != c)
					{
						counter += MyMatrix.HowManySizedCols(r, c, s) + MyMatrix.HowManySizedCols(c, r, s);
					}
					else
						counter += MyMatrix.HowManySizedCols(r, c, s);
				}
			}
		else if (n < m)
			for (int c = m; c >= 1; c--)
			{
				int r = c;
				if (r > n)
					r = n;
				for (; r >= 1; r--)
				{
					if (r != c)
					{
						counter += MyMatrix.HowManySizedCols(r, c, s) + MyMatrix.HowManySizedCols(c, r, s);
					}
					else
						counter += MyMatrix.HowManySizedCols(r, c, s);
				}
			}
		else if (n > m)
			for (int r = n; r >= 1; r--)
			{
				int c = r;
				if (c > m)
					c = m;
				for (; c >= 1; c--)
				{
					if (r != c)
					{
						counter += MyMatrix.HowManySizedCols(r, c, s) + MyMatrix.HowManySizedCols(c, r, s);
					}
					else
						counter += MyMatrix.HowManySizedCols(r, c, s);
				}
			}

		cout << counter << endl;
	}
}