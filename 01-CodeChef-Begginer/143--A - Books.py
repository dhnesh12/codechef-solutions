l = int(input())
for z in range(l):
	a = int(input())
	s = [int(x) for x in input().split()]
	for i in range(a-1):
		print(len(list(filter(lambda x: s[i] < x, s[i+1:]))), end=' ')
	print(0)