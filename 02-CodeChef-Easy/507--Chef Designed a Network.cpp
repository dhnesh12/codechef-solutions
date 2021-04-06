#include <iostream>  // std::cin, std::cout
#include <cassert>   // assert

using namespace std;

/////////////////////////////
//
// declaration class
//
/////////////////////////////
struct Input;


/////////////////////////////
//
// declaration function
//
/////////////////////////////
template<typename T> T read();
void readTestcases(unsigned int T);
long long chefk1(const Input& input);
long long chefk1(unsigned long long N, unsigned long long M, unsigned long long maxCable);
unsigned long long formula1(unsigned long long N, unsigned long long M);
unsigned long long formula2(unsigned long long N, unsigned long long M, unsigned long long maxEdge);
unsigned long long maxEdge(unsigned long long n);


/////////////////////////////
//
// definition class
//
/////////////////////////////
struct Input
{
	Input() : N(read<unsigned long long>()), M(read<unsigned long long>())
	{
	}

	const unsigned long long N;
	const unsigned long long M;
};

/////////////////////////////
//
// definition function
//
/////////////////////////////
template<typename T> T read()
{
	T n;
	cin >> n;
	return n;
}

void readTestcases(unsigned int T)
{
	for (unsigned int i = 0; i < T; ++i)
	{
		cout << chefk1(Input()) << endl;
	}
}

long long chefk1(const Input& input)
{
	return chefk1(input.N, input.M, maxEdge(input.N));
}

long long chefk1(unsigned long long N, unsigned long long M, unsigned long long maxEdge)
{
	if (M < N - 1 || M > maxEdge)
		return -1;
	else if (M <= N + 1)
	{
		if (N == 1)
		{
			if (M == 0)
				return 0;
			else if (M == 1)
				return 1;
			else
				return -1;
		}
		if (N == 2)
		{
			if (M == 1)
				return 1;
			else
				return 2;
		}
		else
			return 2;
	}
	else if (M <= N * 2 - 1)
		return 3;
	else
	{
		assert(formula1(N, M) == formula2(N, M, maxEdge));
		return formula2(N, M, maxEdge);
	}
}

// SOLUTION1
unsigned long long formula1(unsigned long long N, unsigned long long M)
{
	return ((M - N) * 2 - 1) / N + 2;
}

// SOLUTION2
unsigned long long formula2(unsigned long long N, unsigned long long M, unsigned long long maxEdge)
{
	return N - ((maxEdge - M) * 2) / N;
}

unsigned long long maxEdge(unsigned long long N)
{
	return N * (N + 1) / 2;
}

int main()
{
	readTestcases(read<unsigned int>());

	return 0;
}
