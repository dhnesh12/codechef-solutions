t = int(raw_input())
for i in range(t):
	N = int(raw_input())
	st = raw_input().split()
	valid = True
	for k in range(1,N+1):
		n = int(st[k-1])
		if k%n > 0:
			valid = False
		# endif
	# endfor k
	if valid:
		print 'YES'
	else:
		print 'NO'
	# endif
# endfor i

