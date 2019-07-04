input = open('isheap.in', 'r')
output = open('isheap.out', 'w')
n = int(input.readline())
s = input.read()
a = list(map(int, s.split()))
k=0
for i in range(0,n-1):
    if (2 * i + 1 < n and a[i] > a[2 * i + 1]) or (2 * i + 2 < n and a[i] > a[2 * i + 2]):
        k = k + 1
if k == 0:
    output.write('YES')
else:
    output.write('NO')
input.close()
output.close()
