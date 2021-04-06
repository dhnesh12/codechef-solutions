t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	N = int(st[0])
	K = int(st[1])
	A = int(st[2])
	st = raw_input().split()
	op = raw_input().strip()
	v = int(st[0])
	if op == 'XOR':
		for k in range(1,N):
			n = int(st[k])
			v = v^n
		# endfor k
		if K%2 == 0:
			r = A
		else:
			r = A^v
		# endif
	# endif
	if op == 'OR':
		for k in range(1,N):
			n = int(st[k])
			v = v|n
		# endfor k
		if K == 0:
			r = A
		else:
			r = A|v
		# endif
	# endif
	if op == 'AND':
		for k in range(1,N):
			n = int(st[k])
			v = v&n
		# endfor k
		if K == 0:
			r = A
		else:
			r = A&v
		# endif
	# endif
	print r
# endfor i

