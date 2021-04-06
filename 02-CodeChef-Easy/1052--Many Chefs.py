t = int(raw_input())
for i in range(t):
	st = raw_input().strip()
	L = []
	for x in st:
		L.append(x)
	# endfor x
	sz = len(L)
	p = sz-4
	while p >= 0:
		if (L[p] in ['C','?']) and (L[p+1] in ['H','?']) and (L[p+2] in ['E','?']) and (L[p+3] in ['F','?']):
			L[p] = 'C'
			L[p+1] = 'H'
			L[p+2] = 'E'
			L[p+3] = 'F'
			p -= 4
		else:
			p -= 1
		# endif
	# endwhile
	st = ''
	for p in range(sz):
		x = L[p]
		if x == '?':
			x = 'A'
		# endif
		st += x
	# endfor p
	print st

