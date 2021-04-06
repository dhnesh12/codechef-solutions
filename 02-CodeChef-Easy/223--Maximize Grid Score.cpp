#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T-->0)
	{
	    int count[26];
	    for(int i = 0; i < 26; i++)
	        count[i] = 0;
	    int N;
	    cin >> N;
	    for(int i = 0; i < 2; i++)
	    {
	        char str[N+1];
	        cin >> str;
	        for(int i = 0; i < N; i++)
	        {
	            count[str[i]-97]++;
	        }
	    }
	    int odd[26][2], even[26][2], osize = 0, esize = 0;
	    for(int i = 0; i < 26; i++)
	    {
	        if(count[i] % 2 != 0)
	        {
	            odd[osize][0] = count[i];
	            odd[osize++][1] = i;
	        }
	        else if(count[i] > 0)
	        {
	            even[esize][0] = count[i];
	            even[esize++][1] = i;
	        }
	    }
	   // for(int i = 0; i < 26; i++)
	   //     cout << count[i] << " ";
	   // cout << endl;
	   // cout << "o" << osize << " e" << esize << endl;
	    char ans[2][N+2];
	    int size = 0;
	    bool halffull = false;
	    for(int i = 0; i < osize; i++)
	    {
	        char alpha = odd[i][1] + 97;
	        if(halffull)
	        {
	            ans[1][size++] = alpha;
	            int max = size + odd[i][0]/2;
	            int j = size;
	            for(; j < max; j++)
	            {
	                ans[0][j] = alpha;
	                ans[1][j] = alpha;
	            }
	            size += odd[i][0]/2;
	            halffull = false;
	        }
	        else
	        {
	            int max = size + odd[i][0]/2;
	            int j = size;
	            for(; j < max; j++)
	            {
	                ans[0][j] = alpha;
	                ans[1][j] = alpha;
	            }
	            ans[0][j] = alpha;
	            size += odd[i][0]/2;
	            halffull = true;
	        }
	    }
	    for(int i = 0; i < esize; i++)
	    {
	        char alpha = even[i][1] + 97;
	        //cout << "alpha: " << alpha << endl;
	        int max = size + even[i][0]/2;
	        int j = size;
	        for(; j < max; j++)
	        {
	            ans[0][j] = alpha;
	            ans[1][j] = alpha;
	        }
	        size += even[i][0]/2;
	    }
	    ans[0][N] = '\0';
	    ans[1][N] = '\0';
	    cout << ans[0] << endl << ans[1] << endl;
	}
	return 0;
}
