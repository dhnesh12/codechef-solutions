#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
#define fora(i,n) for(int (i) = 0; (i) < (n); (i)++);
const int modn = 1000000007;
const int maxN = 100000;
vector<int>primes;
vector<bool>nums(50001,true);


void sieve()
{
    for (int i = 2; i < 50001; i++)
    {
        if (nums[i])
        {
            int k = 1;
            primes.push_back(i);
            while (k * i < 50001)
            {
                nums[k * i] = false;
                k++;
            }
        }
    }
}

void factor(map<int,int>&mp,int num)
{
    for (int i = 0; i < primes.size(); i++)
    {
        int knt = 0;
        while (num % primes[i] == 0)
        {
            knt++;
            num /= primes[i];
        }
        if (knt > 0)
        {
            auto it = mp.find(primes[i]);
            if (it == mp.end())
            {
                mp[primes[i]] = knt;
            }
            else
            {
                if (knt > mp[primes[i]])
                    mp[primes[i]] = knt;
            }
        }
    }
}




int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int T; cin >> T;
    while (T--)
    {
        /* initialize map to store prime factors */
        map<int, int>mp;

        /* problem states that even if all participants start in the specified
           position - this counts as one whistle                               */
        long totKnt = 1;
        int N; cin >> N;
        /*  participants will be 1-based rather than 0-based  */
        vector<int>A(N+1);
        for (int i = 1; i <= N; i++)cin>>A[i];
        for (int i = 1; i <= N; i++)
        {
            /*  we will count the number of turns necessary for the ith item
                to get to its correct position - every position encountered  
                while performing this task will have the same number of turns
                necessary to reach their correct position                     */

            /* default this sequence count to 1 - same logic as described
               for totKnt above                                           */
            int knt = 1;

            /*  when the count is calculated for a given position, then that
                position rotation number is set to zero, indicating it does
                not have to be checked again.  Here, we skip sequence checks
                if this element has already been calculated                  */
            if (A[i] != 0)
            {
                /*save the position in k*/
                int k = A[i];
                /* set the position to 0, indicating it has been checked */
                A[i] = 0;
                /*  iterate until back to initial position  */
                while (k != i)
                {
                    /*  increment count for this sequence  */
                    knt++;
                    /* save position in last */
                    int last = k;
                    /* iterate to next position */
                    k = A[k];
                    /* zero out the checked position */
                    A[last] = 0;
                }
            }
            /* if knt is greater than one, then update to overall count */
            if (knt > 1)
                factor(mp, knt);
        }
        /* calculate overall count as the product of the factors */

        totKnt = 1;
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            while (it->second > 0)
            {
                totKnt = (totKnt * it->first) % modn;
                it->second--;
            }
        }
        cout << totKnt << "\n";
    }
}
