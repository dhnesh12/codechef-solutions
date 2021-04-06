t = int(raw_input())
MX = 10**6
for i in range(t):
	K = int(raw_input())
	st = raw_input().split()
	yes = True
	p = 0
	v = 1
	while (p < K) and yes:
		n = int(st[p])
		if n > v:
			yes = False
		else:
			v -= n
		# endif
		if v > MX:
			yes = False
		else:
			v = 2*v
		# endif
		p += 1
	# endwhile
	if yes and (v > 0):
		yes = False
	# endif
	if yes:
		print 'Yes'
	else:
		print 'No'
	# endif
# endfor i


