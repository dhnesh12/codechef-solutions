#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    int T, l, i, j;
    char exp[1000], stack[1000];
    cin >> T;
    if (T >= 1 && T <= 100000)
    {
        while (T--)
        {
            j = 0;
            cin >> exp;
            for(i = 0; i < strlen(exp); i++) {
                if((exp[i]>=65 && exp[i]<=90) || (exp[i]>=97 && exp[i]<=122))
                    cout<<exp[i];
                else if(exp[i]!=41 && exp[i]!='\0') {
                    stack[j] = exp[i];
                    j++;
                }
                else {
                    while(j>0) {
                        j--;
                        if(stack[j]==40) {
                            if(exp[i]==0)
                                continue;
                            else
                                break;
                        }
                        cout<<stack[j];
                    }
                }
            }
            cout<<endl;
        }
    }
    return 0;
}