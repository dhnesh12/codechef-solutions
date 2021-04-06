def nCr(n,r):
	v = 1
	if r > n:
		v = 0
	else:
		k = n-r
		if k < r:  # make k larger
			r,k = k,r
		# endif
		while n > k:
			v = v*n
			n -= 1
		# endwhile
		while r > 1:
			v = v/r
			r -= 1
		# endwhile
	# endif
	return v
# end fun
st = raw_input().split()
X = int(st[0])
N = int(st[1])
T = [0 for x in range(7)]
for k in range(N):
	st = raw_input().strip()
	for z in range(9):
		cnt = 0
		for p in range(4*z,4*z+4):
			if st[p] == '0':
				cnt += 1
			# endif
		# endfor p
		for p in range(52-2*z,54-2*z):
			if st[p] == '0':
				cnt += 1
			# endif
		# endfor p
		T[cnt] += 1
	# endfor z
# endfor k
r = 0
for k in range(X,7):
	n = T[k]
	if n > 0:
		c = n*nCr(k,X)
		r += c
	# endif
# endfor k
print r

