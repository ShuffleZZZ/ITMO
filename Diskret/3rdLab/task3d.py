def prev(x):
	c=x
	i=0
	while(c%10==9):
		x-=7*(10**i)
		c=c//10
		i+=1
	return x
input = open('antigray.in', 'r')
output = open('antigray.out', 'w')
n=int(input.read())
c=3**(n-1)
a=[]
a.append(0)
for i in range(n-1):
	a[0]=a[0]*10+2
for i in range(1,c):
	a.append(a[i-1]-1)
	a[i]=prev(a[i])
for i in range(c):
	for k in range(3):
		s=''
		for j in range(n):
			k=str(((a[c-i-1]//(10**(n-1-j)))%10+1)%3)
			s+=k
		a[c-i-1]=int(s)
		output.write(s)
		output.write('\n')

