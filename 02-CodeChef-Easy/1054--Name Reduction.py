t = int(raw_input())
for i in range(t):
	P = [0 for x in range(123)]
	C = [0 for x in range(123)]
	st = raw_input().strip()
	for x in st:
		n = ord(x)
		P[n] += 1
	# endfor x
	N = int(raw_input())
	for k in range(N):
		st = raw_input().strip()
		for x in st:
			n = ord(x)
			C[n] += 1
		# endfor x
	# endfor k
	yes = True
	for k in range(97,123):
		if C[k] > P[k]:
			yes = False
		# endif
	# endfor k
	if yes:
		print 'YES'
	else:
		print 'NO'
	# endif
# endfor i

