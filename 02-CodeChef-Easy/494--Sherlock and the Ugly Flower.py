# cook your dish here
from collections import defaultdict

for _ in range(int(input())):
    s1 = input()
    s2 = input()
    ms = defaultdict(list)
    l,r = 0,len(s1)-1
    while l<=r:
        if s1[l] == s1[r]:
            ms[s1[l]] = [l,r]
        else:
            ms[s1[l]] = [l,r]
            ms[s1[r]] = [r,l]
        l+=1
        r-=1
    #print(ms)
    ugly = 1e10
    n = len(s2)-1
    for i in range(n+1):
        if s2[i] in ms:
            u = abs(ms[s2[i]][0]-i)+abs(ms[s2[i]][1]-i) + abs(ms[s2[i]][0]-(n-i))+abs(ms[s2[i]][1]-(n-i))             
            ugly = min(ugly,u)
    print(ugly)