from math import log2 
def findX(n, arr): 
    X = sum([1 << i for i in range(int(log2(max(arr))) + 1) if (len([j for j in range(n) if (arr[j] & (1 << i))]) > int(n / 2))]) 
    print(sum([(X ^ arr[i])  for i in range(n)]))
for _ in range(int(input())):findX(int(input()), list(map(int, input().split())))