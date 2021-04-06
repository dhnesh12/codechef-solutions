#include<bits/stdc++.h>

using namespace std;

#define endl "\n"


#define mod 1000000007
#define num 1000007

#define ll long long

bool partition (vector<ll>&arr, ll n)
{
    ll sum = 0;
    ll i, j;

    for (i = 0; i < n; i++)
        sum += arr[i];

    if (sum % 2 != 0)
        return false;

    bool part[n + 1][sum / 2 + 1];

    for (i = 0; i <= sum / 2; i++)
        part[0][i] = false;

    for (i = 0; i <= n; i++)
        part[i][0] = true;


    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= sum / 2; j++)
        {
            part[i][j] = part[i - 1][j];
            if (j >= arr[i - 1])
                part[i][j] = part[i][j] ||
                             part[i - 1][j - arr[i - 1]];

        }
    }

    return part[n][sum / 2];
}



int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t;
    cin >> t;

    while (t--)
    {

        ll n;
        cin >> n;

        ll arr[n + 1];

        arr[0] = 0;

        ll i, j;

        for (i = 1; i <= n; i++)
            cin >> arr[i];

        if (n == 1 || n == 2)
        {
            cout << "YES" << endl;
            continue;
        }

        ll count_inversions[n + 1];

        memset(count_inversions, 0, sizeof(count_inversions));

        for (i = 1; i <= n; i++)
        {

            for (j = i + 1; j <= n; j++)
            {

                if (arr[i] > arr[j])
                    count_inversions[i]++;

            }

            for (j = 1; j < i; j++)
            {

                if (arr[i] < arr[j])
                    count_inversions[i]++;

            }

        }

        ll sum = 0;



        vector<ll>vect;

        for (i = 1; i <= n; i++)
        {

            if (count_inversions[i] > 0)
                vect.push_back(count_inversions[i]);

        }


        bool res = partition(vect, vect.size());

        if (res == true)
        {

            cout << "YES" << endl;

        }
        else
        {

            cout << "NO" << endl;

        }



    }

}
