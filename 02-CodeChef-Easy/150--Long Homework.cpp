#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long N, Q, M;
    cin >> N >> Q >> M;

    vector < pair <int, int> > arr[M];

    for(long i=0; i < N; i++)
    {
        long val;
        cin >> val;

        arr[val % M].push_back(make_pair(val,i+1));
    }

    for(long i=0; i < M; i++)
        sort(arr[i].begin(),arr[i].end());

    while(Q--)
    {
        long i, R;
        cin >> i >> R;

        if(arr[R].size() < i)
            cout << -1 << '\n';
        else
            cout << arr[R][i-1].second << '\n';
    }

    return 0;
}