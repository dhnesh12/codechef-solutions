# cook your dish here
import math;
from math import log2,sqrt;
import sys;
sys.setrecursionlimit(pow(10,6))
import collections
from collections import defaultdict
from statistics import median
inf = float("inf")
for i in range(int(input())):
    n=int(input())
    l=list(map(int,input().split()))
    l.sort()
    it1=0
    it2=2*n-1
    m=[]
    while(it1<it2):
        m.append(l[it1])
        it1+=1
        m.append(l[it2])
        it2-=1

    b=[0 for i in range(n)]
    for i in range(n):

        b[i]=max(m[2*i],m[2*i+1])

    print(median(b))
    print(*m)

