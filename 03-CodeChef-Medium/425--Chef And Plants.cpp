#include <iostream>
using namespace std;

int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output1.txt","w",stdout);
    int n,t,minimum,prev,curr;
    long long int cuts;
    cin >> t;
    while(t--)
    {
        cuts=0;
        cin >> n;
        cin >> minimum;
        prev=minimum;
        n--;
        while(n--)
        {
            cin >> curr;
            if(curr>prev)
            {
                cuts+=curr-prev;
            }
            else if(curr<minimum)
            {
                cuts+=minimum-curr;
                minimum=curr;
            }
            prev=curr;
        }
        cout << cuts << endl;
    }
    return 0;
}