#include <bits/stdc++.h>
using namespace std;

int N;
set<pair<int, int>> smallElement, bigElement; // segments are stored as [Right Border, Left Border] to make the checking of intersection easier.

long long findWays(int idx) { // here idx is the index of current X
	// let represent elements of greater than equal to idx by ******** and small by .........
	long long ways = 0;
	vector<pair<int, int>> seg(5, {-1, -1}); // the 5 segments are *******.......********.......******** where the segment 2(0-based indexing) contains idx.
	// Note in the set the segments are stored as [Right Border, Left Border].
	seg[2] = *bigElement.lower_bound(make_pair(idx, -1));
	seg[1] = *smallElement.lower_bound(make_pair(seg[2].second-1, -1));
	seg[3] = *smallElement.lower_bound(make_pair(seg[2].first+1, -1));
	if((seg[1].first != seg[2].second-1) || (seg[1].first == 0) || (seg[1].first == N+1)) seg[1] = {-1, -1}; // segment not exist.
	if((seg[3].second != seg[2].first+1) || (seg[3].second == N+1) || (seg[3].second == N+1)) seg[3] = {-1, -1}; // segment not exist.
	if(seg[1].first != -1) {
		seg[0] = *bigElement.lower_bound(make_pair(seg[1].second-1, -1));
	}
	if(seg[3].first != -1) {
		seg[4] = *bigElement.lower_bound(make_pair(seg[3].first+1, -1));
	}
	if((seg[0].first != seg[1].second-1) || (seg[0].first == 0) || (seg[0].first == N+1)) seg[0] = {-1, -1}; // segment not exist.
	if((seg[4].second != seg[3].first+1) || (seg[4].second == N+1) || (seg[4].second == N+1)) seg[4] = {-1, -1}; // segment not exist.
	for(int i = 0; i < 5; i ++) swap(seg[i].first, seg[i].second);// [Right Border, Left Border] ---> [Left Border, Right Border]

	// Case 1 - ********[.........*********]........*********
	if(seg[1].first != -1) {
		int seg2_size = seg[2].second-seg[2].first+1;
		int seg1_size = seg[1].second-seg[1].first+1;
		int forcedSize = idx-seg[2].first+1; // as we have to include the element at idx
		ways += (long long)max(min(seg2_size-forcedSize+1, seg1_size-forcedSize+1), 0);
	}

	// Case 2 - ********.........[*********........]*********
	if(seg[3].first != -1) {
		int seg2_size = seg[2].second-seg[2].first+1;
		int seg3_size = seg[3].second-seg[3].first+1;
		int forcedSize = seg[2].second-idx+1; // as we have to include the element at idx
		ways += (long long)max(min(seg2_size-forcedSize+1, seg3_size-forcedSize+1), 0);
	}

	// Case 3 - [********.........*********]........*********
	if(seg[0].first != -1) {
		int seg2_size = seg[2].second-seg[2].first+1;
		int seg1_size = seg[1].second-seg[1].first+1;
		int seg0_size = seg[0].second-seg[0].first+1;
		int forcedSize = (idx-seg[2].first+1)+1; // as we have to include the element at idx and 1 element of seg[0]. 
		if((seg1_size <= seg0_size + seg2_size) && (seg1_size >= forcedSize)) {
			int remainEle = seg1_size-forcedSize; // these will be taken from seg[0] and seg[2]. and we force to take atleast one element from seg[0]
			seg2_size -= (idx-seg[2].first+1);
			seg0_size -= 1;
			int minTake = max(remainEle-seg2_size, 0); // minimum number of elements you can take from seg[0].
			int maxTake = min(remainEle, seg0_size); // maximum number of elements you can take from seg[0].
			ways += (long long)(maxTake-minTake+1);
		}
	}

	// Case 4 - ********.........[*********........*********]
	if(seg[4].first != -1) {
		int seg2_size = seg[2].second-seg[2].first+1;
		int seg3_size = seg[3].second-seg[3].first+1;
		int seg4_size = seg[4].second-seg[4].first+1;
		int forcedSize = (seg[2].second-idx+1)+1; // as we have to include the element at idx and 1 element of seg[4]. 
		if((seg3_size <= seg2_size + seg4_size) && (seg3_size >= forcedSize)) {
			int remainEle = seg3_size-forcedSize; // these will be taken from seg[2] and seg[4]. and we force to take atleast one element from seg[4]
			seg2_size -= (seg[2].second-idx+1);
			seg4_size -= 1;
			int minTake = max(remainEle-seg2_size, 0); // minimum number of elements you can take from seg[4].
			int maxTake = min(remainEle, seg4_size); // maximum number of elements you can take from seg[4].
			ways += (long long)(maxTake-minTake+1);
		}
	}

	// Case 5 - ********[.........*********........]*********
	if((seg[1].first != -1) && (seg[3].first != -1)) {
		int seg1_size = seg[1].second-seg[1].first+1;
		int seg2_size = seg[2].second-seg[2].first+1;
		int seg3_size = seg[3].second-seg[3].first+1;
		int forcedSize = 2; // as we have to take one element from seg[1] and seg[3].
		if((seg2_size <= seg1_size + seg3_size) && (seg2_size >= forcedSize)) {
			int remainEle = seg2_size-forcedSize;
			seg1_size -= 1;
			seg3_size -= 1;
			int minTake = max(remainEle-seg1_size, 0); // minimum number of elements you can take from seg[3].
			int maxTake = min(remainEle, seg3_size); // maximum number of elements you can take from seg[3].
			ways += (long long)(maxTake-minTake+1);
		}
	}

	return ways;
}

