#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
using namespace std;
#define llong int
#define MAX_SIZE 100005
llong leftNumber[MAX_SIZE], rightNumber[MAX_SIZE];
int compare(llong* left,int leftPos,llong* right,int rightPos){if (leftPos == -1 || rightPos == -1){return 0;}
    if (leftPos > rightPos){return 1;} else if (leftPos < rightPos){return -1;}
    else {int index = leftPos; while(index >= 0){if (left[index] > right[index]){return 1;}
            else if (left[index] < right[index]){return -1;}index--;}}return 0;}
int addIndex(llong* number,int highPos,int index,int degree){if(index>highPos){highPos=index;}number[index]++;
    if(number[index]==degree){number[index]=0;return addIndex(number,highPos,index+1,degree);}return highPos;}
bool subIndex (llong* number, int index, int degree){
    while(true){if (index >= MAX_SIZE - 1){return false;}number[index]--;
        if (number[index] == -1){number[index] = degree - 1;index++;continue;}break;} return true;}
bool isZero(llong* number, int highPos) {
    for(int i = 0; i <= highPos; i++){if (number[i] != 0){return false;}}return true;}
int compute(int *a, int n, int k){memset(leftNumber, 0, sizeof(leftNumber[0]) * MAX_SIZE);
    for (int i = 0; i < n; i++){addIndex(leftNumber, 0, a[i], k);}
    for (int i = 0; i < n; i++){bool sub = subIndex(leftNumber, a[i], k);
        if (!sub){return i;}sub = subIndex(leftNumber, a[i], k);
        if (!sub){if(isZero(leftNumber,a[i]-1)){return i;}else{return i+1;}}}return 1;}
int main(){ios::sync_with_stdio(false); int t, a[MAX_SIZE]; cin >> t;
    for(int i = 0; i < t; i++){int n, k; cin >> n >> k; for (int j = 0; j < n; j++){cin >> a[j];}
        int v = compute(a, n, k); cout << v << endl;}}