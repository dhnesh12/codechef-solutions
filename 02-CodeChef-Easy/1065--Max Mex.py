t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	N = int(st[0])
	M = int(st[1])
	st = raw_input().split()
	L = []
	for x in st:
		L.append(int(x))
	# endfor x
	L.sort()
	L.append(M+1)
	v = 1
	p = 0
	while (L[p] <= v) and (L[p] < M):
		if L[p] == v:
			v += 1
		# endif
		p += 1
	# endwhile
	r = -1
	if L[p] >= M:
		r = N
		while L[p] == M:
			r -= 1
			p += 1
		# endwhile
	# endif
	print r
# endfor i

