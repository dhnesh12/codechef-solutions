# cook your dish here
def intersection(lst1, lst2):
	z=len(lst1.intersection(lst2))
	return z
p=list(map(int, input().split()))
w=p[0]
h=p[1]
n=p[2]
m=p[3]
arr=set()
a=list(map(int, input().split()))
b=list(map(int, input().split()))
for i in range(0,len(a)-1):
	if (len(a)-i-1)%2==0:
		lim=int((len(a)-i-1)/2)
	else:
		lim=int((len(a)-i-1)/2)+1
	for j in  range(lim):
		u=abs(a[i]-a[i+j+1])
		v=abs(a[i]-a[len(a)-1-j])
		arr.add(u)
		arr.add(v)
init_count=0
for i in range(0,len(b)-1):
	if (len(a)-i-1)%2==0:
		lim=int((len(b)-i-1)/2)
	else:
		lim=int((len(b)-i-1)/2)+1
	for j in range(lim):
		u=abs(b[i]-b[i+j+1])
		v=abs(b[i]-b[len(b)-1-j])
		if u in arr:
			init_count+=1
			arr.discard(u)
		if v in arr:
			init_count+=1
			arr.discard(v)
extra_count=0
for i in range(0,h+1):
    if i not in b:
        grr={abs(z-i) for z in b}
        count=intersection(grr,arr)
        if count>extra_count:
            extra_count=count
            if count==len(arr):
                extra_count=count
                break
print(init_count+extra_count)