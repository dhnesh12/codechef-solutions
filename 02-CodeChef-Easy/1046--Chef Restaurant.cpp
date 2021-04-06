#include<bits/stdc++.h>
using namespace std;

int main()
{

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>>intervals;
        for (int i = 0; i < n; i++) {
            int first, second;
            cin >> first >> second;
            intervals.push_back(make_pair(first, second));
        }

        int *timeOfArrival = new int[m];
        for (int i = 0; i < m; i++) {
            cin >> timeOfArrival[i];
        }

        sort(intervals.begin(), intervals.end());

        for (int i = 0; i < m; i++) {

            int currTime = timeOfArrival[i];
            //Getting index of interval with start time >= currTime
            int index = lower_bound(intervals.begin(), intervals.end(), make_pair(currTime, 0)) - intervals.begin();

            //If currTime is earlier than first interval only, then we print time diff of these two.
            if (index == 0) {
                cout << intervals[0].first - currTime << endl;
            } else {
                int ans = -1;
                //If currTime is either = interval startTime or or between any interval, then we print 0 hrs 
                if (currTime == intervals[index].first || currTime < intervals[index - 1].second) {
                    ans = 0;
                /*Else if the currTime is in between last closing interval, then we print time diff between currTIme 
                    and startTime just greater than it*/ 
                } else if (currTime < intervals[n - 1].second) {
                    ans = intervals[index].first - currTime;
                }
                cout << ans << endl;
            }

        }
    }

    return 0;
}
