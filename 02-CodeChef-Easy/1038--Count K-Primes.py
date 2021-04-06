N = 10**5 # value of N required
def primesieve(N):
	n = N+1
	sieve = [True] * (n/2)
	for i in xrange(3,int(n**0.5)+1,2):
		if sieve[i/2]:
			sieve[i*i/2::i] = [False] * ((n-i*i-1)/(2*i)+1)
		# endif
	# endfor i
	return [2] + [2*i+1 for i in xrange(1,n/2) if sieve[i]]
# end fun
primes = primesieve(N)
R = [[0 for x in range(5)] for y in range(N+1)]
for p in primes:
	v = p
	while v <= N:
		R[v][0] += 1
		v += p
	# endwhile
# endfor p
for k in range(2,N+1):
	n = R[k][0]
	if n > 1:
		R[k][0] = 0
		if n < 6:
			R[k][n-1] = 1
		# endif
	# endif
	for z in range(5):
		R[k][z] += R[k-1][z]
	# endfor z
# endfor k
t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	A = int(st[0])
	B = int(st[1])
	K = int(st[2])
	K -= 1
	A -= 1
	r = R[B][K]-R[A][K]
	print r
# endfor i

