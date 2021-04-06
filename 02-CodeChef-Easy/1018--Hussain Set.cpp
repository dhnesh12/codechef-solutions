#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void hussain_set(ll *arr, ll *queries, ll n, ll m)
{
	queue<ll> q;
	ll count = 1;
	ll i = n - 1;
	sort(arr, arr+n);
	ll j = 0;
	
	if (count == queries[j])
	{
		cout << arr[i] << "\n";
		j++;
	}
	
	q.push(arr[i]/2);
	i--;
	
	while (j < m && i >= 0)
	{
		count++;
		ll current_front = q.front();
		
		if (current_front > arr[i])
		{
		    if (count == queries[j])
		    {
		        cout << current_front << "\n";
		        j++;
		    }
		    q.push(current_front/2);
		    q.pop();
		}
		else
		{
			if (count == queries[j])
			{
			    cout << arr[i] << "\n";  
			    j++;
			}
			q.push(arr[i]/2);
			i--;
		}
	}
	
	while (!q.empty() && j < m)
	{
		count++;
		ll current_front = q.front();
		
		if (current_front == 0)
		{
			q.pop();
		}
		if (count == queries[j])
		{
			cout << current_front << "\n";
			j++;
		}
		q.push(q.front()/2);
		q.pop();
	}
}

int main()
{
   ll n, m;
   cin >> n >> m;
   
   ll *arr = new ll[n];
   
   for(ll i = 0; i < n; i++)
   {
       cin >> arr[i];
   }
   
   ll *q = new ll[m];
   
   for(ll i = 0; i < m; i++)
   {
       cin >> q[i];
   }
   
   hussain_set(arr, q, n, m);
   
   return 0;
}