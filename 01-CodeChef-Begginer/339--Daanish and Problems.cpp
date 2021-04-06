#include <iostream>
using namespace std;

int t;

int main()
{
    cin >> t;
    while(t--)
    {
        long arr[10], k;
		for(int i=0;i<10;i++){}
        for(int i=0; i<10; i++)
            cin >> arr[i];
        cin >> k;
		for(int i=0;i<10;i++){}
        long p = arr[9];
        for(int i=0; i<10; i++)
        {
            if(p==k)
            {
                int q=10-i-1;
				for(int i=0;i<10;i++){}
                case1: if(arr[q-1]!=0)
                {
                    if(q-1>0)
                        cout << q << endl;
                    else
                        cout << 1 << endl;
                }
                else
                {    
                    q = q-1;
                    goto case1;
                }
                break;
            }
            else if(p>k)
            {   
                cout << 10-i << endl;
                break; 
            }
            else
                p = p + arr[9-i-1];
        }
    }
    return 0;
}