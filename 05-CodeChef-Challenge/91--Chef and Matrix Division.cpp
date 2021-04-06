#include<bits/stdc++.h>
using namespace std;

int getFirstRealSum(long long int a[], long long int n) {
    for(int i = 0; i < n; ++i) {
        if (a[i] != -1) {
            return i;
        }
    }
    return -1;
}

void mergeEachLineSum(long long int a[], long long int n) {
    int startIndex, firstIndexToMerge, lastIndexToMerge, prevIndex;
    long long int minMergedSum = 1000000000000;
    startIndex = getFirstRealSum(a, n);
    // int prevIndexSum = a[startIndex];
    prevIndex = startIndex;
    firstIndexToMerge = prevIndex;
     for (int i = startIndex+1; i < n; ++i) {
        if (a[i] == -1) {
            continue;
        }
        if (a[i] + a[prevIndex] < minMergedSum) {
            firstIndexToMerge = prevIndex;
            lastIndexToMerge = i;
            minMergedSum =  a[lastIndexToMerge] + a[firstIndexToMerge];
        }
        prevIndex = i;
    }
    // setting new values
    a[lastIndexToMerge] += a[firstIndexToMerge];
    a[firstIndexToMerge] = -1;
}

void logToConsole(long long int a[], long long int n, long long int p) {
    int cnt = 0;
    for (int i = 0; i < n-1; ++i) {
        if (a[i] != -1) {
            ++cnt;
            // cout << i+1 << " ";
        }
    }
    if (0) {
        for (int i = 0; i < n-1; ++i) {
            if (a[i] != -1) {
                cout << i+1 << " ";
            }
        }
    }
    else {
        for (int i = 1; i <= p; ++i) {
            cout << i << " ";
        }
    }
}

int main() {
    long long int n, p;
    cin >> n >> p;
    long long int a[n][n], eachRowSum[n], eachColumnSum[n];
    for (int i = 0; i < n; ++i) {
        eachRowSum[i] = eachColumnSum[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            eachRowSum[i] += a[i][j];
            eachColumnSum[j] += a[i][j];
        }
    }
    int noOfIterations = n-p;
    while(noOfIterations--) {
        mergeEachLineSum(eachRowSum, n);
        mergeEachLineSum(eachColumnSum, n);
    }
    logToConsole(eachColumnSum, n, p-1);
    cout << endl;
    logToConsole(eachRowSum, n, p-1);
    return 0;
}
