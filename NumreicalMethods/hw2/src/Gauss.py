import numpy as np
import copy


def gaussFunc(a):
    len1 = len(a[:, 0])
    len2 = len(a[0, :])

    for g in range(len1):

        max = abs(a[g][g])
        my = g
        t1 = g
        while t1 < len1:
            # for t1 in range(len(a[:,0])):
            if abs(a[t1][g]) > max:
                max = abs(a[t1][g])
                my = t1
            t1 += 1

        if my != g:
            # a[g][:], a[my][:] = a[my][:], a[g][:]
            # np.swapaxes(a, 1, 0)
            b = copy.deepcopy(a[g])
            a[g] = copy.deepcopy(a[my])
            a[my] = copy.deepcopy(b)

        amain = float(a[g][g])

        z = g
        while z < len2:
            a[g][z] = a[g][z] / amain
            z += 1

        j = g + 1

        while j < len1:
            b = a[j][g]
            z = g

            while z < len2:
                a[j][z] = a[j][z] - a[g][z] * b
                z += 1
            j += 1

    a = backTrace(a, len1, len2)
    return a


def backTrace(a, len1, len2):
    a = np.array(a)
    i = len1 - 1
    while i > 0:
        j = i - 1
        while j >= 0:
            a[j][len1] = a[j][len1] - a[j][i] * a[i][len1]
            j -= 1
        i -= 1
    return a[:, len2 - 1]
