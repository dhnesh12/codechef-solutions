# cook your dish here
from math import gcd

test_case = int(input())
for i in range(test_case):
	size = int(input())
	elements = list(map(int, input().split()))
	empty = []
	for j in range(size - 1):
		for k in range(j + 1, size):
			lcm = (elements[j] * elements[k]) // gcd(elements[j], elements[k])
			empty.append(lcm)
	print(min(empty))