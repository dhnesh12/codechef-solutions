t = int(raw_input())
for i in range(t):
	N = int(raw_input())
	for k in range(N):
		st = raw_input()
	# endfor k
	tot = 0
	while N > 2:
		tot += N
		N = N/2
	# endwhile
	print tot
# endfor i

