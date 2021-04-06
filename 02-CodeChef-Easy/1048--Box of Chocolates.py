# cook your dish here
for _ in range(int(input())):
    a=int(input())
    sweetness =list(map(int, input().split()))
    max_sweet=max(sweetness)
    first=sweetness.index(max_sweet)
    mid =int(len(sweetness)/2)
 
    for i in range(len(sweetness)-1, 0, -1):
        if(sweetness[i]==max_sweet):
            last = i
            break
    ans = ((len(sweetness))-last)-(mid-first)
    print(max(0,ans))