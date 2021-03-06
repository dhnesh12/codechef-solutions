
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

struct pouch {
	LL V, U, L;

	pouch(){}
	pouch(LL V_, LL U_, LL L_): V(V_), U(U_), L(L_) {}

	bool operator < (const pouch &p) const {
		return U > p.U || U == p.U && V > p.V;
	}
};

int main() {
	int T;
	cin >> T;
	for (int tst = 0; tst < T; ++tst) {
		int N;
		cin >> N;

		// A[0] - odd pouches
		// A[1] - good even pouches
		// A[2] - bad even pouches (V=2*L)
		vector<pouch> A[3];
		LL sumV = 0;
		LL maxU = 0;
		for (int i = 0; i < N; ++i) {
			LL V, U, L;
			cin >> V >> U >> L;
			maxU = max(maxU, U);
			sumV += V;
			V = min(V, 2 * L);
			if (V == 2 * L) {
				// bad pouch
				A[2].push_back(pouch(V, U, L)); 
			} else {
				// V%2 == 0 - even pouch --> A[1]
				// V%2 == 1 - odd  pouch --> A[0]
				A[1-V%2].push_back(pouch(V, U, L));
			}
		}
		for (int j = 0; j < 3; ++j) {
			sort(A[j].begin(), A[j].end());
		}
		
		LL res = 0; // the total number of eaten food units
		// a[j] is the position of first not consumed pouch in list A[j]
		int a[3] = {0, 0, 0};
		LL U = maxU; // the current day where we have some free slots for food
		int eat = 0; // the number of foods we have already eaten in day U

		bool test_mode = false;
		int empty = 0; // needed when we leave test_mode

		// temporary variables where we save
		// our current state of all stuff when turn on test_mode
		LL res_save = 0;
		int a_save[3];
		LL U_save;
		int eat_save;

		while (true) {
			LL maxU = 0; // the maximal Ui over not consumed pouches
			for (int k = 0; k < 3; ++k) {
				if (a[k] < A[k].size()) {
					maxU = max(maxU, A[k][a[k]].U);
				}
			}
			// we have some free days between U and maxU (or at least one free slot on day U)
			if(U > maxU) {
				// in usual mode we simply set U to be maxU
				if (!test_mode) {
					U = maxU;
					eat = 0;
				} else {
					// otherwise we decide whether to revert all changes or return the answer

					// Here we have no pouches and have only one slot for food left in the first day
					// it means that our decision to use only 2*L-1 units from the bad pouch we test
					// was optimal and the value in @res is the actual answer
					if (maxU==0 && U==1 && eat==1) {
						break;
					}
					// otherwise we have a free day (possibly half of the maxU-th day will be used)
					// and we should revert our changes back
					test_mode = false;
					res = res_save;
					U = U_save;
					eat = eat_save;
					for (int k = 0; k < 3; ++k) {
						a[k] = a_save[k];
					}
					// we should left empty slot at the U-th day now
					// hence we set this variable to 1
					empty = 1;
				}
			}
			// in both modes it means that we did not waste any food slot
			// other than obvious ones
			if (U == 0) {
				break;
			}
			int j; // the type of pouch we will consume now
			if (eat == 0) {
				// {bad, even, odd} = {2, 1, 0}
				for (j = 2; j >= 0; --j) {
					if (a[j] < A[j].size() && U <= A[j][a[j]].U) {
						// we find the pouch with Ui >= U
						break;
					}
				}
			} else {
				// {odd, even, bad} = {0, 1, 2}
				for (j = 0; j < 3; ++j) {
					if (a[j] < A[j].size() && U <= A[j][a[j]].U) {
						// as above we find the pouch with Ui >= U
						break;
					}
				}
			}
			// whether we use bad pouch for eat=1
			int bad = eat == 1 && j == 2;
			// empty = 1 means we already test this bad situation
			// test_mode = trues means we should analyze it by default
			if (bad && !test_mode && !empty) {
				// otherwise we turn on test_mode
				test_mode = true;
				// and save our current state
				res_save = res;
				U_save = U;
				eat_save = eat;
				for (int k = 0; k < 3; ++k) {
					a_save[k] = a[k];
				}
			}
			// 2*U-eat is the total number of empty slots
			// we subtract @empty since after leaving the test_mode
			// we should left empty slot on day U
			LL food = 2 * U - eat - empty;
			// we subtract bad since in this case we should consume one less food from this pouch
			// but add @empty since when empty=1 then bad=1 and we decide to consume all foods.
			food = min(food, A[j][a[j]].V - bad + empty);

			res += food; // add @food to result

			// eat+empty+food is the total number of slots we will occupy now
			// (or left empty forever) starting from the day U backward
			U -= (eat + empty + food)/2;
			eat = (eat + empty + food)%2;

			++a[j]; // mark pouch A[j][a[j]] as consumed

			// always set to 0, it could 1 only after returning back from test_mode
			empty = 0;
		}

		// the actual results is sumV-res
		// since we need to return the number of wasted food
		cout << sumV - res << endl;
	}
	return 0;
}
