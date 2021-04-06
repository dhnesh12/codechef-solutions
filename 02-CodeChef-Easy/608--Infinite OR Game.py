ck = lambda: map(int, input().split())
for _ in range(int(input())):
	n,k = ck()
	a = list(set(ck()))
	c = 0
	for i in range(k):
		if 1<<i not in a:
			c += 1
	print(c)