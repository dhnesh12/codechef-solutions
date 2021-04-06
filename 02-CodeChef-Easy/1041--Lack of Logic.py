t = int(input())
for i in range(t):
	st = input()
	L = [0 for x in range(123)]
	for x in st:
		n = ord(x)
		if n > 96:
			n -= 32
		# endif
		L[n] += 1
	# endfor x
	p = 65
	while L[p] > 0:
		p += 1
	# endwhile
	if p < 91:
		r = chr(p)
	else:
		r = '~'
	# endif
	print (r)
# endfor i
