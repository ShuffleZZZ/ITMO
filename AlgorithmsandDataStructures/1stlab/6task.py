input = open('style.in', 'r')
output = open('style.out', 'w')
n1 = int(input.readline())
s = input.readline()
a = list(map(int, s.split()))
n2 = int(input.readline())
s = input.readline()
b = list(map(int, s.split()))
k=2
j=0
i=0
min=-1
while (i<=n1-1) and (j<=n2-1):
    if a[i]<=b[j]:
        if ((k==0) and ((min>abs(a[i]-b[j-1]))or(min==-1))):
            min=abs(a[i]-b[j-1])
            dif=str(a[i])+' '+str(b[j-1])
        i=i+1
        k=1
    else:
        if ((k==1) and ((min>abs(a[i-1]-b[j]))or(min==-1))):
            min=abs(a[i-1]-b[j])
            dif=str(a[i-1])+' '+str(b[j])
        j=j+1
        k=0
if i==n1:
    i=i-1
    if ((min > abs(a[i] - b[j])) or (min == -1)):
        min = abs(a[i] - b[j])
        dif = str(a[i]) + ' ' + str(b[j])
elif j==n2:
    j=j-1
    if ((min > abs(a[i] - b[j])) or (min == -1)):
        min = abs(a[i] - b[j])
        dif = str(a[i]) + ' ' + str(b[j])
output.write(dif)
input.close()
output.close()
