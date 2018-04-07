input = open('bwt.in', 'r')
output = open('bwt.out', 'w')
s=input.readline()
a=[]
k=0
for i in range(len(s)):
    for j in range(len(s)):
        a[i-k]+=s[j]
    k++
print(a)