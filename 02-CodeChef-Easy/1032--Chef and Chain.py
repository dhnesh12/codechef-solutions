t = int(raw_input())
for i in range(t):
	st = raw_input().strip()
	op = 0
	om = 0
	ep = 0
	em = 0
	sz = len(st)
	for k in range(sz):
		if k%2 == 0:
			if st[k] == '+':
				ep += 1
			else:
				em += 1
			# endif
		else:
			if st[k] == '+':
				op += 1
			else:
				om += 1
			# endif
		# endif
	# endfor k
	r = min(ep+om,em+op)
	print r
# endfor i

