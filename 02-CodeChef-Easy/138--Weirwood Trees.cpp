#include <bits/stdc++.h>
#define big 1000000007
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long int d, b, t = 0, edges = 1, q;
  cin >> d >> q;
  b = d;
  d++;
  for (int i = 0; i < d; i++)
  {
    edges *= 2;
    edges %= big;
  }
  edges = (edges + big - 2) % big;
  while (q--)
  {
    char a, c;
    cin >> a;
    if (a == '1')
    {
      cin >> c;
      long long int val;
      switch (c)
      {
      case '1':
      case '2':
        edges = (edges * 2 + d) % big;
        b++;
        t++;
        break;
      case '3':
        edges = (edges * 2) % big;
        val = 1;
        for (int i = 0; i < t; i++)
        {
          val = (val * 2) % big;
        }
        edges = (edges + val) % big;
        d = (d * 2) % big;
        t = b;
        break;
      case '4':
        edges = (edges * 2) % big;
        val = 1;
        for (int i = 0; i < b; i++)
        {
          val = (val * 2) % big;
        }
        edges = (edges + val) % big;
        d = (d * 2) % big;
        b = t;
        break;
      }
    }
    else if (a == '2')
      cout << edges << "\n";
  }
}