void modifySets(int idx) { // function now add the current idx from big elements to small elements and modify the ranges accordingly
	// modifying bigElement set.
	{
		pair<int, int> seg = *bigElement.lower_bound(make_pair(idx, -1)); // finding the segment which contains X.
		bigElement.erase(seg); 
		int L = seg.second, R = seg.first; 
		if(L < idx) bigElement.insert(make_pair(idx-1, L)); // if there is some big elements to the left of X.
		if(R > idx) bigElement.insert(make_pair(R, idx+1)); // if there is some big elements to the right of X.
	}

	// modifying smallElement set.
	{
		// here idx is the index of the X.
		int L = idx, R = idx; // current segment to add (idx, idx)
		// below I am checking if any range of type (l, idx-1) exist, and if it then
		// I will merge it with (idx, idx).
		pair<int, int> seg = *smallElement.lower_bound(make_pair(idx-1, -1)); 
		if((seg.first == idx-1) && (seg.first != 0) && (seg.first != N+1)) {
			smallElement.erase(seg);
			L = seg.second;
		}
		// below I am checking if any range of type (idx+1, r) exist, and if it then
		// I will merge it.
		seg = *smallElement.lower_bound(make_pair(idx+1, -1));
		if((seg.second == idx+1) && (seg.second != 0) && (seg.second != N+1)) {
			smallElement.erase(seg);
			R = seg.first;
		}
		smallElement.insert({R, L}); // adding to set.
	}
}

void solveTestCase() {
	smallElement.clear();
	bigElement.clear();

	long long ans = 0;
	cin >> N;
	vector<pair<int, int>> a(N);
	for(int i = 0; i < N; i ++) {
		cin >> a[i].first;
		a[i].second = i+1;
	}
	bigElement.insert({N, 1});
	bigElement.insert({N+1, N+1}); // dummy segment is added to make implementation easy.
	bigElement.insert({0, 0}); // dummy segment is added to make implementation easy.
	smallElement.insert({N+1, N+1}); // dummy segment is added to make implementation easy.
	smallElement.insert({0, 0}); // dummy segment is added to make implementation easy.

	sort(a.begin(), a.end());
	// Question basically ask us to find number of segment of length 2*L such that it is possible to divide the segment into two halfs such that 
	// one half contains smallest L elements and the other half contains the largest L element. So if we fix the smallest element of the larger half and
	// L, and compute it for each element it will help us to prevent overcounting.

	for(int X = 0; X < N; X ++) { // Trying to find all the segment of different length with the smallest element of the larger half a[i].first
		ans += findWays(a[X].second); // a[X].second = index of current X.
		modifySets(a[X].second);
	}
	cout << ans << '\n';
}


int main() {
	ios_base::sync_with_stdio(0); // fast IO
	cin.tie(0);
	cout.tie(0);


	int testCase;
	cin >> testCase;
	for(int i = 1; i <= testCase; i ++) {
		solveTestCase();
	}

	return 0;
}
