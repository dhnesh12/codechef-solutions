# cook your dish here
t = int(input())
for i in range(t):
	st = input().split()
	N = int(st[0])
	K = int(st[1])
	st = input().split()
	L = []
	for x in st:
		L.append(int(x))
	L.sort()
	L.reverse()
	L.append(K)
	r = 1
	p = 0
	while r > 0:
		n = L[p]
		r = K%n
		p += 1
	if n == K:
		n = -1
	print(n)