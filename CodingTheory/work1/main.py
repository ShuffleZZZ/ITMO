import numpy as np
from collections import defaultdict
from operator import itemgetter

G = np.array([
  [1, 0, 0, 0, 1, 1, 0, 0, 1],
  [0, 1, 0, 0, 1, 0, 1, 0, 1],
  [0, 0, 1, 0, 0, 1, 1, 1, 0],
  [0, 0, 0, 1, 1, 0, 0, 1, 1]
])

H = np.array([
  [1, 1, 1, 0, 1, 0, 0, 1, 0],
  [0, 1, 0, 0, 1, 1, 0, 1, 0],
  [1, 1, 0, 0, 0, 1, 1, 0, 0],
  [1, 1, 1, 0, 0, 0, 0, 1, 1],
  [0, 1, 1, 1, 1, 1, 0, 0, 0]
])

min_d = 20

# switch rows and columns to find another min_d
for i in range(1, 32):
  min_d = min(np.sum(np.array(list(np.binary_repr(i).zfill(5))).astype(np.int8) @ H), min_d)
print(min_d)

syndrome = defaultdict(lambda: 1000)

for i in range(0, 512):
  c = np.array(list(np.binary_repr(i).zfill(9))).astype(np.int8)
  word = c @ H.T % 2
  ind = sum(val * 2 ** index for index, val in enumerate(reversed(word)))

  syndrome[ind] = c if np.sum(c) <= np.sum(syndrome[ind]) else syndrome[ind]

syndrome_list = syndrome.items()
syndrome_list = sorted(syndrome_list, key = itemgetter(0))
print(*syndrome_list, sep = '\n')
