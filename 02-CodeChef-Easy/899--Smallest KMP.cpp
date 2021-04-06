#include<bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0);

	int tc; cin >> tc;
	for(int t=0; t<tc; ++t) {
		string str, pat; cin >> str >> pat;
		const int MX = 26;
		vector<int> freq(MX);

		for(char ch : str) freq[ch-'a']++;
		for(char ch : pat) freq[ch-'a']--;

		bool status = false;
		string ans;
		for(int i=0; i<MX; ++i) {
			char ch = 'a' + i;
			if(ch < pat[0] || ch > pat[0]) {
				ans.append(string(freq[i], ch));
			}
			else {
				string str1(freq[i], ch);
				string str2 = pat;
				if(str1 + str2 > str2 + str1) {
					swap(str1, str2);
				}	
				ans.append(str1 + str2);
			}
		}
		cout << ans;
		cout << '\n';
	}
	return 0;
}