input = open('antiqs.in', 'r')
output = open('antiqs.out', 'w')
n = int(input.readline())
a=list()
for i in range(0,n):
    a.append(i+1)
for i in range(0, n):
    a[i], a[i // 2] = a[i // 2], a[i]
for i in range(0, n):
    output.write(str(a[i]))
    output.write(' ')
input.close()
output.close()