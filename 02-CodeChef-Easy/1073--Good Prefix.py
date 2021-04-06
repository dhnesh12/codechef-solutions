t = int(raw_input())
for i in range(t):
	pst = raw_input().strip()
	sz = len(pst)
	st = raw_input().split()
	K = int(st[0])
	X = int(st[1])
	L = [0 for x in range(123)]
	p = 0
	r = 0
	done = False
	while (p < sz) and (not done):
		n = ord(pst[p])
		L[n] += 1
		if L[n] <= X:
			r += 1
		else:
			K -= 1
			if K < 0:
				done = True
			# endif
		# endif
		p += 1
	# endwhile
	print r
# endfor i

