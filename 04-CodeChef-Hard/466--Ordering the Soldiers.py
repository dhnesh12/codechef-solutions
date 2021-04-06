"""
 ___   _   _    ___  __   ___ _  _     __   ____ ___ _  _   _
|__   /_\  |\ |  |  |  | |__  |__|     |_|  |__   |  |__|  /_\
___| /   \ | \|  |  |__| ___| |  |     |__| |___  |  |  | /   \

"""
from statistics import *
from itertools import *
from functools import *
from string import *
from math import *
from sys import *
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    x = list(range(1, n+1))
    print(*[x.pop(n-i-a[n-i-1]-1)for i in range(n)][::-1])
