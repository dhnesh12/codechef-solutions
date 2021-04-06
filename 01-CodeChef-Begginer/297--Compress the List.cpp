#include <cstdio>
#include <vector>
using namespace std;

struct Range{
	int From, To;
};

struct Solution{
	int N, X;
	vector<Range> R;
	
	void Solve() {
		scanf("%d%d", &N, &X);
		R.resize(1);
		R[0].From = R[0].To = X;
		for (int i = 1; i < N; ++i) {
			scanf("%d", &X);
			if (X == R.back().To + 1) {
				++R.back().To;
			} else {
				Range newrange = {X, X};
				R.push_back(newrange);
			}
		} 
		bool head = true;
		for (int i = 0; i < R.size(); ++i) {
			if (!head) printf(",");
			head = false;
			if (R[i].From == R[i].To) {
				printf("%d", R[i].From);
			} else if (R[i].From + 1 == R[i].To){
				printf("%d,%d", R[i].From, R[i].To);
			} else {
				printf("%d...%d", R[i].From, R[i].To);
			}
		}
		printf("\n");
	}
};

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0;i < t; ++i) Solution().Solve();
	return 0;
}