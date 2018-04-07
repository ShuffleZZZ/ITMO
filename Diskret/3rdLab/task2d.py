input = open('gray.in', 'r')
output = open('gray.out', 'w')
s=int(input.read())
a=[]
a.append(a.copy())
a.append(a[0].copy())
a[0].append(0)
a[1].append(1)
k=2
while k<2**s:
    m=k
    for j in range(k):
        a.append(a[k-j-1].copy())
        a[m].append(1)
        a[k-j-1].append(0)
        m+=1
    k*=2
for i in range(2**s):
    for j in range(s):
        output.write(str(a[i][s-j-1]))
    output.write("\n")