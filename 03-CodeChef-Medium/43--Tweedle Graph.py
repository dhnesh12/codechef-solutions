# cook your dish here
from math import *
from collections import *
import sys
sys.setrecursionlimit(10**9)
t = int(input())
for y in range(t):
	n = list(map(int,input().split()))
	l = n[1:]
	n = n[0]
	l.sort()
	s = sum(l)
	s = s - l[-1]
	ans  = l[-1]*s
	s = s - l[-2]
	ans += l[-2]*s
	print(ans)