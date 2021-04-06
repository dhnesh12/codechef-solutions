#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    vector<int> l, result;
    int n1, n2, n3;
    int count = 0;

    cin >> n1 >> n2 >> n3;
    int inp;

    for (int i = 0; i < n1; i++)
    {
        cin >> inp;
        l.push_back(inp);
    }

    for (int i = 0; i < n2; i++)
    {
        cin >> inp;
        l.push_back(inp);
    }

    for (int i = 0; i < n3; i++)
    {
        cin >> inp;
        l.push_back(inp);
    }

    sort(l.begin(), l.end());

    for (int i = 0; i < l.size() - 1; i++)
    {
        if (l[i] == l[i + 2])
        {
            i = i + 2;
            result.push_back(l[i]);
            count++;
        }
        else if (l[i] == l[i + 1])
        {
            i++;
            result.push_back(l[i]);
            count++;
        }
    }

    cout << count << endl;

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }

    return 0;
}