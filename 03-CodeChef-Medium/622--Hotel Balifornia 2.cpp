/**
 * February 2013 Cook-Off
 *
 * Problem:     HOB2 - Hotel Balifornia 2
 * Author:      Anton Lunyov (Problem-Setter)
 * Complexity:  O(N) per test
 * Timing:      0.16 out of 1.00
 *
 * Description:
 * Let records in logbook are numbered from zero.
 * The logbook can be recovered if and only if 0 <= inconv[k] <= min(k, R) for all k.
 * This condition is clearly necessary since when k-th guest (0-based) comes
 * we can have at most k rooms occupied and hence inconvenience can't be more than k.
 * Of course inconvenience can't be more than R as well.
 * How to recover records?
 * Let do this recover in such a way that before k-th visit
 * first min(k,R) rooms will be occupied (rooms 0, 1, ..., min(k,R)-1).
 * Then at k-th visit where k < R we settle guest at room k
 * and set room[k] = k - inconv[k], while stay_time = 31415926 for k < R-1.
 * We will never settle any other guest at some room other than R-1
 * so that rooms from 0 to R-2 will be always occupied for guests starting from (R-1)-th.
 * Now let @last be the index of the last guest that was settled to room R-1
 * so that initially it is R-1. Now for k>=R if we have inconv[k] = R,
 * we simply set room[k] = 0 and stay_time[k] = 31415926.
 * If inconv[k] < R then we set room[k] = R-1 - inconv[k]
 * and in order to settle this guest at room R-1
 * we set stay_time[last] equal to time[k] - time[last],
 * so that this guest will leave exactly at the moment time[k]
 * making room R-1 free for the guest k.
 * So we get very simple linear solution.
 * But probably ideas behind could be not so easy to figure it out.
 */
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxN = 314159;
int time[maxN], room[maxN], stay_time[maxN];

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; ++t) {
		int R, N;
		scanf("%d%d", &R, &N);
		// index of last guest who lives in room R-1
		int last = R - 1;
		for (int k = 0; k < N; ++k) {
			int inconv;
			scanf("%d%d", &time[k], &inconv);
			// for each guest we init room by 0 and stay_time by maximal possible
			room[k] = 0;
			stay_time[k] = 31415926;
			if(inconv < R) {
				// we settle this guest at room k if k<R and at room R-1 otherwise
				// hence the formula for prefered room
				room[k] = min(k, R - 1) - inconv;
				if (k >= R) {
					// The guest @last has occupied the room R-1 at time[last].
					// In order to free it at time[k] his stay time should be at most 
					// the difference time[k] - time[last].
					// But any lower value could ruin some previous records in logbook
					// by allowing some guest with inconv = R to occupy this room.
					stay_time[last] = time[k] - time[last];
					last = k;
				}
			}
		}
		for (int k = 0; k < N; ++k) {
			printf("%d %d\n", room[k], stay_time[k]);
		}
	}
	return 0;
}
