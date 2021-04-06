t = int(raw_input())
for i in xrange(t):
	st = raw_input().split()
	N = int(st[0])
	A = int(st[1])
	B = int(st[2])
	tot = 0
	while A > 0:
		tot += A%2
		A = A/2
	# endwhile
	while B > 0:
		tot += B%2
		B = B/2
	# endwhile
	if tot > N:
		r = tot-N
		tot = N-r
	# endif
	r = N-tot
	v = 2**tot -1
	v = v*2**r
	print v
# endfor i

