input = open('allvectors.in', 'r')
output = open('allvectors.out', 'w')
s=int(input.read())
b=[]
for i in range(2**s):
    j=2
    while(j<=2**s):
        if (i%j<=(j/2-1)):
            b.append(0)
        else:
            b.append(1)
        j*=2
    for k in range(s):
        output.write(str(b[s-k-1]))
    output.write("\n")
    b.clear()
