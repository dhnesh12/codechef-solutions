#include <cstdio>
#include <string>
using namespace std;

char Buffer[80];

struct Solution{
	string S;
	
	void Solve() {
		scanf("%s", Buffer);
		S = Buffer;
		int k = 0;
		for (int i = 0; i < S.size(); ++i) {
			k += S[i] - '0';
		}
		k = 10 - k % 10;
		if (k == 10) k = 0;
		printf("%s%d\n", S.c_str(), k);
	}
};

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) Solution().Solve();
	return 0;
}