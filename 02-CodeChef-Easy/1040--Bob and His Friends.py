t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	N = int(st[0])
	a = int(st[1])
	b = int(st[2])
	c = int(st[3])
	d = 10**9
	if a > b:
		a,b = b,a
	# endif
	st = raw_input().split()
	p = 0
	while (p < N) and (d > 0):
		n = int(st[p])
		nd = 0
		if n < a:
			nd = a-n
		# endif
		if n > b:
			nd = n-b
		# endif
		if nd < d:
			d = nd
		# endif
		p += 1
	# endwhile
	r = 2*d + c + b - a
	print r
# endfor i

