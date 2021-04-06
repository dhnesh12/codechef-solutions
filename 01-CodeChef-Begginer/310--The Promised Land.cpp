#include <cstdio>
#include <vector>
using namespace std;

struct Solution{
	int N, M;
	int X, Y, S;
	vector<int> x, y;
	
	void Solve() {
		scanf("%d%d", &N, &M);
		scanf("%d%d%d", &X, &Y, &S);
		x.resize(X + 2);
		y.resize(Y + 2);
		x[X + 1] = N + 1;
		y[Y + 1] = M + 1;
		int countx = 0;
		for (int i = 1; i <= X; ++i) scanf("%d", &x[i]);
		for (int i = 1; i <= X + 1; ++i) {
			countx += (x[i] - x[i - 1] - 1) / S;
		}  
		int county = 0;
		for (int i = 1; i <= Y; ++i) scanf("%d", &y[i]);
		for (int i = 1; i <= Y + 1; ++i) {
			county += (y[i] - y[i - 1] - 1) / S;
		}
		printf("%d\n", countx * county);
	} 
};

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) Solution().Solve();
	return 0;
}