t = int(raw_input())
for i in range(t):
	st = raw_input()
	if len(st) == 5:
		rst = 'No'
		if (st[0] < 'a') or (st[0] > 'h'):
			rst = 'Error'
		# endif
		if (st[3] < 'a') or (st[3] > 'h'):
			rst = 'Error'
		# endif
		if (st[1] < '1') or (st[1] > '8'):
			rst = 'Error'
		# endif
		if (st[4] < '1') or (st[4] > '8'):
			rst = 'Error'
		# endif
		if st[2] <> '-':
			rst = 'Error'
		# endif
		if rst == 'No':
			n = abs(ord(st[0])-ord(st[3]))
			m = abs(ord(st[1])-ord(st[4]))
			n = n*m
			if n == 2:
				rst = 'Yes'
			# endif
		# endif
	else:
		rst = 'Error'
	# endif
	print rst
# endfor i

