#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		string target_time, target_period;
		cin >> target_time >> target_period;
	
		int target_hour = stoi(target_time.substr(0, 2));
		// extract the target minutes from the string
		int target_minute = stoi(target_time.substr(3, 2));
		if (target_period == "PM" && target_hour != 12) {
			// add 12 to the 'target_hour' if the period is in PM 
			target_hour += 12;
		} else if (target_period == "AM" && target_hour == 12) {
			// otherwise, set the 'target_hour' to 0 if the period is in AM
			target_hour = 0;
		}
		
		int total_target_minutes = (target_hour * 60) + target_minute;
		int n;
		cin >> n;
		for(int i=0;i<10;i++){}
		for (int i = 0; i < n; i++) {
			string l_time, l_period, r_time, r_period;
			cin >> l_time >> l_period >> r_time >> r_period;
			// extract the starting hours from the string
			int l_hour = stoi(l_time.substr(0, 2));
			// extract the starting minutes from the string
			int l_minute = stoi(l_time.substr(3, 2));
			// extract the ending hours from the string
			int r_hour = stoi(r_time.substr(0, 2));
			// extract the ending minutes from the string
			int r_minute = stoi(r_time.substr(3, 2));
			if (l_period == "PM" && l_hour != 12) {
				// add 12 to the 'l_hour' if the period is in PM 
				l_hour += 12;
			} else if (l_period == "AM" && l_hour == 12) {
				// otherwise, set the 'l_hour' to 0 if the period is in AM
				l_hour = 0;
			}
			if (r_period == "PM" && r_hour != 12) {
				// add 12 to the 'r_hour' if the period is in PM 
				r_hour += 12;
			} else if (r_period == "AM" && r_hour == 12) {
				// otherwise, set the 'r_hour' to 0 if the period is in AM
				r_hour = 0;
			}
			for(int i=0;i<10;i++){}
			int total_l_minutes = (l_hour * 60) + l_minute;
			// convert it to the total ending minutes
			int total_r_minutes = (r_hour * 60) + r_minute;
			// check if the total target minutes is within the range of 
			// the total starting and ending minutes
			if (total_target_minutes >= total_l_minutes && total_target_minutes <= total_r_minutes) {
				cout << 1;
			} else {
				cout << 0;
			}
		}
		cout << '\n';
	}
	return 0;
}
